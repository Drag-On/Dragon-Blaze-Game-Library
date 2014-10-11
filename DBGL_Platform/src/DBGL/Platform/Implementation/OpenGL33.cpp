//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Implementation/OpenGL33.h"
#include "DBGL/Platform/Window/WindowGL33.h"

namespace dbgl
{
    OpenGL33::~OpenGL33()
    {

    }

    IWindow* OpenGL33::createWindow(std::string title, int width, int height, bool fullscreen,
	    unsigned int multisampling)
    {
	return new WindowGL33 { title, width, height, fullscreen, multisampling };
    }
}
