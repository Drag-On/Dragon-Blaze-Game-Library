//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SCENEAPPLICATION_H_
#define SCENEAPPLICATION_H_

#include <stack>
#include "SceneGraph.h"
#include "DBGL/System/System.h"
#include "DBGL/System/DBGLApplication.h"
#include "DBGL/System/Entity/Entity.h"
#include "DBGL/System/Entity/TransformComponent.h"
#include "DBGL/System/Entity/RenderComponent.h"
#include "DBGL/System/Entity/LightComponent.h"
#include "DBGL/System/Entity/CameraComponent.h"
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Window/Window.h"

namespace dbgl
{
    /**
     * @brief Basic application main class which structures entities into a scene graph to ease scene management
     */
    class SceneApplication : public DBGLApplication
    {
	public:
	    virtual void init();
	    virtual void run();
	    virtual void terminate();
	protected:
	    /**
	     * @brief Updates all entities
	     * @param args Update event arguments
	     */
	    virtual void update(Window::UpdateEventArgs const& args);
	    /**
	     * @brief Renders all entities
	     * @param args Render event arguments
	     */
	    virtual void render(Window::RenderEventArgs const& args);
	    /**
	     * @brief Returns the window used by this application
	     * @return A pointer to the used window
	     */
	    virtual Window* createWindow() = 0;
	    /**
	     * @brief Loads all required resources
	     */
	    virtual void loadResources() = 0;
	    /**
	     * @brief Creates a new entity.
	     * @details Creates a new entity and tracks it. It will be automatically freed on deconstruction.
	     * @param name Name of the new entity
	     * @return A pointer to the newly created entity
	     */
	    Entity* createEntity(std::string name = "");
	    /**
	     * @brief Deletes an entity and frees it's memory
	     * @param entity Entity to delete
	     */
	    void deleteEntity(Entity* entity);
	    /**
	     * @brief Adds a transform component to \p entity
	     * @param entity Entity to add a transform component to
	     * @param pos Initial position
	     * @param scale Initial scale
	     * @param rot Initial rotation
	     */
	    void addTransformComponent(Entity* entity, Vec3f pos = {0, 0, 0}, Vec3f scale = {1, 1, 1}, QuatF rot = QuatF{});


	    /**
	     * @brief The scene graph
	     */
	    SceneGraph<Entity> m_sceneGraph;
	    /**
	     * @brief List of all entities
	     * @details All created entities will be tracked here. Every entity in this list will be deleted on deconstruction
	     */
	    std::deque<Entity*> m_entities;
	    /**
	     * @brief The used window
	     */
	    Window* m_pWindow;

    };
}

#endif /* SCENEAPPLICATION_H_ */
