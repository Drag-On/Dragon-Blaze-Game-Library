//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Window/Window.h"

namespace dbgl
{
    Window::Window(GLFWwindow* share, const char* title, int width, int height, bool fullscreen)
    {
	m_title = title;
	if(fullscreen)
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
#ifdef __WIN32
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	if(fullscreen)
	    m_pWndHandle = glfwCreateWindow(m_fullscreenWidth, m_fullscreenHeight, title, glfwGetPrimaryMonitor(), share);
	else
	    m_pWndHandle = glfwCreateWindow(m_windowedWidth, m_windowedHeight, title, NULL, share);
	if (!m_pWndHandle)
	{
	    LOG.error("Failed to create new window!");
	    glfwTerminate();
	}

	m_windowedX = getX();
	m_windowedY = getY();

	// Add framebuffer resize event handler
	addFramebufferResizeCallback(
		std::bind(&Window::framebufferResizeCallback, this,
			std::placeholders::_1));

	makeCurrent();

	// Initialize GLEW
	glewExperimental = true;// For core profile
	if (glewInit() != GLEW_OK)
	{
	    LOG.error("Failed to initialize GLEW!");
	    glfwTerminate();
	    exit(EXIT_FAILURE);
	}
    }

    Window::~Window()
    {
	makeCurrent();
	glDeleteVertexArrays(1, &m_vertexArrayId);
	glfwDestroyWindow(m_pWndHandle);

	delete m_pRenderContext;
	m_pRenderContext = NULL;
    }

    void Window::framebufferResizeCallback(FramebufferResizeEventArgs args)
    {
	// Change viewport
	m_pRenderContext->changeSize(args.width, args.height);
    }

    void Window::keyCallback(KeyEventArgs args)
    {
	m_input.updateKey(args.key, args.action);
    }

    void Window::mouseButtonCallback(MouseButtonEventArgs args)
    {
	m_input.updateKey(args.key, args.action);
    }

    void Window::createRenderContext()
    {
	if (m_pRenderContext != NULL)
	    delete m_pRenderContext;

	m_pRenderContext = new RenderContext { (unsigned int) getFrameWidth(), (unsigned int) getFrameHeight() };
    }

    void Window::init(Bitmask<> options)
    {
	makeCurrent();

	// Create render context
	createRenderContext();

	// Enable depth test?
	if (options.isSet(DepthTest))
	{
	    glEnable(GL_DEPTH_TEST);
	    glDepthFunc(GL_LESS);
	}

	// Enable alpha blending?
	if (options.isSet(AlphaBlend))
	{
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Cull triangles that are not facing the camera?
	if (options.isSet(FaceCulling))
	    glEnable(GL_CULL_FACE);

	// Create vertex array
	glGenVertexArrays(1, &m_vertexArrayId);
	glBindVertexArray(m_vertexArrayId);
    }

    void Window::show()
    {
	glfwShowWindow(m_pWndHandle);
    }

    void Window::hide()
    {
	glfwHideWindow(m_pWndHandle);
    }

    void Window::close()
    {
	glfwSetWindowShouldClose(m_pWndHandle, true);
    }

    bool Window::hasFocus() const
    {
	return glfwGetWindowAttrib(m_pWndHandle, GLFW_FOCUSED);
    }

    bool Window::isIconified() const
    {
	return glfwGetWindowAttrib(m_pWndHandle, GLFW_ICONIFIED);
    }

    bool Window::isVisible() const
    {
	return glfwGetWindowAttrib(m_pWndHandle, GLFW_VISIBLE);
    }

    bool Window::isResizable() const
    {
	return glfwGetWindowAttrib(m_pWndHandle, GLFW_RESIZABLE);
    }

    bool Window::isDecorated() const
    {
	return glfwGetWindowAttrib(m_pWndHandle, GLFW_DECORATED);
    }

    const char* Window::getTitle() const
    {
	return m_title.c_str();
    }

    void Window::setTitle(const char* title)
    {
	m_title.assign(title);
	glfwSetWindowTitle(m_pWndHandle, title);
    }

    int Window::getWidth() const
    {
	int width {}, height {};
	glfwGetWindowSize(m_pWndHandle, &width, &height);
	return width;
    }

    int Window::getHeight() const
    {
	int width {}, height {};
	glfwGetWindowSize(m_pWndHandle, &width, &height);
	return height;
    }

    void Window::setSize(int width, int height)
    {
	glfwSetWindowSize(m_pWndHandle, width, height);
    }

    int Window::getFrameWidth() const
    {
	int width {}, height {};
	glfwGetFramebufferSize(m_pWndHandle, &width, &height);
	return width;
    }

    int Window::getFrameHeight() const
    {
	int width {}, height {};
	glfwGetFramebufferSize(m_pWndHandle, &width, &height);
	return height;
    }

    int Window::getX() const
    {
	int x {}, y {};
	glfwGetWindowPos(m_pWndHandle, &x, &y);
	return x;
    }

    int Window::getY() const
    {
	int x {}, y {};
	glfwGetWindowPos(m_pWndHandle, &x, &y);
	return y;
    }

    void Window::setPos(int x, int y)
    {
	glfwSetWindowPos(m_pWndHandle, x, y);
    }

    bool Window::isFullscreen() const
    {
	return m_isFullscreen;
    }

    void Window::setFullscreen(bool fullscreen)
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

    Vec3f Window::getClearColor() const
    {
	return m_clearColor;
    }

    void Window::setClearColor(Vector3<GLclampf> const& color)
    {
	m_clearColor = color;
    }

    RenderContext* Window::getRenderContext() const
    {
	return m_pRenderContext;
    }

    void Window::makeCurrent()
    {
	glfwMakeContextCurrent(m_pWndHandle);
    }

    void Window::getCursorPos(double& x, double& y) const
    {
	glfwGetCursorPos(m_pWndHandle, &x, &y);
    }

    void Window::setCursorPos(double x, double y)
    {
	glfwSetCursorPos(m_pWndHandle, x, y);
    }

    int Window::getButton(int button) const
    {
	return glfwGetMouseButton(m_pWndHandle, button);
    }

    Input::KeyState Window::getKey(Input::Key key) const
    {
	// Convert Input::Key to GLFW key
	int glfwKey = int(key) - Input::keyboard_offset;
	int glfwResult = glfwGetKey(m_pWndHandle, glfwKey);
	Input::KeyState keyState = Input::KeyState::UP;
	if(glfwResult == GLFW_PRESS || glfwResult == GLFW_REPEAT)
	    keyState = Input::KeyState::DOWN;
	return keyState;
    }

    Window::CloseEventType::DelegatePtr Window::addCloseCallback(CloseCallbackType const& callback)
    {
	glfwSetWindowCloseCallback(m_pWndHandle, WindowManager::closeCallback);
	return m_closeCallbacks.addListener(callback);
    }

    bool Window::removeCloseCallback(CloseEventType::DelegatePtr const& callback)
    {
	bool ret = m_closeCallbacks.removeListener(callback);
	if (!m_closeCallbacks.hasListener())
	    glfwSetWindowCloseCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::FocusEventType::DelegatePtr Window::addFocusCallback(FocusCallbackType const& callback)
    {
	glfwSetWindowFocusCallback(m_pWndHandle, WindowManager::focusCallback);
	return m_focusCallbacks.addListener(callback);
    }

    bool Window::removeFocusCallback(FocusEventType::DelegatePtr const& callback)
    {
	bool ret = m_focusCallbacks.removeListener(callback);
	if (!m_focusCallbacks.hasListener())
	    glfwSetWindowFocusCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::IconifiedEventType::DelegatePtr Window::addIconifiedCallback(
	    IconifiedCallbackType const& callback)
    {
	glfwSetWindowIconifyCallback(m_pWndHandle, WindowManager::iconifiedCallback);
	return m_iconifiedCallbacks.addListener(callback);
    }

    bool Window::removeIconifiedCallback(IconifiedEventType::DelegatePtr const& callback)
    {
	bool ret = m_iconifiedCallbacks.removeListener(callback);
	if (!m_iconifiedCallbacks.hasListener())
	    glfwSetWindowIconifyCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::RefreshEventType::DelegatePtr Window::addRefreshCallback(RefreshCallbackType const& callback)
    {
	glfwSetWindowRefreshCallback(m_pWndHandle, WindowManager::refreshCallback);
	return m_refreshCallbacks.addListener(callback);
    }

    bool Window::removeRefreshCallback(RefreshEventType::DelegatePtr const& callback)
    {
	bool ret = m_refreshCallbacks.removeListener(callback);
	if (!m_refreshCallbacks.hasListener())
	    glfwSetWindowRefreshCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::ResizeEventType::DelegatePtr Window::addResizeCallback(ResizeCallbackType const& callback)
    {
	glfwSetWindowSizeCallback(m_pWndHandle, WindowManager::resizeCallback);
	return m_resizeCallbacks.addListener(callback);
    }

    bool Window::removeResizeCallback(ResizeEventType::DelegatePtr const& callback)
    {
	bool ret = m_resizeCallbacks.removeListener(callback);
	if (!m_resizeCallbacks.hasListener())
	    glfwSetWindowSizeCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::FramebufferResizeEventType::DelegatePtr Window::addFramebufferResizeCallback(
	    FramebufferResizeCallbackType const& callback)
    {
	glfwSetFramebufferSizeCallback(m_pWndHandle, WindowManager::framebufferResizeCallback);
	return m_framebufferResizeCallbacks.addListener(callback);
    }

    bool Window::removeFramebufferResizeCallback(FramebufferResizeEventType::DelegatePtr const& callback)
    {
	bool ret = m_framebufferResizeCallbacks.removeListener(callback);
	if (!m_framebufferResizeCallbacks.hasListener())
	    glfwSetFramebufferSizeCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::PositionEventType::DelegatePtr Window::addPositionCallback(PositionCallbackType const& callback)
    {
	glfwSetWindowPosCallback(m_pWndHandle, WindowManager::positionCallback);
	return m_positionCallbacks.addListener(callback);
    }

    bool Window::removePositionCallback(PositionEventType::DelegatePtr const& callback)
    {
	bool ret = m_positionCallbacks.removeListener(callback);
	if (!m_positionCallbacks.hasListener())
	    glfwSetWindowPosCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::CharacterEventType::DelegatePtr Window::addCharacterCallback(
	    CharacterCallbackType const& callback)
    {
	glfwSetCharCallback(m_pWndHandle, WindowManager::characterCallback);
	return m_characterCallbacks.addListener(callback);
    }

    bool Window::removeCharacterCallback(CharacterEventType::DelegatePtr const& callback)
    {
	bool ret = m_characterCallbacks.removeListener(callback);
	if (!m_characterCallbacks.hasListener())
	    glfwSetCharCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::CursorEnterEventType::DelegatePtr Window::addCursorEnterCallback(
	    CursorEnterCallbackType const& callback)
    {
	glfwSetCursorEnterCallback(m_pWndHandle, WindowManager::cursorEnterCallback);
	return m_cursorEnterCallbacks.addListener(callback);
    }

    bool Window::removeCursorEnterCallback(CursorEnterEventType::DelegatePtr const& callback)
    {
	bool ret = m_cursorEnterCallbacks.removeListener(callback);
	if (!m_cursorEnterCallbacks.hasListener())
	    glfwSetCursorEnterCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::CursorEventType::DelegatePtr Window::addCursorCallback(CursorCallbackType const& callback)
    {
	glfwSetCursorPosCallback(m_pWndHandle, WindowManager::cursorCallback);
	return m_cursorCallbacks.addListener(callback);
    }

    bool Window::removeCursorCallback(CursorEventType::DelegatePtr const& callback)
    {
	bool ret = m_cursorCallbacks.removeListener(callback);
	if (!m_cursorCallbacks.hasListener())
	    glfwSetCursorPosCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::MouseButtonEventType::DelegatePtr Window::addMouseButtonCallback(
	    MouseButtonCallbackType const& callback)
    {
	glfwSetMouseButtonCallback(m_pWndHandle, WindowManager::mouseButtonCallback);
	return m_mouseButtonCallbacks.addListener(callback);
    }

    bool Window::removeMouseButtonCallback(MouseButtonEventType::DelegatePtr const& callback)
    {
	bool ret = m_mouseButtonCallbacks.removeListener(callback);
	if (!m_mouseButtonCallbacks.hasListener())
	    glfwSetMouseButtonCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::ScrollEventType::DelegatePtr Window::addScrollCallback(ScrollCallbackType const& callback)
    {
	glfwSetScrollCallback(m_pWndHandle, WindowManager::scrollCallback);
	return m_scrollCallbacks.addListener(callback);
    }

    bool Window::removeScrollCallback(ScrollEventType::DelegatePtr const& callback)
    {
	bool ret = m_scrollCallbacks.removeListener(callback);
	if (!m_scrollCallbacks.hasListener())
	    glfwSetScrollCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::KeyEventType::DelegatePtr Window::addKeyCallback(KeyCallbackType const& callback)
    {
	glfwSetKeyCallback(m_pWndHandle, WindowManager::keyCallback);
	return m_keyCallbacks.addListener(callback);
    }

    bool Window::removeKeyCallback(KeyEventType::DelegatePtr const& callback)
    {
	bool ret = m_keyCallbacks.removeListener(callback);
	if (!m_keyCallbacks.hasListener())
	    glfwSetKeyCallback(m_pWndHandle, NULL);
	return ret;
    }

    Window::UpdateEventType::DelegatePtr Window::addUpdateCallback(UpdateCallbackType const& callback)
    {
	return m_updateCallbacks.addListener(callback);
    }

    bool Window::removeUpdateCallback(UpdateEventType::DelegatePtr const& callback)
    {
	return m_updateCallbacks.removeListener(callback);
    }

    Window::RenderEventType::DelegatePtr Window::addRenderCallback(RenderCallbackType const& callback)
    {
	return m_renderCallbacks.addListener(callback);
    }

    bool Window::removeRenderCallback(RenderEventType::DelegatePtr const& callback)
    {
	return m_renderCallbacks.removeListener(callback);
    }

    Window::InputEventType::DelegatePtr Window::addInputCallback(InputCallbackType const& callback)
    {
	if(m_inputKeyDelegate == nullptr)
	    m_inputKeyDelegate = addKeyCallback(std::bind(&dbgl::Window::keyCallback, this, std::placeholders::_1));
	if(m_inputMouseDelegate == nullptr)
	    m_inputMouseDelegate = addMouseButtonCallback(std::bind(&dbgl::Window::mouseButtonCallback, this, std::placeholders::_1));
	return m_inputCallbacks.addListener(callback);
    }

    bool Window::removeInputCallback(InputEventType::DelegatePtr const& callback)
    {
	auto removed = m_inputCallbacks.removeListener(callback);
	if(!m_inputCallbacks.hasListener())
	{
	    removeKeyCallback(m_inputKeyDelegate);
	    removeMouseButtonCallback(m_inputMouseDelegate);
	}
	return removed;
    }

    void Window::preUpdate()
    {
	m_input.update();
    }

    void Window::update()
    {
	m_updateCallbacks.fire(UpdateEventArgs {
	    m_deltaTime
	});
    }

    void Window::postUpdate()
    {
	// Calculate delta time
	double currentTime = WindowManager::get()->getTime();
	m_deltaTime = currentTime - m_lastTime;
	m_lastTime = currentTime;
    }

    void Window::preRender()
    {
	makeCurrent();
	glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pRenderContext->preRender();
    }

    void Window::render()
    {
	m_renderCallbacks.fire(RenderEventArgs {
	    m_pRenderContext
	});
    }

    void Window::postRender()
    {
	glfwSwapBuffers(m_pWndHandle);
	m_pRenderContext->postRender();
    }
}

