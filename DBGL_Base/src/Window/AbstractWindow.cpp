//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Window/AbstractWindow.h"

namespace dbgl
{
    AbstractWindow::AbstractWindow() :
	    AbstractWindow("Dragon Blaze Game Library")
    {
    }

    AbstractWindow::AbstractWindow(const char* title) :
	    AbstractWindow(title, 800, 600)
    {
    }

    AbstractWindow::AbstractWindow(const char* title, int width, int height) :
	    AbstractWindow(title, width, height, false)
    {
    }

    AbstractWindow::AbstractWindow(const char* title, int width, int height,
	    bool fullscreen)
    {
	if (!glfwInit())
	{
	    LOG->error("Failed to initialize GLFW!");
	    exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(errorCallback);

	if(fullscreen)
	{
	    // Initialize window to default values
	    _windowedWidth = 800;
	    _windowedHeight = 600;
	    // Initialize fullscreen resolution
	    _fullscreenWidth = width;
	    _fullscreenHeight = height;
	    _isFullscreen = true;
	}
	else
	{
	    // Initialize window to default values
	    _windowedWidth = width;
	    _windowedHeight = height;
	    // Initialize fullscreen resolution to screen resolution
	    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	    _fullscreenWidth = mode->width;
	    _fullscreenHeight = mode->height;
	    _isFullscreen = false;
	}

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if(fullscreen)
	_pWndHandle = glfwCreateWindow(_fullscreenWidth, _fullscreenHeight, title, glfwGetPrimaryMonitor(), NULL);
	else
	_pWndHandle = glfwCreateWindow(_windowedWidth, _windowedHeight, title, NULL, NULL);
	if (!_pWndHandle)
	{
	    LOG->error("Failed to create new window!");
	    glfwTerminate();
	    exit(EXIT_FAILURE);
	}
    }

    AbstractWindow::~AbstractWindow()
    {
	glfwDestroyWindow(_pWndHandle);
    }

    void AbstractWindow::show()
    {
	glfwShowWindow(_pWndHandle);
    }

    void AbstractWindow::hide()
    {
	glfwHideWindow(_pWndHandle);
    }

    void AbstractWindow::close()
    {
	glfwSetWindowShouldClose(_pWndHandle, true);
    }

    bool AbstractWindow::hasFocus()
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_FOCUSED);
    }

    bool AbstractWindow::isIconified()
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_ICONIFIED);
    }

    bool AbstractWindow::isVisible()
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_VISIBLE);
    }

    bool AbstractWindow::isResizable()
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_RESIZABLE);
    }

    bool AbstractWindow::isDecorated()
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_DECORATED);
    }

    const char* AbstractWindow::getTitle()
    {
	return _title.c_str();
    }

    void AbstractWindow::setTitle(const char* title)
    {
	_title.assign(title);
	glfwSetWindowTitle(_pWndHandle, title);
    }

    int AbstractWindow::getWidth()
    {
	int width, height;
	glfwGetWindowSize(_pWndHandle, &width, &height);
	return width;
    }

    int AbstractWindow::getHeight()
    {
	int width, height;
	glfwGetWindowSize(_pWndHandle, &width, &height);
	return height;
    }

    void AbstractWindow::setSize(int width, int height)
    {
	glfwSetWindowSize(_pWndHandle, width, height);
    }

    int AbstractWindow::getFrameWidth()
    {
	int width, height;
	glfwGetFramebufferSize(_pWndHandle, &width, &height);
	return width;
    }

    int AbstractWindow::getFrameHeight()
    {
	int width, height;
	glfwGetFramebufferSize(_pWndHandle, &width, &height);
	return height;
    }

    int AbstractWindow::getX()
    {
	int x, y;
	glfwGetWindowPos(_pWndHandle, &x, &y);
	return x;
    }

    int AbstractWindow::getY()
    {
	int x, y;
	glfwGetWindowPos(_pWndHandle, &x, &y);
	return y;
    }

    void AbstractWindow::setPos(int x, int y)
    {
	glfwSetWindowPos(_pWndHandle, x, y);
    }

    bool AbstractWindow::isFullscreen()
    {
	return _isFullscreen;
    }

    void AbstractWindow::setFullscreen(bool fullscreen)
    {
	const char* title = getTitle();
	if (isFullscreen() && !fullscreen)
	{
	    // Destroy window
	    glfwDestroyWindow(_pWndHandle);

	    // Recreate
	    _pWndHandle = glfwCreateWindow(_windowedWidth, _windowedHeight,
		    title, NULL, NULL);
	    if (!_pWndHandle)
	    {
		LOG->error("Failed to enter windowed mode!");
		glfwTerminate();
		exit(EXIT_FAILURE);
	    }
	}
	else if (!isFullscreen() && fullscreen)
	{
	    _windowedWidth = getFrameWidth();
	    _windowedHeight = getFrameHeight();

	    // Destroy window
	    glfwDestroyWindow(_pWndHandle);

	    // Recreate
	    _pWndHandle = glfwCreateWindow(_fullscreenWidth, _fullscreenHeight,
		    title, glfwGetPrimaryMonitor(), NULL);
	    if (!_pWndHandle)
	    {
		LOG->error("Failed to enter fullscreen mode!");
		glfwTerminate();
		exit(EXIT_FAILURE);
	    }
	}
    }

    void AbstractWindow::preUpdate()
    {
    }

    void AbstractWindow::postUpdate()
    {
    }

    void AbstractWindow::preRender()
    {
	glfwMakeContextCurrent(_pWndHandle);
    }

    void AbstractWindow::postRender()
    {
	glfwSwapBuffers(_pWndHandle);
    }

    void AbstractWindow::errorCallback(int error, const char* description)
    {
	LOG->error("Error %d: %s!", error, description);
}
}

