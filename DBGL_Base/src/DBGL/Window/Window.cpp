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
    Window::Window(const char* title, int width, int height, bool fullscreen, unsigned int multisampling) :
	    m_multisampling(multisampling)
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
	    int fullscreenW {}, fullscreenH {};
	    GLProvider::get()->getScreenResolution(fullscreenW, fullscreenH);
	    m_fullscreenWidth = fullscreenW;
	    m_fullscreenHeight = fullscreenH;
	    m_isFullscreen = false;
	}

	int useWidth = m_windowedWidth;
	int useHeight = m_windowedHeight;
	if(fullscreen)
	{
	    useWidth = m_fullscreenWidth;
	    useHeight = m_fullscreenHeight;
	}

	m_wndHandle = GLProvider::get()->wndInit(title, useWidth, useHeight, fullscreen, multisampling);

	m_windowedX = getX();
	m_windowedY = getY();

	// Add framebuffer resize event handler
	addFramebufferResizeCallback(
		std::bind(&Window::framebufferResizeCallback, this,
			std::placeholders::_1));
    }

    Window::~Window()
    {
	makeCurrent();
	glDeleteVertexArrays(1, &m_vertexArrayId);

	GLProvider::get()->wndDestroy(m_wndHandle);

	delete m_pRenderContext;
	m_pRenderContext = NULL;
    }

    void Window::framebufferResizeCallback(FramebufferResizeEventArgs args)
    {
	// Change viewport
	m_pRenderContext->changeSize(args.width, args.height);
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
	    m_pRenderContext->setDepthTest(RenderContext::DepthTestValue::Less);

	// Enable alpha blending?
	if (options.isSet(AlphaBlend))
	    m_pRenderContext->setAlphaBlend(RenderContext::AlphaBlendValue::SrcAlpha, RenderContext::AlphaBlendValue::OneMinusSrcAlpha);

	// Cull triangles that are not facing the camera?
	if (options.isSet(FaceCulling))
	    m_pRenderContext->setFaceCulling(RenderContext::FaceCullingValue::Back);

	if(m_multisampling > 0)
	    glEnable(GL_MULTISAMPLE);

	// Create vertex array
	glGenVertexArrays(1, &m_vertexArrayId);
	glBindVertexArray(m_vertexArrayId);
    }

    void Window::show()
    {
	GLProvider::get()->wndShow(m_wndHandle);
    }

    void Window::hide()
    {
	GLProvider::get()->wndHide(m_wndHandle);
    }

    void Window::close()
    {
	GLProvider::get()->wndClose(m_wndHandle);
    }

    bool Window::hasFocus() const
    {
	return GLProvider::get()->wndCheckFocus(m_wndHandle);
    }

    bool Window::isIconified() const
    {
	return GLProvider::get()->wndCheckFocus(m_wndHandle);
    }

    bool Window::isVisible() const
    {
	return GLProvider::get()->wndCheckVisible(m_wndHandle);
    }

    bool Window::isResizable() const
    {
	return GLProvider::get()->wndCheckResizable(m_wndHandle);
    }

    bool Window::isDecorated() const
    {
	return GLProvider::get()->wndCheckDecorations(m_wndHandle);
    }

    const char* Window::getTitle() const
    {
	return m_title.c_str();
    }

    void Window::setTitle(const char* title)
    {
	m_title.assign(title);
	GLProvider::get()->wndSetTitle(m_wndHandle, m_title);
    }

    int Window::getWidth() const
    {
	int width {}, height {};
	GLProvider::get()->wndGetSize(m_wndHandle, width, height);
	return width;
    }

    int Window::getHeight() const
    {
	int width {}, height {};
	GLProvider::get()->wndGetSize(m_wndHandle, width, height);
	return height;
    }

    void Window::setSize(int width, int height)
    {
	GLProvider::get()->wndSetSize(m_wndHandle, width, height);
    }

    int Window::getFrameWidth() const
    {
	int width {}, height {};
	GLProvider::get()->wndGetFrameSize(m_wndHandle, width, height);
	return width;
    }

    int Window::getFrameHeight() const
    {
	int width {}, height {};
	GLProvider::get()->wndGetFrameSize(m_wndHandle, width, height);
	return height;
    }

    int Window::getX() const
    {
	int x {}, y {};
	GLProvider::get()->wndGetPos(m_wndHandle, x, y);
	return x;
    }

    int Window::getY() const
    {
	int x {}, y {};
	GLProvider::get()->wndGetPos(m_wndHandle, x, y);
	return y;
    }

    void Window::setPos(int x, int y)
    {
	GLProvider::get()->wndSetPos(m_wndHandle, x, y);
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
	glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], 0);
    }

    RenderContext* Window::getRenderContext() const
    {
	return m_pRenderContext;
    }

    void Window::makeCurrent()
    {
	GLProvider::get()->wndMakeCurrent(m_wndHandle);
    }

    void Window::getCursorPos(double& x, double& y) const
    {
	GLProvider::get()->wndGetCursorPos(m_wndHandle, x, y);
    }

    void Window::setCursorPos(double x, double y)
    {
	GLProvider::get()->wndSetCursorPos(m_wndHandle, x, y);
    }

    Input::KeyState Window::getKey(Input::Key key) const
    {
	return GLProvider::get()->wndGetInput(m_wndHandle).getState(key);
    }

    Window::CloseEventType::DelegatePtr Window::addCloseCallback(CloseCallbackType const& callback)
    {
	GLProvider::get()->wndSetCloseCallback(m_wndHandle, WindowManager::closeCallback);
	return m_closeCallbacks.addListener(callback);
    }

    bool Window::removeCloseCallback(CloseEventType::DelegatePtr const& callback)
    {
	bool ret = m_closeCallbacks.removeListener(callback);
	if (!m_closeCallbacks.hasListener())
	    GLProvider::get()->wndSetCloseCallback(m_wndHandle, nullptr);
	return ret;
    }

    Window::FocusEventType::DelegatePtr Window::addFocusCallback(FocusCallbackType const& callback)
    {
	GLProvider::get()->wndSetFocusCallback(m_wndHandle, WindowManager::focusCallback);
	return m_focusCallbacks.addListener(callback);
    }

    bool Window::removeFocusCallback(FocusEventType::DelegatePtr const& callback)
    {
	bool ret = m_focusCallbacks.removeListener(callback);
	if (!m_closeCallbacks.hasListener())
	    GLProvider::get()->wndSetFocusCallback(m_wndHandle, nullptr);
	return ret;
    }

    Window::IconifiedEventType::DelegatePtr Window::addIconifiedCallback(
	    IconifiedCallbackType const& callback)
    {
	GLProvider::get()->wndSetIconifiedCallback(m_wndHandle, WindowManager::iconifiedCallback);
	return m_iconifiedCallbacks.addListener(callback);
    }

    bool Window::removeIconifiedCallback(IconifiedEventType::DelegatePtr const& callback)
    {
	bool ret = m_iconifiedCallbacks.removeListener(callback);
	if (!m_iconifiedCallbacks.hasListener())
	    GLProvider::get()->wndSetIconifiedCallback(m_wndHandle, nullptr);
	return ret;
    }

    Window::ResizeEventType::DelegatePtr Window::addResizeCallback(ResizeCallbackType const& callback)
    {
	GLProvider::get()->wndSetResizeCallback(m_wndHandle, WindowManager::resizeCallback);
	return m_resizeCallbacks.addListener(callback);
    }

    bool Window::removeResizeCallback(ResizeEventType::DelegatePtr const& callback)
    {
	bool ret = m_resizeCallbacks.removeListener(callback);
	if (!m_resizeCallbacks.hasListener())
	    GLProvider::get()->wndSetResizeCallback(m_wndHandle, nullptr);
	return ret;
    }

    Window::FramebufferResizeEventType::DelegatePtr Window::addFramebufferResizeCallback(
	    FramebufferResizeCallbackType const& callback)
    {
	GLProvider::get()->wndSetFramebufferResizeCallback(m_wndHandle, WindowManager::framebufferResizeCallback);
	return m_framebufferResizeCallbacks.addListener(callback);
    }

    bool Window::removeFramebufferResizeCallback(FramebufferResizeEventType::DelegatePtr const& callback)
    {
	bool ret = m_framebufferResizeCallbacks.removeListener(callback);
	if (!m_framebufferResizeCallbacks.hasListener())
	    GLProvider::get()->wndSetFramebufferResizeCallback(m_wndHandle, nullptr);
	return ret;
    }

    Window::PositionEventType::DelegatePtr Window::addPositionCallback(PositionCallbackType const& callback)
    {
	GLProvider::get()->wndSetPositionCallback(m_wndHandle, WindowManager::positionCallback);
	return m_positionCallbacks.addListener(callback);
    }

    bool Window::removePositionCallback(PositionEventType::DelegatePtr const& callback)
    {
	bool ret = m_positionCallbacks.removeListener(callback);
	if (!m_positionCallbacks.hasListener())
	    GLProvider::get()->wndSetPositionCallback(m_wndHandle, nullptr);
	return ret;
    }

    Window::CursorEnterEventType::DelegatePtr Window::addCursorEnterCallback(
	    CursorEnterCallbackType const& callback)
    {
	GLProvider::get()->wndSetCursorEnterCallback(m_wndHandle, WindowManager::cursorEnterCallback);
	return m_cursorEnterCallbacks.addListener(callback);
    }

    bool Window::removeCursorEnterCallback(CursorEnterEventType::DelegatePtr const& callback)
    {
	bool ret = m_cursorEnterCallbacks.removeListener(callback);
	if (!m_cursorEnterCallbacks.hasListener())
	    GLProvider::get()->wndSetCursorEnterCallback(m_wndHandle, nullptr);
	return ret;
    }

    Window::CursorEventType::DelegatePtr Window::addCursorCallback(CursorCallbackType const& callback)
    {
	GLProvider::get()->wndSetCursorPositionCallback(m_wndHandle, WindowManager::cursorCallback);
	return m_cursorCallbacks.addListener(callback);
    }

    bool Window::removeCursorCallback(CursorEventType::DelegatePtr const& callback)
    {
	bool ret = m_cursorCallbacks.removeListener(callback);
	if (!m_cursorCallbacks.hasListener())
	    GLProvider::get()->wndSetCursorPositionCallback(m_wndHandle, nullptr);
	return ret;
    }

    Window::ScrollEventType::DelegatePtr Window::addScrollCallback(ScrollCallbackType const& callback)
    {
	GLProvider::get()->wndSetScrollCallback(m_wndHandle, WindowManager::scrollCallback);
	return m_scrollCallbacks.addListener(callback);
    }

    bool Window::removeScrollCallback(ScrollEventType::DelegatePtr const& callback)
    {
	bool ret = m_scrollCallbacks.removeListener(callback);
	if (!m_scrollCallbacks.hasListener())
	    GLProvider::get()->wndSetScrollCallback(m_wndHandle, nullptr);
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
	GLProvider::get()->wndSetInputCallback(m_wndHandle, WindowManager::inputCallback);
	return m_inputCallbacks.addListener(callback);
    }

    bool Window::removeInputCallback(InputEventType::DelegatePtr const& callback)
    {
	bool ret = m_inputCallbacks.removeListener(callback);
	if (!m_inputCallbacks.hasListener())
	    GLProvider::get()->wndSetInputCallback(m_wndHandle, nullptr);
	return ret;
    }

    void Window::preUpdate()
    {
    }

    void Window::update()
    {
	m_updateCallbacks.fire(UpdateEventArgs {
	    m_deltaTime,
	    GLProvider::get()->wndGetInput(m_wndHandle),
	});
    }

    void Window::postUpdate()
    {
	GLProvider::get()->wndGetInput(m_wndHandle).update();
	// Calculate delta time
	double currentTime = WindowManager::get()->getTime();
	m_deltaTime = currentTime - m_lastTime;
	m_lastTime = currentTime;
    }

    void Window::preRender()
    {
	makeCurrent();
	m_pRenderContext->clear(RenderContext::COLOR | RenderContext::DEPTH | RenderContext::STENCIL);
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
	GLProvider::get()->wndSwapBuffers(m_wndHandle);
	m_pRenderContext->postRender();
    }
}

