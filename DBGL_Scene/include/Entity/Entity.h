//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ENTITY_H_
#define ENTITY_H_

#include <typeindex>
#include <typeinfo>
#include <map>
#include <string>
#include "EntityComponent.h"
#include "TransformEntityComponent.h"
#include "RenderEntityComponent.h"
#include "Rendering/SceneRenderContext.h"
#include "System/Log/Log.h"

namespace dbgl
{
    /**
     * @brief Generic game entity
     */
    class Entity
    {
	public:
	    /**
	     * @brief Constructor
	     */
	    Entity();
	    /**
	     * @brief Constructor
	     * @param name Entity name
	     */
	    Entity(std::string name);
	    /**
	     * @brief Constructor
	     * @param name Entity name
	     * @param renderable Data on how to render
	     * @detail Automatically creates a transform and render component!
	     */
	    Entity(Renderable const& renderable, std::string name = "");
	    /**
	     * @brief Destructor
	     */
	    ~Entity();
	    /**
	     * @return Entity name
	     */
	    std::string const& getName();
	    /**
	     * @brief Creates a component of a certain type and adds it to this entity
	     * @return Reference to the newly created component
	     * @detail Component must be a (sub-)type of EntityComponent. A component
	     * 	       of a specific type can only be added one time.
	     */
	    template<class Component> Component* addComponent();
	    /**
	     * @brief Completely removes a component
	     * @return True in case the component was removed, false if not found
	     * @detail Component must be a (sub-)type of EntityComponent
	     */
	    template<class Component> bool removeComponent();
	    /**
	     * @brief Provides access to a component
	     * @return Pointer to the requested component or NULL if no component of
	     * 	       type Component has been found
	     * @detail Component must be a (sub-)type of EntityComponent
	     */
	    template<class Component> Component* getComponent();
	    /**
	     * @return This entities transform component or NULL if none is attached
	     */
	    TransformEntityComponent* getTransform();
	    /**
	     * @return This entities render component or NULL if none attached
	     */
	    RenderEntityComponent* getRender();
	    /**
	     * @brief Updates all components
	     * @param deltaTime Time since last update
	     */
	    void update(double deltaTime);
	    /**
	     * @brief Renders the geometry component if available
	     * @param rc Context to render to
	     */
	    void render(SceneRenderContext const* rc);
	private:
	    std::map<std::type_index, EntityComponent*> m_Components;
	    std::string m_Name = "";
    };
}

#endif /* ENTITY_H_ */
