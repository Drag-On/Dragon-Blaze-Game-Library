/*
 * RenderContext.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Drag-On
 */

#include "RenderContext.h"

#define ATTRIBUTE_VERTEX "a_vertex"

namespace DBGL
{

/**
 * Constructor
 */
RenderContext::RenderContext()
{
	_curShader = NULL;
}

/**
 * Destructor
 */
RenderContext::~RenderContext()
{
}

/**
 * Sets the passed shader program in use
 */
void RenderContext::useShader(ShaderProgram* shader)
{
	if (shader != NULL)
	{
		_curShader = shader;
		glUseProgram(_curShader->getHandle());
	}
}

/**
 * @brief Renders a mesh to screen using the currently active shader program
 * @param mesh Mesh to render
 */
void RenderContext::render(Mesh* mesh) const
{
	// Check if there is a shader in use
	if (_curShader == NULL)
	{
		LOG->warning("Tried to render mesh without active shader program.");
		return;
	}

	// Pass vertex data
	Mesh::AttributeFormat* vertexFormat = mesh->getVertexFormat();
	glEnableVertexAttribArray(vertexFormat->attributeHandle);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexVBOHandle());

	// Describe the vertex array format
	glVertexAttribPointer(vertexFormat->attributeHandle,// attribute
			vertexFormat->size,// number of elements per vertex
			vertexFormat->type,// the type of each element
			vertexFormat->normalized,// normalize?
			vertexFormat->stride,// no extra data between each position
			vertexFormat->pointer// offset of first element
	);

	// Pass color data
	Mesh::AttributeFormat* colorFormat = NULL;
	if(mesh->getColorData() != NULL)
	{
		colorFormat = mesh->getColorFormat();
		glEnableVertexAttribArray(colorFormat->attributeHandle);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->getColorVBOHandle());

		// Describe the color array format
		glVertexAttribPointer(colorFormat->attributeHandle,// attribute
				colorFormat->size,// number of elements per vertex
				colorFormat->type,// the type of each element
				colorFormat->normalized,// normalize?
				colorFormat->stride,// no extra data between each position
				colorFormat->pointer// offset of first element
		);
	}

	/* Push each element in buffer_vertices to the vertex shader */
	glDrawArrays(GL_TRIANGLES, 0, 3);
	if(colorFormat != NULL)
	{
		glDisableVertexAttribArray(colorFormat->attributeHandle);
	}
	glDisableVertexAttribArray(vertexFormat->attributeHandle);
}

/**
 * @brief Sets the color that is used to clear the screen before rendering
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 * @param a Alpha channel
 */
void RenderContext::setClearColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

/**
 * @brief Clears the render context with the clear color
 */
void RenderContext::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * @brief Displays everything and swaps buffers
 */
void RenderContext::swapBuffers() const
{
	glutSwapBuffers();
}

/**
 * @brief Uploads some data to the graphics card
 * @param data Raw data to push
 * @param length Length of the data array
 * @param vboHandle Handle of the vertex buffer to use. If this is negative a new buffer is created.
 * @param usage Specifies the expected usage pattern
 * @return The handle of the vertex buffer, the data has been uploaded
 */
const GLuint RenderContext::createVBOFloat(GLfloat* data, int length,
		GLuint vboHandle, GLenum usage)
{
	// Check, if a new buffer needs to be created
	if (vboHandle == GL_INVALID_VALUE)
	{
		glGenBuffers(1, &vboHandle);
	}
	// Bind buffer, write data, unbind buffer
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, length, data, usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vboHandle;
}

}
/* namespace DBGL */
