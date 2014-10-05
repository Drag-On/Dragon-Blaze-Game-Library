//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef GLOPENGL33_H_
#define GLOPENGL33_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include "IGL.h"
#include "Exception/CompileException.h"
#include "Exception/LinkException.h"

namespace dbgl
{
    class GLOpenGL33: public IGL
    {
	public:
	    GLOpenGL33();
	    virtual ~GLOpenGL33();
	    virtual void getScreenResolution(int& width, int& height);
	    virtual WindowHandle wndInit(std::string title = "Dragon-Blaze-Game-Library", unsigned int width =
		    800, unsigned int height = 600, bool fullscreen = false, unsigned int multisampling = 0);
	    virtual void wndTerminate();
	    virtual void wndShow(WindowHandle const& wnd);
	    virtual void wndHide(WindowHandle const& wnd);
	    virtual void wndClose(WindowHandle const& wnd);
	    virtual void wndDestroy(WindowHandle const& wnd);
	    virtual bool wndCheckFocus(WindowHandle const& wnd);
	    virtual bool wndCheckIconified(WindowHandle const& wnd);
	    virtual bool wndCheckVisible(WindowHandle const& wnd);
	    virtual bool wndCheckResizable(WindowHandle const& wnd);
	    virtual bool wndCheckDecorations(WindowHandle const& wnd);
	    virtual bool wndCheckClose(WindowHandle const& wnd);
	    virtual void wndSetTitle(WindowHandle const& wnd, std::string const& title);
	    virtual void wndGetSize(WindowHandle const& wnd, int& width, int& height);
	    virtual void wndSetSize(WindowHandle const& wnd, int width, int height);
	    virtual void wndGetFrameSize(WindowHandle const& wnd, int& width, int& height);
	    virtual void wndGetPos(WindowHandle const& wnd, int& x, int& y);
	    virtual void wndSetPos(WindowHandle const& wnd, int x, int y);
	    virtual void wndMakeCurrent(WindowHandle const& wnd);
	    virtual void wndGetCursorPos(WindowHandle const& wnd, double& x, double& y);
	    virtual void wndSetCursorPos(WindowHandle const& wnd, double x, double y);
	    virtual Input& wndGetInput(WindowHandle const& wnd);
	    virtual void wndSwapBuffers(WindowHandle const& wnd);
	    virtual void wndPollEvents();
	    virtual double wndGetTime();
	    virtual void wndSetErrorCallback(WndErrorCallback callback);
	    virtual void wndSetCloseCallback(WindowHandle const& wnd, WndCloseCallback callback);
	    virtual void wndSetFocusCallback(WindowHandle const& wnd, WndFocusCallback callback);
	    virtual void wndSetIconifiedCallback(WindowHandle const& wnd, WndIconifiedCallback callback);
	    virtual void wndSetResizeCallback(WindowHandle const& wnd, WndResizeCallback callback);
	    virtual void wndSetFramebufferResizeCallback(WindowHandle const& wnd, WndFramebufferResizeCallback callback);
	    virtual void wndSetPositionCallback(WindowHandle const& wnd, WndPositionCallback callback);
	    virtual void wndSetCursorEnterCallback(WindowHandle const& wnd, WndCursorEnterCallback callback);
	    virtual void wndSetCursorPositionCallback(WindowHandle const& wnd, WndCursorPositionCallback callback);
	    virtual void wndSetScrollCallback(WindowHandle const& wnd, WndScrollCallback callback);
	    virtual void wndSetInputCallback(WindowHandle const& wnd, WndInputCallback callback);
	    virtual TextureHandle texGenerate(TextureType type);
	    virtual void texDelete(TextureHandle const& handle);
	    virtual void texBind(TextureHandle const& handle);
	    virtual void texWrite(unsigned int level, unsigned int width, unsigned int height,
		    PixelFormat format, PixelType type, void const* data);
	    virtual void texWriteCompressed(unsigned int level, unsigned int width, unsigned int height,
		    PixelFormatCompressed format, unsigned int size, void const* data);
	    virtual void texSetRowAlignment(RowAlignment type, unsigned int align);
	    virtual void texSetMinFilter(MinFilter filter);
	    virtual void texSetMagFilter(MagFilter filter);
	    virtual void texGenerateMipMaps();
	    virtual void texGetSize(unsigned int& width, unsigned int& height, unsigned int level = 0);
	    virtual ShaderHandle shaCreate(ShaderType type, std::string src);
	    virtual void shaDelete(ShaderHandle const& handle);
	    virtual ShaderProgramHandle shaCreateProgram();
	    virtual void shaDeleteProgram(ShaderProgramHandle const& handle);
	    virtual void shaAttachShader(ShaderProgramHandle const& program, ShaderHandle const& shader);
	    virtual void shaLinkProgram(ShaderProgramHandle const& program);
	    virtual void shaUseProgram(ShaderProgramHandle const& program);
	    virtual AttributeHandle shaGetAttributeHandle(ShaderProgramHandle const& program, std::string name);
	    virtual UniformHandle shaGetUniformHandle(ShaderProgramHandle const& program, std::string name);
	    virtual void shaSetUniformFloat(UniformHandle const& uniform, float value);
	    virtual void shaSetUniformFloat2(UniformHandle const& uniform, float value1, float value2);
	    virtual void shaSetUniformFloat3(UniformHandle const& uniform, float value1, float value2, float value3);
	    virtual void shaSetUniformFloat4(UniformHandle const& uniform, float value1, float value2, float value3,
		    float value4);
	    virtual void shaSetUniformInt(UniformHandle const& uniform, int value);
	    virtual void shaSetUniformInt2(UniformHandle const& uniform, int value1, int value2);
	    virtual void shaSetUniformInt3(UniformHandle const& uniform, int value1, int value2, int value3);
	    virtual void shaSetUniformInt4(UniformHandle const& uniform, int value1, int value2, int value3,
		    int value4);
	    virtual void shaSetUniformFloatArray(UniformHandle const& uniform, unsigned int count, float const* values);
	    virtual void shaSetUniformFloat2Array(UniformHandle const& uniform, unsigned int count, float const* values);
	    virtual void shaSetUniformFloat3Array(UniformHandle const& uniform, unsigned int count, float const* values);
	    virtual void shaSetUniformFloat4Array(UniformHandle const& uniform, unsigned int count, float const* values);
	    virtual void shaSetUniformIntArray(UniformHandle const& uniform, unsigned int count, int const* values);
	    virtual void shaSetUniformInt2Array(UniformHandle const& uniform, unsigned int count, int const* values);
	    virtual void shaSetUniformInt3Array(UniformHandle const& uniform, unsigned int count, int const* values);
	    virtual void shaSetUniformInt4Array(UniformHandle const& uniform, unsigned int count, int const* values);
	    virtual void shaSetUniformMatrix2Array(UniformHandle const& uniform, unsigned int count, bool transpose,
		    float const* values);
	    virtual void shaSetUniformMatrix3Array(UniformHandle const& uniform, unsigned int count, bool transpose,
		    float const* values);
	    virtual void shaSetUniformMatrix4Array(UniformHandle const& uniform, unsigned int count, bool transpose,
		    float const* values);

	private:
	    GLOpenGL33(GLOpenGL33 const&); // Disallow copying
	    GLOpenGL33& operator=(GLOpenGL33 const& other);

	    static void wndPassErrorCallback(int error, const char* msg);
	    static void wndPassCloseCallback(GLFWwindow* wnd);
	    static void wndPassFocusCallback(GLFWwindow* wnd, int focus);
	    static void wndPassIconifiedCallback(GLFWwindow* wnd, int iconified);
	    static void wndPassResizeCallback(GLFWwindow* wnd, int width, int height);
	    static void wndPassFramebufferResizeCallback(GLFWwindow* wnd, int width, int height);
	    static void wndPassPositionCallback(GLFWwindow* wnd, int x, int y);
	    static void wndPassCursorEnterCallback(GLFWwindow* wnd, int enter);
	    static void wndPassCursorPositionCallback(GLFWwindow* wnd, double x, double y);
	    static void wndPassScrollCallback(GLFWwindow* wnd, double x, double y);
	    static void wndPassKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	    static void wndPassMouseCallback(GLFWwindow* window, int button, int action, int mods);

	    static GLFWwindow* getGLFWHandle(WindowHandle const& wnd);
	    static WindowHandle getWindowHandle(GLFWwindow* wnd);
	    static Input& getWindowInput(WindowHandle const& wnd);
	    static Input::Key glfwKey2InputKey(int key);
	    static Input::Key glfwButton2InputKey(int button);
	    static Input::KeyState glfwKeyState2InputKeyState(int keyState);
	    static Input::Modifier glfwModifier2InputModifier(int mod);

	    HandleGenerator m_wndHandleGen;

	    static WndErrorCallback s_errorCallback;
	    static std::unordered_map<WindowHandle, GLFWwindow*> s_wnd2GlfwMap;
	    static std::unordered_map<GLFWwindow*, WindowHandle> s_glfw2WndMap;
	    static std::unordered_map<WindowHandle, Input> s_wnd2Input;
	    static std::unordered_map<WindowHandle, WndCloseCallback> s_closeCallbacks;
	    static std::unordered_map<WindowHandle, WndFocusCallback> s_focusCallbacks;
	    static std::unordered_map<WindowHandle, WndIconifiedCallback> s_iconifiedCallbacks;
	    static std::unordered_map<WindowHandle, WndResizeCallback> s_resizeCallbacks;
	    static std::unordered_map<WindowHandle, WndFramebufferResizeCallback> s_frameResizeCallbacks;
	    static std::unordered_map<WindowHandle, WndPositionCallback> s_positionCallbacks;
	    static std::unordered_map<WindowHandle, WndCursorEnterCallback> s_cursorEnterCallbacks;
	    static std::unordered_map<WindowHandle, WndCursorPositionCallback> s_cursorPositionCallbacks;
	    static std::unordered_map<WindowHandle, WndScrollCallback> s_scrollCallbacks;
	    static std::unordered_map<WindowHandle, WndInputCallback> s_inputCallbacks;

	    struct TextureHandleGL : public TextureHandleInternal
	    {
		private:
//		    GLuint m_handle;
		    GLenum m_type;
		    friend class GLOpenGL33;
	    };

	    TextureHandleGL* m_pBoundTexture = nullptr;

	    static GLenum texType2GL(TextureType type);
	    static GLint pixelFormat2GL(PixelFormat format);
	    static GLenum pixelType2GL(PixelType type);
	    static GLenum rowAlignment2GL(RowAlignment align);
	    static GLenum minFilter2GL(MinFilter filter);
	    static GLenum magFilter2GL(MagFilter filter);
	    static GLenum compPixelFormat2GL(PixelFormatCompressed format);

	    struct ShaderHandleGL : public ShaderHandleInternal
	    {
		private:
//		    GLuint m_handle;
		    friend class GLOpenGL33;
	    };
	    struct ShaderProgramHandleGL : public ShaderProgramHandleInternal
	    {
		private:
//		    GLuint m_handle;
		    friend class GLOpenGL33;
	    };
	    struct ShaderAttributeHandleGL : public ShaderAttributeHandleInternal
	    {
		private:
//		    GLint m_handle;
		    friend class GLOpenGL33;
	    };
	    struct ShaderUniformHandleGL : public ShaderUniformHandleInternal
	    {
		private:
//		    GLint m_handle;
		    friend class GLOpenGL33;
	    };

	    static GLenum shaderType2GL(ShaderType type);
    };
}

#endif /* GLOPENGL33_H_ */
