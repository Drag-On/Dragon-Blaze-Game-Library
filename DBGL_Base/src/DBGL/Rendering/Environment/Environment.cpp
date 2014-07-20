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
    Environment::Environment(Camera& cam) : m_pCamera(&cam)
    {

    }

    Camera* Environment::getCamera() const
    {
	return m_pCamera;
    }

    void Environment::setCamera(Camera& cam)
    {
	m_pCamera = &cam;
    }

    void Environment::addLight(Entity const* light)
    {
	m_lights.push_back(light);
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
