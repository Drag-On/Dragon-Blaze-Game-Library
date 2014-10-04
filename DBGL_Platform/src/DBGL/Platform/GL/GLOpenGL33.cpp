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
    GLOpenGL33::WndErrorCallback GLOpenGL33::s_errorCallback = nullptr;
    std::unordered_map<GLOpenGL33::WindowHandle, GLFWwindow*> GLOpenGL33::s_wnd2GlfwMap {};
    std::unordered_map<GLFWwindow*, GLOpenGL33::WindowHandle> GLOpenGL33::s_glfw2WndMap {};
    std::unordered_map<GLOpenGL33::WindowHandle, Input> GLOpenGL33::s_wnd2Input {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndCloseCallback> GLOpenGL33::s_closeCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndFocusCallback> GLOpenGL33::s_focusCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndIconifiedCallback> GLOpenGL33::s_iconifiedCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndResizeCallback> GLOpenGL33::s_resizeCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndFramebufferResizeCallback> GLOpenGL33::s_frameResizeCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndPositionCallback> GLOpenGL33::s_positionCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndCursorEnterCallback> GLOpenGL33::s_cursorEnterCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndCursorPositionCallback> GLOpenGL33::s_cursorPositionCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndScrollCallback> GLOpenGL33::s_scrollCallbacks {};
    std::unordered_map<GLOpenGL33::WindowHandle, GLOpenGL33::WndInputCallback> GLOpenGL33::s_inputCallbacks {};

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

    void GLOpenGL33::wndTerminate()
    {
	glfwTerminate();
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
	// Remove all callbacks
	wndSetCloseCallback(wnd, nullptr);
	wndSetCursorEnterCallback(wnd, nullptr);
	wndSetCursorPositionCallback(wnd, nullptr);
	wndSetFocusCallback(wnd, nullptr);
	wndSetFramebufferResizeCallback(wnd, nullptr);
	wndSetIconifiedCallback(wnd, nullptr);
	wndSetInputCallback(wnd, nullptr);
	wndSetPositionCallback(wnd, nullptr);
	wndSetResizeCallback(wnd, nullptr);
	wndSetScrollCallback(wnd, nullptr);
	// Tell it to close
	GLFWwindow* glfwHandle = nullptr;
	try
	{
	    glfwHandle = s_wnd2GlfwMap.at(wnd);
	}
	catch(...)
	{
	}
	if (glfwHandle != nullptr)
	    glfwSetWindowShouldClose(glfwHandle, true);
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
	    s_wnd2Input.erase(wnd);
	    s_wnd2GlfwMap.erase(wnd);
	    s_glfw2WndMap.erase(glfwHandle);
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

    bool GLOpenGL33::wndCheckClose(WindowHandle wnd)
    {
	return glfwWindowShouldClose(getGLFWHandle(wnd));
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

    Input& GLOpenGL33::wndGetInput(WindowHandle wnd)
    {
	return getWindowInput(wnd);
    }

    void GLOpenGL33::wndSwapBuffers(WindowHandle wnd)
    {
	glfwSwapBuffers(getGLFWHandle(wnd));
    }

    void GLOpenGL33::wndPollEvents()
    {
	glfwPollEvents();
    }

    double GLOpenGL33::wndGetTime()
    {
	return glfwGetTime();
    }

    void GLOpenGL33::wndSetErrorCallback(WndErrorCallback callback)
    {
	if(callback)
	{
	    s_errorCallback = callback;
	    glfwSetErrorCallback(wndPassErrorCallback);
	}
	else
	{
	    s_errorCallback = nullptr;
	    glfwSetErrorCallback(nullptr);
	}
    }

    void GLOpenGL33::wndPassErrorCallback(int error, const char* msg)
    {
	s_errorCallback(error, msg);
    }

    void GLOpenGL33::wndSetCloseCallback(WindowHandle wnd, WndCloseCallback callback)
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
	auto callback = s_closeCallbacks.at(wndHandle);
	callback(wndHandle);
    }

    void GLOpenGL33::wndSetFocusCallback(WindowHandle wnd, WndFocusCallback callback)
    {
	if(callback)
	{
	    s_focusCallbacks[wnd] = callback;
	    glfwSetWindowFocusCallback(getGLFWHandle(wnd), wndPassFocusCallback);
	}
	else
	{
	    s_focusCallbacks.erase(wnd);
	    glfwSetWindowFocusCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassFocusCallback(GLFWwindow* wnd, int focus)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto callback = s_focusCallbacks.at(wndHandle);
	callback(wndHandle, focus);
    }

    void GLOpenGL33::wndSetIconifiedCallback(WindowHandle wnd, WndIconifiedCallback callback)
    {
	if(callback)
	{
	    s_iconifiedCallbacks[wnd] = callback;
	    glfwSetWindowIconifyCallback(getGLFWHandle(wnd), wndPassIconifiedCallback);
	}
	else
	{
	    s_iconifiedCallbacks.erase(wnd);
	    glfwSetWindowIconifyCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassIconifiedCallback(GLFWwindow* wnd, int iconified)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto callback = s_iconifiedCallbacks.at(wndHandle);
	callback(wndHandle, iconified);
    }

    void GLOpenGL33::wndSetResizeCallback(WindowHandle wnd, WndResizeCallback callback)
    {
	if(callback)
	{
	    s_resizeCallbacks[wnd] = callback;
	    glfwSetWindowSizeCallback(getGLFWHandle(wnd), wndPassResizeCallback);
	}
	else
	{
	    s_resizeCallbacks.erase(wnd);
	    glfwSetWindowIconifyCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassResizeCallback(GLFWwindow* wnd, int width, int height)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto callback = s_resizeCallbacks.at(wndHandle);
	callback(wndHandle, width, height);
    }

    void GLOpenGL33::wndSetFramebufferResizeCallback(WindowHandle wnd, WndFramebufferResizeCallback callback)
    {
	if(callback)
	{
	    s_frameResizeCallbacks[wnd] = callback;
	    glfwSetFramebufferSizeCallback(getGLFWHandle(wnd), wndPassFramebufferResizeCallback);
	}
	else
	{
	    s_frameResizeCallbacks.erase(wnd);
	    glfwSetFramebufferSizeCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassFramebufferResizeCallback(GLFWwindow* wnd, int width, int height)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto callback = s_frameResizeCallbacks.at(wndHandle);
	callback(wndHandle, width, height);
    }

    void GLOpenGL33::wndSetPositionCallback(WindowHandle wnd, WndPositionCallback callback)
    {
	if(callback)
	{
	    s_positionCallbacks[wnd] = callback;
	    glfwSetWindowPosCallback(getGLFWHandle(wnd), wndPassPositionCallback);
	}
	else
	{
	    s_positionCallbacks.erase(wnd);
	    glfwSetWindowPosCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassPositionCallback(GLFWwindow* wnd, int x, int y)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto callback = s_positionCallbacks.at(wndHandle);
	callback(wndHandle, x, y);
    }

    void GLOpenGL33::wndSetCursorEnterCallback(WindowHandle wnd, WndCursorEnterCallback callback)
    {
	if(callback)
	{
	    s_cursorEnterCallbacks[wnd] = callback;
	    glfwSetCursorEnterCallback(getGLFWHandle(wnd), wndPassCursorEnterCallback);
	}
	else
	{
	    s_cursorEnterCallbacks.erase(wnd);
	    glfwSetCursorEnterCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassCursorEnterCallback(GLFWwindow* wnd, int enter)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto callback = s_cursorEnterCallbacks.at(wndHandle);
	callback(wndHandle, enter);
    }

    void GLOpenGL33::wndSetCursorPositionCallback(WindowHandle wnd, WndCursorPositionCallback callback)
    {
	if(callback)
	{
	    s_cursorPositionCallbacks[wnd] = callback;
	    glfwSetCursorPosCallback(getGLFWHandle(wnd), wndPassCursorPositionCallback);
	}
	else
	{
	    s_cursorPositionCallbacks.erase(wnd);
	    glfwSetCursorPosCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassCursorPositionCallback(GLFWwindow* wnd, double x, double y)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto callback = s_cursorPositionCallbacks.at(wndHandle);
	callback(wndHandle, x, y);
    }

    void GLOpenGL33::wndSetScrollCallback(WindowHandle wnd, WndScrollCallback callback)
    {
	if(callback)
	{
	    s_scrollCallbacks[wnd] = callback;
	    glfwSetScrollCallback(getGLFWHandle(wnd), wndPassScrollCallback);
	}
	else
	{
	    s_scrollCallbacks.erase(wnd);
	    glfwSetScrollCallback(getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassScrollCallback(GLFWwindow* wnd, double x, double y)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto callback = s_scrollCallbacks.at(wndHandle);
	callback(wndHandle, x, y);
    }

    void GLOpenGL33::wndSetInputCallback(WindowHandle wnd, WndInputCallback callback)
    {
	if(callback)
	{
	    s_inputCallbacks[wnd] = callback;
	    glfwSetKeyCallback(getGLFWHandle(wnd), wndPassKeyCallback);
	    glfwSetMouseButtonCallback (getGLFWHandle(wnd), wndPassMouseCallback);
	}
	else
	{
	    s_inputCallbacks.erase(wnd);
	    glfwSetKeyCallback(getGLFWHandle(wnd), nullptr);
	    glfwSetMouseButtonCallback (getGLFWHandle(wnd), nullptr);
	}
    }

    void GLOpenGL33::wndPassKeyCallback(GLFWwindow* wnd, int key, int /* scancode */, int action, int /* mods */)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto& input = getWindowInput(wndHandle);
	Input::Key inputKey = glfwKey2InputKey(key);
	Input::KeyState keyState = glfwKeyState2InputKeyState(action);
	input.updateKey(inputKey, keyState);
	auto callback = s_inputCallbacks.at(wndHandle);
	callback(wndHandle, inputKey, input);
    }

    void GLOpenGL33::wndPassMouseCallback(GLFWwindow* wnd, int button, int action, int /* mods */)
    {
	auto wndHandle = getWindowHandle(wnd);
	auto& input = getWindowInput(wndHandle);
	Input::Key inputKey = glfwButton2InputKey(button);
	Input::KeyState keyState = glfwKeyState2InputKeyState(action);
	input.updateKey(inputKey, keyState);
	auto callback = s_inputCallbacks.at(wndHandle);
	callback(wndHandle, inputKey, input);
    }

    auto GLOpenGL33::texGenerate(TextureType type) -> TextureHandle
    {
	TextureHandleGL* handle = new TextureHandleGL{};
	glGenTextures(1, &(handle->m_handle));
	if(handle->m_handle == 0)
	{
	    delete handle;
	    return nullptr;
	}
	handle->m_type = texType2GL(type);
	return handle;
    }

    void GLOpenGL33::texDelete(TextureHandle handle)
    {
	TextureHandleGL* hnd = dynamic_cast<TextureHandleGL*>(handle);
	if(!hnd)
	    throw("Invalid texture handle!");
	glDeleteTextures(1, &(hnd->m_handle));
	delete hnd;
    }

    void GLOpenGL33::texBind(TextureHandle handle)
    {
	TextureHandleGL* hnd = dynamic_cast<TextureHandleGL*>(handle);
	if(!hnd)
	    throw("Invalid texture handle!");
	glBindTexture(hnd->m_type, hnd->m_handle);
	m_pBoundTexture = hnd;
    }

    void GLOpenGL33::texWrite(unsigned int level, unsigned int width, unsigned int height, PixelFormat format,
	    PixelType type, void const* data)
    {
	if(m_pBoundTexture == nullptr)
	    throw("No texture bound.");
	GLint intFormatgl = hasAlpha(format) ? GL_RGBA : GL_RGB;
	GLint formatgl = pixelFormat2GL(format);
	glTexImage2D(m_pBoundTexture->m_type, level, intFormatgl, width, height, 0, formatgl,
		pixelType2GL(type), data);
    }

    void GLOpenGL33::texWriteCompressed(unsigned int level, unsigned int width, unsigned int height,
    		    PixelFormatCompressed format, unsigned int size, void const* data)
    {
	if(m_pBoundTexture == nullptr)
	    throw("No texture bound.");
	auto glFormat = compPixelFormat2GL(format);
	glCompressedTexImage2D(m_pBoundTexture->m_type, level, glFormat, width, height, 0, size, data);
    }

    void GLOpenGL33::texSetRowAlignment(RowAlignment type, unsigned int align)
    {
	glPixelStorei(rowAlignment2GL(type), align);
    }

    void GLOpenGL33::texSetMinFilter(MinFilter filter)
    {
	if(m_pBoundTexture == nullptr)
	    throw("No texture bound.");
	glTexParameteri(m_pBoundTexture->m_type, GL_TEXTURE_MIN_FILTER, minFilter2GL(filter));
    }

    void GLOpenGL33::texSetMagFilter(MagFilter filter)
    {
	if(m_pBoundTexture == nullptr)
	    throw("No texture bound.");
	glTexParameteri(m_pBoundTexture->m_type, GL_TEXTURE_MAG_FILTER, magFilter2GL(filter));
    }

    void GLOpenGL33::texGenerateMipMaps()
    {
	if(m_pBoundTexture == nullptr)
	    throw("No texture bound.");
	glGenerateMipmap(m_pBoundTexture->m_type);
    }

    void GLOpenGL33::texGetSize(unsigned int& width, unsigned int& height, unsigned int level)
    {
	if(m_pBoundTexture == nullptr)
	    throw("No texture bound.");
	GLint temp{};
	glGetTexLevelParameteriv(m_pBoundTexture->m_type, level, GL_TEXTURE_WIDTH, &temp);
	width = temp;
	glGetTexLevelParameteriv(m_pBoundTexture->m_type, level, GL_TEXTURE_HEIGHT, &temp);
	height = temp;
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

    Input& GLOpenGL33::getWindowInput(WindowHandle wnd)
    {
	if(wnd != IGL::InvalidWindowHandle)
	{
	    return s_wnd2Input[wnd];
	}
	throw std::invalid_argument("No input for invalid window handles.");
    }

    Input::Key GLOpenGL33::glfwKey2InputKey(int key)
    {
	return Input::Key(Input::keyboard_offset + key);
    }

    Input::Key GLOpenGL33::glfwButton2InputKey(int button)
    {
	return Input::Key(Input::mouse_offset + button);
    }

    Input::KeyState GLOpenGL33::glfwKeyState2InputKeyState(int keyState)
    {
	switch(keyState)
	{
	    case GLFW_RELEASE:
		return Input::KeyState::RELEASED;
	    case GLFW_PRESS:
		return Input::KeyState::PRESSED;
	    case GLFW_REPEAT:
		return Input::KeyState::DOWN;
	    default:
		return Input::KeyState::UP;
	}
    }

    Input::Modifier GLOpenGL33::glfwModifier2InputModifier(int mod)
    {
	switch(mod)
	{
	    case GLFW_MOD_ALT:
		return Input::Modifier::KEY_ALT;
	    case GLFW_MOD_CONTROL:
		return Input::Modifier::KEY_CONTROL;
	    case GLFW_MOD_SHIFT:
		return Input::Modifier::KEY_SHIFT;
	    case GLFW_MOD_SUPER:
		return Input::Modifier::KEY_SUPER;
	    default:
		return Input::Modifier::NONE;
	}
    }

    GLenum GLOpenGL33::texType2GL(TextureType type)
    {
	switch(type)
	{
	    case TextureType::TEX2D:
		return GL_TEXTURE_2D;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLint GLOpenGL33::pixelFormat2GL(PixelFormat format)
    {
	switch(format)
	{
	    case PixelFormat::BGR:
		return GL_BGR;
	    case PixelFormat::BGRA:
		return GL_BGRA;
	    case PixelFormat::RGB:
		return GL_RGB;
	    case PixelFormat::RGBA:
		return GL_RGBA;
	    case PixelFormat::LUMINANCE:
		return GL_LUMINANCE;
	    default:
		return -1;
	}
    }

    GLenum GLOpenGL33::pixelType2GL(PixelType type)
    {
	switch(type)
	{
	    case PixelType::BYTE:
		return GL_BYTE;
	    case PixelType::FLOAT:
		return GL_FLOAT;
	    case PixelType::INT:
		return GL_INT;
	    case PixelType::SHORT:
		return GL_SHORT;
	    case PixelType::UBYTE:
		return GL_UNSIGNED_BYTE;
	    case PixelType::UINT:
		return GL_UNSIGNED_INT;
	    case PixelType::USHORT:
		return GL_UNSIGNED_SHORT;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum GLOpenGL33::rowAlignment2GL(RowAlignment align)
    {
	switch (align)
	{
	    case RowAlignment::PACK:
		return GL_PACK_ALIGNMENT;
	    case RowAlignment::UNPACK:
		return GL_UNPACK_ALIGNMENT;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum GLOpenGL33::minFilter2GL(MinFilter filter)
    {
	switch(filter)
	{
	    case MinFilter::LINEAR:
		return GL_LINEAR;
	    case MinFilter::LINEAR_MIPMAP_LINEAR:
		return GL_LINEAR_MIPMAP_LINEAR;
	    case MinFilter::LINEAR_MIPMAP_NEAREST:
		return GL_LINEAR_MIPMAP_NEAREST;
	    case MinFilter::NEAREST:
		return GL_NEAREST;
	    case MinFilter::NEAREST_MIPMAP_LINEAR:
		return GL_NEAREST_MIPMAP_LINEAR;
	    case MinFilter::NEAREST_MIPMAP_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum GLOpenGL33::magFilter2GL(MagFilter filter)
    {
	switch(filter)
	{
	    case MagFilter::LINEAR:
		return GL_LINEAR;
	    case MagFilter::NEAREST:
		return GL_NEAREST;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum GLOpenGL33::compPixelFormat2GL(PixelFormatCompressed format)
    {
	switch(format)
	{
	    case PixelFormatCompressed::COMP_DXT1:
		return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	    case PixelFormatCompressed::COMP_DXT3:
		return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	    case PixelFormatCompressed::COMP_DXT5:
		return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	    default:
		return GL_INVALID_ENUM;
	}
    }
}
