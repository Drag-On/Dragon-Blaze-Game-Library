//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Entity/LightComponent.h"

namespace dbgl
{
    LightComponent::LightComponent(LightType type, Vec3f const& color, float power) : m_type(type), m_color(color), m_power(power)
    {
    }

    auto LightComponent::type() -> LightType&
    {
	return m_type;
    }

    auto LightComponent::type() const -> LightType const&
    {
	return m_type;
    }

    Vec3f& LightComponent::color()
    {
	return m_color;
    }

    Vec3f const& LightComponent::color() const
    {
	return m_color;
    }

    float& LightComponent::power()
    {
	return m_power;
    }

    float const& LightComponent::power() const
    {
	return m_power;
    }

    float& LightComponent::cutoff()
    {
	return m_cutoff;
    }

    float const& LightComponent::cutoff() const
    {
	return m_cutoff;
    }

    Vec3f& LightComponent::direction()
    {
	return m_direction;
    }

    Vec3f const& LightComponent::direction() const
    {
	return m_direction;
    }

    void LightComponent::update(Entity* /* owner */, double /* deltaTime */)
    {
	// No update needed
    }

    void LightComponent::render(Entity* /* owner */, RenderContext const* /* rc */)
    {
	// No rendering needed
    }

    bool LightComponent::needUpdate() const
    {
	return false;
    }

    bool LightComponent::needRender() const
    {
	return false;
    }

}

