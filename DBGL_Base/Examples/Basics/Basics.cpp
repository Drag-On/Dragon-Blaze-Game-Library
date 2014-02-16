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
#include "Log/Log.h"
#include "Window/WindowManager.h"
#include "Window/SimpleWindow.h"
#include "Rendering/RenderContext.h"
#include "Rendering/Mesh.h"
#include "Rendering/ShaderProgram.h"
#include "Rendering/Camera.h"
#include "Math/Constants.h"

using namespace dbgl;

Mesh* pMesh;
ShaderProgram* pShader;

void renderCallback(const RenderContext* rc)
{
    pShader->use();
    rc->draw(pMesh, pShader);
}

int main()
{
    // Create window
    Window* wnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    wnd->init();
    // Create a viewport over the whole window space
    Viewport* viewport = new Viewport(0, 0, 1, 1);
    // Add a camera
    Camera* cam = new Camera(Vec3f(0, 2, 5), Vec3f(0, 0, 0), Vec3f(0, 1, 0),
	    pi_4(), 0.1, 10);
    viewport->setCamera(cam);
    // Tell the render context about the new viewport
    wnd->getRenderContext()->addViewport(viewport);
    // Load mesh and shader
    pMesh = Mesh::makePyramid();
    pShader = ShaderProgram::createSimpleShader();
    // Add render callback so we can draw the mesh
    wnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    // Show window
    wnd->show();
    // Run update loop
    while (WindowManager::get()->isRunning())
    {
	WindowManager::get()->update();
    }
    // Clean up
    delete pMesh;
    delete pShader;
    delete cam;
    delete viewport;
    // Free remaining internal resources
    WindowManager::get()->terminate();
    return 0;
}

