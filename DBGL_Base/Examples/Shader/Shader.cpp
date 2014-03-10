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
ShaderProgram* pShader, *pShader2;
Texture* pTexture, *pNormalTex, *pTexture2;
Renderable renderable;
Camera* cam;
Vec3f lightPos = Vec3f(0, 5, 3), lightColor = Vec3f(1, 0.8, 0.8) * 50;
Vec3f lightOffset; // For movement
Vec3f matSpecular = Vec3f(0.01, 0.01, 0.02);
float mouseSpeed = 3.0f, moveSpeed = 2.5;
float icoAngle = 0;

void scrollCallback(double x, double y)
{
    // Zoom
    cam->setFieldOfView(cam->getFieldOfView() + 0.1f * y);
}

void updateCallback(double deltaTime)
{
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
    lightOffset[0] = sin(currentTime) * 3;
    lightOffset[1] = cos(currentTime) * 3;
    lightOffset[2] = -sin(currentTime) * 3;
}

void renderCallback(const RenderContext* rc)
{
    // Construct Renderable
    renderable.pShader = pShader;
    renderable.pTexDiffuse = pTexture2;

    // Set light position and color for shader 1
    pShader->use();
    pShader->setUniformFloat3(pShader->getUniformHandle("v_lightPos_w"),
	    (lightPos + lightOffset).getDataPointer());
    pShader->setUniformFloat3(pShader->getUniformHandle("v_lightColor"),
	    lightColor.getDataPointer());
    pShader->setUniformFloat3(pShader->getUniformHandle("v_ambientLight"),
	    Vec3f(0.1, 0.1, 0.1).getDataPointer());
    pShader->setUniformFloat3(pShader->getUniformHandle("v_matSpecColor"),
	    matSpecular.getDataPointer());
    pShader->setUniformFloat(pShader->getUniformHandle("f_matSpecWidth"), 10);

    // Pyramid will be drawn in the center of the world
    renderable.pMesh = pMeshPyramid;
    renderable.position = Vec3f();
    renderable.rotation = QuatF();
    rc->draw(renderable);

    // Set light position and color for shader 2
    pShader2->use();
    pShader2->setUniformFloat3(pShader2->getUniformHandle("v_lightPos_w"),
	(lightPos + lightOffset).getDataPointer());
    pShader2->setUniformFloat3(pShader2->getUniformHandle("v_lightColor"),
	lightColor.getDataPointer());
    pShader2->setUniformFloat3(pShader2->getUniformHandle("v_ambientLight"),
	Vec3f(0.1, 0.1, 0.1).getDataPointer());
    pShader2->setUniformFloat3(pShader2->getUniformHandle("v_matSpecColor"),
	matSpecular.getDataPointer());
    pShader2->setUniformFloat(pShader2->getUniformHandle("f_matSpecWidth"), 10);

    // Box will be drawn at (5, 0, 3)
    renderable.pShader = pShader2;
    renderable.pTexDiffuse = pTexture;
    renderable.pTexNormal = pNormalTex;
    renderable.pMesh = pMeshBox;
    renderable.position = Vec3f(5, 0, 3);
    renderable.rotation = QuatF(Vec3f(0, pi_4(), 0));
    rc->draw(renderable);
    // Icosahedron will be drawn at (-3, 0, 5)
    renderable.pMesh = pMeshIco;
    renderable.position = Vec3f(-3, 0, 5);
    renderable.rotation = QuatF(Vec3f(1, 1, 1), icoAngle);
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
    cam = new Camera(Vec3f(-1, 2, 3), direction, Vec3f(0, 0, 1).cross(direction), pi_4(),
	    0.1, 100);
    viewport->setCamera(cam);
    // Tell the render context about the new viewport
    wnd->getRenderContext()->addViewport(viewport);
    // Load meshes, shader and texture
    pMeshPyramid = Mesh::makePyramid();
    pMeshBox = Mesh::makeCube(true);
    pMeshIco = Mesh::load("../common/Icosahedron.obj", Mesh::OBJ, true);
    pShader = new ShaderProgram("../common/DiffSpec.vert", "../common/DiffSpec.frag");
    pShader2 = new ShaderProgram("../common/DiffSpecNorm.vert", "../common/DiffSpecNorm.frag");
    pTexture = new Texture(Texture::DDS_VERTICAL_FLIP, "../common/Bricks02.DDS");
    pNormalTex = new Texture(Texture::TGA, "../common/Bricks02_normal.tga");
    pTexture2  = new Texture(Texture::DDS_VERTICAL_FLIP, "../common/Bricks01.DDS");
    // Add update- and render callback so we can draw the mesh
    wnd->addUpdateCallback(std::bind(&updateCallback, std::placeholders::_1));
    wnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    wnd->addScrollCallback(
	    std::bind(&scrollCallback, std::placeholders::_1,
		    std::placeholders::_2));
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
    delete pShader2;
    delete pTexture;
    delete pTexture2;
    delete pNormalTex;
    delete cam;
    delete viewport;
    // Free remaining internal resources
    WindowManager::get()->terminate();
    return 0;
}

