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

    Camera::Camera(Vec3f const& position, Vec3f const& target, Vec3f const& up,
	    float fieldOfView, float aspectRatio, float near, float far)
    {
	_position = position;
	_target = target;
	_up = up;
	_fieldOfView = fieldOfView;
	_near = near;
	_far = far;
	_viewMat = Mat4f::makeView(_position, _target, _up);
	_projectionMat = Mat4f::makeProjection(_fieldOfView, aspectRatio, _near,
		_far);
    }

    Camera::~Camera()
    {
    }

    void Camera::update(float aspectRatio)
    {
	_viewMat.view(_position, _target, _up);
	_projectionMat.projection(_fieldOfView, aspectRatio, _near, _far);
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

    Mat4f const& Camera::getViewMat() const
    {
	return _viewMat;
    }

    Mat4f const& Camera::getProjectionMat() const
    {
	return _projectionMat;
    }
}

