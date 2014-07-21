//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Entity/CameraComponent.h"

namespace dbgl
{
    CameraComponent::CameraComponent(float fieldOfView, float near, float far) : m_fieldOfView(fieldOfView), m_near(near), m_far(far)
    {
    }

    float& CameraComponent::fieldOfView()
    {
	return m_fieldOfView;
    }

    float const& CameraComponent::fieldOfView() const
    {
	return m_fieldOfView;
    }

    float& CameraComponent::near()
    {
	return m_near;
    }

    float const& CameraComponent::near() const
    {
	return m_near;
    }

    float& CameraComponent::far()
    {
	return m_far;
    }

    float const& CameraComponent::far() const
    {
	return m_far;
    }

    void CameraComponent::update(Entity* /* owner */, double /* deltaTime */)
    {
	// No update needed
    }

    void CameraComponent::render(Entity* /* owner */, RenderContext const* /* rc */)
    {
	// No rendering needed
    }

    bool CameraComponent::needUpdate() const
    {
	return false;
    }

    bool CameraComponent::needRender() const
    {
	return false;
    }

}
