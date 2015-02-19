//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Window/WindowGL33.h"

namespace dbgl
{
	std::unordered_map<GLFWwindow*, WindowGL33*> WindowGL33::s_windows = std::unordered_map<GLFWwindow*, WindowGL33*>();

	WindowGL33::WindowGL33(std::string title, int width, int height, bool fullscreen, unsigned int multisampling) :
			m_title { title }, m_multisampling { multisampling }
	{
		if (fullscreen)
		{
			// Initialize window to default values
			m_windowedWidth = 800;
			m_windowedHeight = 600;
			// Initialize fullscreen resolution
			m_fullscreenWidth = width;
			m_fullscreenHeight = height;
			m_isFullscreen = true;
		}
		else
		{
			// Initialize window to default values
			m_windowedWidth = width;
			m_windowedHeight = height;
			// Initialize fullscreen resolution to screen resolution
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			m_fullscreenWidth = mode->width;
			m_fullscreenHeight = mode->height;
			m_isFullscreen = false;
		}

		glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_SAMPLES, multisampling);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (fullscreen)
			m_pWndHandle = glfwCreateWindow(m_fullscreenWidth, m_fullscreenHeight, title.c_str(),
					glfwGetPrimaryMonitor(), nullptr);
		else
			m_pWndHandle = glfwCreateWindow(m_windowedWidth, m_windowedHeight, title.c_str(), nullptr, nullptr);
		if (!m_pWndHandle)
		{
			std::cerr << "Failed to create new window!";
			glfwTerminate();
		}

		// Remember window
		s_windows.insert( { m_pWndHandle, this });

		m_windowedX = getX();
		m_windowedY = getY();

		makeCurrent();

		// Initialize GLEW
		glewExperimental = true; // For core profile
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to initialize GLEW!";
			glfwTerminate();
		}

		// Enable multisampling?
		if (m_multisampling > 0)
			m_rc.setMultisampling(true);

		// Wrap context in vao
		glGenVertexArrays(1, &m_vertexArrayId);
		glBindVertexArray(m_vertexArrayId);
	}

	WindowGL33::~WindowGL33()
	{
		makeCurrent();
		glDeleteVertexArrays(1, &m_vertexArrayId);
		s_windows.erase(m_pWndHandle);
		glfwDestroyWindow(m_pWndHandle);
	}

	void WindowGL33::show()
	{
		glfwShowWindow(m_pWndHandle);
	}

	void WindowGL33::hide()
	{
		glfwHideWindow(m_pWndHandle);
	}

	void WindowGL33::close()
	{
		glfwSetWindowShouldClose(m_pWndHandle, true);
	}

	bool WindowGL33::hasFocus() const
	{
		return glfwGetWindowAttrib(m_pWndHandle, GLFW_FOCUSED);
	}

	bool WindowGL33::isIconified() const
	{
		return glfwGetWindowAttrib(m_pWndHandle, GLFW_ICONIFIED);
	}

	bool WindowGL33::isVisible() const
	{
		return glfwGetWindowAttrib(m_pWndHandle, GLFW_VISIBLE);
	}

	bool WindowGL33::isResizable() const
	{
		return glfwGetWindowAttrib(m_pWndHandle, GLFW_RESIZABLE);
	}

	bool WindowGL33::isDecorated() const
	{
		return glfwGetWindowAttrib(m_pWndHandle, GLFW_DECORATED);
	}

	bool WindowGL33::isOpen() const
	{
		return !glfwWindowShouldClose(m_pWndHandle);
	}

	std::string const& WindowGL33::getTitle() const
	{
		return m_title;
	}

	void WindowGL33::setTitle(std::string const& title)
	{
		m_title = title;
		glfwSetWindowTitle(m_pWndHandle, title.c_str());
	}

	int WindowGL33::getWidth() const
	{
		int width { }, height { };
		glfwGetWindowSize(m_pWndHandle, &width, &height);
		return width;
	}

	int WindowGL33::getHeight() const
	{
		int width { }, height { };
		glfwGetWindowSize(m_pWndHandle, &width, &height);
		return height;
	}

	void WindowGL33::setSize(int width, int height)
	{
		glfwSetWindowSize(m_pWndHandle, width, height);
	}

	int WindowGL33::getFrameWidth() const
	{
		int width { }, height { };
		glfwGetFramebufferSize(m_pWndHandle, &width, &height);
		return width;
	}

	int WindowGL33::getFrameHeight() const
	{
		int width { }, height { };
		glfwGetFramebufferSize(m_pWndHandle, &width, &height);
		return height;
	}

	int WindowGL33::getX() const
	{
		int x { }, y { };
		glfwGetWindowPos(m_pWndHandle, &x, &y);
		return x;
	}

	int WindowGL33::getY() const
	{
		int x { }, y { };
		glfwGetWindowPos(m_pWndHandle, &x, &y);
		return y;
	}

	void WindowGL33::setPos(int x, int y)
	{
		glfwSetWindowPos(m_pWndHandle, x, y);
	}

	bool WindowGL33::isFullscreen() const
	{
		return m_isFullscreen;
	}

	void WindowGL33::setFullscreen(bool fullscreen)
	{
		if (isFullscreen() && !fullscreen)
		{
			this->setPos(m_windowedX, m_windowedY);
			this->setSize(m_windowedWidth, m_windowedHeight);
		}
		else if (!isFullscreen() && fullscreen)
		{
			m_windowedWidth = getFrameWidth();
			m_windowedHeight = getFrameHeight();
			m_windowedX = getX();
			m_windowedY = getY();
			this->setPos(0, 0);
			this->setSize(m_fullscreenWidth, m_fullscreenHeight);
		}
		m_isFullscreen = fullscreen;
	}

	void WindowGL33::makeCurrent()
	{
		glfwMakeContextCurrent(m_pWndHandle);
	}

	void WindowGL33::pollEvents()
	{
		glfwPollEvents();
		m_input.update();
	}

	void WindowGL33::waitEvents()
	{
		glfwWaitEvents();
		m_input.update();
	}

	void WindowGL33::swapBuffer()
	{
		glfwSwapBuffers(m_pWndHandle);
	}

	void WindowGL33::getCursorPos(double& x, double& y) const
	{
		glfwGetCursorPos(m_pWndHandle, &x, &y);
	}

	void WindowGL33::setCursorPos(double x, double y)
	{
		glfwSetCursorPos(m_pWndHandle, x, y);
	}

	Input const& WindowGL33::getInput() const
	{
		return m_input;
	}

	IRenderContext const& WindowGL33::getRenderContext() const
	{
		return m_rc;
	}

	IRenderContext& WindowGL33::getRenderContext()
	{
		return m_rc;
	}

	WindowGL33::CloseEventType::DelegatePtr WindowGL33::addCloseCallback(CloseCallbackType const& callback)
	{
		glfwSetWindowCloseCallback(m_pWndHandle, WindowGL33::closeCallback);
		return m_closeCallbacks.addListener(callback);
	}

	bool WindowGL33::removeCloseCallback(CloseEventType::DelegatePtr const& callback)
	{
		bool ret = m_closeCallbacks.removeListener(callback);
		if (!m_closeCallbacks.hasListener())
			glfwSetWindowCloseCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::FocusEventType::DelegatePtr WindowGL33::addFocusCallback(FocusCallbackType const& callback)
	{
		glfwSetWindowFocusCallback(m_pWndHandle, WindowGL33::focusCallback);
		return m_focusCallbacks.addListener(callback);
	}

	bool WindowGL33::removeFocusCallback(FocusEventType::DelegatePtr const& callback)
	{
		bool ret = m_focusCallbacks.removeListener(callback);
		if (!m_focusCallbacks.hasListener())
			glfwSetWindowFocusCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::IconifiedEventType::DelegatePtr WindowGL33::addIconifiedCallback(IconifiedCallbackType const& callback)
	{
		glfwSetWindowIconifyCallback(m_pWndHandle, WindowGL33::iconifiedCallback);
		return m_iconifiedCallbacks.addListener(callback);
	}

	bool WindowGL33::removeIconifiedCallback(IconifiedEventType::DelegatePtr const& callback)
	{
		bool ret = m_iconifiedCallbacks.removeListener(callback);
		if (!m_iconifiedCallbacks.hasListener())
			glfwSetWindowIconifyCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::RefreshEventType::DelegatePtr WindowGL33::addRefreshCallback(RefreshCallbackType const& callback)
	{
		glfwSetWindowRefreshCallback(m_pWndHandle, WindowGL33::refreshCallback);
		return m_refreshCallbacks.addListener(callback);
	}

	bool WindowGL33::removeRefreshCallback(RefreshEventType::DelegatePtr const& callback)
	{
		bool ret = m_refreshCallbacks.removeListener(callback);
		if (!m_refreshCallbacks.hasListener())
			glfwSetWindowRefreshCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::ResizeEventType::DelegatePtr WindowGL33::addResizeCallback(ResizeCallbackType const& callback)
	{
		glfwSetWindowSizeCallback(m_pWndHandle, WindowGL33::resizeCallback);
		return m_resizeCallbacks.addListener(callback);
	}

	bool WindowGL33::removeResizeCallback(ResizeEventType::DelegatePtr const& callback)
	{
		bool ret = m_resizeCallbacks.removeListener(callback);
		if (!m_resizeCallbacks.hasListener())
			glfwSetWindowSizeCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::FramebufferResizeEventType::DelegatePtr WindowGL33::addFramebufferResizeCallback(
			FramebufferResizeCallbackType const& callback)
	{
		glfwSetFramebufferSizeCallback(m_pWndHandle, WindowGL33::framebufferResizeCallback);
		return m_framebufferResizeCallbacks.addListener(callback);
	}

	bool WindowGL33::removeFramebufferResizeCallback(FramebufferResizeEventType::DelegatePtr const& callback)
	{
		bool ret = m_framebufferResizeCallbacks.removeListener(callback);
		if (!m_framebufferResizeCallbacks.hasListener())
			glfwSetFramebufferSizeCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::PositionEventType::DelegatePtr WindowGL33::addPositionCallback(PositionCallbackType const& callback)
	{
		glfwSetWindowPosCallback(m_pWndHandle, WindowGL33::positionCallback);
		return m_positionCallbacks.addListener(callback);
	}

	bool WindowGL33::removePositionCallback(PositionEventType::DelegatePtr const& callback)
	{
		bool ret = m_positionCallbacks.removeListener(callback);
		if (!m_positionCallbacks.hasListener())
			glfwSetWindowPosCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::CursorEnterEventType::DelegatePtr WindowGL33::addCursorEnterCallback(
			CursorEnterCallbackType const& callback)
	{
		glfwSetCursorEnterCallback(m_pWndHandle, WindowGL33::cursorEnterCallback);
		return m_cursorEnterCallbacks.addListener(callback);
	}

	bool WindowGL33::removeCursorEnterCallback(CursorEnterEventType::DelegatePtr const& callback)
	{
		bool ret = m_cursorEnterCallbacks.removeListener(callback);
		if (!m_cursorEnterCallbacks.hasListener())
			glfwSetCursorEnterCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::CursorEventType::DelegatePtr WindowGL33::addCursorCallback(CursorCallbackType const& callback)
	{
		glfwSetCursorPosCallback(m_pWndHandle, WindowGL33::cursorCallback);
		return m_cursorCallbacks.addListener(callback);
	}

	bool WindowGL33::removeCursorCallback(CursorEventType::DelegatePtr const& callback)
	{
		bool ret = m_cursorCallbacks.removeListener(callback);
		if (!m_cursorCallbacks.hasListener())
			glfwSetCursorPosCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::MouseButtonEventType::DelegatePtr WindowGL33::addMouseButtonCallback(
			MouseButtonCallbackType const& callback)
	{
		glfwSetMouseButtonCallback(m_pWndHandle, WindowGL33::mouseButtonCallback);
		return m_mouseButtonCallbacks.addListener(callback);
	}

	bool WindowGL33::removeMouseButtonCallback(MouseButtonEventType::DelegatePtr const& callback)
	{
		bool ret = m_mouseButtonCallbacks.removeListener(callback);
		if (!m_mouseButtonCallbacks.hasListener())
			glfwSetMouseButtonCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::ScrollEventType::DelegatePtr WindowGL33::addScrollCallback(ScrollCallbackType const& callback)
	{
		glfwSetScrollCallback(m_pWndHandle, WindowGL33::scrollCallback);
		return m_scrollCallbacks.addListener(callback);
	}

	bool WindowGL33::removeScrollCallback(ScrollEventType::DelegatePtr const& callback)
	{
		bool ret = m_scrollCallbacks.removeListener(callback);
		if (!m_scrollCallbacks.hasListener())
			glfwSetScrollCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::KeyEventType::DelegatePtr WindowGL33::addKeyCallback(KeyCallbackType const& callback)
	{
		glfwSetKeyCallback(m_pWndHandle, WindowGL33::keyCallback);
		return m_keyCallbacks.addListener(callback);
	}

	bool WindowGL33::removeKeyCallback(KeyEventType::DelegatePtr const& callback)
	{
		bool ret = m_keyCallbacks.removeListener(callback);
		if (!m_keyCallbacks.hasListener())
			glfwSetKeyCallback(m_pWndHandle, NULL);
		return ret;
	}

	WindowGL33::InputEventType::DelegatePtr WindowGL33::addInputCallback(InputCallbackType const& callback)
	{
		if (m_inputKeyDelegate == nullptr)
			m_inputKeyDelegate = addKeyCallback(
					std::bind(&dbgl::WindowGL33::internalKeyCallback, this, std::placeholders::_1));
		if (m_inputMouseDelegate == nullptr)
			m_inputMouseDelegate = addMouseButtonCallback(
					std::bind(&dbgl::WindowGL33::internalMouseButtonCallback, this, std::placeholders::_1));
		return m_inputCallbacks.addListener(callback);
	}

	bool WindowGL33::removeInputCallback(InputEventType::DelegatePtr const& callback)
	{
		auto removed = m_inputCallbacks.removeListener(callback);
		if (!m_inputCallbacks.hasListener())
		{
			removeKeyCallback(m_inputKeyDelegate);
			removeMouseButtonCallback(m_inputMouseDelegate);
		}
		return removed;
	}

	void WindowGL33::errorCallback(int error, const char* description)
	{
		std::cerr << "Error: " << error << ", " << description << std::endl;
		throw std::runtime_error { description };
	}

	void WindowGL33::closeCallback(GLFWwindow* window)
	{
		s_windows[window]->m_closeCallbacks.fire(WindowGL33::CloseEventArgs { });
	}

	void WindowGL33::focusCallback(GLFWwindow* window, int focused)
	{
		s_windows[window]->m_focusCallbacks.fire(WindowGL33::FocusEventArgs { focused == GL_TRUE ? true : false });
	}

	void WindowGL33::iconifiedCallback(GLFWwindow* window, int iconified)
	{
		s_windows[window]->m_iconifiedCallbacks.fire(
				WindowGL33::IconifiedEventArgs { iconified == GL_TRUE ? true : false });
	}

	void WindowGL33::refreshCallback(GLFWwindow* window)
	{
		s_windows[window]->m_refreshCallbacks.fire(WindowGL33::RefreshEventArgs { });
	}

	void WindowGL33::resizeCallback(GLFWwindow* window, int width, int height)
	{
		s_windows[window]->m_resizeCallbacks.fire(WindowGL33::ResizeEventArgs { static_cast<unsigned int>(width),
				static_cast<unsigned int>(height) });
	}

	void WindowGL33::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		s_windows[window]->m_framebufferResizeCallbacks.fire(WindowGL33::FramebufferResizeEventArgs {
				static_cast<unsigned int>(width), static_cast<unsigned int>(height) });
	}

	void WindowGL33::positionCallback(GLFWwindow* window, int xpos, int ypos)
	{
		s_windows[window]->m_positionCallbacks.fire(WindowGL33::PositionEventArgs { xpos, ypos });
	}

	void WindowGL33::cursorEnterCallback(GLFWwindow* window, int entered)
	{
		s_windows[window]->m_cursorEnterCallbacks.fire(
				WindowGL33::CursorEnterEventArgs { entered == GL_TRUE ? true : false });
	}

	void WindowGL33::cursorCallback(GLFWwindow* window, double x, double y)
	{
		s_windows[window]->m_cursorCallbacks.fire(WindowGL33::CursorEventArgs { x, y });
	}

	void WindowGL33::mouseButtonCallback(GLFWwindow* window, int button, int action, int /* mods */)
	{
		// Translate GLFW button into Input::Key
		Input::Key keyConst = Input::Key(Input::mouse_offset + button);
		// Translate GLFW action int Input::KeyState
		Input::KeyState keyState { };
		if (action == GLFW_RELEASE)
			keyState = Input::KeyState::RELEASED;
		else if (action == GLFW_PRESS)
			keyState = Input::KeyState::PRESSED;
		else if (action == GLFW_REPEAT)
			keyState = Input::KeyState::DOWN;
		else
			keyState = Input::KeyState::UP;
		s_windows[window]->m_mouseButtonCallbacks.fire(WindowGL33::MouseButtonEventArgs { keyConst, keyState,
				s_windows[window]->m_input });
		s_windows[window]->m_inputCallbacks.fire(
				WindowGL33::InputEventArgs { keyConst, keyState, s_windows[window]->m_input });
	}

	void WindowGL33::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		s_windows[window]->m_scrollCallbacks.fire(WindowGL33::ScrollEventArgs { xOffset, yOffset });
	}

	void WindowGL33::keyCallback(GLFWwindow* window, int key, int /* scancode */, int action, int /* mods */)
	{
		// Translate GLFW key into Input::Key
		Input::Key keyConst = Input::Key(Input::keyboard_offset + key);
		// Translate GLFW action int Input::KeyState
		Input::KeyState keyState { };
		if (action == GLFW_RELEASE)
			keyState = Input::KeyState::RELEASED;
		else if (action == GLFW_PRESS)
			keyState = Input::KeyState::PRESSED;
		else if (action == GLFW_REPEAT)
			keyState = Input::KeyState::DOWN;
		else
			keyState = Input::KeyState::UP;
		s_windows[window]->m_mouseButtonCallbacks.fire(WindowGL33::MouseButtonEventArgs { keyConst, keyState,
				s_windows[window]->m_input });
		s_windows[window]->m_inputCallbacks.fire(
				WindowGL33::InputEventArgs { keyConst, keyState, s_windows[window]->m_input });
	}

	void WindowGL33::internalKeyCallback(KeyEventArgs args)
	{
		m_input.updateKey(args.key, args.action);
	}

	void WindowGL33::internalMouseButtonCallback(MouseButtonEventArgs args)
	{
		m_input.updateKey(args.key, args.action);
	}
}
