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
#include "DBGL/System/System.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Entity/Entity.h"
#include "DBGL/System/Entity/TransformComponent.h"
#include "DBGL/System/Entity/RenderComponent.h"
#include "DBGL/Window/WindowManager.h"
#include "DBGL/Window/SimpleWindow.h"
#include "DBGL/Window/Input.h"
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Rendering/ShaderProgram.h"
#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/Rendering/Material/Material2DTex.h"
#include "DBGL/Rendering/Environment/Camera.h"
#include "DBGL/Rendering/Environment/Environment.h"
#include "DBGL/Math/Utility.h"

using namespace dbgl;

Window* pWnd = nullptr;
Camera* pCam = nullptr;
Entity* pEntity = nullptr;
float mouseSpeed = 1.5, moveSpeed = 2.5;

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

    // Update entity
    pEntity->update(deltaTime);
}

void renderCallback(Window::RenderEventArgs const& args)
{
    auto rc = args.rc;

    // Render entity
    pEntity->render(rc);
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
    Vec3f direction = Vec3f(-0.0f, 0.0f, -1.0f);
    Vec3f up = Vec3f(0.0f, 1.0f, 0.0f);
    pCam = new Camera { Vec3f(0.0f, 0.0f, 4.0f), direction, up, pi_4(), 0.1f, 100.0f };
    // Load mesh, shader, texture...
    Mesh* pMeshBox = Mesh::makeCube();
    ShaderProgram* pShader = ShaderProgram::createSimpleShader();
    Texture* pTexture = Texture::load(Texture::DDS, "../common/Bricks01.DDS", Texture::FlipVertically);
    Material2DTex material {*pShader, *pTexture, nullptr, nullptr};
    Environment environment {*pCam};
    // Create entity
    pEntity = new Entity{};
    auto transform = std::make_shared<TransformComponent>();
    transform->position() = Vec3f{0.0f, 0.0f, 0.0f};
    transform->rotation().fromAngleAxis({0.0f, 1.0f, 0.0f}, toRadians(30.0f));
    pEntity->addComponent(transform);
    auto render = std::make_shared<RenderComponent>(*pMeshBox, material, environment);
    pEntity->addComponent(render);
    // Add update- and render callback so we can draw the mesh
    pWnd->addUpdateCallback(std::bind(&updateCallback, std::placeholders::_1));
    pWnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    // Show window
    pWnd->show();
    // Run update loop
    while (dbgl::isRunning())
    {
	dbgl::update();
    }
    // Clean up
    delete pMeshBox;
    delete pShader;
    delete pTexture;
    delete pCam;
    delete pEntity;
    // delete pWnd; // No need for this as windows will delete themselves when closed
    // Free remaining internal resources
    dbgl::terminate();
    return 0;
}
