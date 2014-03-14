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
#include "Log/Log.h"
#include "Window/WindowManager.h"
#include "Window/SimpleWindow.h"
#include "Rendering/RenderContext.h"
#include "Rendering/Mesh.h"
#include "Rendering/ShaderProgram.h"
#include "Rendering/Texture.h"
#include "Rendering/Camera.h"
#include "Rendering/Renderable.h"
#include "Math/Vector3.h"
#include "Math/Utility.h"
#include "Math/Quaternion.h"

using namespace dbgl;

Window* wnd;
Mesh* pMeshPyramid;
Mesh* pMeshBox;
Mesh* pMeshIco;
ShaderProgram* pShader;
Texture* pTexture;
Renderable renderable;
Camera* cam;
float mouseSpeed = 1.5, moveSpeed = 2.5;

void scrollCallback(Window::ScrollEventArgs const& args)
{
    // Zoom
    cam->setFieldOfView(cam->getFieldOfView() + 0.1f * args.yOffset);
}

void updateCallback(Window::UpdateEventArgs const& args)
{
    auto deltaTime = args.deltaTime;

    // Update mouse
    double x, y;
    wnd->getCursorPos(x, y);
    float horizontal = deltaTime * mouseSpeed
	    * float(wnd->getFrameWidth() / 2 - x);
    float vertical = deltaTime * mouseSpeed
	    * float(wnd->getFrameHeight() / 2 - y);
    cam->rotate(horizontal, -vertical);
    // Camera vectors
    Vec3f direction = cam->rotation() * Vec3f(0, 0, 1);
    Vec3f right = cam->rotation() * Vec3f(-1, 0, 0);
    // Reset mouse position to center of the screen
    wnd->setCursorPos(wnd->getFrameWidth() / 2, wnd->getFrameHeight() / 2);

    // Update keyboard
    if (wnd->getKey(GLFW_KEY_W) == GLFW_PRESS)
	cam->position() += direction * deltaTime * moveSpeed;
    if (wnd->getKey(GLFW_KEY_A) == GLFW_PRESS)
	cam->position() -= right * deltaTime * moveSpeed;
    if (wnd->getKey(GLFW_KEY_S) == GLFW_PRESS)
	cam->position() -= direction * deltaTime * moveSpeed;
    if (wnd->getKey(GLFW_KEY_D) == GLFW_PRESS)
	cam->position() += right * deltaTime * moveSpeed;
    if (wnd->getKey(GLFW_KEY_E) == GLFW_PRESS)
	cam->position() += Vec3f(0, 1, 0) * deltaTime * moveSpeed;
    if (wnd->getKey(GLFW_KEY_Q) == GLFW_PRESS)
	cam->position() -= Vec3f(0, 1, 0) * deltaTime * moveSpeed;
}

void renderCallback(Window::RenderEventArgs const& args)
{
    auto rc = args.rc;

    // Construct Renderable
    renderable.pShader = pShader;
    renderable.pTexDiffuse = pTexture;

    pShader->use();

    // Pyramid will be drawn in the center of the world
    renderable.pMesh = pMeshPyramid;
    renderable.position = Vec3f();
    renderable.rotation = QuatF();
    rc->draw(renderable);
    // Box will be drawn at (5, 0, 3)
    renderable.pMesh = pMeshBox;
    renderable.position = Vec3f(5, 0, 3);
    renderable.rotation = QuatF(Vec3f(0, pi_4(), 0));
    rc->draw(renderable);
    // Icosahedron will be drawn at (-3, 0, 5)
    renderable.pMesh = pMeshIco;
    renderable.position = Vec3f(-3, 0, 5);
    renderable.rotation = QuatF();
    rc->draw(renderable);
}

int main()
{
    LOG->setLogLevel(DBG);
    // Create window
    wnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    wnd->init();
    // Create a viewport over the whole window space
    Viewport* viewport = new Viewport(0, 0, 1, 1);
    // Add a camera
    Vec3f direction = Vec3f(6, -2, 0);
    cam = new Camera(Vec3f(-1, 2, 3), Vec3f(6, -2, 0), Vec3f(0, 0, 1).cross(direction), pi_4(),
	    0.1, 100);
    viewport->setCamera(cam);
    // Tell the render context about the new viewport
    wnd->getRenderContext()->addViewport(viewport);
    // Load meshes, shader and texture
    pMeshPyramid = Mesh::makePyramid();
    pMeshBox = Mesh::makeCube();
    pMeshIco = Mesh::load("../common/Icosahedron.obj", Mesh::OBJ);
    pShader = ShaderProgram::createSimpleShader();
    pTexture = new Texture(Texture::DDS_VERTICAL_FLIP, "../common/Bricks01.DDS");
    // Add update- and render callback so we can draw the mesh
    wnd->addUpdateCallback(std::bind(&updateCallback, std::placeholders::_1));
    wnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    wnd->addScrollCallback(std::bind(&scrollCallback, std::placeholders::_1));
    // Show window
    wnd->show();
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
    delete cam;
    delete viewport;
    // Free remaining internal resources
    WindowManager::get()->terminate();
    return 0;
}

