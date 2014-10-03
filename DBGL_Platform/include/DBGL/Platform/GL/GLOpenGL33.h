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
	    virtual void wndShow(WindowHandle wnd);
	    virtual void wndHide(WindowHandle wnd);
	    virtual void wndClose(WindowHandle wnd);
	    virtual void wndDestroy(WindowHandle wnd);
	    virtual bool wndCheckFocus(WindowHandle wnd);
	    virtual bool wndCheckIconified(WindowHandle wnd);
	    virtual bool wndCheckVisible(WindowHandle wnd);
	    virtual bool wndCheckResizable(WindowHandle wnd);
	    virtual bool wndCheckDecorations(WindowHandle wnd);
	    virtual bool wndCheckClose(WindowHandle wnd);
	    virtual void wndSetTitle(WindowHandle wnd, std::string const& title);
	    virtual void wndGetSize(WindowHandle wnd, int& width, int& height);
	    virtual void wndSetSize(WindowHandle wnd, int width, int height);
	    virtual void wndGetFrameSize(WindowHandle wnd, int& width, int& height);
	    virtual void wndGetPos(WindowHandle wnd, int& x, int& y);
	    virtual void wndSetPos(WindowHandle wnd, int x, int y);
	    virtual void wndMakeCurrent(WindowHandle wnd);
	    virtual void wndGetCursorPos(WindowHandle wnd, double& x, double& y);
	    virtual void wndSetCursorPos(WindowHandle wnd, double x, double y);
	    virtual Input& wndGetInput(WindowHandle wnd);
	    virtual void wndSwapBuffers(WindowHandle wnd);
	    virtual void wndPollEvents();
	    virtual double wndGetTime();
	    virtual void wndSetErrorCallback(WndErrorCallback callback);
	    virtual void wndSetCloseCallback(WindowHandle wnd, WndCloseCallback callback);
	    virtual void wndSetFocusCallback(WindowHandle wnd, WndFocusCallback callback);
	    virtual void wndSetIconifiedCallback(WindowHandle wnd, WndIconifiedCallback callback);
	    virtual void wndSetResizeCallback(WindowHandle wnd, WndResizeCallback callback);
	    virtual void wndSetFramebufferResizeCallback(WindowHandle wnd, WndFramebufferResizeCallback callback);
	    virtual void wndSetPositionCallback(WindowHandle wnd, WndPositionCallback callback);
	    virtual void wndSetCursorEnterCallback(WindowHandle wnd, WndCursorEnterCallback callback);
	    virtual void wndSetCursorPositionCallback(WindowHandle wnd, WndCursorPositionCallback callback);
	    virtual void wndSetScrollCallback(WindowHandle wnd, WndScrollCallback callback);
	    virtual void wndSetInputCallback(WindowHandle wnd, WndInputCallback callback);
	    virtual TextureHandle texGenerate(TextureType type);
	    virtual void texBind(TextureHandle handle);
	    virtual void texWrite(unsigned int level, unsigned int width,
		    unsigned int height, PixelFormat format, PixelType type, void* data);

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

	    static GLFWwindow* getGLFWHandle(WindowHandle wnd);
	    static WindowHandle getWindowHandle(GLFWwindow* wnd);
	    static Input& getWindowInput(WindowHandle wnd);
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
    };
}

#endif /* GLOPENGL33_H_ */
