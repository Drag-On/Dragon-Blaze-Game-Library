/*
 * GameHandler.cpp
 *
 *  Created on: 10.08.2013
 *      Author: Drag-On
 */

#include "GameHandler.h"

/**
 * Constructor
 * @param argc Amount of arguments passed to the application
 * @param argv Array of argument values
 * @param title Window title
 * @param width Window width in pixels
 * @param height Window height in pixels
 * @param displayMode Binary OR connected flags, i.e. GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH
 */
GameHandler::GameHandler(int argc, char* argv[], const char* title,
		unsigned int width, unsigned int height, unsigned int displayMode) :
		BasicGame(argc, argv, title, width, height, displayMode)
{
	_pShaderProgram = NULL;
	_pMesh = NULL;
}

/**
 * Destructor
 */
GameHandler::~GameHandler()
{
	delete _pShaderProgram;
	_pShaderProgram = NULL;

	delete _pMesh;
	_pMesh = NULL;
}

/**
 * @brief Gets called once a window is initialized
 * @param wnd Window that is being initialized
 */
void GameHandler::init(BaseGameWindow* wnd, RenderContext* rc)
{
	BasicGame::init(wnd, rc);

	// Create shader
	const char* vert = "uniform mat4 m_mvp;"
			"attribute vec3 v_vertex;"
			"attribute vec3 v_color;"
			"varying vec3 f_color;"
			"void main(void)"
			"{"
			"	gl_Position = m_mvp  * vec4(v_vertex, 1.0);"
			"	f_color = v_color;"
			"}";
	const char* frag = "varying vec3 f_color;"
			"uniform float fade;"
			"void main(void)"
			"{"
			"	gl_FragColor = vec4(f_color.r, f_color.g, f_color.b, fade);"
			"}";
	_pShaderProgram = new ShaderProgram(vert, frag);

	// Mesh
	_pMesh = Mesh::createCube();
}

/**
 * @brief Gets called once a frame before rendering takes place
 * @param wnd Window that is being updated
 */
void GameHandler::update(BaseGameWindow* wnd, RenderContext* rc)
{
	BasicGame::update(wnd, rc);

	float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;
	glm::vec3 axis_y(0.0, 1.0, 0.0);
	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);

	glm::mat4 model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0, 0.0, -4.0));
	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0),
			glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(45.0f,
			1.0f * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT),
			0.1f, 10.0f);
	rc->setModelMatrix(model * anim);
	rc->setViewMatrix(view);
	rc->setProjectionMatrix(projection);

	float curFade = sinf(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * (2 * M_PI) / 5)
			/ 2 + 0.5;
	glm::vec3 axis_z(0, 0, 1);
	_pShaderProgram->setUniformFloat(_pShaderProgram->getUniformHandle("fade"),
			curFade);
}

/**
 * @brief Gets called once a frame after updating
 * @param wnd Window that is being rendered
 */
void GameHandler::render(BaseGameWindow* wnd, RenderContext* rc)
{
	BasicGame::render(wnd, rc);

	rc->useShader(_pShaderProgram);
	rc->render(_pMesh);
}
