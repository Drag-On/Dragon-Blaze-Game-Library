//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Entity/TransformEntityComponent.h"

namespace dbgl
{
    TransformEntityComponent::~TransformEntityComponent()
    {
    }

    void TransformEntityComponent::init(Vec3f pos, Vec3f scale, QuatF rot)
    {
	m_position = pos;
	m_scale = scale;
	m_rotation = rot;
    }

    Vec3f& TransformEntityComponent::position()
    {
	return m_position;
    }

    Vec3f& TransformEntityComponent::scale()
    {
	return m_scale;
    }

    QuatF& TransformEntityComponent::rotation()
    {
	return m_rotation;
    }

    void TransformEntityComponent::update(std::map<std::type_index, EntityComponent*> const& components, double deltaTime)
    {
    }
}

