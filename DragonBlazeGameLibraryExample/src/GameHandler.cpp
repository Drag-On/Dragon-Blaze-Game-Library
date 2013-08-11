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
void GameHandler::init(BaseGameWindow* wnd)
{
	BasicGame::init(wnd);

	// Create shader
	const char* vert = "attribute vec2 coord2d;"
			"attribute vec3 v_color;"
			"varying vec3 f_color;"
			"void main(void)"
			"{"
			"	gl_Position = vec4(coord2d, 0.0, 1.0);"
			"	f_color = v_color;"
			"}";
	const char* frag = "varying vec3 f_color;"
			"uniform float fade;"
			"void main(void)"
			"{"
			"	gl_FragColor = vec4(f_color.r, f_color.g, f_color.b, fade);"
			"}";
	_pShaderProgram = new ShaderProgram(vert, frag);
	int attributeHandle = _pShaderProgram->getAttributeHandle("coord2d");

	// Mesh
	GLfloat triangle_vertices[] =
	{ 0.0, 0.8, //
			-0.8, -0.8, //
			0.8, -0.8, };
	Mesh::AttributeFormat* format = new Mesh::AttributeFormat();
	format->attributeHandle = attributeHandle;
	format->size = 2;
	format->type = GL_FLOAT;
	format->normalized = GL_FALSE;
	format->stride = 0;
	format->pointer = 0;
	_pMesh = new Mesh(triangle_vertices, sizeof(triangle_vertices), format);
	// Don't delete vertices or format! Mesh does it.

	// Add some color data
	GLfloat triangle_colors[] =
	{ 1.0, 1.0, 0.0, //
			1.0, 0.0, 1.0, //
			1.0, 0.0, 0.0, };
	Mesh::AttributeFormat* colorFormat = new Mesh::AttributeFormat();
	colorFormat->attributeHandle = _pShaderProgram->getAttributeHandle(
			"v_color");
	colorFormat->size = 3;
	colorFormat->type = GL_FLOAT;
	colorFormat->normalized = GL_FALSE;
	colorFormat->stride = 0;
	colorFormat->pointer = 0;
	_pMesh->setColorData(triangle_colors, sizeof(triangle_colors), colorFormat);
}

/**
 * @brief Gets called once a frame before rendering takes place
 * @param wnd Window that is being updated
 */
void GameHandler::update(BaseGameWindow* wnd)
{
	BasicGame::update(wnd);
}

/**
 * @brief Gets called once a frame after updating
 * @param wnd Window that is being rendered
 */
void GameHandler::render(BaseGameWindow* wnd, RenderContext* rc)
{
	BasicGame::render(wnd, rc);

	rc->useShader(_pShaderProgram);
	float curFade = sinf(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * (2 * M_PI) / 5)
			/ 2 + 0.5;
	_pShaderProgram->setUniformFloat(_pShaderProgram->getUniformHandle("fade"),
			curFade);
	rc->render(_pMesh);
}
