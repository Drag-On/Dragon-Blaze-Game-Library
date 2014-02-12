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
#include <string>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Math/Vector3.h"
#include "Log/Log.h"
#include "WindowManager.h"
#include "Rendering/RenderContext.h"

namespace dbgl
{
    /**
     * @brief Base class for all windows
     * @details Windows need to be constructed by the @see WindowManager and
     * 		will automatically taken care of by it. This includes freeing
     * 		all memory after the window has been closed.
     * 		All classes that derive from Window need to add
     * 		WindowManager as their friend, otherwise construction will
     * 		not work properly.
     */
    class Window
    {
	public:
	    /**
	     * @brief Frees all memory allocated to this window
	     */
	    virtual ~Window();
	    /**
	     * @brief Initializes the window
	     * @warning Must be called exactly once!
	     * @param depthTest Indicates if depth testing should be enabled
	     * @param faceCulling Indicates if faces that are not facing the camera
	     * 	      should be culled
	     */
	    void init(bool depthTest = true, bool faceCulling = true);
	    /**
	     * @brief Makes this window show
	     */
	    void show();
	    /**
	     * @brief Hides the window
	     */
	    void hide();
	    /**
	     * @brief Closes the window permanently
	     */
	    void close();
	    /**
	     * @return True in case the window is currently in focus, otherwise false
	     */
	    bool hasFocus() const;
	    /**
	     * @return True in case the window is currently iconified, otherwise false
	     */
	    bool isIconified() const;
	    /**
	     * @return True in case the window is currently visible, otherwise false
	     */
	    bool isVisible() const;
	    /**
	     * @return True in case the window is resizable, otherwise false
	     */
	    bool isResizable() const;
	    /**
	     * @return True in case the window has decorations (i.e. borders etc.),
	     * 		otherwise false
	     */
	    bool isDecorated() const;
	    /**
	     * @return The window's title
	     */
	    const char* getTitle() const;
	    /**
	     * @param title The new title to set
	     */
	    void setTitle(const char* title);
	    /**
	     * @return Width of the window in screen dimensions
	     */
	    int getWidth() const;
	    /**
	     * @return Height of the window in screen dimensions
	     */
	    int getHeight() const;
	    /**
	     * @brief Sets a new window size
	     * @param width New width
	     * @param height New height
	     */
	    void setSize(int width, int height);
	    /**
	     * @return Width of the actual rendering space in pixels
	     */
	    int getFrameWidth() const;
	    /**
	     * @return Height of the actual rendering space in pixels
	     */
	    int getFrameHeight() const;
	    /**
	     * @return X coordinate on screen
	     */
	    int getX() const;
	    /**
	     * @return Y coordinate on screen
	     */
	    int getY() const;
	    /**
	     * @brief Moves the window to a new location on screen
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    void setPos(int x, int y);
	    /**
	     * @return True in case the window is in fullscreen mode,
	     * 		otherwise false
	     */
	    bool isFullscreen() const;
	    /**
	     * @brief Provides the possibility to switch between fullscreen
	     * 	      and window mode
	     * @param fullscreen Indicates if window should switch to fullscreen
	     * 			 or back to window
	     */
	    void setFullscreen(bool fullscreen);
	    /**
	     * @return The currently set clear color
	     */
	    Vec3f getClearColor() const;
	    /**
	     * @param color New clear color to use
	     */
	    void setClearColor(Vector3<GLclampf> const& color);
	    /**
	     * @return A pointer to the used render context
	     */
	    RenderContext* getRenderContext() const;
	    /**
	     * @brief Makes this window the current one
	     */
	    void makeCurrent();
	    /**
	     * @brief Registers a function as callback for close events
	     * @param callback Function to be called when this window is getting closed
	     */
	    void addCloseCallback(std::function<void()> const& callback);
	    /**
	     * @brief Registers a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    void addFocusCallback(std::function<void(int)> const& callback);
	    /**
	     * @brief Registers a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    void addIconifiedCallback(std::function<void(int)> const& callback);
	    /**
	     * @brief Registers a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    void addRefreshCallback(std::function<void()> const& callback);
	    /**
	     * @brief Registers a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    void addResizeCallback(
		    std::function<void(int, int)> const& callback);
	    /**
	     * @brief Registers a function as callback for framebuffer resize events
	     * @param callback Function to be called when this window's framebuffer needs a resize
	     */
	    void addFramebufferResizeCallback(
		    std::function<void(int, int)> const& callback);
	    /**
	     * @brief Registers a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    void addPositionCallback(
		    std::function<void(int, int)> const& callback);
	    /**
	     * @brief Registers a function as callback for unicode character events
	     * @param callback Function to be called when a character is typed into this window
	     */
	    void addCharacterCallback(
		    std::function<void(unsigned int)> const& callback);
	    /**
	     * @brief Registers a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    void addCursorEnterCallback(
		    std::function<void(int)> const& callback);
	    /**
	     * @brief Registers a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    void addCursorCallback(
		    std::function<void(double, double)> const& callback);
	    /**
	     * @brief Registers a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    void addMouseButtonCallback(
		    std::function<void(int, int, int)> const& callback);
	    /**
	     * @brief Registers a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    void addScrollCallback(
		    std::function<void(double, double)> const& callback);
	    /**
	     * @brief Registers a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    void addKeyCallback(
		    std::function<void(int, int, int, int)> const& callback);
	    /**
	     * @brief Registers a function as callback for update events
	     * @param callback Function to be called when the window is being updated
	     */
	    void addUpdateCallback(std::function<void()> const& callback);
	    /**
	     * @brief Registers a function as callback for render events
	     * @param callback Function to be called when the window is being rendered
	     */
	    void addRenderCallback(
		    std::function<void(const RenderContext*)> const& callback);
	    /**
	     * @brief Gets called once a frame before @see update
	     */
	    virtual void preUpdate();
	    /**
	     * @brief Gets called once a frame and should update everything
	     */
	    virtual void update();
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
	    virtual void render();
	    /**
	     * @brief Gets called once a frame after @see update
	     */
	    virtual void postRender();

	protected:
	    // Constructors
	    /**
	     * @brief Constructs a window of size 800x600 with a standard title
	     * @param share Window to share resources with or NULL if none
	     */
	    Window(GLFWwindow* share);
	    /**
	     * @brief Constructs a window of size 800x600
	     * @param share Window to share resources with or NULL if none
	     * @param title Title of the window
	     */
	    Window(GLFWwindow* share, const char* title);
	    /**
	     * @brief Constructs a window
	     * @param share Window to share resources with or NULL if none
	     * @param title Title of the window
	     * @param width Width of the rendering plane
	     * @param height Height of the rendering plane
	     */
	    Window(GLFWwindow* share, const char* title, int width, int height);
	    /**
	     * @brief Constructs a window
	     * @param share Window to share resources with or NULL if none
	     * @param title Title of the window
	     * @param width Width of the rendering plane
	     * @param height Height of the rendering plane
	     * @param fullscreen Indicates if it is opened to fullscreens
	     */
	    Window(GLFWwindow* share, const char* title, int width, int height, bool fullscreen);

	    /**
	     * GLFW window handle
	     */
	    GLFWwindow* _pWndHandle = NULL;

	private:
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
	    std::function<void()> _updateCallback;
	    std::function<void(const RenderContext* rc)> _renderCallback;

	    std::string _title;
	    bool _isFullscreen;
	    unsigned int _fullscreenWidth, _fullscreenHeight; // Resolution for full screen
	    unsigned int _windowedWidth, _windowedHeight; // Resolution for window
	    unsigned int _windowedX, _windowedY; // Last window position before entering fullscreen mode
	    Vector3<GLclampf> _clearColor = Vector3<GLclampf>(0.1, 0.1, 0.1);
	    RenderContext* _pRenderContext;
	    GLuint _vertexArrayId;

	    friend class WindowManager;
    };
}

#endif /* WINDOW_H_ */
