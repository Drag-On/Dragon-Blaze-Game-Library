//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef WINDOWGL33_H_
#define WINDOWGL33_H_

#include <iostream>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IWindow.h"

namespace dbgl
{
    class WindowGL33: public IWindow
    {
	public:
	    WindowGL33(std::string title = "Dragon Blaze Game Library", int width = 800, int height = 600,
		    bool fullscreen = false, unsigned int multisampling = 2);
	    virtual ~WindowGL33() = default;
	    virtual void show();
	    virtual void hide();
	    virtual void close();
	    virtual bool hasFocus() const;
	    virtual bool isIconified() const;
	    virtual bool isVisible() const;
	    virtual bool isResizable() const;
	    virtual bool isDecorated() const;
	    virtual bool isOpen() const;
	    virtual std::string const& getTitle() const;
	    virtual void setTitle(std::string const& title);
	    virtual int getWidth() const;
	    virtual int getHeight() const;
	    virtual void setSize(int width, int height);
	    virtual int getFrameWidth() const;
	    virtual int getFrameHeight() const;
	    virtual int getX() const;
	    virtual int getY() const;
	    virtual void setPos(int x, int y);
	    virtual bool isFullscreen() const;
	    virtual void setFullscreen(bool fullscreen);
	    virtual void makeCurrent();
	    virtual void pollEvents();
	    virtual void waitEvents();
	    virtual void getCursorPos(double& x, double& y) const;
	    virtual void setCursorPos(double x, double y);
	    virtual Input const& getInput() const;
	    virtual CloseEventType::DelegatePtr addCloseCallback(CloseCallbackType const& callback);
	    virtual bool removeCloseCallback(CloseEventType::DelegatePtr const& callback);
	    virtual FocusEventType::DelegatePtr addFocusCallback(FocusCallbackType const& callback);
	    virtual bool removeFocusCallback(FocusEventType::DelegatePtr const& callback);
	    virtual IconifiedEventType::DelegatePtr addIconifiedCallback(
		    IconifiedCallbackType const& callback);
	    virtual bool removeIconifiedCallback(IconifiedEventType::DelegatePtr const& callback);
	    virtual RefreshEventType::DelegatePtr addRefreshCallback(RefreshCallbackType const& callback);
	    virtual bool removeRefreshCallback(RefreshEventType::DelegatePtr const& callback);
	    virtual ResizeEventType::DelegatePtr addResizeCallback(ResizeCallbackType const& callback);
	    virtual bool removeResizeCallback(ResizeEventType::DelegatePtr const& callback);
	    virtual FramebufferResizeEventType::DelegatePtr addFramebufferResizeCallback(
		    FramebufferResizeCallbackType const& callback);
	    virtual bool removeFramebufferResizeCallback(
		    FramebufferResizeEventType::DelegatePtr const& callback);
	    virtual PositionEventType::DelegatePtr addPositionCallback(
		    PositionCallbackType const& callback);
	    virtual bool removePositionCallback(PositionEventType::DelegatePtr const& callback);
	    virtual CursorEnterEventType::DelegatePtr addCursorEnterCallback(
		    CursorEnterCallbackType const& callback);
	    virtual bool removeCursorEnterCallback(CursorEnterEventType::DelegatePtr const& callback);
	    virtual CursorEventType::DelegatePtr addCursorCallback(CursorCallbackType const& callback);
	    virtual bool removeCursorCallback(CursorEventType::DelegatePtr const& callback);
	    virtual MouseButtonEventType::DelegatePtr addMouseButtonCallback(
		    MouseButtonCallbackType const& callback);
	    virtual bool removeMouseButtonCallback(MouseButtonEventType::DelegatePtr const& callback);
	    virtual ScrollEventType::DelegatePtr addScrollCallback(ScrollCallbackType const& callback);
	    virtual bool removeScrollCallback(ScrollEventType::DelegatePtr const& callback);
	    virtual KeyEventType::DelegatePtr addKeyCallback(KeyCallbackType const& callback);
	    virtual bool removeKeyCallback(KeyEventType::DelegatePtr const& callback);
	    virtual InputEventType::DelegatePtr addInputCallback(InputCallbackType const& callback);
	    virtual bool removeInputCallback(InputEventType::DelegatePtr const& callback);

	protected:
	    /**
	     * GLFW window handle
	     */
	    GLFWwindow* m_pWndHandle = nullptr;
// TODO: Use GLEW MX for support of multiple windows
//	    GLEWContext* m_pGlewContext = nullptr;
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
	    CursorEnterEventType m_cursorEnterCallbacks;
	    CursorEventType m_cursorCallbacks;
	    MouseButtonEventType m_mouseButtonCallbacks;
	    ScrollEventType m_scrollCallbacks;
	    KeyEventType m_keyCallbacks;
	    InputEventType m_inputCallbacks;

	    std::string m_title;
	    bool m_isFullscreen;
	    unsigned int m_fullscreenWidth, m_fullscreenHeight; // Resolution for full screen
	    unsigned int m_windowedWidth, m_windowedHeight; // Resolution for window
	    unsigned int m_windowedX, m_windowedY; // Last window position before entering fullscreen mode
	    unsigned int m_multisampling;
	    double m_lastTime = 0; // Last timestamp
	    GLuint m_vertexArrayId;
	    Input m_input;
	    KeyEventType::DelegatePtr m_inputKeyDelegate;
	    MouseButtonEventType::DelegatePtr m_inputMouseDelegate;

	    /**
	     * @brief Called on key input if an input listener needs to be fed
	     * @param args Key event arguments
	     */
	    void internalKeyCallback(KeyEventArgs args);
	    /**
	     * @brief Called on mouse button events if an input listener needs to be fed
	     * @param args Mouse button event arguments
	     */
	    void internalMouseButtonCallback(MouseButtonEventArgs args);

	    static std::unordered_map<GLFWwindow*, WindowGL33*> s_windows;

	    static void errorCallback(int error, const char* description);
	    static void closeCallback(GLFWwindow* window);
	    static void focusCallback(GLFWwindow* window, int focused);
	    static void iconifiedCallback(GLFWwindow* window, int iconified);
	    static void refreshCallback(GLFWwindow* window);
	    static void resizeCallback(GLFWwindow* window, int width, int height);
	    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	    static void positionCallback(GLFWwindow* window, int xpos, int ypos);
	    static void characterCallback(GLFWwindow* window, unsigned int codepoint);
	    static void cursorEnterCallback(GLFWwindow* window, int entered);
	    static void cursorCallback(GLFWwindow* window, double x, double y);
	    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    };
}

#endif /* WINDOWGL33_H_ */
