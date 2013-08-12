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
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../Main/Log.h"
#include "ShaderProgram.h"
#include "Mesh.h"

namespace DBGL
{

#define ATTRIBUTE_VERTEX "v_vertex"
#define ATTRIBUTE_COLOR "v_color"

class Mesh;

/**
 * @brief Defines an interface to place draw calls
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
	 * Sets the model matrix
	 * @param modelMat New model matrix
	 */
	void setModelMatrix(glm::mat4 modelMat);

	void setViewMatrix(glm::mat4 viewMat);

	void setProjectionMatrix(glm::mat4 projectionMat);

	/**
	 * @brief Creates a buffer on the graphics card
	 * @param data Raw data to push
	 * @param length Length of the data array
	 * @param bufferHandle Handle of a buffer to overwrite. If this equals GL_INVALID_VALUE a new buffer is created.
	 * @param usage Specifies the expected usage pattern, defaults to GL_STATIC_DRAW
	 * @param type Specifies buffer type, i.e. vertex buffer or index buffer, defaults to GL_ARRAY_BUFFER
	 * @return The handle of the created buffer object
	 */
	static const GLuint createBuffer(void* data, int length,
			GLuint bufferHandle =
			GL_INVALID_VALUE, GLenum usage = GL_STATIC_DRAW, int type =
			GL_ARRAY_BUFFER);

private:
	ShaderProgram* _pCurShader; // Current "in use" shader
	glm::mat4 _modelMat; // Model matrix
	glm::mat4 _viewMat; // View matrix
	glm::mat4 _projectionMat; // Model matrix
};

} /* namespace DBGL */
#endif /* RENDERCONTEXT_H_ */
