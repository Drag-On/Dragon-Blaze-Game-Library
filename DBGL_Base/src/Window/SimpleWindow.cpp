//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Window/SimpleWindow.h"

namespace dbgl
{
    SimpleWindow::SimpleWindow() :
	    SimpleWindow("Dragon Blaze Game Library")
    {
    }

    SimpleWindow::SimpleWindow(const char* title) :
	    SimpleWindow(title, 800, 600)
    {
    }

    SimpleWindow::SimpleWindow(const char* title, int width, int height) :
	    SimpleWindow(title, width, height, false)
    {
    }

    SimpleWindow::SimpleWindow(const char* title, int width, int height,
	    bool fullscreen) :
	    AbstractWindow(title, width, height, fullscreen)
    {
	// Add callbacks for framebuffer and keyboard input
	addFramebufferResizeCallback(
		std::bind(&SimpleWindow::framebufferResizeCallback, this,
			std::placeholders::_1, std::placeholders::_2));
	addKeyCallback(
		std::bind(&SimpleWindow::keyCallback, this,
			std::placeholders::_1, std::placeholders::_2,
			std::placeholders::_3, std::placeholders::_4));
    }

    SimpleWindow::~SimpleWindow()
    {

    }

    void SimpleWindow::update()
    {

    }

    void SimpleWindow::render()
    {

    }

    void SimpleWindow::framebufferResizeCallback(int width, int height)
    {
	// Change viewport
	glViewport(0, 0, width, height);
    }

    void SimpleWindow::keyCallback(int key, int scancode, int action, int mods)
    {
	// Close on escape
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	    close();

	// Switch to fullscreen on alt + enter
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS
		&& (mods & (1 << GLFW_MOD_ALT)) == 0)
	    setFullscreen(!isFullscreen());
    }
}

