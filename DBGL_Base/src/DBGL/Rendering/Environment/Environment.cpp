//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Environment/Environment.h"

namespace dbgl
{
    Environment::Environment(Entity const& cam)
    {
	setCamera(cam);
    }

    Entity const* Environment::getCamera() const
    {
	return m_pCamera;
    }

    void Environment::setCamera(Entity const& cam)
    {
	if(cam.getComponent<CameraComponent>() && cam.getComponent<TransformComponent>())
	    m_pCamera = &cam;
	else
	    throw std::invalid_argument("Passed camera entity without camera- or transform component to environment.");
    }

    void Environment::addLight(Entity const* light)
    {
	if(light->getComponent<LightComponent>())
	    m_lights.push_back(light);
	else
	    LOG.warning("Tried to add a light entity to environment which doesn't have a LightComponent attached.");
    }

    void Environment::removeLight(Entity const* light)
    {
	m_lights.erase(std::find(m_lights.begin(), m_lights.end(), light));
    }

    std::vector<Entity const*> const& Environment::getLights() const
    {
	return m_lights;
    }
}
