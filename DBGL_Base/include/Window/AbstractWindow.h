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
	    /**
	     * @brief Constructs a window of size 800x600 with a standard title
	     */
	    AbstractWindow();
	    /**
	     * @brief Constructs a window of size 800x600
	     * @param title Title of the window
	     */
	    AbstractWindow(const char* title);
	    /**
	     * @brief Constructs a window
	     * @param title Title of the window
	     * @param width Width of the rendering plane
	     * @param height Height of the rendering plane
	     */
	    AbstractWindow(const char* title, int width, int height);
	    /**
	     * @brief Constructs a window
	     * @param title Title of the window
	     * @param width Width of the rendering plane
	     * @param height Height of the rendering plane
	     * @param fullscreen Indicates if it is opened to fullscreens
	     */
	    AbstractWindow(const char* title, int width, int height,
		    bool fullscreen);
	    // Callbacks
	    /**
	     * @brief Called when the window is closed
	     */
	    virtual void closeCallback() = 0;
	    /**
	     * @brief Called when the focus state changes
	     * @param focused True if the window got focused, otherwise false
	     */
	    virtual void focusCallback(int focused) = 0;
	    /**
	     * @brief Called when the iconified state changes
	     * @param iconified True if the window got iconified, otherwise false
	     */
	    virtual void iconifiedCallback(int iconified) = 0;
	    /**
	     * @brief Called when the window needs to be refreshed
	     */
	    virtual void refreshCallback() = 0;
	    /**
	     * @brief Called when the window was resized
	     * @param width New width
	     * @param height New height
	     */
	    virtual void sizeCallback(int width, int height) = 0;
	    /**
	     * @brief Called when the rendering plane was resized
	     * @param width New width
	     * @param height New height
	     */
	    virtual void framebufferSizeCallback(int width, int height) = 0;
	    /**
	     * @brief Called whe the window was moved
	     * @param xpos New x coordinate
	     * @param ypos New y coordinate
	     */
	    virtual void windowPosCallback(int xpos, int ypos) = 0;
	    /**
	     * @brief Called when a unicode character was typed in
	     * @param codepoint Unicode code point of the character
	     */
	    virtual void characterCallback(unsigned int codepoint) = 0;
	    /**
	     * @brief Called when the cursor enters or exits the window
	     * @param entered True if the cursor entered the window, otherwise false
	     */
	    virtual void cursorEnterCallback(int entered) = 0;
	    /**
	     * @brief Called when the cursor was moved
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    virtual void cursorCallback(double x, double y) = 0;
	    /**
	     * @brief Called when a mouse button was pressed
	     * @param button Button that was pressed
	     * @param action GLFW_PRESS or GLFW_RELEASE
	     * @param mods Bit field of modifier keys
	     */
	    virtual void mouseButtonCallback(int button, int action,
		    int mods) = 0;
	    /**
	     * @brief Called when the scroll wheel was used
	     * @param xOffset Scroll amount in x direction
	     * @param yOffset Scroll amount in y direction
	     */
	    virtual void scrollCallback(double xOffset, double yOffset) = 0;
	    /**
	     * @brief Called when a key was pressed
	     * @param key Key that was pressed
	     * @param scancode System-specific scancode
	     * @param action GLFW_PRESS or GLFW_RELEASE or GLFW_REPEAT
	     * @param mods Bit field of modifier keys
	     */
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
