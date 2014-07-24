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
#include "DBGL/System/Scene/SceneApplication.h"
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

class MainHandler: public SceneApplication
{
    public:
	virtual ~MainHandler()
	{
	}

	virtual void init()
	{
	    // Create window
	    m_pWnd = WindowManager::get()->createWindow<SimpleWindow>();
	    // Initialize it
	    m_pWnd->init();
	    // Load mesh, shader, texture...
	    Mesh* pMeshBox = Mesh::makeCube(Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
	    ShaderProgram* pShader = new ShaderProgram{"../common/DiffSpecNorm.vert", "../common/DiffSpecNorm.frag"};
	    Texture* pTexDiffuse = Texture::load(Texture::DDS, "../common/Bricks01.DDS", Texture::FlipVertically);
	    Texture*pTexNormal = Texture::load(Texture::TGA, "../common/Bricks01_normal.tga");
	    Texture* pTexSpecular = Texture::load(Texture::TGA, "../common/Bricks01_specular.tga");
	    Material2DTex material {*pShader, *pTexDiffuse, pTexNormal, pTexSpecular};
	    // Create entity for the camera
	    m_pCam = new Entity{};
	    auto transformCam = std::make_shared<TransformComponent>();
	    transformCam->position() = Vec3f{0.0f, 0.0f, 4.0f};
	    transformCam->rotation().fromVectors(Vec3f{0.0f, 0.0f, 1.0f}, Vec3f{0.0f, 0.0f, -1.0f}, Vec3f{0.0f, 1.0f, 0.0f});
	    m_pCam->addComponent(transformCam);
	    auto camComp = std::make_shared<CameraComponent>();
	    m_pCam->addComponent(camComp);
	    // Add the camera to the environment
	    Environment environment {*m_pCam};
	    // Create entity for a box
	    m_pEntity = new Entity{};
	    auto transform = std::make_shared<TransformComponent>();
	    transform->position() = Vec3f{0.0f, 0.0f, 0.0f};
	    transform->rotation().fromAngleAxis({0.0f, 1.0f, 0.0f}, toRadians(30.0f));
	    m_pEntity->addComponent(transform);
	    auto render = std::make_shared<RenderComponent>(*pMeshBox, material, environment);
	    m_pEntity->addComponent(render);
	    SceneGraph<Entity>::Node boxNode{m_pEntity};
	    m_sceneGraph.setRoot(&boxNode);
	    // Create another box entity
	    Entity otherBox{};
	    auto otherTransform = std::make_shared<TransformComponent>();
	    otherTransform->position() = Vec3f{3.0f, 0.0f, 0.0f};
	    otherTransform->rotation().fromAngleAxis({0.0f, 1.0f, 0.0f}, toRadians(30.0f));
	    otherBox.addComponent(otherTransform);
	    auto otherRender = std::make_shared<RenderComponent>(*pMeshBox, material, environment);
	    otherBox.addComponent(otherRender);
	    SceneGraph<Entity>::Node otherBoxNode{&otherBox};
	    boxNode.addChild(&otherBoxNode);
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
	    m_pWnd->addUpdateCallback(std::bind(&MainHandler::updateCallback, this, std::placeholders::_1));
	    m_pWnd->addRenderCallback(std::bind(&MainHandler::renderCallback, this, std::placeholders::_1));
	    // Show window
	    m_pWnd->show();
	    // Run update loop
	    while (dbgl::isRunning())
	    {
		dbgl::update();
	    }
	    // Clean up
	    delete pMeshBox;
	    delete pShader;
	    delete pTexDiffuse;
	}

	virtual void terminate()
	{
	    delete m_pCam;
	    delete m_pEntity;
	}

	void updateCallback(Window::UpdateEventArgs const& args)
	{
	    auto deltaTime = args.deltaTime;

	    // Update mouse
	    double x = 0, y = 0;
	    m_pWnd->getCursorPos(x, y);
	    float horizontal = deltaTime * m_mouseSpeed * float(m_pWnd->getFrameWidth() / 2 - x);
	    float vertical = deltaTime * m_mouseSpeed * float(m_pWnd->getFrameHeight() / 2 - y);
	    auto transform = m_pCam->getComponent<TransformComponent>();
	    auto curRotation = transform->rotation();
	    transform->rotation() = QuatF(Vec3f(0, horizontal, 0)) * curRotation * QuatF(Vec3f(-vertical, 0, 0));
	    // Camera vectors
	    Vec3f direction = transform->rotation() * Vec3f(0, 0, 1);
	    Vec3f right = transform->rotation() * Vec3f(-1, 0, 0);
	    // Reset mouse position to center of the screen
	    m_pWnd->setCursorPos(m_pWnd->getFrameWidth() / 2, m_pWnd->getFrameHeight() / 2);

	    // Update keyboard
	    if (m_pWnd->getKey(Input::Key::KEY_W) == Input::KeyState::DOWN)
		transform->position() += direction * deltaTime * m_moveSpeed;
	    if (m_pWnd->getKey(Input::Key::KEY_A) == Input::KeyState::DOWN)
		transform->position() -= right * deltaTime * m_moveSpeed;
	    if (m_pWnd->getKey(Input::Key::KEY_S) == Input::KeyState::DOWN)
		transform->position() -= direction * deltaTime * m_moveSpeed;
	    if (m_pWnd->getKey(Input::Key::KEY_D) == Input::KeyState::DOWN)
		transform->position() += right * deltaTime * m_moveSpeed;
	    if (m_pWnd->getKey(Input::Key::KEY_E) == Input::KeyState::DOWN)
		transform->position() += Vec3f(0, 1, 0) * deltaTime * m_moveSpeed;
	    if (m_pWnd->getKey(Input::Key::KEY_Q) == Input::KeyState::DOWN)
		transform->position() -= Vec3f(0, 1, 0) * deltaTime * m_moveSpeed;

	    // Rotate box
	    m_pEntity->getComponent<TransformComponent>()->rotation() *= QuatF(Vec3f{0.0f, deltaTime, 0.0f});

	    // Call base update
	    SceneApplication::update(deltaTime);
	}

	void renderCallback(Window::RenderEventArgs const& args)
	{
	    // Call base render
	    SceneApplication::render(args.rc);
	}

    private:
	Window* m_pWnd = nullptr;
	Entity* m_pEntity = nullptr;
	Entity* m_pCam = nullptr;
	float m_mouseSpeed = 1.5;
	float m_moveSpeed = 2.5;
};


int main()
{
    LOG.setLogLevel(Log::Level::DBG);
    // Create instance of MainHandler
    auto handler = new MainHandler();
    // Init
    dbgl::initialize(handler);
    // Free remaining internal resources
    dbgl::terminate();
    return 0;
}
