//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <vector>
#include "Camera.h"
#include "DBGL/System/Entity/Entity.h"
#include "DBGL/System/Entity/CameraComponent.h"
#include "DBGL/System/Entity/LightComponent.h"
#include "DBGL/System/Entity/TransformComponent.h"

namespace dbgl
{
    /**
     * @brief Holds data about the environment that are relevant to the render process.
     */
    class Environment
    {
	public:
	    /**
	     * @brief Constructor
	     * @param cam Camera to use. Must have a camera- and a transform component.
	     */
	    Environment(Entity const& cam);
	    /**
	     * @brief Retrieve the camera
	     * @return Current camera
	     */
	    Entity const* getCamera() const;
	    /**
	     * @brief Sets a new active camera
	     * @param cam Camera to use. Must have a camera- and a transform component.
	     */
	    void setCamera(Entity const& cam);
	    /**
	     * @brief Adds a new light to the environment
	     * @param light Light to add
	     */
	    void addLight(Entity const* light);
	    /**
	     * @brief Removes a light from the environment
	     * @param light Light to remove
	     */
	    void removeLight(Entity const* light);
	    /**
	     * @brief Provides access to all the known lights
	     * @return A list of all lights
	     */
	    std::vector<Entity const*> const& getLights() const;

	private:
	    /**
	     * @brief Currently active camera
	     */
	    Entity const* m_pCamera;
	    /**
	     * @brief All entities that emit light
	     */
	    std::vector<Entity const*> m_lights; // TODO: Split in static/dynamic, faster data structure
    };
}

#endif /* ENVIRONMENT_H_ */
