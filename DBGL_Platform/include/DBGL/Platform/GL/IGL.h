//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IGL_H_
#define IGL_H_

#include <string>
#include <iostream>
#include <functional>
#include "HandleGenerator.h"

// TODO: DEBUG!
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace dbgl
{
    class IGL
    {
	public:
	    /**
	     * @brief Type of handles used for windows
	     */
	    using WindowHandle = HandleGenerator::Handle;
	    /**
	     * @brief Constant for invalid window handles
	     */
	    static constexpr WindowHandle InvalidWindowHandle = HandleGenerator::InvalidHandle;

	    /**
	     * @brief Function type for error callback
	     */
	    using WndErrorCallback = std::function<void(int,const char*)>;
	    /**
	     * @brief Function type for close callback
	     */
	    using WndCloseCallback = std::function<void(WindowHandle)>;
	    /**
	     * @brief Function type for focus callback
	     */
	    using WndFocusCallback = std::function<void(WindowHandle,int)>;
	    /**
	     * @brief Function type for iconified callback
	     */
	    using WndIconifiedCallback = std::function<void(WindowHandle,int)>;
	    /**
	     * @brief Function type for resize callback
	     */
	    using WndResizeCallback = std::function<void(WindowHandle,int,int)>;
	    /**
	     * @brief Function type for framebuffer resize callback
	     */
	    using WndFramebufferResizeCallback = std::function<void(WindowHandle,int,int)>;
	    /**
	     * @brief Function type for window position callback
	     */
	    using WndWindowPosCallback = std::function<void(WindowHandle,int,int)>;
	    /**
	     * @brief Function type for cursor enter callback
	     */
	    using WndCursorEnterCallback = std::function<void(WindowHandle,int)>;
	    /**
	     * @brief Function type for cursor movement callback
	     */
	    using WndCursorMoveCallback = std::function<void(WindowHandle,double,double)>;
	    /**
	     * @brief Function type for general input callback
	     */
	    using WndInputCallback = std::function<void(WindowHandle,int,int,int)>;
	    /**
	     * @brief Function type for scroll callback
	     */
	    using WndScrollCallback = std::function<void(WindowHandle,double,double)>;

	    /**
	     * @brief Virtual destructor
	     */
	    virtual ~IGL() = default;
	    /**
	     * @brief Retrieves the resolution of the main screen
	     * @param[out] width Screen width
	     * @param[out] height Screen height
	     */
	    virtual void getScreenResolution(int& width, int& height) = 0;
	    /**
	     * @brief Initializes a window
	     * @param title Window title
	     * @param width Window width
	     * @param height Window height
	     * @param fullscreen Specifies if fullscreen
	     * @return Handle to the newly created window
	     */
	    virtual WindowHandle wndInit(std::string title = "Dragon-Blaze-Game-Library", unsigned int width =
		    800, unsigned int height = 600, bool fullscreen = false,
		    unsigned int multisampling = 0) = 0;
	    /**
	     * @brief Show a window
	     * @param wnd Window to show
	     */
	    virtual void wndShow(WindowHandle wnd) = 0;
	    /**
	     * @brief Hide a window
	     * @param wnd Window to hide
	     */
	    virtual void wndHide(WindowHandle wnd) = 0;
	    /**
	     * @brief Closes a window
	     * @param wnd Window to close
	     */
	    virtual void wndClose(WindowHandle wnd) = 0;
	    /**
	     * @brief Destroys a window without calling any events
	     * @param wnd Window to destroy
	     */
	    virtual void wndDestroy(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is in focus
	     * @param wnd Window to check
	     * @return True in case the window is in focus, otherwise false
	     */
	    virtual bool wndCheckFocus(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is iconified
	     * @param wnd Window to check
	     * @return True in case the window is iconified, otherwise false
	     */
	    virtual bool wndCheckIconified(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is visible
	     * @param wnd Window to check
	     * @return True in case the window is visible, otherwise false
	     */
	    virtual bool wndCheckVisible(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window is resizable
	     * @param wnd Window to check
	     * @return True in case the window is resizable, otherwise false
	     */
	    virtual bool wndCheckResizable(WindowHandle wnd) = 0;
	    /**
	     * @brief Checks if a window has decorations
	     * @param wnd Window to check
	     * @return True in case the window has decorations, otherwise false
	     */
	    virtual bool wndCheckDecorations(WindowHandle wnd) = 0;
	    /**
	     * @brief Modifies the title of a window
	     * @param wnd Window to set title for
	     * @param title New title
	     */
	    virtual void wndSetTitle(WindowHandle wnd, std::string const& title) = 0;
	    /**
	     * @brief Retrieves the size of a window
	     * @param wnd Window to get width from
	     * @param[out] width The window's width
	     * @param[out] height The window's height
	     */
	    virtual void wndGetSize(WindowHandle wnd, int& width, int& height) = 0;
	    /**
	     * @brief Modifies the size of a window
	     * @param wnd Window to modify
	     * @param width New width
	     * @param height New height
	     */
	    virtual void wndSetSize(WindowHandle wnd, int width, int height) = 0;
	    /**
	     * @brief Retrieves the frame size of a window
	     * @param wnd Window to get frame size from
	     * @param[out] width Frame width
	     * @param[out] height Frame height
	     */
	    virtual void wndGetFrameSize(WindowHandle wnd, int& width, int& height) = 0;
	    /**
	     * @brief Retrieves the coordinates of a window
	     * @param wnd Window to get coordinates from
	     * @param[out] x X coordinate
	     * @param[out] y Y coordinate
	     */
	    virtual void wndGetPos(WindowHandle wnd, int& x, int& y) = 0;
	    /**
	     * @brief Modifies the coordinates of a window
	     * @param wnd Window to modify
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    virtual void wndSetPos(WindowHandle wnd, int x, int y) = 0;
	    /**
	     * @brief Makes a window current
	     * @param wnd Window to make current
	     */
	    virtual void wndMakeCurrent(WindowHandle wnd) = 0;
	    /**
	     * @brief Retrieves the current cursor coordinates within a window
	     * @param wnd Window to check
	     * @param x[out] X coordinate
	     * @param y[out] Y coordinate
	     */
	    virtual void wndGetCursorPos(WindowHandle wnd, double& x, double& y) = 0;
	    /**
	     * @brief Modifies the cursor coordinates within a window
	     * @param wnd Window to modify
	     * @param x[in] New x coordinate
	     * @param y[in] New y coordinate
	     */
	    virtual void wndSetCursorPos(WindowHandle wnd, double x, double y) = 0;
	    /**
	     * @brief Swaps the render buffers of a window
	     * @param wnd Window to modify
	     */
	    virtual void wndSwapBuffers(WindowHandle wnd) = 0;
	    /**
	     * @brief Set a callback to call on errors regarding windows
	     * @param callback Callback function
	     */
	    virtual void wndSetErrorCallback(WndErrorCallback callback) = 0;
	    /**
	     * @brief Set a callback that is called when a window is closed
	     * @param wnd Wnd to set the callback for
	     * @param callback Callback function to call on close events
	     */
	    virtual void wndSetCloseCallback(WindowHandle wnd, WndCloseCallback callback) = 0;
	    // TODO: Callbacks

	    //TODO: DEBUG!
	    virtual GLFWwindow* getBasePointer(WindowHandle wnd) = 0;

	protected:
	    IGL()
	    {
		static bool initialized { false };
		if(initialized)
		    throw("Can't have more than one graphics layer.");
		initialized = true;
	    }
	private:
	    IGL(IGL const&); // Disallow copying
	    IGL& operator=(IGL const& other);
    };
}

#endif /* IGL_H_ */
