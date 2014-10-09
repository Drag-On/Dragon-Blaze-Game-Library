//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IWINDOW_H_
#define IWINDOW_H_

#include <string>

namespace dbgl
{
    class IWindow
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~IWindow() = default;
	    /**
	     * @brief Shows the window
	     */
	    virtual void show() = 0;
	    /**
	     * @brief Hides the window
	     */
	    virtual void hide() = 0;
	    /**
	     * @brief Marks the window to be closed permanently
	     */
	    virtual void close() = 0;
	    /**
	     * @return True in case the window is currently in focus, otherwise false
	     */
	    bool hasFocus() const = 0;
	    /**
	     * @return True in case the window is currently iconified, otherwise false
	     */
	    bool isIconified() const = 0;
	    /**
	     * @return True in case the window is currently visible, otherwise false
	     */
	    bool isVisible() const = 0;
	    /**
	     * @return True in case the window is resizable, otherwise false
	     */
	    bool isResizable() const = 0;
	    /**
	     * @return True in case the window has decorations (i.e. borders etc.),
	     * 		otherwise false
	     */
	    bool isDecorated() const = 0;
	    /**
	     * @return The window's title
	     */
	    std::string getTitle() const = 0;
	    /**
	     * @param title The new title to set
	     */
	    void setTitle(std::string* title) = 0;
	    /**
	     * @return Width of the window in screen dimensions
	     */
	    int getWidth() const = 0;
	    /**
	     * @return Height of the window in screen dimensions
	     */
	    int getHeight() const = 0;
	    /**
	     * @brief Sets a new window size
	     * @param width New width
	     * @param height New height
	     */
	    void setSize(int width, int height) = 0;
	    /**
	     * @return Width of the actual rendering space in pixels
	     */
	    int getFrameWidth() const = 0;
	    /**
	     * @return Height of the actual rendering space in pixels
	     */
	    int getFrameHeight() const = 0;
	    /**
	     * @return X coordinate on screen
	     */
	    int getX() const = 0;
	    /**
	     * @return Y coordinate on screen
	     */
	    int getY() const = 0;
	    /**
	     * @brief Moves the window to a new location on screen
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    void setPos(int x, int y) = 0;
	    /**
	     * @return True in case the window is in fullscreen mode,
	     * 		otherwise false
	     */
	    bool isFullscreen() const = 0;
	    /**
	     * @brief Provides the possibility to switch between fullscreen
	     * 	      and window mode
	     * @param fullscreen Indicates if window should switch to fullscreen
	     * 			 or back to window
	     */
	    void setFullscreen(bool fullscreen) = 0;
	    /**
	     * @brief Makes this window the current one
	     */
	    void makeCurrent() = 0;
	    /**
	     * @brief Grants access to the current cursor position inside of the window
	     * @param x X coordinate is stored here
	     * @param y Y coordinate is stored here
	     */
	    void getCursorPos(double& x, double& y) const = 0;
	    /**
	     * @brief Changes the cursor position inside of the window
	     * @param x New x coordinate
	     * @param y New y coordinate
	     */
	    void setCursorPos(double x, double y) = 0;
    };
}

#endif /* IWINDOW_H_ */
