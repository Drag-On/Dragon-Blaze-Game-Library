/*
 * GameHandler.h
 *
 *  Created on: 10.08.2013
 *      Author: Drag-On
 */

#ifndef GAMEHANDLER_H_
#define GAMEHANDLER_H_

#include <Main/BasicGame.h>
#include <Graphics/Mesh.h>
#include <Graphics/ShaderProgram.h>
#include <Graphics/RenderContext.h>
#include <math.h>

using namespace DBGL;

class GameHandler: public DBGL::BasicGame
{
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
	GameHandler(int argc, char* argv[], const char* title = "DBGL Window",
			unsigned int width = 640, unsigned int height = 480,
			unsigned int displayMode = GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE
					| GLUT_DEPTH);

	/**
	 * Destructor
	 */
	virtual ~GameHandler();

	/**
	 * @brief Gets called once a window is initialized
	 * @param wnd Window that is being initialized
	 */
	virtual void init(BaseGameWindow* wnd);

	/**
	 * @brief Gets called once a frame before rendering takes place
	 * @param wnd Window that is being updated
	 */
	virtual void update(BaseGameWindow* wnd);

	/**
	 * @brief Gets called once a frame after updating
	 * @param wnd Window that is being rendered
	 */
	virtual void render(BaseGameWindow* wnd, RenderContext* rc);

private:
	ShaderProgram* _pShaderProgram;
	Mesh* _pMesh;
};

#endif /* GAMEHANDLER_H_ */
