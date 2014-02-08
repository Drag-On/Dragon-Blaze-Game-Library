//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <map>//#include <unordered_map>#include "GLFW/glfw3.h"#include "AbstractWindow.h"
#include "Log/Log.h"

namespace dbgl
{
    class AbstractWindow;

    class WindowManager
    {
	    friend class AbstractWindow; // For creation/destruction notification

	public:
	    static WindowManager* get();
	private:
	    WindowManager();
	    ~WindowManager();
	    static void closeCallback(GLFWwindow* window);
	    static void focusCallback(GLFWwindow* window, int focused);
	    static void iconifiedCallback(GLFWwindow* window, int iconified);
	    static void refreshCallback(GLFWwindow* window);
	    static void sizeCallback(GLFWwindow* window, int width, int height);
	    static void framebufferSizeCallback(GLFWwindow* window, int width,
		    int height);
	    static void positionCallback(GLFWwindow* window, int xpos,
		    int ypos);
	    static void characterCallback(GLFWwindow* window,
		    unsigned int codepoint);
	    static void cursorEnterCallback(GLFWwindow* window, int entered);
	    static void cursorCallback(GLFWwindow* window, double x, double y);
	    static void mouseButtonCallback(GLFWwindow* window, int button,
		    int action, int mods);
	    static void scrollCallback(GLFWwindow* window, double xOffset,
		    double yOffset);
	    static void keyCallback(GLFWwindow* window, int key, int scancode,
		    int action, int mods);
	    //static void monitorCallback(GLFWmonitor* monitor, int event);

	    void add(GLFWwindow* wndH, AbstractWindow* window);
	    void remove(GLFWwindow* wndH);


	    static std::map<GLFWwindow*, AbstractWindow*> windows; // TODO: unordered_map?
	    static WindowManager instance;
    };
}

#endif /* WINDOWMANAGER_H_ */
