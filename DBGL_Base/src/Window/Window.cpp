//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Window/Window.h"

namespace dbgl
{
    Window::Window()
    {
	if(!glfwInit())
	{
	    LOG->error("Failed to initialize GLFW");
	    exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(errorCallback);
    }

    Window::~Window()
    {
	glfwDestroyWindow(_pWndHandle);
    }

    void Window::open()
    {
	_pWndHandle = glfwCreateWindow(640, 480, "My Title", NULL, NULL); // glfwGetPrimaryMonitor()
	if (!_pWndHandle)
	{
	    glfwTerminate();
	    exit(EXIT_FAILURE);
	}
    }

    void Window::errorCallback(int error, const char* description)
    {
	LOG->error("Error %d: %s", error, description);
    }
}

