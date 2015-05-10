//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/Component/CameraComponent.h"

namespace dbgl
{
    CameraComponent::CameraComponent(TransformComponent* transform, float fov, unsigned int near, unsigned int far,
                                     IWindow* wnd) : m_fov(fov),
                                                     m_near(near),
                                                     m_far(far),
                                                     m_pWnd(wnd),
                                                     m_pTransform(transform)
    {
        update();
    }

    void CameraComponent::update()
    {
        m_dir = m_pTransform->rotation() * Vec3f{0, 0, -1};
        m_up = m_pTransform->rotation() * Vec3f{0, 1, 0};
        m_view = Mat4f::makeView(getPosition(), m_dir, m_up);
        m_projection = Mat4f::makeProjection(getFieldOfView(), getRatio(), getNear(), getFar());
    }

    Mat4f const& CameraComponent::getViewMatrix() const
    {
        return m_view;
    }

    Mat4f const& CameraComponent::getProjectionMatrix() const
    {
        return m_projection;
    }

    Vec3f const& CameraComponent::getPosition() const
    {
        return m_pTransform->position();
    }

    Vec3f const& CameraComponent::getDirection() const
    {
        return m_dir;
    }

    Vec3f const& CameraComponent::getUp() const
    {
        return m_up;
    }

    float CameraComponent::getNear() const
    {
        return m_near;
    }

    float CameraComponent::getFar() const
    {
        return m_far;
    }

    float CameraComponent::getFieldOfView() const
    {
        return m_fov;
    }

    float CameraComponent::getRatio() const
    {
        return static_cast<float>(m_pWnd->getFrameWidth()) / m_pWnd->getFrameHeight();
    }

    IGameComponent* CameraComponent::clone() const
    {
        auto copy = new CameraComponent(m_pTransform, m_fov, m_near, m_far, m_pWnd);
        copy->m_dir = m_dir;
        copy->m_up = m_up;
        copy->m_view = m_view;
        copy->m_projection = m_projection;
        return copy;
    }
}