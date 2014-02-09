//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ABSTRACTWINDOW_H_
#define ABSTRACTWINDOW_H_

#include <stdlib.h>
#include <string>
#include <functional>
#include "GLFW/glfw3.h"
#include "Log/Log.h"
#include "WindowManager.h"

namespace dbgl
{
    /**
     * @brief Base class for all windows
     * @details Windows need to be constructed by the @see WindowManager and
     * 		will automatically taken care of by it. This includes freeing
     * 		all memory after the window has been closed.
     * 		All classes that derive from AbstractWindow need to add
     * 		WindowManager as their friend, otherwise construction will
     * 		not work properly.
     */
    class AbstractWindow
    {
	public:
	    /**
	     * @brief Frees all memory allocated to this window
	     */
	    virtual ~AbstractWindow();
	    /**
	     * @brief Makes this window show
	     */
	    virtual void show() final;
	    /**
	     * @brief Hides the window
	     */
	    virtual void hide() final;
	    /**
	     * @brief Closes the window permanently
	     */
	    virtual void close() final;
	    /**
	     * @return True in case the window is currently in focus, otherwise false
	     */
	    virtual bool hasFocus() final;
	    /**
	     * @return True in case the window is currently iconified, otherwise false
	     */
	    virtual bool isIconified() final;
	    /**
	     * @return True in case the window is currently visible, otherwise false
	     */
	    virtual bool isVisible() final;
	    /**
	     * @return True in case the window is resizable, otherwise false
	     */
	    virtual bool isResizable() final;
	    /**
	     * @return True in case the window has decorations (i.e. borders etc.),
	     * 		otherwise false
	     */
	    virtual bool isDecorated() final;
	    /**
	     * @return The window's title
	     */
	    virtual const char* getTitle() final;
	    /**
	     * @param title The new title to set
	     */
	    virtual void setTitle(const char* title) final;
	    /**
	     * @return Width of the window in screen dimensions
	     */
	    virtual int getWidth() final;
	    /**
	     * @return Height of the window in screen dimensions
	     */
	    virtual int getHeight() final;
	    /**
	     * @brief Sets a new window size
	     * @param width New width
	     * @param height New height
	     */
	    virtual void setSize(int width, int height) final;
	    /**
	     * @return Width of the actual rendering space in pixels
	     */
	    virtual int getFrameWidth() final;
	    /**
	     * @return Height of the actual rendering space in pixels
	     */
	    virtual int getFrameHeight() final;
	    /**
	     * @return X coordinate on screen
	     */
	    virtual int getX() final;
	    /**
	     * @return Y coordinate on screen
	     */
	    virtual int getY() final;
	    /**
	     * @brief Moves the window to a new location on screen
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    virtual void setPos(int x, int y) final;
	    /**
	     * @return True in case the window is in fullscreen mode,
	     * 		otherwise false
	     */
	    virtual bool isFullscreen() final;
	    /**
	     * @brief Provides the possibility to switch between fullscreen
	     * 	      and window mode
	     * @param fullscreen Indicates if window should switch to fullscreen
	     * 			 or back to window
	     */
	    virtual void setFullscreen(bool fullscreen) final;
	    /**
	     * @brief Registers a function as callback for close events
	     * @param callback Function to be called when this window is getting closed
	     */
	    virtual void addCloseCallback(std::function<void()> callback) final;
	    /**
	     * @brief Registers a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    virtual void addFocusCallback(
		    std::function<void(int)> callback) final;
	    /**
	     * @brief Registers a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    virtual void addIconifiedCallback(
		    std::function<void(int)> callback) final;
	    /**
	     * @brief Registers a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    virtual void addRefreshCallback(
		    std::function<void()> callback) final;
	    /**
	     * @brief Registers a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    virtual void addResizeCallback(
		    std::function<void(int, int)> callback) final;
	    /**
	     * @brief Registers a function as callback for framebuffer resize events
	     * @param callback Function to be called when this window's framebuffer needs a resize
	     */
	    virtual void addFramebufferResizeCallback(
		    std::function<void(int, int)> callback) final;
	    /**
	     * @brief Registers a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    virtual void addPositionCallback(
		    std::function<void(int, int)> callback) final;
	    /**
	     * @brief Registers a function as callback for unicode character events
	     * @param callback Function to be called when a character is typed into this window
	     */
	    virtual void addCharacterCallback(
		    std::function<void(unsigned int)> callback) final;
	    /**
	     * @brief Registers a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    virtual void addCursorEnterCallback(
		    std::function<void(int)> callback) final;
	    /**
	     * @brief Registers a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    virtual void addCursorCallback(
		    std::function<void(double, double)> callback) final;
	    /**
	     * @brief Registers a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    virtual void addMouseButtonCallback(
		    std::function<void(int, int, int)> callback) final;
	    /**
	     * @brief Registers a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    virtual void addScrollCallback(
		    std::function<void(double, double)> callback) final;
	    /**
	     * @brief Registers a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    virtual void addKeyCallback(
		    std::function<void(int, int, int, int)> callback) final;
	    /**
	     * @brief Gets called once a frame before @see update
	     */
	    virtual void preUpdate();
	    /**
	     * @brief Gets called once a frame and should update everything
	     */
	    virtual void update() = 0;
	    /**
	     * @brief Gets called once a frame after @see update
	     */
	    virtual void postUpdate();
	    /**
	     * @brief Gets called once a frame before @see render
	     */
	    virtual void preRender();
	    /**
	     * @brief Gets called once a frame and should render everything
	     */
	    virtual void render() = 0;
	    /**
	     * @brief Gets called once a frame after @see update
	     */
	    virtual void postRender();

	protected:
	    // Constructors
	    /**
	     * @brief Constructs a window of size 800x600 with a standard title
	     */
	    AbstractWindow();
	    /**
	     * @brief Constructs a window of size 800x600
	     * @param title Title of the window
	     */
	    AbstractWindow(const char* title);
	    /**
	     * @brief Constructs a window
	     * @param title Title of the window
	     * @param width Width of the rendering plane
	     * @param height Height of the rendering plane
	     */
	    AbstractWindow(const char* title, int width, int height);
	    /**
	     * @brief Constructs a window
	     * @param title Title of the window
	     * @param width Width of the rendering plane
	     * @param height Height of the rendering plane
	     * @param fullscreen Indicates if it is opened to fullscreens
	     */
	    AbstractWindow(const char* title, int width, int height,
		    bool fullscreen);


	    /**
	     * GLFW window handle
	     */
	    GLFWwindow* _pWndHandle = NULL;

	private:
	    static void errorCallback(int error, const char* description);

	    std::function<void()> _closeCallback;
	    std::function<void(int)> _focusCallback;
	    std::function<void(int)> _iconifiedCallback;
	    std::function<void()> _refreshCallback;
	    std::function<void(int, int)> _resizeCallback;
	    std::function<void(int, int)> _framebufferResizeCallback;
	    std::function<void(int, int)> _positionCallback;
	    std::function<void(unsigned int)> _characterCallback;
	    std::function<void(int)> _cursorEnterCallback;
	    std::function<void(double, double)> _cursorCallback;
	    std::function<void(int, int, int)> _mouseButtonCallback;
	    std::function<void(double, double)> _scrollCallback;
	    std::function<void(int, int, int, int)> _keyCallback;

	    std::string _title;
	    bool _isFullscreen;
	    unsigned int _fullscreenWidth, _fullscreenHeight; // Resolution for full screen
	    unsigned int _windowedWidth, _windowedHeight; // Resolution for window

	    friend class WindowManager;
    };
}

#endif /* ABSTRACTWINDOW_H_ */
