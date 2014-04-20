//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SIMPLESCENEWINDOW_H_
#define SIMPLESCENEWINDOW_H_

#include "DBGL/Window/SceneWindow.h"

namespace dbgl
{
    class SimpleSceneWindow: public SceneWindow
    {
	protected:
	    SimpleSceneWindow(GLFWwindow* share, const char* title = "Dragon Blaze Game Library",
		    int width = 800, int height = 600, bool fullscreen = false);
	    // Callbacks
	    void keyCallback(KeyEventArgs args);

	private:
	    friend class WindowManager;
    };
}

#endif /* SIMPLESCENEWINDOW_H_ */
