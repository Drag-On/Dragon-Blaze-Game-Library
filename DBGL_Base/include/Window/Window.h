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
    using CloseCallbackType = std::function<void()>;
    using FocusCallbackType = std::function<void(int)>;
    using IconifiedCallbackType = std::function<void(int)>;
    using RefreshCallbackType = std::function<void()>;
    using ResizeCallbackType = std::function<void(int, int)>;
    using FramebufferResizeCallbackType = std::function<void(int, int)>;
    using PositionCallbackType = std::function<void(int, int)>;
    using CharacterCallbackType = std::function<void(unsigned int)>;
    using CursorEnterCallbackType = std::function<void(int)>;
    using CursorCallbackType = std::function<void(double, double)>;
    using MouseButtonCallbackType = std::function<void(int, int, int)>;
    using ScrollCallbackType = std::function<void(double, double)>;
    using KeyCallbackType = std::function<void(int, int, int, int)>;
    using UpdateCallbackType = std::function<void(double)>;
    using RenderCallbackType = std::function<void(const RenderContext* rc)>;

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
	     * @param alphaBlend Indicates if alpha blending should be enabled
	     * @param faceCulling Indicates if faces that are not facing the camera
	     * 	      should be culled
	     */
	    void init(bool depthTest = true, bool alphaBlend = false,
		    bool faceCulling = true);
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
	     * @brief Grants access to the current cursor position inside of the window
	     * @param x X coordinate is stored here
	     * @param y Y coordinate is stored here
	     */
	    void getCursorPos(double& x, double& y) const;
	    /**
	     * @brief Changes the cursor position inside of the window
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    void setCursorPos(double x, double y);
	    /**
	     * @brief Checks a mouse button's state
	     * @param button Button to check
	     * @return GLFW_PRESS or GLFW_RELEASE
	     */
	    int getButton(int button) const;
	    /**
	     * @brief Checks a key's state
	     * @param key Key to check
	     * @return GLFW_PRESS or GLFW_RELEASE
	     */
	    int getKey(int key) const;
	    /**
	     * @brief Registers a function as callback for close events
	     * @param callback Function to be called when this window is getting closed
	     */
	    void addCloseCallback(CloseCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    void addFocusCallback(FocusCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    void addIconifiedCallback(IconifiedCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    void addRefreshCallback(RefreshCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    void addResizeCallback(ResizeCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for framebuffer resize events
	     * @param callback Function to be called when this window's framebuffer needs a resize
	     */
	    void addFramebufferResizeCallback(
		    FramebufferResizeCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    void addPositionCallback(PositionCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for unicode character events
	     * @param callback Function to be called when a character is typed into this window
	     */
	    void addCharacterCallback(CharacterCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    void addCursorEnterCallback(
		    CursorEnterCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    void addCursorCallback(CursorCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    void addMouseButtonCallback(
		    MouseButtonCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    void addScrollCallback(ScrollCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    void addKeyCallback(KeyCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for update events
	     * @param callback Function to be called when the window is being updated
	     */
	    void addUpdateCallback(UpdateCallbackType const& callback);
	    /**
	     * @brief Registers a function as callback for render events
	     * @param callback Function to be called when the window is being rendered
	     */
	    void addRenderCallback(RenderCallbackType const& callback);
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
	    Window(GLFWwindow* share, const char* title, int width, int height,
		    bool fullscreen);

	    /**
	     * GLFW window handle
	     */
	    GLFWwindow* _pWndHandle = NULL;
	    RenderContext* _pRenderContext;

	private:
	    CloseCallbackType _closeCallback;
	    FocusCallbackType _focusCallback;
	    IconifiedCallbackType _iconifiedCallback;
	    RefreshCallbackType _refreshCallback;
	    ResizeCallbackType _resizeCallback;
	    FramebufferResizeCallbackType _framebufferResizeCallback;
	    PositionCallbackType _positionCallback;
	    CharacterCallbackType _characterCallback;
	    CursorEnterCallbackType _cursorEnterCallback;
	    CursorCallbackType _cursorCallback;
	    MouseButtonCallbackType _mouseButtonCallback;
	    ScrollCallbackType _scrollCallback;
	    KeyCallbackType _keyCallback;
	    UpdateCallbackType _updateCallback;
	    RenderCallbackType _renderCallback;

	    std::string _title;
	    bool _isFullscreen;
	    unsigned int _fullscreenWidth, _fullscreenHeight; // Resolution for full screen
	    unsigned int _windowedWidth, _windowedHeight; // Resolution for window
	    unsigned int _windowedX, _windowedY; // Last window position before entering fullscreen mode
	    double _deltaTime = 0, _lastTime = 0; // Time since last frame
	    Vector3<GLclampf> _clearColor = Vector3<GLclampf>(0, 0, 0);
	    GLuint _vertexArrayId;

	    friend class WindowManager;
    };
}

#endif /* WINDOW_H_ */
