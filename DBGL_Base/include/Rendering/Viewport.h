//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include "Window/AbstractWindow.h"

namespace dbgl
{
    class Viewport
    {
	private:
	    unsigned int _x, _y;
	    unsigned int _width, _height;
	    AbstractWindow* _pWindow;
    };
}

#endif /* VIEWPORT_H_ */
