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
	    _position(position), _fieldOfView(fieldOfView), _near(near), _far(
		    far)
    {
	setOrientation(direction, up);
    }

    Camera::Camera(Vec3f position, QuatF orientation, float fieldOfView,
	    float near, float far) :
	    _position(position), _rotation(orientation), _fieldOfView(
		    fieldOfView), _near(near), _far(far)
    {
    }

    Camera::~Camera()
    {
    }

    Vec3f& Camera::position()
    {
	return _position;
    }

    QuatF& Camera::rotation()
    {
	return _rotation;
    }

    void Camera::getOrientation(Vec3f* direction, Vec3f* up, Vec3f* right) const
    {
	if (direction != NULL)
	    *direction = _rotation * Vec3f(0, 0, 1);
	if (right != NULL)
	    *right = _rotation * Vec3f(-1, 0, 0);
	if (up != NULL)
	    *up = _rotation * Vec3f(0, 1, 0);
    }

    void Camera::setOrientation(Vec3f const& direction, Vec3f const& up)
    {
	_rotation.fromVectors(Vec3f(0, 0, 1), direction, up);
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

