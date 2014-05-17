//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Entity/Entity.h"

namespace dbgl
{
    Entity::Entity()
    {
    }

    Entity::Entity(std::string name) : m_Name(name)
    {
    }

    Entity::Entity(Renderable const& renderable, std::string name) : m_Name(name)
    {
	auto transform = addComponent<TransformEntityComponent>();
	transform->init(renderable.position, renderable.scale, renderable.rotation);
	auto render = addComponent<RenderEntityComponent>();
	render->init(renderable);
    }

    Entity::~Entity()
    {
	// Deallocate all components
	for(auto it = m_Components.begin(); it != m_Components.end(); ++it)
	    delete it->second;
    }

    std::string const& Entity::getName()
    {
	return m_Name;
    }

    template<class Component> Component* Entity::addComponent()
    {
	// Check if component of that type already exists
	if(m_Components.find(typeid(Component)) != m_Components.end())
	{
	    LOG->warning("Tried to add a component to entity % which was already there.", m_Name);
	    return dynamic_cast<Component*>(m_Components[typeid(Component)]);
	}

	// Create component and add into map
	m_Components[typeid(Component)] = new Component();

	return dynamic_cast<Component*>(m_Components[typeid(Component)]);
    }

    template<class Component> bool Entity::removeComponent()
    {
	auto it = m_Components.find(typeid(Component));
	if(it != m_Components.end())
	{
	    m_Components.erase(it);
	    return true;
	}
	return false;
    }

    template<class Component> Component* Entity::getComponent()
    {
	return m_Components.find(typeid(Component));
    }

    TransformEntityComponent* Entity::getTransform()
    {
	auto result = m_Components.find(typeid(TransformEntityComponent));
	return dynamic_cast<TransformEntityComponent*>(result->second);
    }

    RenderEntityComponent* Entity::getRender()
    {
	auto result = m_Components.find(typeid(RenderEntityComponent));
	return dynamic_cast<RenderEntityComponent*>(result->second);
    }

    void Entity::update(double deltaTime)
    {
	for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
	{
	    it->second->update(m_Components, deltaTime);
	}
    }

    void Entity::render(SceneRenderContext const* rc)
    {
	if(getRender())
	    getRender()->render(rc);
    }
}

