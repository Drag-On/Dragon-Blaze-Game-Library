/*
 * BaseGameWindow.h
 *
 *  Created on: 05.08.2013
 *      Author: Drag-On
 */

#ifndef BASEGAMEWINDOW_H_
#define BASEGAMEWINDOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <GL/glew.h> // automatically includes gl.h
#include <GL/glut.h> // GLUT for base windowing setup
#include <GL/freeglut_ext.h> // GLUT extensions
#include "Input.h"
#include "../Main/Log.h"
#include "../Main/BasicGame.h"
#include "../Graphics/RenderContext.h"

namespace DBGL
{

class BasicGame;

/**
 * @brief Most basic window class. Implements basic functions for window and input handling
 */
class BaseGameWindow
{
	friend class BasicGame;

public:

	/**
	 * Constructor
	 * @param title Window title
	 * @param width Window width in pixels
	 * @param height Window height in pixels
	 * @param displayMode Binary OR connected flags, i.e. GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH
	 * @brief Allows to pass the window title, arguments, set the window size and display mode manually
	 */
	BaseGameWindow(const char* title = "DBGL Window", unsigned int width = 640,
			unsigned int height = 480,
			unsigned int displayMode = GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE
					| GLUT_DEPTH);

	/**
	 * Destructor
	 */
	virtual ~BaseGameWindow();

	/**
	 * @brief Closes the window immediately
	 */
	void close();

	/**
	 * @brief Sets the current window position immediately
	 * @param x X coordinate
	 * @param y Y coordinate
	 */
	void setPosition(unsigned int x, unsigned int y) const;

	/**
	 * @return Current x position
	 */
	int getX() const;

	/**
	 * @return Current y position
	 */
	int getY() const;

	/**
	 * @brief Sets the window size immediately
	 * @param width New window width
	 * @param height New window height
	 */
	void setSize(unsigned int width, unsigned int height) const;

	/**
	 * @return Current window width
	 */
	int getWidth() const;

	/**
	 * @return Current window height
	 */
	int getHeight() const;

	/**
	 * @brief Toggles fullscreen mode of this window
	 * @param fullscreen Flag indicating if fullscreen should be on or off
	 */
	void setFullscreen(bool fullscreen) const;

	/**
	 * @return True in case this window is currently in fullscreen mode, otherwise false
	 */
	bool isFullscreen() const;

	/**
	 * @brief Makes this window the currently active window
	 */
	void setActive() const;

	/**
	 * @return Indicates, if this window is currently active
	 */
	bool isActive() const;

	/**
	 * @return ID of this window
	 */
	int getId() const;

	/**
	 * @return The input handler of this window
	 */
	const Input* getInput() const;

	/**
	 * @return The render context of this window
	 */
	const RenderContext* getRC() const;

	/**
	 * @return Time in milliseconds since last frame
	 */
	unsigned int getDeltaTime() const;

protected:
	/**
	 * @brief Renders everything to screen
	 */
	virtual void render();

	/**
	 * @brief Updates everything before rendering
	 */
	virtual void update();

	/**
	 * @brief Handles window resize
	 * @param width New window width
	 * @param height New window height
	 */
	virtual void resize(int width, int height);

	/**
	 * @brief Handles key pressed events
	 */
	virtual void keyPressed(KEY key, char character);

	/**
	 * @brief Handles key released events
	 */
	virtual void keyReleased(KEY key, char character);

	/**
	 * @brief Handles key pressed events
	 */
	virtual void mouseDragged(int x, int y, int lastX, int lastY);

	/**
	 * @brief Handles key pressed events
	 */
	virtual void mouseWheel(int change, int x, int y);

private:
	static std::list<BaseGameWindow*> windows; // List of all windows
	static unsigned int deltaTime; // Time since last frame
	static unsigned int lastCumulativeTime; // Cumulative time since application start
	static unsigned int fpsTimeBase; // Time since application start when we last computed the frame rate
	static unsigned int fpsAmount; // Amount of frames since last computation of frame rate
	static unsigned int fps; // Current frame rate

	const char* _title; // Window title
	unsigned int _id; // Window ID
	Input* _pInput; // Input handler
	RenderContext* _pRC; // Render context
	BasicGame* _game; // Game handler that owns this window

	/**
	 * @brief Sets the owner of this window
	 * @param game Game handler owning this window
	 */
	void setOwner(BasicGame* game);

	/**
	 * @brief Called once a frame, updates and renders all windows
	 */
	static void onDisplay();

	/**
	 * @brief Called on every resize operation
	 * @param width New window width
	 * @param height New window height
	 */
	static void onResize(int width, int height);

	/**
	 * @brief Called on every keyboard input
	 * @param key Key that got pressed
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	static void onKeyInput(unsigned char key, int x, int y);

	/**
	 * @brief Called on every mouse input
	 * @param button Mouse button that changed state
	 * @param state New state of the button
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	static void onMouseInput(int button, int state, int x, int y);

	/**
	 * @brief Called when the mouse got moved with a mouse button pressed down
	 * @param x X mouse coordinate
	 * @param y Y mouse coordinate
	 */
	static void onMouseDrag(int x, int y);

	/**
	 * @brief Called when the mouse got moved
	 * @param x X mouse coordinate
	 * @param y Y mouse coordinate
	 */
	static void onMouseMove(int x, int y);

	/**
	 * @brief Called once a special key on the keyboard got pressed
	 * @param key Special key that got pressed
	 * @param x X mouse coordinate
	 * @param y Y mouse coordinate
	 */
	static void onSpecialKeyInput(int key, int x, int y);

	/**
	 * @brief Called once a key was released
	 * @param key Key that has been released
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	static void onKeyInputUp(unsigned char key, int x, int y);

	/**
	 * @brief Called once a special key was released
	 * @param key Key that has been released
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	static void onSpecialKeyUp(int key, int x, int y);

	/**
	 * @brief Called once the mouse wheel changed
	 * @param button Mouse button
	 * @param dir Direction of scroll wheel
	 * @param x Mouse x coordinate
	 * @param y Mouse y coordinate
	 */
	static void onMouseWheel(int button, int dir, int x, int y);

	/**
	 * Called when the current draw process has been finished
	 */
	static void onIdle();
};

} /* namespace DBGL */
#endif /* BASEGAMEWINDOW_H_ */
