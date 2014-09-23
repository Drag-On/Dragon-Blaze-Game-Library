//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Scene/BaseScene.h"

namespace dbgl
{
    BaseScene::BaseScene()
    {
    }

    BaseScene::~BaseScene()
    {
	// Clean up
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	    delete *it;
	m_entities.clear();
    }

    void BaseScene::update(Window::UpdateEventArgs const& args)
    {
	// Pre-order traversal of the scene graph
	std::stack<SceneGraph<Entity>::Node*> stack {};
	auto rootNodes = m_sceneGraph.getNodes();
	SceneGraph<Entity>::Node* top = nullptr;
	for (auto node : rootNodes)
	{
	    stack.push(nullptr);
	    top = node;
	    while (top)
	    {
		top->getEntity()->update(args.deltaTime);
		auto children = top->getChildren();
		for (auto it = children.rend(); it != children.rbegin(); --it)
		{
		    SceneGraph<Entity>::Node* entity = *it;
		    stack.push(entity);
		}
		top = stack.top();
		stack.pop();
	    }
	}
    }

    void BaseScene::render(Window::RenderEventArgs const& args)
    {
	// Pre-order traversal of the scene graph
	std::stack<SceneGraph<Entity>::Node*> stack {};
	auto rootNodes = m_sceneGraph.getNodes();
	SceneGraph<Entity>::Node* top = nullptr;
	for (auto node : rootNodes)
	{
	    stack.push(nullptr);
	    top = node;
	    while (top)
	    {
		top->getEntity()->render(args.rc);
		auto children = top->getChildren();
		for (auto it = children.rend(); it != children.rbegin(); --it)
		{
		    SceneGraph<Entity>::Node* entity = *it;
		    stack.push(entity);
		}
		top = stack.top();
		stack.pop();
	    }
	}
    }

    Entity* BaseScene::createEntity(std::string name)
    {
	auto entity = new Entity {name};
	m_entities.push_back(entity);
	return entity;
    }

    void BaseScene::deleteEntity(Entity* entity)
    {
	m_entities.erase(std::find(m_entities.begin(), m_entities.end(), entity));
    }

    void BaseScene::addTransformComp(Entity* entity, Vec3f pos, Vec3f scale, QuatF rot)
    {
	auto transform = std::make_shared<TransformComponent>(pos, scale, rot);
	entity->addComponent(transform);
    }

    void BaseScene::addRenderComp(Entity* entity, Mesh& mesh, Material& mat, Environment& env)
    {
	auto render = std::make_shared<RenderComponent>(mesh, mat, env);
	entity->addComponent(render);
    }

    void BaseScene::addComponent(Entity* entity, std::shared_ptr<Entity::Component> comp)
    {
	entity->addComponent(comp);

	// Check if a light component is being added
	if(typeid(*comp.get()) == typeid(LightComponent))
	    m_environment.addLight(entity);
    }
}


