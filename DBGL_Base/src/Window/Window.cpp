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
    Window::Window() :
	    Window("Dragon Blaze Game Library")
    {
    }

    Window::Window(const char* title) :
	    Window(title, 800, 600)
    {
    }

    Window::Window(const char* title, int width, int height) :
	    Window(title, width, height, false)
    {
    }

    Window::Window(const char* title, int width, int height, bool fullscreen)
    {
	if (!glfwInit())
	{
	    LOG->error("Failed to initialize GLFW!");
	    exit(EXIT_FAILURE);
	}

	_title = title;
	if(fullscreen)
	{
	    // Initialize window to default values
	    _windowedWidth = 800;
	    _windowedHeight = 600;
	    // Initialize fullscreen resolution
	    _fullscreenWidth = width;
	    _fullscreenHeight = height;
	    _isFullscreen = true;
	}
	else
	{
	    // Initialize window to default values
	    _windowedWidth = width;
	    _windowedHeight = height;
	    // Initialize fullscreen resolution to screen resolution
	    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	    _fullscreenWidth = mode->width;
	    _fullscreenHeight = mode->height;
	    _isFullscreen = false;
	}

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if(fullscreen)
	_pWndHandle = glfwCreateWindow(_fullscreenWidth, _fullscreenHeight, title, glfwGetPrimaryMonitor(), NULL);
	else
	_pWndHandle = glfwCreateWindow(_windowedWidth, _windowedHeight, title, NULL, NULL);
	if (!_pWndHandle)
	{
	    LOG->error("Failed to create new window!");
	    glfwTerminate();
	    exit(EXIT_FAILURE);
	}

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
	glDeleteVertexArrays(1, &_vertexArrayId);
	glfwDestroyWindow(_pWndHandle);
    }

    void Window::init(bool depthTest, bool faceCulling)
    {
	makeCurrent();

	// Enable depth test?
	if (depthTest)
	{
	    glEnable(GL_DEPTH_TEST);
	    glDepthFunc(GL_LESS);
	}

	// Cull triangles that are not facing the camera?
	if (faceCulling)
	    glEnable(GL_CULL_FACE);

	// Create vertex array
	glGenVertexArrays(1, &_vertexArrayId);
	glBindVertexArray(_vertexArrayId);
    }

    void Window::show()
    {
	glfwShowWindow(_pWndHandle);
    }

    void Window::hide()
    {
	glfwHideWindow(_pWndHandle);
    }

    void Window::close()
    {
	glfwSetWindowShouldClose(_pWndHandle, true);
    }

    bool Window::hasFocus() const
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_FOCUSED);
    }

    bool Window::isIconified() const
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_ICONIFIED);
    }

    bool Window::isVisible() const
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_VISIBLE);
    }

    bool Window::isResizable() const
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_RESIZABLE);
    }

    bool Window::isDecorated() const
    {
	return glfwGetWindowAttrib(_pWndHandle, GLFW_DECORATED);
    }

    const char* Window::getTitle() const
    {
	return _title.c_str();
    }

    void Window::setTitle(const char* title)
    {
	_title.assign(title);
	glfwSetWindowTitle(_pWndHandle, title);
    }

    int Window::getWidth() const
    {
	int width, height;
	glfwGetWindowSize(_pWndHandle, &width, &height);
	return width;
    }

    int Window::getHeight() const
    {
	int width, height;
	glfwGetWindowSize(_pWndHandle, &width, &height);
	return height;
    }

    void Window::setSize(int width, int height)
    {
	glfwSetWindowSize(_pWndHandle, width, height);
    }

    int Window::getFrameWidth() const
    {
	int width, height;
	glfwGetFramebufferSize(_pWndHandle, &width, &height);
	return width;
    }

    int Window::getFrameHeight() const
    {
	int width, height;
	glfwGetFramebufferSize(_pWndHandle, &width, &height);
	return height;
    }

    int Window::getX() const
    {
	int x, y;
	glfwGetWindowPos(_pWndHandle, &x, &y);
	return x;
    }

    int Window::getY() const
    {
	int x, y;
	glfwGetWindowPos(_pWndHandle, &x, &y);
	return y;
    }

    void Window::setPos(int x, int y)
    {
	glfwSetWindowPos(_pWndHandle, x, y);
    }

    bool Window::isFullscreen() const
    {
	return _isFullscreen;
    }

    void Window::setFullscreen(bool fullscreen)
    {
	auto oldHandle = _pWndHandle;
	if (isFullscreen() && !fullscreen)
	{
	    // Destroy window
	    glfwDestroyWindow(_pWndHandle);

	    // Recreate
	    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	    _pWndHandle = glfwCreateWindow(_windowedWidth, _windowedHeight,
		    _title.c_str(), NULL, NULL);
	    if (!_pWndHandle)
	    {
		LOG->error("Failed to enter windowed mode!");
		glfwTerminate();
		exit(EXIT_FAILURE);
	    }
	}
	else if (!isFullscreen() && fullscreen)
	{
	    _windowedWidth = getFrameWidth();
	    _windowedHeight = getFrameHeight();

	    // Destroy window
	    glfwDestroyWindow(_pWndHandle);

	    // Recreate
	    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	    _pWndHandle = glfwCreateWindow(_fullscreenWidth, _fullscreenHeight,
		    _title.c_str(), glfwGetPrimaryMonitor(), NULL);
	    if (!_pWndHandle)
	    {
		LOG->error("Failed to enter fullscreen mode!");
		glfwTerminate();
		exit(EXIT_FAILURE);
	    }
	}
	_isFullscreen = fullscreen;
	WindowManager::get()->updateHandle(oldHandle, _pWndHandle);

	// Re-add callbacks
	if (_characterCallback)
	    addCharacterCallback(_characterCallback);
	if (_closeCallback)
	    addCloseCallback(_closeCallback);
	if (_cursorCallback)
	    addCursorCallback(_cursorCallback);
	if (_cursorEnterCallback)
	    addCursorEnterCallback(_cursorEnterCallback);
	if (_focusCallback)
	    addFocusCallback(_focusCallback);
	if (_framebufferResizeCallback)
	    addFramebufferResizeCallback(_framebufferResizeCallback);
	if (_iconifiedCallback)
	    addIconifiedCallback(_iconifiedCallback);
	if (_keyCallback)
	    addKeyCallback(_keyCallback);
	if (_positionCallback)
	    addPositionCallback(_positionCallback);
	if (_refreshCallback)
	    addRefreshCallback(_refreshCallback);
	if (_resizeCallback)
	    addResizeCallback(_resizeCallback);
	if (_scrollCallback)
	    addScrollCallback(_scrollCallback);
    }

    Vec3f Window::getClearColor() const
    {
	return _clearColor;
    }

    void Window::setClearColor(Vector3<GLclampf> const& color)
    {
	_clearColor = color;
    }

    void Window::makeCurrent()
    {
	glfwMakeContextCurrent(_pWndHandle);
    }

    void Window::addCloseCallback(std::function<void()> const& callback)
    {
	_closeCallback = callback;
	glfwSetWindowCloseCallback(_pWndHandle, WindowManager::closeCallback);
    }

    void Window::addFocusCallback(std::function<void(int)> const& callback)
    {
	_focusCallback = callback;
	glfwSetWindowFocusCallback(_pWndHandle, WindowManager::focusCallback);
    }

    void Window::addIconifiedCallback(std::function<void(int)> const& callback)
    {
	_iconifiedCallback = callback;
	glfwSetWindowIconifyCallback(_pWndHandle,
		WindowManager::iconifiedCallback);
    }

    void Window::addRefreshCallback(std::function<void()> const& callback)
    {
	_refreshCallback = callback;
	glfwSetWindowRefreshCallback(_pWndHandle,
		WindowManager::refreshCallback);
    }

    void Window::addResizeCallback(
	    std::function<void(int, int)> const& callback)
    {
	_resizeCallback = callback;
	glfwSetWindowSizeCallback(_pWndHandle, WindowManager::resizeCallback);
    }

    void Window::addFramebufferResizeCallback(
	    std::function<void(int, int)> const& callback)
    {
	_framebufferResizeCallback = callback;
	glfwSetFramebufferSizeCallback(_pWndHandle,
		WindowManager::framebufferResizeCallback);
    }

    void Window::addPositionCallback(
	    std::function<void(int, int)> const& callback)
    {
	_positionCallback = callback;
	glfwSetWindowPosCallback(_pWndHandle, WindowManager::positionCallback);
    }

    void Window::addCharacterCallback(
	    std::function<void(unsigned int)> const& callback)
    {
	_characterCallback = callback;
	glfwSetCharCallback(_pWndHandle, WindowManager::characterCallback);
    }

    void Window::addCursorEnterCallback(
	    std::function<void(int)> const& callback)
    {
	_cursorEnterCallback = callback;
	glfwSetCursorEnterCallback(_pWndHandle,
		WindowManager::cursorEnterCallback);
    }

    void Window::addCursorCallback(
	    std::function<void(double, double)> const& callback)
    {
	_cursorCallback = callback;
	glfwSetCursorPosCallback(_pWndHandle, WindowManager::cursorCallback);
    }

    void Window::addMouseButtonCallback(
	    std::function<void(int, int, int)> const& callback)
    {
	_mouseButtonCallback = callback;
	glfwSetMouseButtonCallback(_pWndHandle,
		WindowManager::mouseButtonCallback);
    }

    void Window::addScrollCallback(
	    std::function<void(double, double)> const& callback)
    {
	_scrollCallback = callback;
	glfwSetScrollCallback(_pWndHandle, WindowManager::scrollCallback);
    }

    void Window::addKeyCallback(
	    std::function<void(int, int, int, int)> const& callback)
    {
	_keyCallback = callback;
	glfwSetKeyCallback(_pWndHandle, WindowManager::keyCallback);
    }

    void Window::addUpdateCallback(std::function<void()> const& callback)
    {
	_updateCallback = callback;
    }

    void Window::addRenderCallback(
	    std::function<void(const RenderContext*)> const& callback)
    {
	_renderCallback = callback;
    }

    void Window::preUpdate()
    {
    }

    void Window::update()
    {
	if (_updateCallback)
	    _updateCallback();
    }

    void Window::postUpdate()
    {
    }

    void Window::preRender()
    {
	makeCurrent();
	glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::render()
    {
	if (_renderCallback)
	    _renderCallback(&_renderContext);
    }

    void Window::postRender()
    {
	glfwSwapBuffers(_pWndHandle);
    }
}

