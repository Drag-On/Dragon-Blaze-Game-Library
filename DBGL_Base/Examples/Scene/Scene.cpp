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
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Rendering/ShaderProgram.h"
#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/Rendering/Material/Material2DTex.h"
#include "DBGL/Rendering/Material/MaterialColor.h"
#include "DBGL/Rendering/Environment/Camera.h"
#include "DBGL/Rendering/Environment/Environment.h"
#include "DBGL/Math/Utility.h"

using namespace dbgl;

/**
 * @brief A component that makes it's entity spin
 */
class SpinComponent : public Entity::Component
{
    public:
	SpinComponent(float speed, float* speedFactor) : m_speed(speed), m_pSpeedFactor(speedFactor)
	{
	}

	virtual void update(Entity* entity, double deltaTime)
	{
	    entity->getComponent<TransformComponent>()->rotation() *= QuatF(Vec3f{0.0f, (float)deltaTime * m_speed * *m_pSpeedFactor, 0.0f});
	}

	virtual void render(Entity* /* entity */, RenderContext const* /* rc */)
	{
	}

	virtual bool needUpdate() const
	{
	    return true;
	}

	virtual bool needRender() const
	{
	    return false;
	}

    private:
	float m_speed;
	float* m_pSpeedFactor;
};

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
	    m_pMeshSphere = Mesh::load(Mesh::Type::OBJ, "../common/Sphere.obj", Mesh::SendToGPU | Mesh::Optimize);
	    m_pShader = new ShaderProgram{"../common/DiffSpec_Sun.vert", "../common/DiffSpec_Sun.frag"};
	    m_pShaderNoLight = new ShaderProgram{"../common/NoLight.vert", "../common/NoLight.frag"};
	    m_pTexSun = Texture::load(Texture::DDS, "../common/Sun_Diffuse.DDS", Texture::FlipVertically);
	    m_pTexMercury = Texture::load(Texture::DDS, "../common/Mercury_Diffuse.DDS", Texture::FlipVertically);
	    m_pTexVenus = Texture::load(Texture::DDS, "../common/Venus_Diffuse.DDS", Texture::FlipVertically);
	    m_pTexEarth = Texture::load(Texture::DDS, "../common/Earth_Diffuse.DDS", Texture::FlipVertically);
	    m_pTexMoon = Texture::load(Texture::DDS, "../common/Moon_Diffuse.DDS", Texture::FlipVertically);
	    m_pMatSun = new Material2DTex{*m_pShader, *m_pTexSun, nullptr, nullptr};
	    m_pMatMercury = new Material2DTex{*m_pShader, *m_pTexMercury, nullptr, nullptr};
	    m_pMatVenus = new Material2DTex{*m_pShader, *m_pTexVenus, nullptr, nullptr};
	    m_pMatEarth = new Material2DTex{*m_pShader, *m_pTexEarth, nullptr, nullptr};
	    m_pMatMoon = new Material2DTex{*m_pShader, *m_pTexMoon, nullptr, nullptr};
	    m_pMatColor = new MaterialColor{*m_pShaderNoLight, Vec3f{1, 1, 1}};
	}

	virtual void init()
	{
	    // Call base init
	    SceneApplication::init();

	    // Register input callback
	    m_pWindow->addInputCallback(std::bind(&MainHandler::onInput, this, std::placeholders::_1));

	    // Create entity for the camera
	    m_pCam = createEntity();
	    addTransformComp(m_pCam, {150.0f*m_distanceFactor, 0, 0}, {1, 1, 1}, QuatF{Vec3f{0.0f, 0.0f, 1.0f}, Vec3f{-1.0f, 0.0f, 0.0f}, Vec3f{0.0f, 1.0f, 0.0f}});
	    addComponent(m_pCam, std::make_shared<CameraComponent>(pi_4(), 0.1f, 500.0f));
	    // Add the camera to the environment
	    m_environment.setCamera(m_pCam);
	    // Let there be... sun!
	    makeSun();
	    makeMercury();
	    makeVenus();
	    makeEarth();
//	    // Create entity for a box
//	    m_pEntity = createEntity();
//	    addTransformComp(m_pEntity, {0, 0, 0}, {1, 1, 1}, QuatF{{0.0f, 1.0f, 0.0f}, toRadians(30.0f)});
//	    addRenderComp(m_pEntity, *m_pMeshSphere, *m_pMatSun, m_environment);
//	    auto boxNode = m_sceneGraph.addNode(m_pEntity);
//	    // Create another box entity
//	    Entity* pOtherBox = createEntity();
//	    addTransformComp(pOtherBox, {3, 0, 0}, {1, 1, 1}, QuatF{{0.0f, 1.0f, 0.0f}, toRadians(30.0f)});
//	    addRenderComp(pOtherBox, *m_pMeshSphere, *m_pMatSun, m_environment);
//	    boxNode->addChild(pOtherBox);
	    // Create lights
	    // Ambient light
	    Entity* pLightAmb = createEntity();
	    addComponent(pLightAmb, std::make_shared<LightComponent>(LightComponent::LightType::AMBIENT, Vec3f{1.0f, 1.0f, 1.0f}, 0.2f));
	    // First point light
//	    Entity* pLight = createEntity();
//	    addTransformComp(pLight, {2, 5, 2}, {0.3f, 0.3f, 0.3f});
//	    addRenderComp(pLight, *m_pMeshSphere, *m_pMatColor, m_environment);
//	    addComponent(pLight, std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{1.0f, 0.8f, 0.8f}, 20.0f));
//	    m_sceneGraph.addNode(pLight);
//	    // Second point light
//	    Entity* pLight2 = createEntity();
//	    addTransformComp(pLight2, {-3, 4, 3}, {0.3f, 0.3f, 0.3f});
//	    addRenderComp(pLight2, *m_pMeshSphere, *m_pMatColor, m_environment);
//	    addComponent(pLight2, std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{0.8f, 0.8f, 1.0f}, 20.0f));
//	    m_sceneGraph.addNode(pLight2);
	}

	void makeSun()
	{
	    // The sun is in the center of the solar system and doesn't spin
	    // Its diameter is 1.392.684 km, thus we'll resize it to 13.9 of it's regular size
	    // Since its the system's major source of light we'll also add a strong point light
	    Entity* sun = createEntity("Sun");
	    addTransformComp(sun, {0.0f, 0.0f, 0.0f}, {13.9f, 13.9f, 13.9f});
	    addRenderComp(sun, *m_pMeshSphere, *m_pMatSun, m_environment);
	    addComponent(sun, std::make_shared<LightComponent>(LightComponent::LightType::POINT, Vec3f{1.0f, 1.0f, 1.0f}, 0.8f));
	    m_sceneGraph.addNode(sun);
	}

	void makeMercury()
	{
	    // Mercury is 57.00.000 km away from the sun, thus we position it at 57 in x direction
	    // Its diameter is 0.004.879 km, thus we'll resize it to 0.04 of its regular size
	    // Its speed is about 47,87 km/s, thus we'll set it to 47
	    Entity* center = createEntity("MercuryCenterOfRotation");
	    addTransformComp(center, {0.0f, 0.0f, 0.0f});
	    addComponent(center, std::make_shared<SpinComponent>(47.0f, &m_speedFactor));
	    Entity* mercury = createEntity("Mercury");
	    float size = 0.04f * m_sizeFactor;
	    addTransformComp(mercury, {57.0f*m_distanceFactor, 0.0f, 0.0f}, {size, size, size});
	    addRenderComp(mercury, *m_pMeshSphere, *m_pMatMercury, m_environment);
	    m_sceneGraph.addNode(center)->addChild(mercury);
	}

	void makeVenus()
	{
	    // Venus is 108.000.000 km away from the sun, thus we position it at 108 in x direction
	    // Its diameter is 0.012.103 km, thus we'll resize it to 0.12 of its regular size
	    // Its speed is about 35,02 km/s, thus we'll set it to 35
	    Entity* center = createEntity("VenusCenterOfRotation");
	    addTransformComp(center, {0.0f, 0.0f, 0.0f});
	    addComponent(center, std::make_shared<SpinComponent>(35.0f, &m_speedFactor));
	    Entity* venus = createEntity("Venus");
	    float size = 0.12f * m_sizeFactor;
	    addTransformComp(venus, {108.0f*m_distanceFactor, 0.0f, 0.0f}, {size, size, size});
	    addRenderComp(venus, *m_pMeshSphere, *m_pMatVenus, m_environment);
	    m_sceneGraph.addNode(center)->addChild(venus);
	}

	void makeEarth()
	{
	    // Earth is 149.000.000 km away from the sun, thus we position it at 149 in x direction
	    // Its diameter is 0.012.713 km, thus we'll resize it to 0.12 of its regular size
	    // Its speed is about 29,78 km/s, thus we'll set it' speed to 29
	    // It spins with 0,46527 km/s.
	    Entity* center = createEntity("EarthCenterOfRotation");
	    addTransformComp(center, {0.0f, 0.0f, 0.0f});
	    addComponent(center, std::make_shared<SpinComponent>(29.0f, &m_speedFactor));
	    Entity* earth = createEntity("Earth");
	    float size = 0.12f * m_sizeFactor;
	    addTransformComp(earth, {149.0f*m_distanceFactor, 0.0f, 0.0f}, {size, size, size});
	    addRenderComp(earth, *m_pMeshSphere, *m_pMatEarth, m_environment);
	    addComponent(earth, std::make_shared<SpinComponent>(460.0f, &m_speedFactor));
	    auto earthnode = m_sceneGraph.addNode(center)->addChild(earth);
	    // The moon is 384.400 km away from the earth, thus we position it at 0.38 in x direction relative to earth
	    // Its diameter is 0.003.476 km, thus we'll resize it to 0.03 of its regular size
	    // Its speed is about 1,023 km/s, thus we'll set it to 1
	    Entity* centermoon = createEntity("MoonCenterOfRotation");
	    addTransformComp(centermoon, {0.0f, 0.0f, 0.0f});
	    addComponent(centermoon, std::make_shared<SpinComponent>(100.0f, &m_speedFactor));
	    Entity* moon = createEntity("Moon");
	    size = 0.03f * m_sizeFactor;
	    addTransformComp(moon, {3.84f*m_distanceFactor, 0.0f, 0.0f}, {size, size, size});
	    addRenderComp(moon, *m_pMeshSphere, *m_pMatMoon, m_environment);
	    earthnode->addChild(centermoon)->addChild(moon);
	}

	virtual void terminate()
	{
	    // Clean up
	    SceneApplication::terminate();
	    delete m_pMatSun;
	    delete m_pMatMercury;
	    delete m_pMatVenus;
	    delete m_pMatEarth;
	    delete m_pMatMoon;
	    delete m_pMatColor;
	    delete m_pMeshSphere;
	    delete m_pShader;
	    delete m_pShaderNoLight;
	    delete m_pTexSun;
	    delete m_pTexMercury;
	    delete m_pTexVenus;
	    delete m_pTexEarth;
	    delete m_pTexMoon;
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
//	    m_pEntity->getComponent<TransformComponent>()->rotation() *= QuatF(Vec3f{0.0f, (float)deltaTime, 0.0f});

	    // Call base update
	    SceneApplication::update(args);
	}

	void onInput(Window::InputEventArgs args)
	{
	    if (args.input.isReleased(Input::Key::KEY_KP_ADD))
		m_speedFactor += 1.0f/1000.0f;
	    if (args.input.isReleased(Input::Key::KEY_KP_SUBTRACT))
		m_speedFactor -= 1.0f/1000.0f;
	}

    private:
//	Entity* m_pEntity = nullptr;
	Entity* m_pCam = nullptr;
	float m_mouseSpeed = 1.5;
	float m_moveSpeed = 5.0f;
	Mesh* m_pMeshSphere = nullptr;
	ShaderProgram* m_pShader = nullptr;
	ShaderProgram* m_pShaderNoLight = nullptr;
	Texture* m_pTexSun = nullptr;
	Texture* m_pTexMercury = nullptr;
	Texture* m_pTexVenus = nullptr;
	Texture* m_pTexEarth = nullptr;
	Texture* m_pTexMoon = nullptr;
	Material2DTex* m_pMatSun = nullptr;
	Material2DTex* m_pMatMercury = nullptr;
	Material2DTex* m_pMatVenus = nullptr;
	Material2DTex* m_pMatEarth = nullptr;
	Material2DTex* m_pMatMoon = nullptr;
	MaterialColor* m_pMatColor = nullptr;

	float m_sizeFactor = 4.0f; // Modifies planet size (does not affect sun)
	float m_distanceFactor = 1.0f/2.0f;
	float m_speedFactor = 1.0f/1000.0f;//1.0f/200.0f;
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
