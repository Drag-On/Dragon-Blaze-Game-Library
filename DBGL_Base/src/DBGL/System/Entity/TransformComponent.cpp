//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Entity/TransformComponent.h"

namespace dbgl
{
    TransformComponent::TransformComponent(Vec3f pos, Vec3f scale, QuatF rot) : m_position(pos), m_scale(scale), m_rotation(rot)
    {
    }

    Vec3f& TransformComponent::position()
    {
	return m_position;
    }

    Vec3f& TransformComponent::scale()
    {
	return m_scale;
    }

    QuatF& TransformComponent::rotation()
    {
	return m_rotation;
    }

    void TransformComponent::update(Entity* /* owner */, double /* deltaTime */)
    {
	// No update needed
    }

    void TransformComponent::render(Entity* /* owner */, RenderContext const* /* rc */)
    {
	// No rendering needed
    }

    bool TransformComponent::needUpdate() const
    {
	return false;
    }

    bool TransformComponent::needRender() const
    {
	return false;
    }
}
