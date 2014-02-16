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

    Camera::Camera(Vec3f position, Vec3f target, Vec3f up, float fieldOfView,
	    float near, float far)
    {
	_position = position;
	_target = target;
	_up = up;
	_fieldOfView = fieldOfView;
	_near = near;
	_far = far;
    }

    Camera::~Camera()
    {
    }

    Vec3f& Camera::position()
    {
	return _position;
    }

    Vec3f& Camera::target()
    {
	return _target;
    }

    Vec3f& Camera::up()
    {
	return _up;
    }

    float Camera::getFieldOfView() const
    {
	return _fieldOfView;
    }

    void Camera::setFieldOfView(float fieldOfView)
    {
	_fieldOfView = fieldOfView;
    }

    float Camera::getNear() const
    {
	return _near;
    }

    void Camera::setNear(float near)
    {
	_near = near;
    }

    float Camera::getFar() const
    {
	return _far;
    }

    void Camera::setFar(float far)
    {
	_far = far;
    }
}

