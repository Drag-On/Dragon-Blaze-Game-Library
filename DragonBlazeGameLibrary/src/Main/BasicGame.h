/*
 * BasicGame.h
 *
 *  Created on: 06.08.2013
 *      Author: Drag-On
 */

#ifndef BASICGAME_H_
#define BASICGAME_H_

#include <GL/glew.h> // automatically includes gl.h
#include <GL/glut.h> // GLUT for base windowing setup
#include "../Window/BaseGameWindow.h"
#include "../Graphics/RenderContext.h"
#include "Log.h"

namespace DBGL
{
class BaseGameWindow;

/**
 * @brief Base class for all games. Processes initial configuration.
 */
class BasicGame
{
	friend class BaseGameWindow;

public:
	/**
	 * Constructor
	 * @param argc Amount of arguments passed to the application
	 * @param argv Array of argument values
	 * @param title Window title
	 * @param width Window width in pixels
	 * @param height Window height in pixels
	 * @param displayMode Binary OR connected flags, i.e. GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH
	 */
	BasicGame(int argc, char* argv[], const char* title = "DBGL Window",
			unsigned int width = 640, unsigned int height = 480,
			unsigned int displayMode = GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE
					| GLUT_DEPTH);

	/**
	 * Destructor
	 */
	virtual ~BasicGame();

	/**
	 * @brief Gets called once a window is initialized
	 * @param wnd Window that is being initialized
	 */
	virtual void init(BaseGameWindow* wnd, RenderContext* rc);

	/**
	 * @brief Gets called once a frame before rendering takes place
	 * @param wnd Window that is being updated
	 */
	virtual void update(BaseGameWindow* wnd, RenderContext* rc);

	/**
	 * @brief Gets called once a frame after updating
	 * @param wnd Window that is being rendered
	 */
	virtual void render(BaseGameWindow* wnd, RenderContext* rc);

	/**
	 * @brief Starts the main loop, showing and updating all windows
	 */
	const void run();

	/**
	 * @brief Exits all game processes
	 */
	const void exit() const;

private:
	BaseGameWindow* _pWnd; // Window holding the render context

	/**
	 * @brief Initializes the rendering process
	 * @param wnd Window holding the rendering context
	 */
	const void preRender(BaseGameWindow* wnd);

	/**
	 * @brief Finishes the rendering process for this frame
	 * @param wnd Window holding the rendering context
	 */
	const void postRender(BaseGameWindow* wnd);
};
} /* namespace DBGL */
#endif /* BASICGAME_H_ */
