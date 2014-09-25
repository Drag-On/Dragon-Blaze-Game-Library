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
#include "DBGL/Rendering/Environment/Camera.h"
#include "DBGL/Math/Vector3.h"
#include "DBGL/Math/Utility.h"
#include "DBGL/Math/Quaternion.h"

using namespace dbgl;

Window* pWnd = nullptr;
Mesh* pMeshPyramid = nullptr;
Mesh* pMeshBox = nullptr;
Mesh* pMeshIco = nullptr;
ShaderProgram* pShader = nullptr;
Texture* pTexture = nullptr;
Camera* pCam = nullptr;
Mat4f view{}, projection{};
float mouseSpeed = 1.5, moveSpeed = 2.5;

void scrollCallback(Window::ScrollEventArgs const& args)
{
    // Zoom
    pCam->setFieldOfView(pCam->getFieldOfView() + 0.1f * args.yOffset);
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	    float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(),
	    pCam->getNear(), pCam->getFar());
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
}

void renderCallback(Window::RenderEventArgs const& args)
{
    auto rc = args.rc;

    // Instruct shader
    pShader->use();
    // Check for uniforms
    GLint mvpId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    GLint itmvId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::ITMV);
    if (mvpId <= 0 || itmvId <= 0)
	return;
    // Diffuse texture
    GLint diffuseId = pShader->getDefaultUniformHandle(
	    ShaderProgram::TEX_DIFFUSE);
    if (diffuseId >= 0)
    {
	// Bind diffuse texture to unit 0
	pShader->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexture->getHandle());
	pShader->setUniformSampler(diffuseId, 0);
    }

    // Pyramid will be drawn in the center of the world
    // The model matrix equals the identity matrix and can thus be left out
    Mat4f mvp = projection * view;
    // Send to shader
    pShader->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE,
	    mvp.getDataPointer());
    pShader->setUniformFloatMatrix4Array(itmvId, 1, GL_FALSE,
	    view.getDataPointer());
    rc->draw(*pMeshPyramid);

    // Box will be drawn at (5, 0, 3) with a slight rotation around Y axis
    Mat4f model = Mat4f::makeTranslation(5, 0, 3) * Mat4f::makeRotationY(pi_4());
    mvp = projection * view * model;
    // Send to shader
    pShader->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE,
	    mvp.getDataPointer());
    pShader->setUniformFloatMatrix4Array(itmvId, 1, GL_FALSE,
	    (view * model).getInverted().transpose().getDataPointer());
    rc->draw(*pMeshBox);

    // Icosahedron will be drawn at (-3, 0, 5)
    model = Mat4f::makeTranslation(-3, 0, 5);
    mvp = projection * view * model;
    // Send to shader
    pShader->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE,
	    mvp.getDataPointer());
    pShader->setUniformFloatMatrix4Array(itmvId, 1, GL_FALSE,
	    (view * model).getInverted().transpose().getDataPointer());
    rc->draw(*pMeshIco);
}

int main()
{
    LOG.setLogLevel(Log::Level::DBG);
    // Init
    dbgl::initialize();
    // Create window
    pWnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    pWnd->init();
    // Add a camera
    Vec3f direction = Vec3f(6, -2, 0);
    pCam = new Camera {Vec3f(-1, 2, 3), Vec3f(6, -2, 0), Vec3f(0, 0, 1).cross(direction), pi_4(),
	    0.1, 100};
    view = Mat4f::makeView(pCam->position(),
    	    pCam->rotation() * Vec3f(0, 0, 1), pCam->rotation() * Vec3f(0, 1, 0));
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(), pCam->getNear(), pCam->getFar());
    // Load meshes, shader and texture
    pMeshPyramid = Mesh::makePyramid();
    pMeshBox = Mesh::makeCube();
    pMeshIco = Mesh::load(Mesh::OBJ, "../common/Icosahedron.obj");
    pShader = ShaderProgram::createSimpleShader();
    pTexture = Texture::load(Texture::DDS, "../common/Bricks01.DDS", Texture::FlipVertically);
    // Add update- and render callback so we can draw the mesh
    pWnd->addUpdateCallback(std::bind(&updateCallback, std::placeholders::_1));
    pWnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    pWnd->addScrollCallback(std::bind(&scrollCallback, std::placeholders::_1));
    pWnd->addFramebufferResizeCallback(std::bind(&framebufferResizeCallback, std::placeholders::_1));
    // Show window
    pWnd->show();
    // Run update loop
    while (dbgl::isRunning())
    {
	dbgl::update();
    }
    // Clean up
    delete pMeshPyramid;
    delete pMeshBox;
    delete pMeshIco;
    delete pShader;
    delete pTexture;
    delete pCam;
    // delete pWnd; // No need for this as windows will delete themselves when closed
    // Free remaining internal resources
    dbgl::terminate();
    return 0;
}

