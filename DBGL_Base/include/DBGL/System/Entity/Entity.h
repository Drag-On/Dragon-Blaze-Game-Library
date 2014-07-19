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

#include <string>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "DBGL/System/Log/Log.h"

class TransformComponent;
class RenderComponent;
class RenderContext;

namespace dbgl
{
    /**
     * @brief Game entity which can hold components of different types
     */
    class Entity
    {
	public:
	    /**
	     * @brief Generic component used by entities
	     */
	    class Component
	    {
		public:
		    /**
		     * @brief Constructor
		     */
		    virtual ~Component() = default;
		    /**
		     * @brief Called upon update process
		     * @param entity Entity owning this component
		     * @param deltaTime Time since last udpate
		     */
		    virtual void update(Entity* entity, double deltaTime) = 0;
		    /**
		     * @brief Called upon render process
		     * @param entity Entity owning this component
		     * @param rc RenderContext to draw to
		     */
		    virtual void render(Entity* entity, RenderContext const* rc) = 0;
		    /**
		     * @brief Determines whether this component wants to be updated
		     * @return True if needs to be updated, otherwise false
		     */
		    virtual bool needUpdate() const = 0;
		    /**
		     * @brief Determines whether this component wants to be rendered
		     * @return True if needs to be rendered, otherwise false
		     */
		    virtual bool needRender() const = 0;
	    };

	    /**
	     * @brief Constructor
	     * @param name Name to give this entity
	     */
	    Entity(std::string name = "");
	    /**
	     * @brief Destructor
	     */
	    ~Entity() = default;
	    /**
	     * @return Entity name
	     */
	    std::string const& getName();
	    /**
	     * @brief Creates a component of a certain type and adds it to this entity
	     * @return Reference to the newly created component
	     * @details Component must be a (sub-)type of Component. A component
	     * 	        of a specific type can only be added one time.
	     */
	    void addComponent(std::shared_ptr<Component> component);
	    /**
	     * @brief Completely removes a component
	     * @return True in case the component was removed, false if not found
	     * @details Component must be a (sub-)type of Component
	     */
	    bool removeComponent(std::shared_ptr<Component> component);
	    /**
	     * @brief Provides access to a component
	     * @return Pointer to the requested component or nullptr if no component of has been found
	     * @details Component must be a (sub-)type of Component
	     */
	    template<class T> std::shared_ptr<T> getComponent();
	    /**
	     * @brief Updates all components
	     * @param deltaTime Time since last update
	     */
	    void update(double deltaTime);
	    /**
	     * @brief Renders the geometry component if available
	     * @param rc Context to render to
	     */
	    void render(RenderContext const* rc);

	private:
	    std::string m_name = "";
	    std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
	    std::vector<std::shared_ptr<Component>> m_updateComponents;
	    std::vector<std::shared_ptr<Component>> m_renderComponents;
    };
}



#endif /* ENTITY_H_ */
