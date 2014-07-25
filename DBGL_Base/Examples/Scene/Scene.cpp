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
#include <deque>
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

	virtual Window* createWindow()
	{
	    return WindowManager::get()->createWindow<SimpleWindow>();
	}

	virtual void loadResources()
	{
	    // Load mesh, shader, texture...
	    m_pMeshBox = Mesh::makeCube(Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
	    m_pShader = new ShaderProgram{"../common/DiffSpecNorm.vert", "../common/DiffSpecNorm.frag"};
	    m_pTexDiffuse = Texture::load(Texture::DDS, "../common/Bricks01.DDS", Texture::FlipVertically);
	    m_pTexNormal = Texture::load(Texture::TGA, "../common/Bricks01_normal.tga");
	    m_pTexSpecular = Texture::load(Texture::TGA, "../common/Bricks01_specular.tga");
	    m_pMaterial = new Material2DTex{*m_pShader, *m_pTexDiffuse, m_pTexNormal, m_pTexSpecular};
	}

	virtual void init()
	{
	    // Call base init
	    SceneApplication::init();

	    // Create entity for the camera
	    m_pCam = new Entity{};
	    m_entities.push_back(m_pCam);
	    auto transformCam = std::make_shared<TransformComponent>();
	    transformCam->position() = Vec3f{0.0f, 0.0f, 4.0f};
	    transformCam->rotation().fromVectors(Vec3f{0.0f, 0.0f, 1.0f}, Vec3f{0.0f, 0.0f, -1.0f}, Vec3f{0.0f, 1.0f, 0.0f});
	    m_pCam->addComponent(transformCam);
	    auto camComp = std::make_shared<CameraComponent>();
	    m_pCam->addComponent(camComp);
	    // Add the camera to the environment
	    m_pEnvironment = new Environment {*m_pCam};
	    // Create entity for a box
	    m_pEntity = new Entity{};
	    m_entities.push_back(m_pEntity);
	    auto transform = std::make_shared<TransformComponent>();
	    transform->position() = Vec3f{0.0f, 0.0f, 0.0f};
	    transform->rotation().fromAngleAxis({0.0f, 1.0f, 0.0f}, toRadians(30.0f));
	    m_pEntity->addComponent(transform);
	    auto render = std::make_shared<RenderComponent>(*m_pMeshBox, *m_pMaterial, *m_pEnvironment);
	    m_pEntity->addComponent(render);
	    auto boxNode = m_sceneGraph.addNode(m_pEntity);
	    // Create another box entity
	    Entity* pOtherBox = new Entity{};
	    m_entities.push_back(pOtherBox);
	    auto otherTransform = std::make_shared<TransformComponent>();
	    otherTransform->position() = Vec3f{3.0f, 0.0f, 0.0f};
	    otherTransform->rotation().fromAngleAxis({0.0f, 1.0f, 0.0f}, toRadians(30.0f));
	    pOtherBox->addComponent(otherTransform);
	    auto otherRender = std::make_shared<RenderComponent>(*m_pMeshBox, *m_pMaterial, *m_pEnvironment);
	    pOtherBox->addComponent(otherRender);
	    boxNode->addChild(pOtherBox);
	    // Create lights
	    // Ambient light
	    Entity* pLightAmb = new Entity{};
	    m_entities.push_back(pLightAmb);
	    auto lightCompAmb = std::make_shared<LightComponent>(LightComponent::LightType::AMBIENT, Vec3f{1.0f, 1.0f, 1.0f}, 0.2f);
	    pLightAmb->addComponent(lightCompAmb);
	    m_pEnvironment->addLight(pLightAmb);
	    // First point light
	    Entity* pLight = new Entity{};
	    m_entities.push_back(pLight);
	    auto transformLight = std::make_shared<TransformComponent>();
	    transformLight->position() = Vec3f{2.0f, 5.0f, 2.0f};
	    pLight->addComponent(transformLight);
	    auto lightComp = std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{1.0f, 0.8f, 0.8f}, 20.0f);
	    pLight->addComponent(lightComp);
	    m_pEnvironment->addLight(pLight);
	    // Second point light
	    Entity* light2 = new Entity{};
	    m_entities.push_back(light2);
	    auto transformLight2 = std::make_shared<TransformComponent>();
	    transformLight2->position() = Vec3f{-2.0f, 4.0f, 3.0f};
	    light2->addComponent(transformLight2);
	    auto lightComp2 = std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{0.8f, 0.8f, 1.0f}, 20.0f);
	    light2->addComponent(lightComp2);
	    m_pEnvironment->addLight(light2);
	}

	virtual void terminate()
	{
	    // Clean up
	    for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
		delete *it;
	    m_entities.clear();
	    delete m_pEnvironment;
	    delete m_pMaterial;
	    delete m_pMeshBox;
	    delete m_pShader;
	    delete m_pTexDiffuse;
	    delete m_pTexNormal;
	    delete m_pTexSpecular;
	}

	virtual void update(Window::UpdateEventArgs const& args)
	{
	    auto deltaTime = args.deltaTime;

	    // Update mouse
	    double x = 0, y = 0;
	    m_pWindow->getCursorPos(x, y);
	    float horizontal = deltaTime * m_mouseSpeed * float(m_pWindow->getFrameWidth() / 2 - x);
	    float vertical = deltaTime * m_mouseSpeed * float(m_pWindow->getFrameHeight() / 2 - y);
	    auto transform = m_pCam->getComponent<TransformComponent>();
	    auto curRotation = transform->rotation();
	    transform->rotation() = QuatF(Vec3f(0, horizontal, 0)) * curRotation * QuatF(Vec3f(-vertical, 0, 0));
	    // Camera vectors
	    Vec3f direction = transform->rotation() * Vec3f(0, 0, 1);
	    Vec3f right = transform->rotation() * Vec3f(-1, 0, 0);
	    // Reset mouse position to center of the screen
	    m_pWindow->setCursorPos(m_pWindow->getFrameWidth() / 2, m_pWindow->getFrameHeight() / 2);

	    // Update keyboard
	    if (m_pWindow->getKey(Input::Key::KEY_W) == Input::KeyState::DOWN)
		transform->position() += direction * deltaTime * m_moveSpeed;
	    if (m_pWindow->getKey(Input::Key::KEY_A) == Input::KeyState::DOWN)
		transform->position() -= right * deltaTime * m_moveSpeed;
	    if (m_pWindow->getKey(Input::Key::KEY_S) == Input::KeyState::DOWN)
		transform->position() -= direction * deltaTime * m_moveSpeed;
	    if (m_pWindow->getKey(Input::Key::KEY_D) == Input::KeyState::DOWN)
		transform->position() += right * deltaTime * m_moveSpeed;
	    if (m_pWindow->getKey(Input::Key::KEY_E) == Input::KeyState::DOWN)
		transform->position() += Vec3f(0, 1, 0) * deltaTime * m_moveSpeed;
	    if (m_pWindow->getKey(Input::Key::KEY_Q) == Input::KeyState::DOWN)
		transform->position() -= Vec3f(0, 1, 0) * deltaTime * m_moveSpeed;

	    // Rotate box
	    m_pEntity->getComponent<TransformComponent>()->rotation() *= QuatF(Vec3f{0.0f, (float)deltaTime, 0.0f});

	    // Call base update
	    SceneApplication::update(args);
	}

    private:
	std::deque<Entity*> m_entities;
	Entity* m_pEntity = nullptr;
	Entity* m_pCam = nullptr;
	Environment* m_pEnvironment = nullptr;
	float m_mouseSpeed = 1.5;
	float m_moveSpeed = 2.5;
	Mesh* m_pMeshBox = nullptr;
	ShaderProgram* m_pShader = nullptr;
	Texture* m_pTexDiffuse = nullptr;
	Texture* m_pTexNormal = nullptr;
	Texture* m_pTexSpecular = nullptr;
	Material2DTex* m_pMaterial = nullptr;
};


int main()
{
    LOG.setLogLevel(Log::Level::DBG);
    // Create instance of MainHandler
    auto handler = new MainHandler();
    // Init
    dbgl::initialize(handler);
    // Run
    handler->run();
    // Free remaining internal resources
    dbgl::terminate();
    delete handler;
    return 0;
}
