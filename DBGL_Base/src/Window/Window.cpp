//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Window/Window.h"

namespace dbgl
{
    Window::Window(GLFWwindow* share) :
	    Window(share, "Dragon Blaze Game Library")
    {
    }

    Window::Window(GLFWwindow* share, const char* title) :
	    Window(share, title, 800, 600)
    {
    }

    Window::Window(GLFWwindow* share, const char* title, int width, int height) :
	    Window(share, title, width, height, false)
    {
    }

    Window::Window(GLFWwindow* share, const char* title, int width, int height,
	    bool fullscreen)
    {
	if (!glfwInit())
	{
	    LOG->error("Failed to initialize GLFW!");
	    exit(EXIT_FAILURE);
	}

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
	    LOG->error("Failed to create new window!");
	    glfwTerminate();
	    exit(EXIT_FAILURE);
	}

	m_windowedX = getX();
	m_windowedY = getY();

	// Create render context object
	m_pRenderContext = new RenderContext(getFrameWidth(), getFrameHeight());

	makeCurrent();

	// Initialize GLEW
	glewExperimental = true;// For core profile
	if (glewInit() != GLEW_OK)
	{
	    LOG->error("Failed to initialize GLEW!");
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

    void Window::init(bool depthTest, bool alphaBlend, bool faceCulling)
    {
	makeCurrent();

	// Enable depth test?
	if (depthTest)
	{
	    glEnable(GL_DEPTH_TEST);
	    glDepthFunc(GL_LESS);
	}

	// Enable alpha blending?
	if (alphaBlend)
	{
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Cull triangles that are not facing the camera?
	if (faceCulling)
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
	int width, height;
	glfwGetWindowSize(m_pWndHandle, &width, &height);
	return width;
    }

    int Window::getHeight() const
    {
	int width, height;
	glfwGetWindowSize(m_pWndHandle, &width, &height);
	return height;
    }

    void Window::setSize(int width, int height)
    {
	glfwSetWindowSize(m_pWndHandle, width, height);
    }

    int Window::getFrameWidth() const
    {
	int width, height;
	glfwGetFramebufferSize(m_pWndHandle, &width, &height);
	return width;
    }

    int Window::getFrameHeight() const
    {
	int width, height;
	glfwGetFramebufferSize(m_pWndHandle, &width, &height);
	return height;
    }

    int Window::getX() const
    {
	int x, y;
	glfwGetWindowPos(m_pWndHandle, &x, &y);
	return x;
    }

    int Window::getY() const
    {
	int x, y;
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

    int Window::getKey(int key) const
    {
	return glfwGetKey(m_pWndHandle, key);
    }

    void Window::addCloseCallback(CloseCallbackType const& callback)
    {
	m_closeCallback = callback;
	glfwSetWindowCloseCallback(m_pWndHandle, WindowManager::closeCallback);
    }

    void Window::addFocusCallback(FocusCallbackType const& callback)
    {
	m_focusCallback = callback;
	glfwSetWindowFocusCallback(m_pWndHandle, WindowManager::focusCallback);
    }

    void Window::addIconifiedCallback(IconifiedCallbackType const& callback)
    {
	m_iconifiedCallback = callback;
	glfwSetWindowIconifyCallback(m_pWndHandle,
		WindowManager::iconifiedCallback);
    }

    void Window::addRefreshCallback(RefreshCallbackType const& callback)
    {
	m_refreshCallback = callback;
	glfwSetWindowRefreshCallback(m_pWndHandle,
		WindowManager::refreshCallback);
    }

    void Window::addResizeCallback(ResizeCallbackType const& callback)
    {
	m_resizeCallback = callback;
	glfwSetWindowSizeCallback(m_pWndHandle, WindowManager::resizeCallback);
    }

    void Window::addFramebufferResizeCallback(
	    FramebufferResizeCallbackType const& callback)
    {
	m_framebufferResizeCallback = callback;
	glfwSetFramebufferSizeCallback(m_pWndHandle,
		WindowManager::framebufferResizeCallback);
    }

    void Window::addPositionCallback(PositionCallbackType const& callback)
    {
	m_positionCallback = callback;
	glfwSetWindowPosCallback(m_pWndHandle, WindowManager::positionCallback);
    }

    void Window::addCharacterCallback(CharacterCallbackType const& callback)
    {
	m_characterCallback = callback;
	glfwSetCharCallback(m_pWndHandle, WindowManager::characterCallback);
    }

    void Window::addCursorEnterCallback(CursorEnterCallbackType const& callback)
    {
	m_cursorEnterCallback = callback;
	glfwSetCursorEnterCallback(m_pWndHandle,
		WindowManager::cursorEnterCallback);
    }

    void Window::addCursorCallback(CursorCallbackType const& callback)
    {
	m_cursorCallback = callback;
	glfwSetCursorPosCallback(m_pWndHandle, WindowManager::cursorCallback);
    }

    void Window::addMouseButtonCallback(MouseButtonCallbackType const& callback)
    {
	m_mouseButtonCallback = callback;
	glfwSetMouseButtonCallback(m_pWndHandle,
		WindowManager::mouseButtonCallback);
    }

    void Window::addScrollCallback(ScrollCallbackType const& callback)
    {
	m_scrollCallback = callback;
	glfwSetScrollCallback(m_pWndHandle, WindowManager::scrollCallback);
    }

    void Window::addKeyCallback(KeyCallbackType const& callback)
    {
	m_keyCallback = callback;
	glfwSetKeyCallback(m_pWndHandle, WindowManager::keyCallback);
    }

    void Window::addUpdateCallback(UpdateCallbackType const& callback)
    {
	m_updateCallback = callback;
    }

    void Window::addRenderCallback(RenderCallbackType const& callback)
    {
	m_renderCallback = callback;
    }

    void Window::preUpdate()
    {
    }

    void Window::update()
    {
	if (m_updateCallback)
	    m_updateCallback(m_deltaTime);
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
	m_pRenderContext->update();
    }

    void Window::render()
    {
	if (m_renderCallback)
	    m_renderCallback(m_pRenderContext);
    }

    void Window::postRender()
    {
	glfwSwapBuffers(m_pWndHandle);
    }
}

