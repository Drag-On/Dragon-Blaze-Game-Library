//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SCENEWINDOW_H_
#define SCENEWINDOW_H_

#include "DBGL/Window/Window.h"
#include "DBGL/Rendering/SceneRenderContext.h"

namespace dbgl
{
    class SceneWindow: public Window
    {
	protected:
	    /**
	     * @brief Constructs a window
	     * @param share Window to share resources with or NULL if none
	     * @param title Title of the window
	     * @param width Width of the rendering plane
	     * @param height Height of the rendering plane
	     * @param fullscreen Indicates if it is opened to fullscreens
	     */
	    SceneWindow(GLFWwindow* share, const char* title = "Dragon Blaze Game Library", int width =
		    800, int height = 600, bool fullscreen = false);
	    /**
	     * @brief Removes the current render context from the window and applies a new one
	     */
	    virtual void createRenderContext();

	private:
		    friend class WindowManager;
    };
}

#endif /* SCENEWINDOW_H_ */
