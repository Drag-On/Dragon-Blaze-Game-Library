//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Entity/Entity.h"

namespace dbgl
{
    Entity::Entity(std::string name) : m_name(name)
    {
    }

    std::string const& Entity::getName()
    {
	return m_name;
    }

    void Entity::addComponent(std::shared_ptr<Component> component)
    {
	std::type_index index(typeid(component));
	if (m_components.count(index) != 0)
	{
	    // There already is a component of the same type
	    LOG.warning("Replacing a component of entity %.", getName());
	    removeComponent(component);
	}

	m_components[std::type_index(typeid(*component))] = component;
	if(component->needUpdate())
	    m_updateComponents.push_back(component);
	if(component->needRender())
	    m_renderComponents.push_back(component);
    }

    bool Entity::removeComponent(std::shared_ptr<Component> component)
    {
	auto it = m_components.find(typeid(*component));
	if (it != m_components.end())
	{
	    m_updateComponents.erase(std::find(m_updateComponents.begin(), m_updateComponents.end(), component));
	    m_renderComponents.erase(std::find(m_renderComponents.begin(), m_renderComponents.end(), component));
	    m_components.erase(it);
	    return true;
	}
	return false;
    }

    template<class T> std::shared_ptr<T> Entity::getComponent()
    {
	std::type_index index(typeid(T));
	if (m_components.count(index) != 0)
	{
	    return std::static_pointer_cast<T>(m_components[index]);
	}
	else
	{
	    return std::shared_ptr<T> {};
	}
    }

    void Entity::update(double deltaTime)
    {
	for (auto it = m_updateComponents.begin(); it != m_updateComponents.end(); ++it)
	{
	    it->get()->update(this, deltaTime);
	}
    }

    void Entity::render(RenderContext const* rc)
    {
	for (auto it = m_renderComponents.begin(); it != m_renderComponents.end(); ++it)
	{
	    it->get()->render(this, rc);
	}
    }
}
