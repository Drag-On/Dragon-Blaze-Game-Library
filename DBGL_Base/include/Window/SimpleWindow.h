//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SIMPLEWINDOW_H_
#define SIMPLEWINDOW_H_

#include "Window.h"

namespace dbgl
{
    /**
     * @brief Simple default window with often used properties
     */
    class SimpleWindow: public Window
    {
	public:
	    /**
	     * @brief Frees all memory allocated to this window
	     */
	    ~SimpleWindow();

	protected:
	    // Constructors
	    SimpleWindow();
	    SimpleWindow(const char* title);
	    SimpleWindow(const char* title, int width, int height);
	    SimpleWindow(const char* title, int width, int height,
		    bool fullscreen);
	    // Callbacks
	    virtual void framebufferResizeCallback(int width, int height);
	    virtual void keyCallback(int key, int scancode, int action,
		    int mods);

	private:
	    friend class WindowManager;
    };
}

#endif /* SIMPLEWINDOW_H_ */
