//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RENDERCONTEXTGL33WINDOW_H_
#define RENDERCONTEXTGL33WINDOW_H_

#include "RenderContextGL33.h"
#include "DBGL/Platform/Window/IWindow.h"

namespace dbgl
{
    /**
     * @brief RenderContext that draws into a window
     */
    class RenderContextGL33Window: public RenderContextGL33
    {
	public:
	    /**
	     * @brief Constructor
	     * @param wnd Wnd to create render context from
	     */
	    RenderContextGL33Window(IWindow* wnd);
	    virtual ~RenderContextGL33Window();
	    virtual int getWidth();
	    virtual int getHeight();

	private:
	    IWindow* m_pWindow = nullptr;
    };
}

#endif /* RENDERCONTEXTGL33WINDOW_H_ */
