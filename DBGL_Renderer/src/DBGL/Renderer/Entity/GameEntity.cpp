//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/Entity/GameEntity.h"
#include <algorithm>
#include <typeinfo>

namespace dbgl
{
	void GameEntity::update()
	{
		for (auto c : m_components)
			c->update();
	}

	template<typename Component, typename ... Args> Component* GameEntity::addComponent(Args ... args)
	{
		m_components.emplace(m_components.end(), args...);
		// Store pointer to special components
		if (typeid(Component) == typeid(TransformComponent))
			m_transform = *m_components.rbegin();
		if (typeid(Component) == typeid(RenderComponent))
			m_render = *m_components.rbegin();
	}

	unsigned int GameEntity::removeComponent(IGameComponent* component)
	{
		auto it = std::find(m_components.begin(), m_components.end(), component);
		if (it != m_components.end())
		{
			m_components.erase(it);
			return 1;
		}
		else
			return 0;
	}

	IGameComponent* GameEntity::getComponent(std::function<bool(IGameComponent*)> criterion) const
	{
		for (auto c : m_components)
			if (criterion(c))
				return c;
		return nullptr;
	}

	TransformComponent* GameEntity::transformComponent() const
	{
		return m_transform;
	}

	RenderComponent* GameEntity::renderComponent() const
	{
		return m_render;
	}
}
