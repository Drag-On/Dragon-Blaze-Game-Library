//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Monitor/MonitorGL33.h"

namespace dbgl
{
    void MonitorGL33::getResolution(int& width, int& height)
    {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = mode->width;
	height = mode->height;
    }
}
