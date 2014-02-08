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

#include "AbstractWindow.h"

namespace dbgl
{
    class SimpleWindow: public AbstractWindow
    {
	public:
	    SimpleWindow();
	    ~SimpleWindow();
	    virtual void update();
	    virtual void render();

	protected:
	    // Callbacks
	    virtual void closeCallback();
	    virtual void focusCallback(int focused);
	    virtual void iconifiedCallback(int iconified);
	    virtual void refreshCallback();
	    virtual void sizeCallback(int width, int height);
	    virtual void framebufferSizeCallback(int width, int height);
	    virtual void windowPosCallback(int xpos, int ypos);
	    virtual void characterCallback(unsigned int codepoint);
	    virtual void cursorEnterCallback(int entered);
	    virtual void cursorCallback(double x, double y);
	    virtual void mouseButtonCallback(int button, int action, int mods);
	    virtual void scrollCallback(double xOffset, double yOffset);
	    virtual void keyCallback(int key, int scancode, int action,
		    int mods);

	private:
    };
}

#endif /* SIMPLEWINDOW_H_ */
