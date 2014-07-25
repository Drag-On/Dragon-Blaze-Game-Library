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
	    m_pCam = createEntity();
	    addTransformComp(m_pCam, {0, 0, 4}, {1, 1, 1}, QuatF{Vec3f{0.0f, 0.0f, 1.0f}, Vec3f{0.0f, 0.0f, -1.0f}, Vec3f{0.0f, 1.0f, 0.0f}});
	    addComponent(m_pCam, std::make_shared<CameraComponent>());
	    // Add the camera to the environment
	    m_environment.setCamera(m_pCam);
	    // Create entity for a box
	    m_pEntity = createEntity();
	    addTransformComp(m_pEntity, {0, 0, 0}, {1, 1, 1}, QuatF{{0.0f, 1.0f, 0.0f}, toRadians(30.0f)});
	    addRenderComp(m_pEntity, *m_pMeshBox, *m_pMaterial, m_environment);
	    auto boxNode = m_sceneGraph.addNode(m_pEntity);
	    // Create another box entity
	    Entity* pOtherBox = createEntity();
	    addTransformComp(pOtherBox, {3, 0, 0}, {1, 1, 1}, QuatF{{0.0f, 1.0f, 0.0f}, toRadians(30.0f)});
	    addRenderComp(pOtherBox, *m_pMeshBox, *m_pMaterial, m_environment);
	    boxNode->addChild(pOtherBox);
	    // Create lights
	    // Ambient light
	    Entity* pLightAmb = createEntity();
	    addComponent(pLightAmb, std::make_shared<LightComponent>(LightComponent::LightType::AMBIENT, Vec3f{1.0f, 1.0f, 1.0f}, 0.2f));
	    // First point light
	    Entity* pLight = createEntity();
	    addTransformComp(pLight, {2, 5, 2});
	    addComponent(pLight, std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{1.0f, 0.8f, 0.8f}, 20.0f));
	    // Second point light
	    Entity* pLight2 = createEntity();
	    addTransformComp(pLight2, {-2, 4, 3});
	    addComponent(pLight2, std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{0.8f, 0.8f, 1.0f}, 20.0f));
	}

	virtual void terminate()
	{
	    // Clean up
	    SceneApplication::terminate();
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
	Entity* m_pEntity = nullptr;
	Entity* m_pCam = nullptr;
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
