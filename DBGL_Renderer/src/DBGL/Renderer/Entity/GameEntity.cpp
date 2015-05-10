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
#include "DBGL/Renderer/Component/RenderComponent.h"
#include "DBGL/Renderer/Component/TransformComponent.h"
#include <algorithm>

namespace dbgl
{
    GameEntity::GameEntity()
    {
    }

    GameEntity::GameEntity(GameEntity const& other)
    {
        m_components.reserve(other.m_components.size());
        for (auto comp : other.m_components)
        {
            m_components.push_back(comp->clone());
            checkSpecialComponent(m_components.back());
        }
    }

    GameEntity::GameEntity(GameEntity&& other)
    {
        m_components = std::move(other.m_components);
        m_transform = other.m_transform;
        m_render = other.m_render;
        other.m_components.clear();
        other.m_transform = nullptr;
        other.m_render = nullptr;
    }

    GameEntity::~GameEntity()
    {
        for (unsigned int i = 0; i < m_components.size(); i++)
            delete m_components[i];
    }

    GameEntity& GameEntity::operator=(GameEntity const& other)
    {
        if (this != &other)
        {
            for (auto comp : m_components)
                delete comp;
            m_components.clear();
            m_components.reserve(other.m_components.size());
            for (auto comp : other.m_components)
            {
                m_components.push_back(comp->clone());
                checkSpecialComponent(m_components.back());
            }
        }
        return *this;
    }

    GameEntity& GameEntity::operator=(GameEntity&& other)
    {
        if (this != &other)
        {
            for (auto comp : m_components)
                delete comp;
            m_components.clear();
            m_components = std::move(other.m_components);
            m_transform = other.m_transform;
            m_render = other.m_render;
            other.m_components.clear();
            other.m_transform = nullptr;
            other.m_render = nullptr;
        }
        return *this;
    }

    void GameEntity::checkSpecialComponent(IGameComponent* comp)
    {
        TransformComponent* transform = dynamic_cast<TransformComponent*>(comp);
        if (transform)
            m_transform = transform;
        RenderComponent* render = dynamic_cast<RenderComponent*>(comp);
        if (render)
            m_render = render;
    }

    void GameEntity::update()
    {
        for (auto c : m_components)
            c->update();
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
