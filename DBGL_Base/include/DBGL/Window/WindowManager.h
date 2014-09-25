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

#include <stdlib.h>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "DBGL/Platform/GL/GLProvider.h"
#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    class Window;
    class RenderContext;

    /**
     * @brief Handles all open windows
     * @details Is implemented as a singleton, so the only instance needs to be
     * 		acquired by calling the static get() method.
     */
    class WindowManager
    {
	public:
	    /**
	     * @return The only instance of this class
	     */
	    static WindowManager* get();

	    /**
	     * @brief Constructs a new window
	     * @param title Window title
	     * @param width Window width
	     * @param height Window height
	     * @param fullscreen True if the window shall be opened fullscreen,
	     * 			 otherwise false
	     * @param multisampling Amount of multisampling (0 to disable)
	     * @return A new window of the specified type
	     */
	    template<typename T> T* createWindow(const char* title = "Dragon Blaze Game Library", int width =
		    800, int height = 600, bool fullscreen = false, unsigned int multisampling = 2)
	    {
		auto wnd = new T(nullptr, title, width, height, fullscreen, multisampling);
		s_windows.insert(std::pair<IGL::WindowHandle, Window*>(wnd->m_wndHandle, wnd));
		return wnd;
	    }
	    /**
	     * @brief Updates and renders all windows for one frame
	     */
	    void update();
	    /**
	     * @brief Terminates all windows.
	     * @warning Needs to be called before exiting the program!
	     */
	    void terminate();
	    /**
	     * @return True in case there are still windows open, otherwise false
	     */
	    bool isRunning() const;
	    /**
	     * @return Current time in seconds since the first window has been created
	     */
	    double getTime() const;
	private:
	    WindowManager();
	    ~WindowManager();
	    static void closeCallback(IGL::WindowHandle window);
	    static void focusCallback(IGL::WindowHandle window, int focused);
	    static void iconifiedCallback(IGL::WindowHandle window, int iconified);
	    static void resizeCallback(IGL::WindowHandle window, int width, int height);
	    static void framebufferResizeCallback(IGL::WindowHandle window, int width, int height);
	    static void positionCallback(IGL::WindowHandle window, int xpos, int ypos);
	    static void cursorEnterCallback(IGL::WindowHandle window, int entered);
	    static void cursorCallback(IGL::WindowHandle window, double x, double y);
	    static void scrollCallback(IGL::WindowHandle window, double xOffset, double yOffset);
	    static void inputCallback(IGL::WindowHandle window, Input::Key, Input const& input);

	    void updateHandle(IGL::WindowHandle oldHandle, IGL::WindowHandle newHandle);

	    static std::map<IGL::WindowHandle, Window*> s_windows;
	    static WindowManager s_instance;

	    friend class Window;
    };
}

#endif /* WINDOWMANAGER_H_ */
