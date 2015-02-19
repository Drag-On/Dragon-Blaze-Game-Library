//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
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
#include "DBGL/Platform/RenderContext/RenderContextGL33Window.h"

namespace dbgl
{
	/**
	 * @brief OpenGL 3.3 implementation of the window class
	 */
	class WindowGL33: public IWindow
	{
	public:
		/**
		 * @brief Constructor
		 * @param title Window title
		 * @param width Initial window width
		 * @param height Initial window height
		 * @param fullscreen Flag defining if the window will be created fullscreen
		 * @param multisampling Amount of multisampling to use
		 */
		WindowGL33(std::string title = "Dragon Blaze Game Library", int width = 800, int height = 600, bool fullscreen =
				false, unsigned int multisampling = 2);
		virtual ~WindowGL33();
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
		virtual void swapBuffer();
		virtual void getCursorPos(double& x, double& y) const;
		virtual void setCursorPos(double x, double y);
		virtual Input const& getInput() const;
		virtual IRenderContext const& getRenderContext() const;
		virtual IRenderContext& getRenderContext();
		/**
		 * @copydoc IWindow::addCloseCallback()
		 */
		virtual CloseEventType::DelegatePtr addCloseCallback(CloseCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeCloseCallback()
		 */
		virtual bool removeCloseCallback(CloseEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addFocusCallback()
		 */
		virtual FocusEventType::DelegatePtr addFocusCallback(FocusCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeFocusCallback()
		 */
		virtual bool removeFocusCallback(FocusEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addIconifiedCallback()
		 */
		virtual IconifiedEventType::DelegatePtr addIconifiedCallback(IconifiedCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeIconifiedCallback()
		 */
		virtual bool removeIconifiedCallback(IconifiedEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addRefreshCallback()
		 */
		virtual RefreshEventType::DelegatePtr addRefreshCallback(RefreshCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeRefreshCallback()
		 */
		virtual bool removeRefreshCallback(RefreshEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addResizeCallback()
		 */
		virtual ResizeEventType::DelegatePtr addResizeCallback(ResizeCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeResizeCallback()
		 */
		virtual bool removeResizeCallback(ResizeEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addFramebufferResizeCallback()
		 */
		virtual FramebufferResizeEventType::DelegatePtr addFramebufferResizeCallback(
				FramebufferResizeCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeFramebufferResizeCallback()
		 */
		virtual bool removeFramebufferResizeCallback(FramebufferResizeEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addPositionCallback()
		 */
		virtual PositionEventType::DelegatePtr addPositionCallback(PositionCallbackType const& callback);
		/**
		 * @copydoc IWindow::removePositionCallback()
		 */
		virtual bool removePositionCallback(PositionEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addCursorEnterCallback()
		 */
		virtual CursorEnterEventType::DelegatePtr addCursorEnterCallback(CursorEnterCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeCursorEnterCallback()
		 */
		virtual bool removeCursorEnterCallback(CursorEnterEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addCursorCallback()
		 */
		virtual CursorEventType::DelegatePtr addCursorCallback(CursorCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeCursorCallback()
		 */
		virtual bool removeCursorCallback(CursorEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addMouseButtonCallback()
		 */
		virtual MouseButtonEventType::DelegatePtr addMouseButtonCallback(MouseButtonCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeMouseButtonCallback()
		 */
		virtual bool removeMouseButtonCallback(MouseButtonEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addScrollCallback()
		 */
		virtual ScrollEventType::DelegatePtr addScrollCallback(ScrollCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeScrollCallback()
		 */
		virtual bool removeScrollCallback(ScrollEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addKeyCallback()
		 */
		virtual KeyEventType::DelegatePtr addKeyCallback(KeyCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeKeyCallback()
		 */
		virtual bool removeKeyCallback(KeyEventType::DelegatePtr const& callback);
		/**
		 * @copydoc IWindow::addInputCallback()
		 */
		virtual InputEventType::DelegatePtr addInputCallback(InputCallbackType const& callback);
		/**
		 * @copydoc IWindow::removeInputCallback()
		 */
		virtual bool removeInputCallback(InputEventType::DelegatePtr const& callback);

	private:
		/**
		 * GLFW window handle
		 */
		GLFWwindow* m_pWndHandle = nullptr;
// TODO: Use GLEW MX for support of multiple windows
//	    GLEWContext* m_pGlewContext = nullptr;

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
		GLuint m_vertexArrayId = 0;
		Input m_input;
		RenderContextGL33Window m_rc { this };
		KeyEventType::DelegatePtr m_inputKeyDelegate;
		MouseButtonEventType::DelegatePtr m_inputMouseDelegate;

		void internalKeyCallback(KeyEventArgs args);
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
