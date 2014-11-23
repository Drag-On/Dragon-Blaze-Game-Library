//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IWINDOW_H_
#define IWINDOW_H_

#include <string>
#include <functional>
#include "DBGL/Platform/Input/Input.h"
#include "DBGL/Core/Utility/Event.h"
#include "DBGL/Platform/RenderContext/IRenderContext.h"

namespace dbgl
{
    /**
     * @brief Interface class for windows
     */
    class IWindow
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
		    unsigned int width;
		    /**
		     * @brief New window height
		     */
		    unsigned int height;
	    };
	    /**
	     * @brief Arguments passed on a framebuffer resize event
	     */
	    struct FramebufferResizeEventArgs
	    {
		    /**
		     * @brief New framebuffer width
		     */
		    unsigned int width;
		    /**
		     * @brief New framebuffer height
		     */
		    unsigned int height;
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
		     * @brief Key constant representing the button
		     */
		    Input::Key key;
		    /**
		     * @brief Action that happened.
		     */
		    Input::KeyState action;
		    /**
		     * @brief Input object
		     */
		    Input const& input;
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
		     * @brief Action that happened
		     */
		    Input::KeyState action;
		    /**
		     * @brief Input object
		     */
		    Input const& input;
	    };
	    /**
	     * @brief Arguments passed on an input event
	     */
	    struct InputEventArgs
	    {
		    /**
		     * @brief Key that triggered the event
		     */
		    Input::Key key;
		    /**
		     * @brief Action that happened
		     */
		    Input::KeyState action;
		    /**
		     * @brief Input object
		     */
		    Input const& input;
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
	     * @brief Type of an input event
	     */
	    using InputEventType = Event<InputCallbackType, InputEventArgs>;

	    /**
	     * @brief Destructor
	     */
	    virtual ~IWindow() = default;
	    /**
	     * @brief Shows the window
	     */
	    virtual void show() = 0;
	    /**
	     * @brief Hides the window
	     */
	    virtual void hide() = 0;
	    /**
	     * @brief Marks the window to be closed permanently
	     */
	    virtual void close() = 0;
	    /**
	     * @return True in case the window is currently in focus, otherwise false
	     */
	    virtual bool hasFocus() const = 0;
	    /**
	     * @return True in case the window is currently iconified, otherwise false
	     */
	    virtual bool isIconified() const = 0;
	    /**
	     * @return True in case the window is currently visible, otherwise false
	     */
	    virtual bool isVisible() const = 0;
	    /**
	     * @return True in case the window is resizable, otherwise false
	     */
	    virtual bool isResizable() const = 0;
	    /**
	     * @return True in case the window has decorations (i.e. borders etc.),
	     * 		otherwise false
	     */
	    virtual bool isDecorated() const = 0;
	    /**
	     * @return True in case the window is currently open, otherwise false
	     */
	    virtual bool isOpen() const = 0;
	    /**
	     * @return The window's title
	     */
	    virtual std::string const& getTitle() const = 0;
	    /**
	     * @param title The new title to set
	     */
	    virtual void setTitle(std::string const& title) = 0;
	    /**
	     * @return Width of the window in screen dimensions
	     */
	    virtual int getWidth() const = 0;
	    /**
	     * @return Height of the window in screen dimensions
	     */
	    virtual int getHeight() const = 0;
	    /**
	     * @brief Sets a new window size
	     * @param width New width
	     * @param height New height
	     */
	    virtual void setSize(int width, int height) = 0;
	    /**
	     * @return Width of the actual rendering space in pixels
	     */
	    virtual int getFrameWidth() const = 0;
	    /**
	     * @return Height of the actual rendering space in pixels
	     */
	    virtual int getFrameHeight() const = 0;
	    /**
	     * @return X coordinate on screen
	     */
	    virtual int getX() const = 0;
	    /**
	     * @return Y coordinate on screen
	     */
	    virtual int getY() const = 0;
	    /**
	     * @brief Moves the window to a new location on screen
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    virtual void setPos(int x, int y) = 0;
	    /**
	     * @return True in case the window is in fullscreen mode,
	     * 		otherwise false
	     */
	    virtual bool isFullscreen() const = 0;
	    /**
	     * @brief Provides the possibility to switch between fullscreen
	     * 	      and window mode
	     * @param fullscreen Indicates if window should switch to fullscreen
	     * 			 or back to window
	     */
	    virtual void setFullscreen(bool fullscreen) = 0;
	    /**
	     * @brief Makes this window the current one
	     */
	    virtual void makeCurrent() = 0;
	    /**
	     * @brief Check if there are new events to process
	     */
	    virtual void pollEvents() = 0;
	    /**
	     * @brief Wait for new events to provess
	     */
	    virtual void waitEvents() = 0;
	    /**
	     * @brief Swaps the back buffer
	     */
	    virtual void swapBuffer() = 0;
	    /**
	     * @brief Grants access to the current cursor position inside of the window
	     * @param x X coordinate is stored here
	     * @param y Y coordinate is stored here
	     */
	    virtual void getCursorPos(double& x, double& y) const = 0;
	    /**
	     * @brief Changes the cursor position inside of the window
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    virtual void setCursorPos(double x, double y) = 0;
	    /**
	     * @brief Provides an input object that can be used to check input inside the window
	     * @return Reference to the input object
	     */
	    virtual Input const& getInput() const = 0;
	    /**
	     * @brief Provides the render context that can be used to display stuff inside of this window
	     * @return Reference to the RC object
	     */
	    virtual IRenderContext const& getRenderContext() const = 0;
	    /**
	     * @brief Provides the render context that can be used to display stuff inside of this window
	     * @return Reference to the RC object
	     */
	    virtual IRenderContext& getRenderContext() = 0;
	    /**
	     * @brief Registers a function as callback for close events
	     * @param callback Function to be called when this window is getting closed
	     */
	    virtual CloseEventType::DelegatePtr addCloseCallback(CloseCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for close events
	     * @param callback Function to be called when this window is getting closed
	     */
	    virtual bool removeCloseCallback(CloseEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    virtual FocusEventType::DelegatePtr addFocusCallback(FocusCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for focus events
	     * @param callback Function to be called when this window's focus state changes
	     */
	    virtual bool removeFocusCallback(FocusEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    virtual IconifiedEventType::DelegatePtr addIconifiedCallback(
		    IconifiedCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for iconified events
	     * @param callback Function to be called when this window is getting iconified or restored
	     */
	    virtual bool removeIconifiedCallback(IconifiedEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    virtual RefreshEventType::DelegatePtr addRefreshCallback(RefreshCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for refresh events
	     * @param callback Function to be called when this window needs to be refreshed
	     */
	    virtual bool removeRefreshCallback(RefreshEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    virtual ResizeEventType::DelegatePtr addResizeCallback(ResizeCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for resize events
	     * @param callback Function to be called when this window is getting resized
	     */
	    virtual bool removeResizeCallback(ResizeEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for framebuffer resize events
	     * @param callback Function to be called when this window's framebuffer needs a resize
	     */
	    virtual FramebufferResizeEventType::DelegatePtr addFramebufferResizeCallback(
		    FramebufferResizeCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for framebuffer resize events
	     * @param callback Function to be called when this window's framebuffer needs a resize
	     */
	    virtual bool removeFramebufferResizeCallback(
		    FramebufferResizeEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    virtual PositionEventType::DelegatePtr addPositionCallback(
		    PositionCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for window move events
	     * @param callback Function to be called when this window is getting moved
	     */
	    virtual bool removePositionCallback(PositionEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    virtual CursorEnterEventType::DelegatePtr addCursorEnterCallback(
		    CursorEnterCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for cursor enter events
	     * @param callback Function to be called when the cursor enters or leaves this window
	     */
	    virtual bool removeCursorEnterCallback(CursorEnterEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    virtual CursorEventType::DelegatePtr addCursorCallback(CursorCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for cursor move events
	     * @param callback Function to be called when the cursor is moved inside this window
	     */
	    virtual bool removeCursorCallback(CursorEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    virtual MouseButtonEventType::DelegatePtr addMouseButtonCallback(
		    MouseButtonCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for mouse button events
	     * @param callback Function to be called when a mouse button state changes
	     */
	    virtual bool removeMouseButtonCallback(MouseButtonEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    virtual ScrollEventType::DelegatePtr addScrollCallback(ScrollCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for scroll events
	     * @param callback Function to be called when the mouse wheel is scrolled
	     */
	    virtual bool removeScrollCallback(ScrollEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    virtual KeyEventType::DelegatePtr addKeyCallback(KeyCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for key events
	     * @param callback Function to be called when a key state changes
	     */
	    virtual bool removeKeyCallback(KeyEventType::DelegatePtr const& callback) = 0;
	    /**
	     * @brief Registers a function as callback for input events
	     * @param callback Function to be called when some sort of input happens
	     */
	    virtual InputEventType::DelegatePtr addInputCallback(InputCallbackType const& callback) = 0;
	    /**
	     * @brief Unregisters a function as callback for input events
	     * @param callback Function to be called when some sort of input happens
	     */
	    virtual bool removeInputCallback(InputEventType::DelegatePtr const& callback) = 0;
    };
}

#endif /* IWINDOW_H_ */
