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
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Bitmask/Bitmask.h"
#include "DBGL/Window/WindowManager.h"
#include "DBGL/Window/SimpleWindow.h"
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Rendering/ShaderProgram.h"
#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/Rendering/Camera.h"
#include "DBGL/Math/Utility.h"

using namespace dbgl;

Mesh* pMesh;
ShaderProgram* pShader;
Texture* pTexture;
Camera* pCam;
Mat4f view, projection;

void framebufferResizeCallback(Window::FramebufferResizeEventArgs const& args)
{
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	    float(args.width) / args.height, pCam->getNear(), pCam->getFar());
}

void renderCallback(Window::RenderEventArgs const& args)
{
    // Instruct shader
    pShader->use();
    // Diffuse texture
    GLint diffuseId = pShader->getDefaultUniformHandle(
	    ShaderProgram::TEX_DIFFUSE);
    if (diffuseId >= 0)
    {
	// Bind diffuse texture to unit 0
	pShader->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexture->getHandle());
	pShader->setUniformSampler(diffuseId, 0);
    }
    // MVP matrix
    Mat4f mvp = projection * view; // Identity model matrix
    GLint mvpId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    if (mvpId >= 0)
    {
	pShader->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE,
		mvp.getDataPointer());
    }
    // ITMV matrix
    GLint itmvId = pShader->getDefaultUniformHandle(
	    ShaderProgram::Uniform::ITMV);
    if (itmvId >= 0)
    {
	// In this case inverse transpose of view equals view
	pShader->setUniformFloatMatrix4Array(itmvId, 1, GL_FALSE,
		view.getDataPointer());
    }

    // Draw
    args.rc->draw(*pMesh);
}

int main()
{
    LOG->setLogLevel(DBG);
    // Create window
    Window* pWnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    pWnd->init();
    // Add a camera
    Vec3f direction = Vec3f(1, -2.5, -3);
    pCam = new Camera(Vec3f(-1, 2, 3), direction, Vec3f(1, 0, 0).cross(direction), pi_4(), 0.1, 10);
    // Calculate model and view matrix
    view = Mat4f::makeView(pCam->position(),
	    pCam->rotation() * Vec3f(0, 0, 1), pCam->rotation() * Vec3f(0, 1, 0));
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	    float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(), pCam->getNear(), pCam->getFar());
    // Load mesh, shader and texture
    pMesh = Mesh::makePyramid();
    pShader = ShaderProgram::createSimpleShader();
    pTexture = Texture::load(Texture::DDS, "../common/Bricks01.DDS", Texture::FlipVertically);
    // Add render callback so we can draw the mesh
    pWnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    pWnd->addFramebufferResizeCallback(std::bind(&framebufferResizeCallback, std::placeholders::_1));
    // Show window
    pWnd->show();
    // Run update loop
    while (WindowManager::get()->isRunning())
    {
	WindowManager::get()->update();
    }
    // Clean up
    delete pMesh;
    delete pShader;
    delete pTexture;
    delete pCam;
    // delete pWnd; // No need for this as windows will delete themselves when closed
    // Free remaining internal resources
    WindowManager::get()->terminate();
    return 0;
}

