//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/GL/GLOpenGL33.h"

namespace dbgl
{
    std::unordered_map<GLOpenGL33::WindowHandle, GLFWwindow*> GLOpenGL33::s_wnd2GlfwMap {};
    std::unordered_map<GLFWwindow*, GLOpenGL33::WindowHandle> GLOpenGL33::s_glfw2WndMap {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::CloseCallbackFun> GLOpenGL33::s_closeCallbacks {};

    GLOpenGL33::GLOpenGL33()
    {
	// Initialize GLFW
	if (!glfwInit())
	    throw(std::runtime_error("Unable to initialize GLFW."));
    }

    GLOpenGL33::~GLOpenGL33()
    {
	// Terminate all windows
	glfwTerminate();
    }

    void GLOpenGL33::getScreenResolution(int& width, int& height)
    {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = mode->width;
	height = mode->height;
    }

    auto GLOpenGL33::wndInit(std::string title, unsigned int width, unsigned int height, bool fullscreen,
	    unsigned int multisampling) -> WindowHandle
    {
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, multisampling);
#ifdef __WIN32 // TODO: Check how this works on different linux distributions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	GLFWwindow* glfwHandle = nullptr;

	if(fullscreen)
	    glfwHandle = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
	    glfwHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!glfwHandle)
	{
	    glfwTerminate();
	    return HandleGenerator::InvalidHandle;
	}

	glfwMakeContextCurrent(glfwHandle);

	// Initialize GLEW
#ifdef __WIN32
	glewExperimental = GL_TRUE;// For core profile
#endif
	if (auto err = glewInit() != GLEW_OK)
	{
	    std::cerr << glewGetErrorString(err) << std::endl;
	    glfwTerminate();
	    return HandleGenerator::InvalidHandle;
	}

	auto wndHandle = m_wndHandleGen.generate();
	s_wnd2GlfwMap.insert({wndHandle, glfwHandle});
	s_glfw2WndMap.insert({glfwHandle, wndHandle});
	return wndHandle;
    }

    void GLOpenGL33::wndShow(WindowHandle wnd)
    {
	glfwShowWindow(getGLFWHandle(wnd));
    }

    void GLOpenGL33::wndHide(WindowHandle wnd)
    {
	glfwHideWindow(getGLFWHandle(wnd));
    }

    void GLOpenGL33::wndClose(WindowHandle wnd)
    {
	GLFWwindow* glfwHandle = nullptr;
	try
	{
	    glfwHandle = s_wnd2GlfwMap.at(wnd);
	}
	catch(...)
	{
	}
	s_wnd2GlfwMap.erase(wnd);
	s_closeCallbacks.erase(wnd);
	if (glfwHandle != nullptr)
	{
	    s_glfw2WndMap.erase(glfwHandle);
	    glfwSetWindowShouldClose(glfwHandle, true);
	}
    }

    void GLOpenGL33::wndDestroy(WindowHandle wnd)
    {
	GLFWwindow* glfwHandle = nullptr;
	try
	{
	    glfwHandle = s_wnd2GlfwMap.at(wnd);
	}
	catch(...)
	{
	}
	if (glfwHandle != nullptr)
	{
	    wndClose(wnd);
	    glfwDestroyWindow(glfwHandle);
	}
    }

    bool GLOpenGL33::wndCheckFocus(WindowHandle wnd)
    {
	return glfwGetWindowAttrib(getGLFWHandle(wnd), GLFW_FOCUSED);
    }

    bool GLOpenGL33::wndCheckIconified(WindowHandle wnd)
    {
	return glfwGetWindowAttrib(getGLFWHandle(wnd), GLFW_ICONIFIED);
    }

    bool GLOpenGL33::wndCheckVisible(WindowHandle wnd)
    {
	return glfwGetWindowAttrib(getGLFWHandle(wnd), GLFW_VISIBLE);
    }

    bool GLOpenGL33::wndCheckResizable(WindowHandle wnd)
    {
	return glfwGetWindowAttrib(getGLFWHandle(wnd), GLFW_RESIZABLE);
    }

    bool GLOpenGL33::wndCheckDecorations(WindowHandle wnd)
    {
	return glfwGetWindowAttrib(getGLFWHandle(wnd), GLFW_DECORATED);
    }

    void GLOpenGL33::wndSetTitle(WindowHandle wnd, std::string const& title)
    {
	glfwSetWindowTitle(getGLFWHandle(wnd), title.c_str());
    }

    void GLOpenGL33::wndGetSize(WindowHandle wnd, int& width, int& height)
    {
	glfwGetWindowSize(getGLFWHandle(wnd), &width, &height);
    }

    void GLOpenGL33::wndSetSize(WindowHandle wnd, int width, int height)
    {
	glfwSetWindowSize(getGLFWHandle(wnd), width, height);
    }

    void GLOpenGL33::wndGetFrameSize(WindowHandle wnd, int& width, int& height)
    {
	glfwGetFramebufferSize(getGLFWHandle(wnd), &width, &height);
    }

    void GLOpenGL33::wndGetPos(WindowHandle wnd, int& x, int& y)
    {
	glfwGetWindowPos(getGLFWHandle(wnd), &x, &y);
    }

    void GLOpenGL33::wndSetPos(WindowHandle wnd, int x, int y)
    {
	glfwSetWindowPos(getGLFWHandle(wnd), x, y);
    }

    void GLOpenGL33::wndMakeCurrent(WindowHandle wnd)
    {
	glfwMakeContextCurrent(getGLFWHandle(wnd));
    }

    void GLOpenGL33::wndGetCursorPos(WindowHandle wnd, double& x, double& y)
    {
	glfwGetCursorPos(getGLFWHandle(wnd), &x, &y);
    }

    void GLOpenGL33::wndSetCursorPos(WindowHandle wnd, double x, double y)
    {
	glfwSetCursorPos(getGLFWHandle(wnd), x, y);
    }

    void GLOpenGL33::wndSwapBuffers(WindowHandle wnd)
    {
	glfwSwapBuffers(getGLFWHandle(wnd));
    }

    void GLOpenGL33::wndSetCloseCallback(WindowHandle wnd, CloseCallbackFun callback)
    {
	if(callback)
	{
	    s_closeCallbacks[wnd] = callback;
	    glfwSetWindowCloseCallback(getGLFWHandle(wnd), wndPassCloseCallback);
	}
	else
	{
	    s_closeCallbacks.erase(wnd);
	    glfwSetWindowCloseCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassCloseCallback(GLFWwindow* wnd)
    {
	auto wndHandle = getWindowHandle(wnd);
	s_closeCallbacks.at(wndHandle)(wndHandle);
    }

    GLFWwindow* GLOpenGL33::getGLFWHandle(WindowHandle wnd)
    {
	try
	{
	    return s_wnd2GlfwMap.at(wnd);
	}
	catch (...)
	{
	    return nullptr;
	}
    }

    auto GLOpenGL33::getWindowHandle(GLFWwindow* wnd) -> WindowHandle
    {
	try
	{
	    return s_glfw2WndMap.at(wnd);
	}
	catch (...)
	{
	    return HandleGenerator::InvalidHandle;
	}
    }
}
