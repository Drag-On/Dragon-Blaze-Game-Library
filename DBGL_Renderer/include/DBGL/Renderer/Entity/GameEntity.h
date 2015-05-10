//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_ENTITY_GAMEENTITY_H_
#define INCLUDE_DBGL_RENDERER_ENTITY_GAMEENTITY_H_

#include "DBGL/Renderer/Component/IGameComponent.h"
#include <vector>
#include <functional>

namespace dbgl
{
    class TransformComponent;

    class RenderComponent;

    class GameEntity
    {
    public:
        /**
         * @brief Constructor
         */
        GameEntity();
        /**
         * @brief Copy constructor
         */
        GameEntity(GameEntity const& other);
        /**
         * @brief Move constructor
         */
        GameEntity(GameEntity&& other);
        /**
         * @brief Destructor
         */
        ~GameEntity();
        /**
         * @brief Assignment operator
         */
        GameEntity& operator=(GameEntity const& other);
        /**
         * @brief Move-assignment operator
         */
        GameEntity& operator=(GameEntity&& other);
        /**
         * @brief Update the entity and all of its components
         */
        void update();
        /**
         * @brief Create a component and add it to this entity
         * @param args Arguments to pass to the component constructor
         * @returns A pointer to the component
         */
        template<typename Component, typename ... Args>
        Component* addComponent(Args ... args);
        /**
         * @brief Removes a component from the entity
         * @param component Component that matches the ones to remove
         * @return Amount of removed components
         */
        unsigned int removeComponent(IGameComponent* component);
        /**
         * @brief Gets a component
         * @param criterion Function or lambda returning true for the component to get
         * @return The requested component
         */
        IGameComponent* getComponent(std::function<bool(IGameComponent*)> criterion) const;
        /**
         * @brief Get a component by type
         */
        template<typename T>
        T* getComponent() const;
        /**
         * @brief A pointer to this entity's transform component
         * @return Pointer to transform component or nullptr if none set
         */
        TransformComponent* transformComponent() const;
        /**
         * @brief A pointer to this entity's render component
         * @return Pointer to render component or nullptr if none set
         */
        RenderComponent* renderComponent() const;
    private:
        void checkSpecialComponent(IGameComponent* comp);

        std::vector<IGameComponent*> m_components;
        TransformComponent* m_transform = nullptr;
        RenderComponent* m_render = nullptr;
    };
}

#include "GameEntity.imp"

#endif /* INCLUDE_DBGL_RENDERER_ENTITY_GAMEENTITY_H_ */
