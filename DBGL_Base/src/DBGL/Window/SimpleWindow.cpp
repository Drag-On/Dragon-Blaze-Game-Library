//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Window/SimpleWindow.h"

namespace dbgl
{
    SimpleWindow::SimpleWindow(GLFWwindow* share, const char* title,
	    int width, int height, bool fullscreen, unsigned int multisampling) :
	    Window(share, title, width, height, fullscreen, multisampling)
    {
	// Add callback for keyboard input
	addKeyCallback(std::bind(&SimpleWindow::keyCallback, this,
		std::placeholders::_1));
    }

    SimpleWindow::~SimpleWindow()
    {
    }

    void SimpleWindow::keyCallback(KeyEventArgs args)
    {
	// Close on escape
	if (args.key == Input::Key::KEY_ESCAPE && args.action == Input::KeyState::PRESSED)
	    close();

	// Switch to fullscreen on alt + enter
	if (args.key == Input::Key::KEY_ENTER && args.action == Input::KeyState::PRESSED
		&& args.mods.isSet(Input::Modifier::KEY_ALT))
	    setFullscreen(!isFullscreen());
    }
}

