//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef BASESCENE_H_
#define BASESCENE_H_

#include <stack>
#include <deque>
#include "IScene.h"
#include "DBGL/System/Entity/Entity.h"
#include "DBGL/System/Entity/TransformComponent.h"
#include "DBGL/System/Entity/RenderComponent.h"
#include "DBGL/System/Entity/LightComponent.h"
#include "DBGL/System/Entity/CameraComponent.h"
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Rendering/Material/Material.h"
#include "DBGL/Rendering/Environment/Camera.h"
#include "DBGL/Rendering/Environment/Environment.h"

namespace dbgl
{
    /**
     * @brief Base class for scenes that can be used within a SceneApplication
     */
    class BaseScene : public IScene
    {
	public:
	    /**
	     * @brief Constructor
	     */
	    BaseScene();
	    /**
	     * @brief Destructor
	     */
	    virtual ~BaseScene();
	    /**
	     * @brief Called when the scene is being entered
	     */
	    virtual void enter() = 0;
	    /**
	     * @brief Called once per frame, update everything
	     * @param args Update arguments
	     */
	    virtual void update(Window::UpdateEventArgs const& args);
	    /**
	     * @brief Called once per frame, render everything
	     * @param args Render arguments
	     */
	    virtual void render(Window::RenderEventArgs const& args);
	    /**
	     * @brief Called when the scene is being left
	     */
	    virtual void leave() = 0;
	protected:
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
	    void addTransformComp(Entity* entity, Vec3f pos = {0, 0, 0}, Vec3f scale = {1, 1, 1}, QuatF rot = QuatF{});
	    /**
	     * @brief Adds a render component to \p entity
	     * @param entity Entity to add a render component to
	     * @param mesh Mesh to use
	     * @param mat Material to use
	     * @param env Environment holding information such as camera...
	     */
	    void addRenderComp(Entity* entity, Mesh& mesh, Material& mat, Environment& env);
	    /**
	     * @brief Add a component to \p entity
	     * @param entity Entity to add the component to
	     * @param comp Component to add
	     * @note This method will automatically pass \p entity to the environment if a light component is added
	     */
	    void addComponent(Entity* entity, std::shared_ptr<Entity::Component> comp);


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
	     * @brief Environment data
	     */
	    Environment m_environment;
    };
}

#endif /* BASESCENE_H_ */
