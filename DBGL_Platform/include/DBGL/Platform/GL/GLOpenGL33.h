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
	    virtual void wndShow(WindowHandle wnd);
	    virtual void wndHide(WindowHandle wnd);
	    virtual void wndClose(WindowHandle wnd);
	    virtual bool wndCheckFocus(WindowHandle wnd);
	    virtual bool wndCheckIconified(WindowHandle wnd);
	    virtual bool wndCheckVisible(WindowHandle wnd);
	    virtual bool wndCheckResizable(WindowHandle wnd);
	    virtual bool wndCheckDecorations(WindowHandle wnd);
	    virtual void wndSetTitle(WindowHandle wnd, std::string const& title);
	    virtual void wndGetSize(WindowHandle wnd, int& width, int& height);
	    virtual void wndSetSize(WindowHandle wnd, int width, int height);
	    virtual void wndGetFrameSize(WindowHandle wnd, int& width, int& height);
	    virtual void wndGetPos(WindowHandle wnd, int& x, int& y);
	    virtual void wndSetPos(WindowHandle wnd, int x, int y);
	    virtual void wndMakeCurrent(WindowHandle wnd);
	    virtual void wndGetCursorPos(WindowHandle wnd, double& x, double& y);
	    virtual void wndSetCursorPos(WindowHandle wnd, double x, double y);
	    virtual void wndSwapBuffers(WindowHandle wnd);
	private:
	    GLFWwindow* getGLFWHandle(WindowHandle wnd);

	    HandleGenerator m_wndHandleGen;
	    std::unordered_map<WindowHandle, GLFWwindow*> m_wndMap;
    };
}

#endif /* GLOPENGL33_H_ */
