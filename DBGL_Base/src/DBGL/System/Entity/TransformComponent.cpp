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

    Vec3f const& TransformComponent::position() const
    {
	return m_position;
    }

    Vec3f const& TransformComponent::scale() const
    {
	return m_scale;
    }

    QuatF const& TransformComponent::rotation() const
    {
	return m_rotation;
    }

    Vec3f TransformComponent::worldPosition() const
    {
	// TODO: cache world transform for better performance?
	// Use local position as a start
	Vec3f worldPos = position();
	// If there are parent nodes add their positions
	SceneGraph<Entity>::Node* parent = nullptr;
	if (getOwner()->getSceneNode())
	    parent = getOwner()->getSceneNode()->getParent();
	while (parent)
	{
	    auto parentTransform = parent->getEntity()->getComponent<TransformComponent>();
	    if (parentTransform)
		worldPos += parentTransform->m_position;
	    parent = parent->getParent();
	}
	return worldPos;
    }

    Vec3f TransformComponent::worldScale() const
    {
	// Use local scale as a start
	Vec3f worldScale = scale();
	// If there are parent nodes multiply their scale
	SceneGraph<Entity>::Node* parent = nullptr;
	if (getOwner()->getSceneNode())
	    parent = getOwner()->getSceneNode()->getParent();
	while (parent)
	{
	    auto parentTransform = parent->getEntity()->getComponent<TransformComponent>();
	    if (parentTransform)
		worldScale *= parentTransform->m_scale;
	    parent = parent->getParent();
	}
	return worldScale;
    }

    QuatF TransformComponent::worldRotation() const
    {
	// Use local rotation as a start
	QuatF worldRotation = rotation();
	// If there are parent nodes multiply their rotations
	SceneGraph<Entity>::Node* parent = nullptr;
	if (getOwner()->getSceneNode())
	    parent = getOwner()->getSceneNode()->getParent();
	while (parent)
	{
	    auto parentTransform = parent->getEntity()->getComponent<TransformComponent>();
	    if (parentTransform)
		worldRotation *= parentTransform->m_rotation;
	    parent = parent->getParent();
	}
	return worldRotation;
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
