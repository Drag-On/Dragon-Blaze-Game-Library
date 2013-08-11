/*
 * RenderContext.h
 *
 *  Created on: 09.08.2013
 *      Author: Drag-On
 */

#ifndef RENDERCONTEXT_H_
#define RENDERCONTEXT_H_

#include <GL/glew.h>
#include <GL/glut.h>
#include "../Main/Log.h"
#include "ShaderProgram.h"
#include "Mesh.h"

namespace DBGL
{

class Mesh;

/**
 * Defines an interface to place draw calls
 */
class RenderContext
{
public:
	/**
	 * Constructor
	 */
	RenderContext();

	/**
	 * Destructor
	 */
	virtual ~RenderContext();

	/**
	 * Sets the passed shader program in use
	 */
	void useShader(ShaderProgram* shader);

	/**
	 * @brief Renders a mesh to screen using the currently active shader program
	 * @param mesh Mesh to render
	 */
	void render(Mesh* mesh) const;

	/**
	 * @brief Sets the color that is used to clear the screen before rendering
	 * @param r Red channel
	 * @param g Green channel
	 * @param b Blue channel
	 * @param a Alpha channel
	 */
	void setClearColor(float r, float g, float b, float a) const;

	/**
	 * @brief Clears the render context with the clear color
	 */
	void clear() const;

	/**
	 * @brief Displays everything and swaps buffers
	 */
	void swapBuffers() const;

	/**
	 * @brief Uploads some data to the graphics card
	 * @param data Raw data to push
	 * @param length Length of the data array
	 * @param vboHandle Handle of the vertex buffer to use. If this is negative a new buffer is created.
	 * @param usage Specifies the expected usage pattern
	 * @return The handle of the vertex buffer, the data has been uploaded
	 */
	static const GLuint createVBOFloat(GLfloat* data, int length,
			GLuint vboHandle = GL_INVALID_VALUE, GLenum usage = GL_STATIC_DRAW);

private:
	ShaderProgram* _curShader; // Current "in use" shader
};

} /* namespace DBGL */
#endif /* RENDERCONTEXT_H_ */
