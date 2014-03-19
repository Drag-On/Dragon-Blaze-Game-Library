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
#include "Rendering/Texture.h"
#include "Rendering/Camera.h"
#include "Rendering/Renderable.h"
#include "Entity/Entity.h"
#include "Math/Vector3.h"
#include "Math/Utility.h"
#include "Math/Quaternion.h"

using namespace dbgl;

Window* wnd;
Mesh* pMeshPyramid, *pMeshBox, *pMeshIco, *pMeshPlane, *pMeshSphere;
ShaderProgram* pShaderDiffSpec, *pShaderNorm, *pShaderCheap;
Texture* pTexBricks, *pTexBricksNormal, *pTexBricksSpecular, *pTexWhite;
Entity* pPyramid, *pBox, *pIco, *pPlane, *pSphere, *pLight, *pLight2;
Camera* cam;
Vec3f lightPos = Vec3f(0, 3, 3), lightColor = Vec3f(1.0f, 0.5f, 0.0f) * 15; // Orange
Vec3f light2Pos = Vec3f(1, 2, 4.5f), light2Color = Vec3f(0.5f, 0.5f, 1.0f) * 25; // Blue-ish
Vec3f lightOffset; // For movement
Vec3f matSpecular = Vec3f(0.1, 0.1, 0.2);
float mouseSpeed = 3.0f, moveSpeed = 2.5;
float icoAngle = 0;

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
    double horizontal = deltaTime * mouseSpeed
	    * (wnd->getFrameWidth() / 2.0 - x);
    double vertical = deltaTime * mouseSpeed
	    * (wnd->getFrameHeight() / 2.0 - y);
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

    // Drive rotation of icosahedron
    icoAngle += deltaTime;
    pIco->getTransform()->rotation() = QuatF(Vec3f(1, 1, 1), icoAngle);
    pIco->update(deltaTime);

    // Update moving light
    double currentTime = WindowManager::get()->getTime();
    lightOffset.x() = sin(currentTime) * 3;
    lightOffset.y() = -sin(currentTime) * 1;
    lightOffset.z() = cos(currentTime) * 3;
    pLight->getTransform()->position() = lightPos + lightOffset;
    pLight->update(deltaTime);
}

void renderCallback(Window::RenderEventArgs const& args)
{
    auto rc = args.rc;

    pShaderCheap->use();
    pShaderCheap->setUniformFloat3(pShaderCheap->getDefaultUniformHandle(ShaderProgram::COLOR), Vec3f(1, 1, 1).getDataPointer());

    // Draw sphere at light position using the "cheap" shader
    pLight->render(rc);
    pLight2->render(rc);

    // Set light position and color for shader 1
    pShaderDiffSpec->use();
    pShaderDiffSpec->setUniformInt(
	    pShaderDiffSpec->getUniformHandle("i_numLights"), 2);
    pShaderDiffSpec->setUniformFloat3(
	    pShaderDiffSpec->getUniformHandle("lights[0].v3_position_w"),
	    pLight->getTransform()->position().getDataPointer());
    pShaderDiffSpec->setUniformFloat3(
	    pShaderDiffSpec->getUniformHandle("lights[0].v3_color"),
	    lightColor.getDataPointer());
    pShaderDiffSpec->setUniformFloat3(
	    pShaderDiffSpec->getUniformHandle("lights[1].v3_position_w"),
	    pLight2->getTransform()->position().getDataPointer());
    pShaderDiffSpec->setUniformFloat3(
	    pShaderDiffSpec->getUniformHandle("lights[1].v3_color"),
	    light2Color.getDataPointer());
    pShaderDiffSpec->setUniformFloat3(
	    pShaderDiffSpec->getUniformHandle("v3_ambientLight"),
	    Vec3f(0.2, 0.2, 0.2).getDataPointer());
    pShaderDiffSpec->setUniformFloat3(
	    pShaderDiffSpec->getUniformHandle("mat.v3_specColor"),
	    matSpecular.getDataPointer());
    pShaderDiffSpec->setUniformFloat(
	    pShaderDiffSpec->getUniformHandle("mat.f_specWidth"), 10);

    // Draw ground plane using the diffuse + specular shader
    pPlane->render(rc);

    // Set light position and color for shader 2
    pShaderNorm->use();
    pShaderNorm->setUniformInt(pShaderNorm->getUniformHandle("i_numLights"), 2);
    pShaderNorm->setUniformFloat3(
	    pShaderNorm->getUniformHandle("lights[0].v3_position_w"),
	    pLight->getTransform()->position().getDataPointer());
    pShaderNorm->setUniformFloat3(
	    pShaderNorm->getUniformHandle("lights[0].v3_color"),
	    lightColor.getDataPointer());
    pShaderNorm->setUniformFloat3(
	    pShaderNorm->getUniformHandle("lights[1].v3_position_w"),
	    pLight2->getTransform()->position().getDataPointer());
    pShaderNorm->setUniformFloat3(
	    pShaderNorm->getUniformHandle("lights[1].v3_color"),
	    light2Color.getDataPointer());
    pShaderNorm->setUniformFloat3(
	    pShaderNorm->getUniformHandle("v3_ambientLight"),
	    Vec3f(0.1, 0.1, 0.1).getDataPointer());
    pShaderNorm->setUniformFloat3(
	    pShaderNorm->getUniformHandle("mat.v3_specColor"),
	    matSpecular.getDataPointer());
    pShaderNorm->setUniformFloat(
	    pShaderNorm->getUniformHandle("mat.f_specWidth"), 10);

    // Draw other objects using the normal shader
    pPyramid->render(rc);
    pBox->render(rc);
    pSphere->render(rc);
    pIco->render(rc);
}

int main()
{
    LOG->setLogLevel(DBG);
    // Create window
    wnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    wnd->init(true, true, true);
    // Create a viewport over the whole window space
    Viewport* viewport = new Viewport(0, 0, 1, 1);
    // Add a camera
    Vec3f direction = Vec3f(6, -2, 0);
    cam = new Camera(Vec3f(-1, 2, 3), direction, Vec3f(0, 0, 1).cross(direction), pi_4(),
	    0.1, 100);
    viewport->setCamera(cam);
    // Tell the render context about the new viewport
    wnd->getRenderContext()->addViewport(viewport);
    // Load meshes, shader and texture
    pMeshPyramid = Mesh::makePyramid(true);
    pMeshBox = Mesh::makeCube(true);
    pMeshPlane = Mesh::makePlane(false);
    pMeshIco = Mesh::load("../common/Icosahedron.obj", Mesh::OBJ, true);
    pMeshSphere = Mesh::load("../common/Sphere.obj", Mesh::OBJ, true);
    pShaderCheap = new ShaderProgram("../common/NoLight.vert", "../common/NoLight.frag");
    pShaderDiffSpec = new ShaderProgram("../common/DiffSpec.vert", "../common/DiffSpec.frag");
    pShaderNorm = new ShaderProgram("../common/DiffSpecNorm.vert", "../common/DiffSpecNorm.frag");
    pTexBricks = new Texture(Texture::DDS_VERTICAL_FLIP, "../common/Bricks01.DDS");
    pTexBricksNormal = new Texture(Texture::TGA, "../common/Bricks01_normal.tga");
    pTexBricksSpecular = new Texture(Texture::TGA, "../common/Bricks01_specular.tga");
    pTexWhite = new Texture(Texture::BOGUS, "");
    // Create pyramid entity
    Renderable data(pMeshPyramid, pShaderNorm, pTexBricks, pTexBricksNormal, pTexBricksSpecular, Vec3f(0, 0, 0),
	    Vec3f(1, 1, 1), QuatF(0, 0, 0, 1));
    pPyramid = new Entity(data, "pyramid");
    // Create box entity
    data.set(pMeshBox, pShaderNorm, pTexBricks, pTexBricksNormal, pTexBricksSpecular, Vec3f(5, 0, 3),
	    Vec3f(1, 1, 1), QuatF(Vec3f(0, pi_4(), 0)));
    pBox = new Entity(data, "box");
    // Create icosahedron entity
    data.set(pMeshIco, pShaderNorm, pTexBricks, pTexBricksNormal, pTexBricksSpecular, Vec3f(-3, 0, 5),
	    Vec3f(1, 1, 1), QuatF());
    pIco = new Entity(data, "icosahedron");
    // Create sphere entity
    data.set(pMeshSphere, pShaderNorm, pTexBricks, pTexBricksNormal, pTexBricksSpecular, Vec3f(2, 0, 8),
	    Vec3f(1, 1, 1), QuatF());
    pSphere = new Entity(data, "sphere");
    // Create plane entity
    data.set(pMeshPlane, pShaderDiffSpec, pTexWhite, NULL, pTexWhite, Vec3f(0, -1, 0),
	    Vec3f(10, 10, 10), QuatF(Vec3f(0, 0, 1), Vec3f(0, 1, 0)));
    pPlane = new Entity(data, "plane");
    // Create flying sphere symbolizing the light
    data.set(pMeshSphere, pShaderCheap, NULL, NULL, NULL, lightPos,
	    Vec3f(0.2f, 0.2f, 0.2f), QuatF());
    pLight = new Entity(data, "light");
    // Other light
    data.set(pMeshSphere, pShaderCheap, NULL, NULL, NULL, light2Pos,
    	    Vec3f(0.2f, 0.2f, 0.2f), QuatF());
    pLight2 = new Entity(data, "light2");
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
    delete pMeshPlane;
    delete pMeshSphere;
    delete pShaderCheap;
    delete pShaderDiffSpec;
    delete pShaderNorm;
    delete pTexBricks;
    delete pTexBricksNormal;
    delete pTexBricksSpecular;
    delete pTexWhite;
    delete pPyramid;
    delete pBox;
    delete pIco;
    delete pPlane;
    delete pSphere;
    delete pLight;
    delete pLight2;
    delete cam;
    delete viewport;
    // Free remaining internal resources
    WindowManager::get()->terminate();
    return 0;
}

