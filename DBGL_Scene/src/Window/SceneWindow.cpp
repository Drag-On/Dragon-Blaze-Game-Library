//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Window/SceneWindow.h"

namespace dbgl
{
    SceneWindow::SceneWindow(GLFWwindow* share, const char* title, int width, int height,
	    bool fullscreen) :
	    Window(share, title, width, height, fullscreen)
    {

    }

    void SceneWindow::createRenderContext()
    {
	if (m_pRenderContext != NULL)
	    delete m_pRenderContext;

	m_pRenderContext = new SceneRenderContext(getFrameWidth(), getFrameHeight());
    }
}
