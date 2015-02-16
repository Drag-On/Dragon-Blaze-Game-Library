//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/RenderContext/RenderContextGL33Window.h"

namespace dbgl
{
    RenderContextGL33Window::RenderContextGL33Window(IWindow* wnd) : m_pWindow{wnd}
    {
    }

    RenderContextGL33Window::~RenderContextGL33Window()
    {
    }

    int RenderContextGL33Window::getWidth()
    {
	return m_pWindow->getFrameWidth();
    }

    int RenderContextGL33Window::getHeight()
    {
	return m_pWindow->getFrameHeight();
    }
}
