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
#include "System/Log/Log.h"
#include "Window/WindowManager.h"
#include "Window/SimpleWindow.h"
#include "Rendering/RenderContext.h"
#include "Rendering/Mesh.h"
#include "Rendering/ShaderProgram.h"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Camera.h"
#include "Math/Vector3.h"
#include "Math/Utility.h"
#include "Math/Quaternion.h"

using namespace dbgl;

Window* pWnd;
Mesh* pMeshPyramid;
Mesh* pMeshBox;
Mesh* pMeshIco;
ShaderProgram* pShader;
Texture* pTexture;
Camera* pCam;
Mat4f view, projection;
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
    double x, y;
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
    if (pWnd->getKey(GLFW_KEY_W) == GLFW_PRESS)
	pCam->position() += direction * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_A) == GLFW_PRESS)
	pCam->position() -= right * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_S) == GLFW_PRESS)
	pCam->position() -= direction * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_D) == GLFW_PRESS)
	pCam->position() += right * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_E) == GLFW_PRESS)
	pCam->position() += Vec3f(0, 1, 0) * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_Q) == GLFW_PRESS)
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
    LOG->setLogLevel(DBG);
    // Create window
    pWnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    pWnd->init();
    // Add a camera
    Vec3f direction = Vec3f(6, -2, 0);
    pCam = new Camera(Vec3f(-1, 2, 3), Vec3f(6, -2, 0), Vec3f(0, 0, 1).cross(direction), pi_4(),
	    0.1, 100);
    view = Mat4f::makeView(pCam->position(),
    	    pCam->rotation() * Vec3f(0, 0, 1), pCam->rotation() * Vec3f(0, 1, 0));
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(), pCam->getNear(), pCam->getFar());
    // Load meshes, shader and texture
    pMeshPyramid = Mesh::makePyramid();
    pMeshBox = Mesh::makeCube();
    pMeshIco = Mesh::load("../common/Icosahedron.obj", Mesh::OBJ);
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
    while (WindowManager::get()->isRunning())
    {
	WindowManager::get()->update();
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
    WindowManager::get()->terminate();
    return 0;
}

