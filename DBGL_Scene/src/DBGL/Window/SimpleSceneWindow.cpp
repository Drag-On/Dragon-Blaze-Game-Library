//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Window/SimpleSceneWindow.h"

namespace dbgl
{
    SimpleSceneWindow::SimpleSceneWindow(GLFWwindow* share, const char* title, int width,
	    int height, bool fullscreen) :
	    SceneWindow(share, title, width, height, fullscreen)
    {
	// Add callback for keyboard input
	addKeyCallback(std::bind(&SimpleSceneWindow::keyCallback, this, std::placeholders::_1));
    }

    void SimpleSceneWindow::keyCallback(KeyEventArgs args)
    {
	// Close on escape
	if (args.key == GLFW_KEY_ESCAPE && args.action == GLFW_PRESS)
	    close();

	// Switch to fullscreen on alt + enter
	if (args.key == GLFW_KEY_ENTER && args.action == GLFW_PRESS
		&& (args.mods & (1 << GLFW_MOD_ALT)) == 0)
	    setFullscreen(!isFullscreen());
    }
}


