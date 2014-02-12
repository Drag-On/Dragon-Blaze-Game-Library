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
    Viewport::Viewport(unsigned int x, unsigned int y, unsigned int width,
	    unsigned int height) :
	    _x(x), _y(y), _width(width), _height(height), _camera(NULL)
    {
    }

    Viewport::~Viewport()
    {
    }

    unsigned int Viewport::getX() const
    {
	return _x;
    }

    unsigned int Viewport::getY() const
    {
	return _y;
    }

    unsigned int Viewport::getWidth() const
    {
	return _width;
    }

    unsigned int Viewport::getHeight() const
    {
	return _height;
    }

    void Viewport::setPos(unsigned int x, unsigned int y)
    {
	_x = x;
	_y = y;
    }

    void Viewport::setSize(unsigned int width, unsigned int height)
    {
	_width = width;
	_height = height;
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

