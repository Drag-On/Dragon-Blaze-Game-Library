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
Mesh* pMeshPlane;
Mesh* pMeshSphere;
ShaderProgram* pShaderDiffSpec, *pShaderNorm, *pShaderCheap;
Texture* pTexture, *pNormalTex, *pTextureWhite;
Renderable renderable;
Camera* cam;
Vec3f lightPos = Vec3f(0, 3, 3), lightColor = Vec3f(1, 0.8, 0.8) * 25;
Vec3f lightOffset; // For movement
Vec3f matSpecular = Vec3f(0.01, 0.01, 0.02);
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

    // Drive rotation of icosahedron
    icoAngle += deltaTime;

    // Update moving light
    double currentTime = WindowManager::get()->getTime();
    lightOffset.x() = sin(currentTime) * 3;
    lightOffset.y() = -sin(currentTime) * 1;
    lightOffset.z() = cos(currentTime) * 3;
}

void renderCallback(Window::RenderEventArgs const& args)
{
    auto rc = args.rc;

    pShaderCheap->use();
    pShaderCheap->setUniformFloat3(pShaderCheap->getDefaultUniformHandle(ShaderProgram::COLOR), Vec3f(1, 1, 1).getDataPointer());

    // Draw sphere at light position
    renderable.pShader = pShaderCheap;
    renderable.pMesh = pMeshSphere;
    renderable.pTexDiffuse = pTextureWhite;
    renderable.position = lightPos + lightOffset;
    renderable.rotation = QuatF();
    renderable.scale = Vec3f(0.2f, 0.2f, 0.2f);
    rc->draw(renderable);

    // Set light position and color for shader 1
    pShaderDiffSpec->use();
    pShaderDiffSpec->setUniformFloat3(pShaderDiffSpec->getUniformHandle("v_lightPos_w"),
	    (lightPos + lightOffset).getDataPointer());
    pShaderDiffSpec->setUniformFloat3(pShaderDiffSpec->getUniformHandle("v_lightColor"),
	    lightColor.getDataPointer());
    pShaderDiffSpec->setUniformFloat3(pShaderDiffSpec->getUniformHandle("v_ambientLight"),
	    Vec3f(0.1, 0.1, 0.1).getDataPointer());
    pShaderDiffSpec->setUniformFloat3(pShaderDiffSpec->getUniformHandle("v_matSpecColor"),
	    matSpecular.getDataPointer());
    pShaderDiffSpec->setUniformFloat(pShaderDiffSpec->getUniformHandle("f_matSpecWidth"), 10);

    // Draw ground plane
    renderable.pShader = pShaderDiffSpec;
    renderable.pMesh = pMeshPlane;
    renderable.pTexDiffuse = pTextureWhite;
    renderable.position = Vec3f(0, -1, 0);
    renderable.rotation = QuatF(Vec3f(0, 0, 1), Vec3f(0, 1, 0));
    renderable.scale = Vec3f(10, 10, 10);
    rc->draw(renderable);

    // Set light position and color for shader 2
    pShaderNorm->use();
    pShaderNorm->setUniformFloat3(pShaderNorm->getUniformHandle("v_lightPos_w"),
	(lightPos + lightOffset).getDataPointer());
    pShaderNorm->setUniformFloat3(pShaderNorm->getUniformHandle("v_lightColor"),
	lightColor.getDataPointer());
    pShaderNorm->setUniformFloat3(pShaderNorm->getUniformHandle("v_ambientLight"),
	Vec3f(0.1, 0.1, 0.1).getDataPointer());
    pShaderNorm->setUniformFloat3(pShaderNorm->getUniformHandle("v_matSpecColor"),
	matSpecular.getDataPointer());
    pShaderNorm->setUniformFloat(pShaderNorm->getUniformHandle("f_matSpecWidth"), 10);

    // Pyramid will be drawn in the center of the world
    renderable.pShader = pShaderNorm;
    renderable.pTexDiffuse = pTexture;
    renderable.pMesh = pMeshPyramid;
    renderable.position = Vec3f();
    renderable.rotation = QuatF();
    renderable.scale = Vec3f(1, 1, 1);
    rc->draw(renderable);

    // Box will be drawn at (5, 0, 3)
    renderable.pShader = pShaderNorm;
    renderable.pTexDiffuse = pTexture;
    renderable.pTexNormal = pNormalTex;
    renderable.pMesh = pMeshBox;
    renderable.position = Vec3f(5, 0, 3);
    renderable.rotation = QuatF(Vec3f(0, pi_4(), 0));
    renderable.scale = Vec3f(1, 1, 1);
    rc->draw(renderable);

    // Sphere will be drawn at (2, 0, 8)
    renderable.pShader = pShaderNorm;
    renderable.pTexDiffuse = pTexture;
    renderable.pTexNormal = pNormalTex;
    renderable.pMesh = pMeshSphere;
    renderable.position = Vec3f(2, 0, 8);
    renderable.rotation = QuatF();
    renderable.scale = Vec3f(1, 1, 1);
    rc->draw(renderable);

    // Icosahedron will be drawn at (-3, 0, 5)
    renderable.pMesh = pMeshIco;
    renderable.position = Vec3f(-3, 0, 5);
    renderable.rotation = QuatF(Vec3f(1, 1, 1), icoAngle);
    renderable.scale = Vec3f(1, 1, 1);
    rc->draw(renderable);
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
    pTexture = new Texture(Texture::DDS_VERTICAL_FLIP, "../common/Bricks01.DDS");
    pNormalTex = new Texture(Texture::TGA, "../common/Bricks01_normal.tga");
    pTextureWhite = new Texture(Texture::BOGUS, "");
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
    delete pTexture;
    delete pNormalTex;
    delete pTextureWhite;
    delete cam;
    delete viewport;
    // Free remaining internal resources
    WindowManager::get()->terminate();
    return 0;
}

