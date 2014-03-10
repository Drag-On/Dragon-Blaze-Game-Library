//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/Camera.h"

namespace dbgl
{

    Camera::Camera(Vec3f position, Vec3f direction, Vec3f up, float fieldOfView,
	    float near, float far) :
	    m_position(position), m_fieldOfView(fieldOfView), m_near(near), m_far(
		    far)
    {
	setOrientation(direction, up);
    }

    Camera::Camera(Vec3f position, QuatF orientation, float fieldOfView,
	    float near, float far) :
	    m_position(position), m_rotation(orientation), m_fieldOfView(
		    fieldOfView), m_near(near), m_far(far)
    {
    }

    Camera::~Camera()
    {
    }

    Vec3f& Camera::position()
    {
	return m_position;
    }

    QuatF& Camera::rotation()
    {
	return m_rotation;
    }

    void Camera::getOrientation(Vec3f* direction, Vec3f* up, Vec3f* right) const
    {
	if (direction != NULL)
	    *direction = m_rotation * Vec3f(0, 0, 1);
	if (right != NULL)
	    *right = m_rotation * Vec3f(-1, 0, 0);
	if (up != NULL)
	    *up = m_rotation * Vec3f(0, 1, 0);
    }

    void Camera::setOrientation(Vec3f const& direction, Vec3f const& up)
    {
	m_rotation.fromVectors(Vec3f(0, 0, 1), direction, up);
    }

    void Camera::rotate(float horizontal, float vertical)
    {
	rotation() = QuatF(Vec3f(0, horizontal, 0)) * rotation()
		* QuatF(Vec3f(vertical, 0, 0));
    }

    float Camera::getFieldOfView() const
    {
	return m_fieldOfView;
    }

    void Camera::setFieldOfView(float fieldOfView)
    {
	m_fieldOfView = fieldOfView;
    }

    float Camera::getNear() const
    {
	return m_near;
    }

    void Camera::setNear(float near)
    {
	m_near = near;
    }

    float Camera::getFar() const
    {
	return m_far;
    }

    void Camera::setFar(float far)
    {
	m_far = far;
    }
}

