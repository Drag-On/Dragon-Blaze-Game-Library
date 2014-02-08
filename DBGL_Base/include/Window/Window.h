//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdlib.h>
#include "GLFW/glfw3.h"
#include "Log/Log.h"

namespace dbgl
{
    class Window
    {
	public:
	    Window();
	    ~Window();
	    void open();
	private:
	    static void errorCallback(int error, const char* description);

	    GLFWwindow* _pWndHandle = NULL;
    };
}

#endif /* WINDOW_H_ */
