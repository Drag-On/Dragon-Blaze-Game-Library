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
#include <set>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DBGL/Math/Vector3.h"
#include "DBGL/System/Event/Event.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Bitmask/Bitmask.h"
#include "DBGL/Rendering/RenderContext.h"
#include "WindowManager.h"

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
	    struct CloseEventArgs {};
	    struct FocusEventArgs {bool focused;};
	    struct IconifiedEventArgs {bool iconified;};
	    struct RefreshEventArgs {};
	    struct ResizeEventArgs {int width; int height;};
	    struct FramebufferResizeEventArgs {int width; int height;};
	    struct PositionEventArgs {int x; int y;};
	    struct CharacterEventArgs {unsigned int codepoint;};
	    struct CursorEnterEventArgs {bool entered;};
	    struct CursorEventArgs {double x; double y;};
	    struct MouseButtonEventArgs {int button; int action; int mods;};
	    struct ScrollEventArgs {double xOffset; double yOffset;};
	    struct KeyEventArgs {int key; int scancode; int action; int mods;};
	    struct UpdateEventArgs {double deltaTime;};
	    struct RenderEventArgs {const RenderContext* rc;};

	    using CloseCallbackType = std::function<void(CloseEventArgs const&)>;
	    using FocusCallbackType = std::function<void(FocusEventArgs const&)>;
	    using IconifiedCallbackType = std::function<void(IconifiedEventArgs const&)>;
	    using RefreshCallbackType = std::function<void(RefreshEventArgs const&)>;
	    using ResizeCallbackType = std::function<void(ResizeEventArgs const&)>;
	    using FramebufferResizeCallbackType = std::function<void(FramebufferResizeEventArgs const&)>;
	    using PositionCallbackType = std::function<void(PositionEventArgs const&)>;
	    using CharacterCallbackType = std::function<void(CharacterEventArgs const&)>;
	    using CursorEnterCallbackType = std::function<void(CursorEnterEventArgs const&)>;
	    using CursorCallbackType = std::function<void(CursorEventArgs const&)>;
	    using MouseButtonCallbackType = std::function<void(MouseButtonEventArgs const&)>;
	    using ScrollCallbackType = std::function<void(ScrollEventArgs const&)>;
	    using KeyCallbackType = std::function<void(KeyEventArgs const&)>;
	    using UpdateCallbackType = std::function<void(UpdateEventArgs const&)>;
	    using RenderCallbackType = std::function<void(RenderEventArgs const&)>;

	    using CloseEventType = Event<CloseCallbackType, CloseEventArgs>;
	    using FocusEventType = Event<FocusCallbackType, FocusEventArgs>;
	    using IconifiedEventType = Event<IconifiedCallbackType, IconifiedEventArgs>;
	    using RefreshEventType = Event<RefreshCallbackType, RefreshEventArgs>;
	    using ResizeEventType = Event<ResizeCallbackType, ResizeEventArgs>;
	    using FramebufferResizeEventType = Event<FramebufferResizeCallbackType, FramebufferResizeEventArgs>;
	    using PositionEventType = Event<PositionCallbackType, PositionEventArgs>;
	    using CharacterEventType = Event<CharacterCallbackType, CharacterEventArgs>;
	    using CursorEnterEventType = Event<CursorEnterCallbackType, CursorEnterEventArgs>;
	    using CursorEventType = Event<CursorCallbackType, CursorEventArgs>;
	    using MouseButtonEventType = Event<MouseButtonCallbackType, MouseButtonEventArgs>;
	    using ScrollEventType = Event<ScrollCallbackType, ScrollEventArgs>;
	    using KeyEventType = Event<KeyCallbackType, KeyEventArgs>;
	    using UpdateEventType = Event<UpdateCallbackType, UpdateEventArgs>;
	    using RenderEventType = Event<RenderCallbackType, RenderEventArgs>;

	    // Constants used for bitmasks
	    static const int DepthTest = 1 << 0;
	    static const int AlphaBlend = 1 << 1;
	    static const int FaceCulling = 1 << 2;

	    /**
	     * @brief Frees all memory allocated to this window
	     */
	    virtual ~Window();
	    /**
	     * @brief Initializes the window
	     * @warning Must be called exactly once!
	     * @param options Bitmask indicating which options are set. Accounts for
	     * 		      DepthTest, AlphaBlend & FaceCulling
	     */
	    void init(Bitmask<> options = DepthTest | FaceCulling);
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
	    CloseEventType::DelegatePtr addCloseCallback(
		    CloseCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for close events
	     * @param callback Function to be called when this window is getting closed
	     */
	    bool removeCloseCallback(
		    CloseEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    FocusEventType::DelegatePtr addFocusCallback(
		    FocusCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    bool removeFocusCallback(
		    FocusEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    IconifiedEventType::DelegatePtr addIconifiedCallback(
		    IconifiedCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    bool removeIconifiedCallback(
		    IconifiedEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    RefreshEventType::DelegatePtr addRefreshCallback(
		    RefreshCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    bool removeRefreshCallback(
		    RefreshEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    ResizeEventType::DelegatePtr addResizeCallback(
		    ResizeCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    bool removeResizeCallback(
		    ResizeEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for framebuffer resize events
	     * @param callback Function to be called when this window's framebuffer needs a resize
	     */
	    FramebufferResizeEventType::DelegatePtr addFramebufferResizeCallback(
		    FramebufferResizeCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for framebuffer resize events
	     * @param callback Function to be called when this window's framebuffer needs a resize
	     */
	    bool removeFramebufferResizeCallback(
		    FramebufferResizeEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    PositionEventType::DelegatePtr addPositionCallback(
		    PositionCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    bool removePositionCallback(
		    PositionEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for unicode character events
	     * @param callback Function to be called when a character is typed into this window
	     */
	    CharacterEventType::DelegatePtr addCharacterCallback(
		    CharacterCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for unicode character events
	     * @param callback Function to be called when a character is typed into this window
	     */
	    bool removeCharacterCallback(
		    CharacterEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    CursorEnterEventType::DelegatePtr addCursorEnterCallback(
		    CursorEnterCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    bool removeCursorEnterCallback(
		    CursorEnterEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    CursorEventType::DelegatePtr addCursorCallback(
		    CursorCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    bool removeCursorCallback(
		    CursorEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    MouseButtonEventType::DelegatePtr addMouseButtonCallback(
		    MouseButtonCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    bool removeMouseButtonCallback(
		    MouseButtonEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    ScrollEventType::DelegatePtr addScrollCallback(
		    ScrollCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    bool removeScrollCallback(
		    ScrollEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    KeyEventType::DelegatePtr addKeyCallback(
		    KeyCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    bool removeKeyCallback(
		    KeyEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for update events
	     * @param callback Function to be called when the window is being updated
	     */
	    UpdateEventType::DelegatePtr addUpdateCallback(
		    UpdateCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for update events
	     * @param callback Function to be called when the window is being updated
	     */
	    bool removeUpdateCallback(
		    UpdateEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for render events
	     * @param callback Function to be called when the window is being rendered
	     */
	    RenderEventType::DelegatePtr addRenderCallback(
		    RenderCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for render events
	     * @param callback Function to be called when the window is being rendered
	     */
	    bool removeRenderCallback(
		    RenderEventType::DelegatePtr const& callback);
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
	    /**
	     * @brief Constructs a window
	     * @param share Window to share resources with or NULL if none
	     * @param title Title of the window
	     * @param width Width of the rendering plane
	     * @param height Height of the rendering plane
	     * @param fullscreen Indicates if it is opened to fullscreens
	     */
	    Window(GLFWwindow* share, const char* title = "Dragon Blaze Game Library", int width =
		    800, int height = 600, bool fullscreen = false);
	    /**
	     * @brief Removes the current render context from the window and applies a new one
	     */
	    virtual void createRenderContext();
	    /**
	     * @brief Needed to update render context on window resize
	     * @param args New size
	     */
	    void framebufferResizeCallback(FramebufferResizeEventArgs args);

	    /**
	     * GLFW window handle
	     */
	    GLFWwindow* m_pWndHandle = NULL;
	    RenderContext* m_pRenderContext = NULL;

	private:
	    CloseEventType m_closeCallbacks;
	    FocusEventType m_focusCallbacks;
	    IconifiedEventType m_iconifiedCallbacks;
	    RefreshEventType m_refreshCallbacks;
	    ResizeEventType m_resizeCallbacks;
	    FramebufferResizeEventType m_framebufferResizeCallbacks;
	    PositionEventType m_positionCallbacks;
	    CharacterEventType m_characterCallbacks;
	    CursorEnterEventType m_cursorEnterCallbacks;
	    CursorEventType m_cursorCallbacks;
	    MouseButtonEventType m_mouseButtonCallbacks;
	    ScrollEventType m_scrollCallbacks;
	    KeyEventType m_keyCallbacks;
	    UpdateEventType m_updateCallbacks;
	    RenderEventType m_renderCallbacks;

	    std::string m_title;
	    bool m_isFullscreen;
	    unsigned int m_fullscreenWidth, m_fullscreenHeight; // Resolution for full screen
	    unsigned int m_windowedWidth, m_windowedHeight; // Resolution for window
	    unsigned int m_windowedX, m_windowedY; // Last window position before entering fullscreen mode
	    double m_deltaTime = 0, m_lastTime = 0; // Time since last frame
	    Vector3<GLclampf> m_clearColor = Vector3<GLclampf>(0, 0, 0);
	    GLuint m_vertexArrayId;

	    friend class WindowManager;
    };
}

#endif /* WINDOW_H_ */
