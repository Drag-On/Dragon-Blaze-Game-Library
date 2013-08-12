/*
 * BasicGame.cpp
 *
 *  Created on: 06.08.2013
 *      Author: Drag-On
 */

#include "BasicGame.h"

namespace DBGL
{

/**
 * Constructor
 * @param argc Amount of arguments passed to the application
 * @param argv Array of argument values
 * @param title Window title
 * @param width Window width in pixels
 * @param height Window height in pixels
 * @param displayMode Binary OR connected flags, i.e. GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH
 */
BasicGame::BasicGame(int argc, char* argv[], const char* title,
		unsigned int width, unsigned int height, unsigned int displayMode)
{
	LOG->info("Dragon Blaze Game Library - Development Build");

	// Initialize glut
	glutInit(&argc, argv);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	// Create window
	_pWnd = new BaseGameWindow(title, width, height, displayMode);
	_pWnd->setOwner(this);
	// Set a default clear color
	_pWnd->getRC()->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

/**
 * Destructor
 */
BasicGame::~BasicGame()
{
	delete _pWnd;
	_pWnd = NULL;
}

/**
 * @brief Gets called once a window is initialized
 * @param wnd Window that is being initialized
 */
void BasicGame::init(BaseGameWindow* wnd, RenderContext* rc)
{
}

/**
 * @brief Gets called once a frame before rendering takes place
 * @param wnd Window that is being updated
 */
void BasicGame::update(BaseGameWindow* wnd, RenderContext* rc)
{
}

/**
 * @brief Gets called once a frame after updating
 * @param wnd Window that is being rendered
 */
void BasicGame::render(BaseGameWindow* wnd, RenderContext* rc)
{
}

/**
 * @brief Starts the main loop, showing and updating all windows
 */
const void BasicGame::run()
{
	// Initialize glew
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		LOG->error("Unable to initialize GLEW: %s",
				glewGetErrorString(glew_status));
		return;
	}
	if (!GLEW_VERSION_2_0)
	{
		LOG->error("Your graphic card does not support OpenGL 2.0.");
		return;
	}
	if ((glutGet(GLUT_INIT_DISPLAY_MODE) & GLUT_ALPHA) == GLUT_ALPHA)
	{
		// Enable alpha mode
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glEnable(GL_DEPTH_TEST);

	// Initialize
	init(_pWnd, _pWnd->_pRC);

	// Run main loop
	glutMainLoop();
}

/**
 * @brief Initializes the rendering process
 * @param wnd Window holding the rendering context
 */
const void BasicGame::preRender(BaseGameWindow* wnd)
{
	wnd->getRC()->clear();
}

/**
 * @brief Finishes the rendering process for this frame
 * @param wnd Window holding the rendering context
 */
const void BasicGame::postRender(BaseGameWindow* wnd)
{
	wnd->getRC()->swapBuffers();
}

} /* namespace DBGL */
