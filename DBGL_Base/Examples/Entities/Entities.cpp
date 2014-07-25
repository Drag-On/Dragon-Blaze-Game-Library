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
#include "DBGL/System/Entity/LightComponent.h"
#include "DBGL/System/Entity/CameraComponent.h"
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
Entity* pEntity = nullptr;
Entity* pCam = nullptr;
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
    auto transform = pCam->getComponent<TransformComponent>();
    auto curRotation = transform->rotation();
    transform->rotation() = QuatF(Vec3f(0, horizontal, 0)) * curRotation * QuatF(Vec3f(-vertical, 0, 0));
    // Camera vectors
    Vec3f direction = transform->rotation() * Vec3f(0, 0, 1);
    Vec3f right = transform->rotation() * Vec3f(-1, 0, 0);
    // Reset mouse position to center of the screen
    pWnd->setCursorPos(pWnd->getFrameWidth() / 2, pWnd->getFrameHeight() / 2);

    // Update keyboard
    if (pWnd->getKey(Input::Key::KEY_W) == Input::KeyState::DOWN)
	transform->position() += direction * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_A) == Input::KeyState::DOWN)
	transform->position() -= right * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_S) == Input::KeyState::DOWN)
	transform->position() -= direction * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_D) == Input::KeyState::DOWN)
	transform->position() += right * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_E) == Input::KeyState::DOWN)
	transform->position() += Vec3f(0, 1, 0) * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_Q) == Input::KeyState::DOWN)
	transform->position() -= Vec3f(0, 1, 0) * deltaTime * moveSpeed;

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
    // Load mesh, shader, texture...
    Mesh* pMeshBox = Mesh::makeCube(Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
    ShaderProgram* pShader = new ShaderProgram{"../common/DiffSpecNorm.vert", "../common/DiffSpecNorm.frag"};
    Texture* pTexDiffuse = Texture::load(Texture::DDS, "../common/Bricks01.DDS", Texture::FlipVertically);
    Texture*pTexNormal = Texture::load(Texture::TGA, "../common/Bricks01_normal.tga");
    Texture* pTexSpecular = Texture::load(Texture::TGA, "../common/Bricks01_specular.tga");
    Material2DTex material {*pShader, *pTexDiffuse, pTexNormal, pTexSpecular};
    // Create entity for the camera
    pCam = new Entity{};
    auto transformCam = std::make_shared<TransformComponent>();
    transformCam->position() = Vec3f{0.0f, 0.0f, 4.0f};
    transformCam->rotation().fromVectors(Vec3f{0.0f, 0.0f, 1.0f}, Vec3f{0.0f, 0.0f, -1.0f}, Vec3f{0.0f, 1.0f, 0.0f});
    pCam->addComponent(transformCam);
    auto camComp = std::make_shared<CameraComponent>();
    pCam->addComponent(camComp);
    // Add the camera to the environment
    Environment environment {pCam};
    // Create entity for a box
    pEntity = new Entity{};
    auto transform = std::make_shared<TransformComponent>();
    transform->position() = Vec3f{0.0f, 0.0f, 0.0f};
    transform->rotation().fromAngleAxis({0.0f, 1.0f, 0.0f}, toRadians(30.0f));
    pEntity->addComponent(transform);
    auto render = std::make_shared<RenderComponent>(*pMeshBox, material, environment);
    pEntity->addComponent(render);
    // Create lights
    // Ambient light
    Entity lightAmb{};
    auto lightCompAmb = std::make_shared<LightComponent>(LightComponent::LightType::AMBIENT, Vec3f{1.0f, 1.0f, 1.0f}, 0.2f);
    lightAmb.addComponent(lightCompAmb);
    environment.addLight(&lightAmb);
    // First point light
    Entity light{};
    auto transformLight = std::make_shared<TransformComponent>();
    transformLight->position() = Vec3f{2.0f, 5.0f, 2.0f};
    light.addComponent(transformLight);
    auto lightComp = std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{1.0f, 0.8f, 0.8f}, 20.0f);
    light.addComponent(lightComp);
    environment.addLight(&light);
    // Second point light
    Entity light2{};
    auto transformLight2 = std::make_shared<TransformComponent>();
    transformLight2->position() = Vec3f{-2.0f, 4.0f, 3.0f};
    light2.addComponent(transformLight2);
    auto lightComp2 = std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{0.8f, 0.8f, 1.0f}, 20.0f);
    light2.addComponent(lightComp2);
    environment.addLight(&light2);
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
    delete pTexDiffuse;
    delete pCam;
    delete pEntity;
    // delete pWnd; // No need for this as windows will delete themselves when closed
    // Free remaining internal resources
    dbgl::terminate();
    return 0;
}
