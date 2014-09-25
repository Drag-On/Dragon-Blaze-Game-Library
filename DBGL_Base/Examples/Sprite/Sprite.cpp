//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <functional>
#include <cmath>
#include "DBGL/System/System.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Bitmask/Bitmask.h"
#include "DBGL/Window/WindowManager.h"
#include "DBGL/Window/SimpleWindow.h"
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Rendering/ShaderProgram.h"
#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/Rendering/Sprite/Sprite.h"
#include "DBGL/Rendering/Environment/Camera.h"
#include "DBGL/Math/Matrix3x3.h"
#include "DBGL/Math/Matrix4x4.h"
#include "DBGL/Math/Vector3.h"
#include "DBGL/Math/Utility.h"
#include "DBGL/Math/Quaternion.h"

using namespace dbgl;

Window* pWnd = nullptr;
ShaderProgram* p3DShader = nullptr;
ShaderProgram* pSpriteShader = nullptr;
Texture* pTexture = nullptr;
Sprite* pSprite = nullptr;
Camera* pCam = nullptr;
Mat4f view{}, projection{};
float mouseSpeed = 1.5, moveSpeed = 2.5;
float curRotation = 0.0f, rotationSpeed = 1.0f;

void inputCallback(Window::InputEventArgs const& args)
{
    // If the tab key has just been released
    if(args.input.isReleased(Input::KEY_TAB))
    {
	// Check if the currently shown rectangle contains the whole texture
	if(pSprite->getRect().right(0) == pTexture->getWidth() && pSprite->getRect().right(1) == pTexture->getHeight() &&
		pSprite->getRect().left(0) == 0 && pSprite->getRect().left(1) == 0)
	{
	    // Crop to the upper part
	    Rectangle<unsigned int> rect = pSprite->getRect();
	    rect.pos().y() = 142;
	    pSprite->setRect(rect);
	}
	else
	{
	    Rectangle<unsigned int> rect(Vector2<unsigned int>{0, 0}, Vector2<unsigned int>{pTexture->getWidth(), pTexture->getHeight()});
	    pSprite->setRect(rect);
	}
    }
}

void framebufferResizeCallback(Window::FramebufferResizeEventArgs const& args)
{
    // Update projection matrix if the windows was rescaled
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	    float(args.width) / args.height, pCam->getNear(), pCam->getFar());
}

void updateCallback(Window::UpdateEventArgs const& args)
{
    auto deltaTime = args.deltaTime;

    // Update mouse
    double x=0, y=0;
    pWnd->getCursorPos(x, y);
    float horizontal = deltaTime * mouseSpeed
	    * float(pWnd->getFrameWidth() / 2 - x);
    float vertical = deltaTime * mouseSpeed
	    * float(pWnd->getFrameHeight() / 2 - y);
    pCam->rotate(horizontal, -vertical);
    // Camera vectors
    Vec3f direction = pCam->rotation() * Vec3f(0, 0, 1);
    Vec3f right = pCam->rotation() * Vec3f(-1, 0, 0);
    // Reset mouse position to center of the screen
    pWnd->setCursorPos(pWnd->getFrameWidth() / 2, pWnd->getFrameHeight() / 2);

    // Update view matrix
    view = Mat4f::makeView(pCam->position(), pCam->rotation() * Vec3f(0, 0, 1),
	    pCam->rotation() * Vec3f(0, 1, 0));

    // Update keyboard
    if (pWnd->getKey(Input::Key::KEY_W) == Input::KeyState::DOWN)
	pCam->position() += direction * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_A) == Input::KeyState::DOWN)
	pCam->position() -= right * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_S) == Input::KeyState::DOWN)
	pCam->position() -= direction * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_D) == Input::KeyState::DOWN)
	pCam->position() += right * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_E) == Input::KeyState::DOWN)
	pCam->position() += Vec3f(0, 1, 0) * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_Q) == Input::KeyState::DOWN)
	pCam->position() -= Vec3f(0, 1, 0) * deltaTime * moveSpeed;

    // Rotate sprite
    curRotation += rotationSpeed * deltaTime;
    while(curRotation >= 2 * pi())
	curRotation -= 2 * pi();
}

void renderCallback(Window::RenderEventArgs const& args)
{
    auto rc = args.rc;

    /*
     * Draw a 3D billboard
     */
    // Enable depth testing for 3D
    rc->setDepthTest(RenderContext::DepthTestValue::Less);
    // Instruct shader
    p3DShader->use();
    // Check for uniforms
    GLint mvpId = p3DShader->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    GLint itmvId = p3DShader->getDefaultUniformHandle(ShaderProgram::Uniform::ITMV);
    if (mvpId <= 0 || itmvId <= 0)
	return;
    // Diffuse texture
    GLint diffuseId = p3DShader->getDefaultUniformHandle(ShaderProgram::TEX_DIFFUSE);
    if (diffuseId >= 0)
    {
	// Bind diffuse texture to unit 0
	p3DShader->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexture->getHandle());
	p3DShader->setUniformSampler(diffuseId, 0);
    }

    // Sprite will be drawn in the center of the world
    // The model matrix equals the identity matrix and can thus be left out
    Mat4f mvp = projection * view * Mat4f::makeScale(1.0f/512.0f);
    // Send to shader
    p3DShader->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    p3DShader->setUniformFloatMatrix4Array(itmvId, 1, GL_FALSE, view.getDataPointer());
    rc->draw(*(pSprite->getMesh()));

    // Clear depth buffer so the 2D sprites don't interfere with the 3D models
    rc->clear(RenderContext::Buffer::DEPTH);

    /*
     * Draw sprite flat to screen and rotate it
     */
    // Disable depth testing for 2D
    rc->setDepthTest(RenderContext::DepthTestValue::Always);
    // Instruct shader
    pSpriteShader->use();
    // Check for uniforms
    GLint transformId = pSpriteShader->getDefaultUniformHandle(ShaderProgram::Uniform::TRANSFORM_2D);
    GLint screenResId = pSpriteShader->getDefaultUniformHandle(ShaderProgram::Uniform::SCREEN_RES);
    if (screenResId <= 0 || transformId <= 0)
	return;
    // Diffuse texture
    diffuseId = pSpriteShader->getDefaultUniformHandle(ShaderProgram::TEX_DIFFUSE);
    if (diffuseId >= 0)
    {
	// Bind diffuse texture to unit 0
	pSpriteShader->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexture->getHandle());
	pSpriteShader->setUniformSampler(diffuseId, 0);
    }

    // Sprite will be drawn in the top left corner
    // Send to shader
    Mat3f transform = Mat3f::make2DTranslation(0, pWnd->getFrameHeight() - pSprite->getHeight())
	    * Mat3f::make2DTranslation(pSprite->getWidth() / 2.0f, pSprite->getHeight() / 2.0f)
	    * Mat3f::make2DRotation(curRotation)
	    * Mat3f::make2DTranslation(pSprite->getWidth() / -2.0f, pSprite->getHeight() / -2.0f);
    pSpriteShader->setUniformFloat2(screenResId, Vec2f { static_cast<float>(pWnd->getFrameWidth()),
	static_cast<float>(pWnd->getFrameHeight()) }.getDataPointer());
    pSpriteShader->setUniformFloatMatrix3Array(transformId, 1, GL_FALSE, transform.getDataPointer());
    rc->draw(*(pSprite->getMesh()));

    /*
     * Draw a small version to the top right of the screen
     */
    float scale = 0.25f;
    transform = Mat3f::make2DTranslation(pWnd->getFrameWidth() - pSprite->getWidth() * scale,
	    pWnd->getFrameHeight() - pSprite->getHeight() * scale) * Mat3f::make2DScale(0.25f);
    pSpriteShader->setUniformFloatMatrix3Array(transformId, 1, GL_FALSE, transform.getDataPointer());
    rc->draw(*(pSprite->getMesh()));
}

int main()
{
    LOG.setLogLevel(Log::Level::DBG);
    // Init
    dbgl::initialize();
    // Create window
    pWnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    pWnd->init(Window::DepthTest | Window::FaceCulling | Window::AlphaBlend);
    // Add a camera
    pCam = new Camera {Vec3f(0, 0, 3), Vec3f(0, 0, -1), Vec3f(0, 1, 0), pi_4(), 0.1, 100};
    view = Mat4f::makeView(pCam->position(),
    	    pCam->rotation() * Vec3f(0, 0, 1), pCam->rotation() * Vec3f(0, 1, 0));
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(), pCam->getNear(), pCam->getFar());
    // Load shader and texture
    p3DShader = ShaderProgram::createSimpleShader();
    pSpriteShader = ShaderProgram::createSpriteShader();
    pTexture = Texture::load(Texture::TGA, "../common/DBGL_Logo_512.tga");
    pSprite = new Sprite{pTexture};
    // Add update- and render callback so we can draw the mesh
    pWnd->addUpdateCallback(std::bind(&updateCallback, std::placeholders::_1));
    pWnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    pWnd->addFramebufferResizeCallback(std::bind(&framebufferResizeCallback, std::placeholders::_1));
    pWnd->addInputCallback(std::bind(&inputCallback, std::placeholders::_1));
    // Show window
    pWnd->show();
    // Run update loop
    while (dbgl::isRunning())
    {
	dbgl::update();
    }
    // Clean up
    delete p3DShader;
    delete pSpriteShader;
    delete pTexture;
    delete pSprite;
    delete pCam;
    // Free remaining internal resources
    dbgl::terminate();
    return 0;
}

