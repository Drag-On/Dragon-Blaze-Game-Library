//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ABSTRACTWINDOW_H_
#define ABSTRACTWINDOW_H_

#include <stdlib.h>
#include <string>
#include "GLFW/glfw3.h"
#include "Log/Log.h"
#include "WindowManager.h"

namespace dbgl
{
    class AbstractWindow
    {
	    friend class WindowManager;

	public:
	    AbstractWindow();
	    virtual ~AbstractWindow();
	    virtual void show() final;
	    virtual void hide() final;
	    virtual void close() final;
	    virtual bool hasFocus() final;
	    virtual bool isIconified() final;
	    virtual bool isVisible() final;
	    virtual bool isResizable() final;
	    virtual bool isDecorated() final;
	    virtual const char* getTitle() final;
	    virtual void setTitle(const char* title) final;
	    virtual int getWidth() final;
	    virtual int getHeight() final;
	    virtual void setSize(int width, int height) final;
	    virtual int getFrameWidth() final;
	    virtual int getFrameHeight() final;
	    virtual int getX() final;
	    virtual int getY() final;
	    virtual void setPos(int x, int y) final;
	    virtual bool isFullscreen() final;
	    virtual void setFullscreen(bool fullscreen) final;
	    virtual void preUpdate();
	    virtual void update() = 0;
	    virtual void postUpdate();
	    virtual void preRender();
	    virtual void render() = 0;
	    virtual void postRender();

	protected:
	    // Callbacks
	    virtual void closeCallback() = 0;
	    virtual void focusCallback(int focused) = 0;
	    virtual void iconifiedCallback(int iconified) = 0;
	    virtual void refreshCallback() = 0;
	    virtual void sizeCallback(int width, int height) = 0;
	    virtual void framebufferSizeCallback(int width, int height) = 0;
	    virtual void windowPosCallback(int xpos, int ypos) = 0;
	    virtual void characterCallback(unsigned int codepoint) = 0;
	    virtual void cursorEnterCallback(int entered) = 0;
	    virtual void cursorCallback(double x, double y) = 0;
	    virtual void mouseButtonCallback(int button, int action,
		    int mods) = 0;
	    virtual void scrollCallback(double xOffset, double yOffset) = 0;
	    virtual void keyCallback(int key, int scancode, int action,
		    int mods) = 0;

	private:
	    static void errorCallback(int error, const char* description);

	    GLFWwindow* _pWndHandle = NULL;
	    std::string _title;
	    bool _isFullscreen;
	    unsigned int _fullscreenWidth, _fullscreenHeight; // Resolution for full screen
	    unsigned int _windowedWidth, _windowedHeight; // Resolution for window
    };
}

#endif /* ABSTRACTWINDOW_H_ */
