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

namespace dbgl
{
    /**
     * @brief Base class for all windows
     * @details Windows need to be constructed by the @see WindowManager and
     * 		will automatically taken care of by it. This includes freeing
     * 		all memory after the window has been closed.
     * 		All classes that derive from AbstractWindow need to add
     * 		WindowManager as their friend, otherwise construction will
     * 		not work properly.
     */
    class AbstractWindow
    {
	public:
	    /**
	     * @brief Frees all memory allocated to this window
	     */
	    virtual ~AbstractWindow();
	    /**
	     * @brief Makes this window show
	     */
	    virtual void show() final;
	    /**
	     * @brief Hides the window
	     */
	    virtual void hide() final;
	    /**
	     * @brief Closes the window permanently
	     */
	    virtual void close() final;
	    /**
	     * @return True in case the window is currently in focus, otherwise false
	     */
	    virtual bool hasFocus() final;
	    /**
	     * @return True in case the window is currently iconified, otherwise false
	     */
	    virtual bool isIconified() final;
	    /**
	     * @return True in case the window is currently visible, otherwise false
	     */
	    virtual bool isVisible() final;
	    /**
	     * @return True in case the window is resizable, otherwise false
	     */
	    virtual bool isResizable() final;
	    /**
	     * @return True in case the window has decorations (i.e. borders etc.),
	     * 		otherwise false
	     */
	    virtual bool isDecorated() final;
	    /**
	     * @return The window's title
	     */
	    virtual const char* getTitle() final;
	    /**
	     * @param title The new title to set
	     */
	    virtual void setTitle(const char* title) final;
	    /**
	     * @return Width of the window in screen dimensions
	     */
	    virtual int getWidth() final;
	    /**
	     * @return Height of the window in screen dimensions
	     */
	    virtual int getHeight() final;
	    /**
	     * @brief Sets a new window size
	     * @param width New width
	     * @param height New height
	     */
	    virtual void setSize(int width, int height) final;
	    /**
	     * @return Width of the actual rendering space in pixels
	     */
	    virtual int getFrameWidth() final;
	    /**
	     * @return Height of the actual rendering space in pixels
	     */
	    virtual int getFrameHeight() final;
	    /**
	     * @return X coordinate on screen
	     */
	    virtual int getX() final;
	    /**
	     * @return Y coordinate on screen
	     */
	    virtual int getY() final;
	    /**
	     * @brief Moves the window to a new location on screen
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    virtual void setPos(int x, int y) final;
	    /**
	     * @return True in case the window is in fullscreen mode,
	     * 		otherwise false
	     */
	    virtual bool isFullscreen() final;
	    /**
	     * @brief Provides the possibility to switch between fullscreen
	     * 	      and window mode
	     * @param fullscreen Indicates if window should switch to fullscreen
	     * 			 or back to window
	     */
	    virtual void setFullscreen(bool fullscreen) final;
	    /**
	     * @brief Gets called once a frame before @see update
	     */
	    virtual void preUpdate();
	    /**
	     * @brief Gets called once a frame and should update everything
	     */
	    virtual void update() = 0;
	    /**
	     * @brief Gets called once a frame after @see update
	     */
	    virtual void postUpdate();
	    /**
	     * @brief Gets called once a frame before @see render
	     */
	    virtual void preRender();
	    /**
	     * @brief Gets called once a frame and should render everything
	     */
	    virtual void render() = 0;
	    /**
	     * @brief Gets called once a frame after @see update
	     */
	    virtual void postRender();

	protected:
	    // Constructors
	    AbstractWindow();
	    AbstractWindow(const char* title);
	    AbstractWindow(const char* title, int width, int height);
	    AbstractWindow(const char* title, int width, int height,
		    bool fullscreen);
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

	    friend class WindowManager;
    };
}

#endif /* ABSTRACTWINDOW_H_ */
