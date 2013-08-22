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
	_pMesh2 = NULL;
	_pTex = NULL;
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

	delete _pMesh2;
	_pMesh2 = NULL;

	delete _pTex;
	_pTex = NULL;
}

/**
 * @brief Gets called once a window is initialized
 * @param wnd Window that is being initialized
 */
void GameHandler::init(BaseGameWindow* wnd, RenderContext* rc)
{
	BasicGame::init(wnd, rc);

	// Create shader
	_pShaderProgram = new ShaderProgram(
			"../DragonBlazeGameLibrary/src/Graphics/Shaders/SimpleDiffuse.vert",
			"../DragonBlazeGameLibrary/src/Graphics/Shaders/SimpleDiffuse.frag",
			true);

	// Mesh
	_pMesh = Mesh::createCube();
	_pMesh2 = Mesh::createPyramid();
	_pTex = new Texture("tex.jpg");
	_pMesh->setTexture(_pTex);
	_pMesh2->setTexture(_pTex);
}

/**
 * @brief Gets called once a frame before rendering takes place
 * @param wnd Window that is being updated
 */
void GameHandler::update(BaseGameWindow* wnd, RenderContext* rc)
{
	BasicGame::update(wnd, rc);

	if (wnd->getInput()->isReleased(KEY_F1))
	{
		Mesh* temp = _pMesh;
		_pMesh = _pMesh2;
		_pMesh2 = temp;
	}
}

/**
 * @brief Gets called once a frame after updating
 * @param wnd Window that is being rendered
 */
void GameHandler::render(BaseGameWindow* wnd, RenderContext* rc)
{
	BasicGame::render(wnd, rc);

	rc->useShader(_pShaderProgram);
	float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;

	glm::vec3 axis_y(0.0, 1.0, 0.0);
	glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle * 3.0f,
			glm::vec3(1, 0, 0)) *  // X axis
			glm::rotate(glm::mat4(1.0f), angle * 2.0f, glm::vec3(0, 1, 0)) * // Y axis
			glm::rotate(glm::mat4(1.0f), angle * 4.0f, glm::vec3(0, 0, 1)); // Z axis

	glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0),
			glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projection = glm::perspective(45.0f,
			1.0f * glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT),
			0.1f, 10.0f);

	glm::mat4 model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0, 0.0, -8.0));
	if (_pMesh2 != NULL)
	{
		rc->setModelMatrix(model);
		rc->render(_pMesh2);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
	rc->setModelMatrix(model * anim);
	rc->setViewMatrix(view);
	rc->setProjectionMatrix(projection);

	rc->render(_pMesh);
}
