//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/Viewport.h"

namespace dbgl
{
    Viewport::Viewport(float xRatio, float yRatio, float widthRatio,
	    float heightRatio) :
	    _xRatio(xRatio), _yRatio(yRatio), _widthRatio(widthRatio), _heightRatio(
		    heightRatio), _camera(NULL)
    {
    }

    Viewport::~Viewport()
    {
    }

    float Viewport::getXRatio() const
    {
	return _xRatio;
    }

    float Viewport::getYRatio() const
    {
	return _yRatio;
    }

    float Viewport::getWidthRatio() const
    {
	return _widthRatio;
    }

    float Viewport::getHeightRatio() const
    {
	return _heightRatio;
    }

    void Viewport::setPosRatio(float xRatio, float yRatio)
    {
	_xRatio = xRatio;
	_yRatio = yRatio;
    }

    void Viewport::setSizeRatio(float widthRatio, float heightRatio)
    {
	_widthRatio = widthRatio;
	_heightRatio = heightRatio;
    }

    Camera* Viewport::getCamera() const
    {
	return _camera;
    }

    void Viewport::setCamera(Camera* camera)
    {
	_camera = camera;
    }
}

