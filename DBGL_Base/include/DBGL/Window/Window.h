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

#include <string>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DBGL/Math/Vector3.h"
#include "DBGL/System/Event/Event.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Bitmask/Bitmask.h"
#include "DBGL/Rendering/RenderContext.h"
#include "WindowManager.h"
#include "Input.h"

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
	     * @brief Arguments passed on a close event
	     */
	    struct CloseEventArgs
	    {
	    };
	    /**
	     * @brief Arguments passed on a focus event
	     */
	    struct FocusEventArgs
	    {
		    /**
		     * @brief True in case the window is in focus now, otherwise false
		     */
		    bool focused;
	    };
	    /**
	     * @brief Arguments passed on a iconified event
	     */
	    struct IconifiedEventArgs
	    {
		    /**
		     * @brief True in case the window is iconified now, otherwise false
		     */
		    bool iconified;
	    };
	    /**
	     * @brief Arguments passed on a refresh event
	     */
	    struct RefreshEventArgs
	    {
	    };
	    /**
	     * @brief Arguments passed on a resize event
	     */
	    struct ResizeEventArgs
	    {
		    /**
		     * @brief New window width
		     */
		    int width;
		    /**
		     * @brief New window height
		     */
		    int height;
	    };
	    /**
	     * @brief Arguments passed on a framebuffer resize event
	     */
	    struct FramebufferResizeEventArgs
	    {
		    /**
		     * @brief New framebuffer width
		     */
		    int width;
		    /**
		     * @brief New framebuffer height
		     */
		    int height;
	    };
	    /**
	     * @brief Arguments passed on a position event
	     */
	    struct PositionEventArgs
	    {
		    /**
		     * @brief New x coordinate
		     */
		    int x;
		    /**
		     * @brief New y coordinate
		     */
		    int y;
	    };
	    /**
	     * @brief Arguments passed on a character event
	     */
	    struct CharacterEventArgs
	    {
		    /**
		     * @brief Unicode codepoint of the character
		     */
		    unsigned int codepoint;
	    };
	    /**
	     * @brief Arguments passed on a cursor enter event
	     */
	    struct CursorEnterEventArgs
	    {
		    /**
		     * @brief True in case the cursor entered the window, otherwise false
		     */
		    bool entered;
	    };
	    /**
	     * @brief Arguments passed on a cursor event
	     */
	    struct CursorEventArgs
	    {
		    /**
		     * @brief New cursor x coordinate
		     */
		    double x;
		    /**
		     * @brief New cursor y coordinate
		     */
		    double y;
	    };
	    /**
	     * @brief Arguments passed on a mouse button event
	     */
	    struct MouseButtonEventArgs
	    {
		    /**
		     * @brief Pressed button
		     */
		    int button;
		    /**
		     * @brief Key constant representing the button
		     */
		    Input::Key key;
		    /**
		     * @brief Action that happened.
		     */
		    Input::KeyState action;
		    /**
		     * @brief Bitmask describing which modifier keys were held down.
		     * @details Input::Modifier constants may be set
		     */
		    Bitmask<> mods;
	    };
	    /**
	     * @brief Arguments passed on a scroll event
	     */
	    struct ScrollEventArgs
	    {
		    /**
		     * @brief Scroll x offset
		     */
		    double xOffset;
		    /**
		     * @brief Scroll y offset
		     */
		    double yOffset;
	    };
	    /**
	     * @brief Arguments passed on a key event
	     */
	    struct KeyEventArgs
	    {
		    /**
		     * @brief Key that was pressed or released.
		     */
		    Input::Key key;
		    /**
		     * @brief System-specific scancode of that key
		     */
		    int scancode;
		    /**
		     * @brief Action that happened
		     */
		    Input::KeyState action;
		    /**
		     * @brief Bitmask describing which modifier keys were held down.
		     * @details Input::Modifier constants may be set
		     */
		    Bitmask<> mods;
	    };
	    /**
	     * @brief Arguments passed on an update event
	     */
	    struct UpdateEventArgs
	    {
		    /**
		     * @brief Time since last update
		     */
		    double deltaTime;
		    /**
		     * @brief Input object
		     */
		    Input const& input;
	    };
	    /**
	     * @brief Arguments passed on a render event
	     */
	    struct RenderEventArgs
	    {
		    /**
		     * @brief Current render context
		     */
		    RenderContext* rc;
	    };
	    /**
	     * @brief Arguments passed on an input event
	     */
	    struct InputEventArgs
	    {
		    /**
		     * @brief Input object
		     */
		    Input const& input;
		    /**
		     * @brief Key that triggered the event
		     */
		    Input::Key key;
	    };

	    /**
	     * @brief Type of a close event method
	     */
	    using CloseCallbackType = std::function<void(CloseEventArgs const&)>;
	    /**
	     * @brief Type of a focus event method
	     */
	    using FocusCallbackType = std::function<void(FocusEventArgs const&)>;
	    /**
	     * @brief Type of a iconified event method
	     */
	    using IconifiedCallbackType = std::function<void(IconifiedEventArgs const&)>;
	    /**
	     * @brief Type of a refresh event method
	     */
	    using RefreshCallbackType = std::function<void(RefreshEventArgs const&)>;
	    /**
	     * @brief Type of a resize event method
	     */
	    using ResizeCallbackType = std::function<void(ResizeEventArgs const&)>;
	    /**
	     * @brief Type of a framebuffer resize event method
	     */
	    using FramebufferResizeCallbackType = std::function<void(FramebufferResizeEventArgs const&)>;
	    /**
	     * @brief Type of a position event method
	     */
	    using PositionCallbackType = std::function<void(PositionEventArgs const&)>;
	    /**
	     * @brief Type of a character event method
	     */
	    using CharacterCallbackType = std::function<void(CharacterEventArgs const&)>;
	    /**
	     * @brief Type of a cursor enter event method
	     */
	    using CursorEnterCallbackType = std::function<void(CursorEnterEventArgs const&)>;
	    /**
	     * @brief Type of a cursor event method
	     */
	    using CursorCallbackType = std::function<void(CursorEventArgs const&)>;
	    /**
	     * @brief Type of a mouse button event method
	     */
	    using MouseButtonCallbackType = std::function<void(MouseButtonEventArgs const&)>;
	    /**
	     * @brief Type of a scroll event method
	     */
	    using ScrollCallbackType = std::function<void(ScrollEventArgs const&)>;
	    /**
	     * @brief Type of a key event method
	     */
	    using KeyCallbackType = std::function<void(KeyEventArgs const&)>;
	    /**
	     * @brief Type of a update event method
	     */
	    using UpdateCallbackType = std::function<void(UpdateEventArgs const&)>;
	    /**
	     * @brief Type of a render event method
	     */
	    using RenderCallbackType = std::function<void(RenderEventArgs const&)>;
	    /**
	     * @brief Type of a input event method
	     */
	    using InputCallbackType = std::function<void(InputEventArgs const&)>;

	    /**
	     * @brief Type of a close event
	     */
	    using CloseEventType = Event<CloseCallbackType, CloseEventArgs>;
	    /**
	     * @brief Type of a focus event
	     */
	    using FocusEventType = Event<FocusCallbackType, FocusEventArgs>;
	    /**
	     * @brief Type of a iconified event
	     */
	    using IconifiedEventType = Event<IconifiedCallbackType, IconifiedEventArgs>;
	    /**
	     * @brief Type of a refresh event
	     */
	    using RefreshEventType = Event<RefreshCallbackType, RefreshEventArgs>;
	    /**
	     * @brief Type of a resize event
	     */
	    using ResizeEventType = Event<ResizeCallbackType, ResizeEventArgs>;
	    /**
	     * @brief Type of a framebuffer resize event
	     */
	    using FramebufferResizeEventType = Event<FramebufferResizeCallbackType, FramebufferResizeEventArgs>;
	    /**
	     * @brief Type of a position event
	     */
	    using PositionEventType = Event<PositionCallbackType, PositionEventArgs>;
	    /**
	     * @brief Type of a character event
	     */
	    using CharacterEventType = Event<CharacterCallbackType, CharacterEventArgs>;
	    /**
	     * @brief Type of a cursor enter event
	     */
	    using CursorEnterEventType = Event<CursorEnterCallbackType, CursorEnterEventArgs>;
	    /**
	     * @brief Type of a cursor event
	     */
	    using CursorEventType = Event<CursorCallbackType, CursorEventArgs>;
	    /**
	     * @brief Type of a mouse button event
	     */
	    using MouseButtonEventType = Event<MouseButtonCallbackType, MouseButtonEventArgs>;
	    /**
	     * @brief Type of a scroll event
	     */
	    using ScrollEventType = Event<ScrollCallbackType, ScrollEventArgs>;
	    /**
	     * @brief Type of a key event
	     */
	    using KeyEventType = Event<KeyCallbackType, KeyEventArgs>;
	    /**
	     * @brief Type of a update event
	     */
	    using UpdateEventType = Event<UpdateCallbackType, UpdateEventArgs>;
	    /**
	     * @brief Type of a render event
	     */
	    using RenderEventType = Event<RenderCallbackType, RenderEventArgs>;
	    /**
	     * @brief Type of an input event
	     */
	    using InputEventType = Event<InputCallbackType, InputEventArgs>;

	    // Constants used for bitmasks
	    /**
	     * @brief Constant to enable depth testing
	     */
	    static const int DepthTest = 1 << 0;
	    /**
	     * @brief Constant to enable alpha blending
	     */
	    static const int AlphaBlend = 1 << 1;
	    /**
	     * @brief Constant to enable backface culling
	     */
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
	     * @return Input::Up or Input::Down
	     */
	    Input::KeyState getKey(Input::Key) const;
	    /**
	     * @brief Registers a function as callback for close events
	     * @param callback Function to be called when this window is getting closed
	     */
	    CloseEventType::DelegatePtr addCloseCallback(CloseCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for close events
	     * @param callback Function to be called when this window is getting closed
	     */
	    bool removeCloseCallback(CloseEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    FocusEventType::DelegatePtr addFocusCallback(FocusCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    bool removeFocusCallback(FocusEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    IconifiedEventType::DelegatePtr addIconifiedCallback(IconifiedCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    bool removeIconifiedCallback(IconifiedEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    RefreshEventType::DelegatePtr addRefreshCallback(RefreshCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    bool removeRefreshCallback(RefreshEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    ResizeEventType::DelegatePtr addResizeCallback(ResizeCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    bool removeResizeCallback(ResizeEventType::DelegatePtr const& callback);
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
	    bool removeFramebufferResizeCallback(FramebufferResizeEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    PositionEventType::DelegatePtr addPositionCallback(PositionCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    bool removePositionCallback(PositionEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for unicode character events
	     * @param callback Function to be called when a character is typed into this window
	     */
	    CharacterEventType::DelegatePtr addCharacterCallback(CharacterCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for unicode character events
	     * @param callback Function to be called when a character is typed into this window
	     */
	    bool removeCharacterCallback(CharacterEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    CursorEnterEventType::DelegatePtr addCursorEnterCallback(CursorEnterCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    bool removeCursorEnterCallback(CursorEnterEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    CursorEventType::DelegatePtr addCursorCallback(CursorCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    bool removeCursorCallback(CursorEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    MouseButtonEventType::DelegatePtr addMouseButtonCallback(MouseButtonCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    bool removeMouseButtonCallback(MouseButtonEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    ScrollEventType::DelegatePtr addScrollCallback(ScrollCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    bool removeScrollCallback(ScrollEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    KeyEventType::DelegatePtr addKeyCallback(KeyCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    bool removeKeyCallback(KeyEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for update events
	     * @param callback Function to be called when the window is being updated
	     */
	    UpdateEventType::DelegatePtr addUpdateCallback(UpdateCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for update events
	     * @param callback Function to be called when the window is being updated
	     */
	    bool removeUpdateCallback(UpdateEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for render events
	     * @param callback Function to be called when the window is being rendered
	     */
	    RenderEventType::DelegatePtr addRenderCallback(RenderCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for render events
	     * @param callback Function to be called when the window is being rendered
	     */
	    bool removeRenderCallback(RenderEventType::DelegatePtr const& callback);
	    /**
	     * @brief Registers a function as callback for input events
	     * @param callback Function to be called when some sort of input happens
	     */
	    InputEventType::DelegatePtr addInputCallback(InputCallbackType const& callback);
	    /**
	     * @brief Unregisters a function as callback for input events
	     * @param callback Function to be called when some sort of input happens
	     */
	    bool removeInputCallback(InputEventType::DelegatePtr const& callback);
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
	     * @param multisampling Amount of multisampling (0 to disable)
	     */
	    Window(GLFWwindow* share, const char* title = "Dragon Blaze Game Library", int width = 800,
		    int height = 600, bool fullscreen = false, unsigned int multisampling = 2);
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
	     * @brief Called on key input if an input listener needs to be fed
	     * @param args Key event arguments
	     */
	    void keyCallback(KeyEventArgs args);
	    /**
	     * @brief Called on mouse button events if an input listener needs to be fed
	     * @param args Mouse button event arguments
	     */
	    void mouseButtonCallback(MouseButtonEventArgs args);

	    /**
	     * GLFW window handle
	     */
	    GLFWwindow* m_pWndHandle = nullptr;
// TODO: Use GLEW MX for support of multiple windows
//	    GLEWContext* m_pGlewContext = nullptr;
	    /**
	     * @brief Render context
	     */
	    RenderContext* m_pRenderContext = nullptr;
	    /**
	     * @brief Time since last frame
	     */
	    double m_deltaTime = 0;

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
	    InputEventType m_inputCallbacks;

	    std::string m_title;
	    bool m_isFullscreen;
	    unsigned int m_fullscreenWidth, m_fullscreenHeight; // Resolution for full screen
	    unsigned int m_windowedWidth, m_windowedHeight; // Resolution for window
	    unsigned int m_windowedX, m_windowedY; // Last window position before entering fullscreen mode
	    unsigned int m_multisampling = 2;
	    double m_lastTime = 0; // Last timestamp
	    Vector3<GLclampf> m_clearColor = Vector3<GLclampf>(0, 0, 0);
	    GLuint m_vertexArrayId;
	    Input m_input;
	    KeyEventType::DelegatePtr m_inputKeyDelegate;
	    MouseButtonEventType::DelegatePtr m_inputMouseDelegate;

	    friend class WindowManager;
    };
}

#endif /* WINDOW_H_ */
