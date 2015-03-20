//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/Component/TransformComponent.h"

namespace dbgl
{
	TransformComponent::TransformComponent(Vec3f const& pos, Vec3f const& scale, QuatF const& rot)
			: m_pos { pos }, m_scale { scale }, m_rot { rot }
	{
	}

	void TransformComponent::update()
	{
		m_modelMat = m_rot.getMatrix() * Mat4f::makeScale(m_scale) * Mat4f::makeTranslation(m_pos);
	}

	Vec3f& TransformComponent::position()
	{
		return m_pos;
	}

	Vec3f const& TransformComponent::position() const
	{
		return m_pos;
	}

	Vec3f& TransformComponent::scale()
	{
		return m_scale;
	}

	Vec3f const& TransformComponent::scale() const
	{
		return m_scale;
	}

	QuatF& TransformComponent::rotation()
	{
		return m_rot;
	}

	QuatF const& TransformComponent::rotation() const
	{
		return m_rot;
	}

	Mat4f const& TransformComponent::modelMat() const
	{
		return m_modelMat;
	}

}
