/*
 * RenderContext.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Drag-On
 */

#include "RenderContext.h"

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
	int vertexHandle = _curShader->getAttributeHandle(ATTRIBUTE_VERTEX);
	glEnableVertexAttribArray(vertexHandle);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexVBOHandle());

	// Describe the vertex array format
	glVertexAttribPointer(vertexHandle,// attribute
			vertexFormat->size,// number of elements per vertex
			vertexFormat->type,// the type of each element
			vertexFormat->normalized,// normalize?
			vertexFormat->stride,// no extra data between each position
			vertexFormat->pointer// offset of first element
	);

	// Pass color data
	Mesh::AttributeFormat* colorFormat = NULL;
	int colorHandle = _curShader->getAttributeHandle(ATTRIBUTE_COLOR);
	if(mesh->getColorData() != NULL)
	{
		colorFormat = mesh->getColorFormat();
		glEnableVertexAttribArray(colorHandle);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->getColorVBOHandle());

		// Describe the color array format
		glVertexAttribPointer(colorHandle,// attribute
				colorFormat->size,// number of elements per vertex
				colorFormat->type,// the type of each element
				colorFormat->normalized,// normalize?
				colorFormat->stride,// no extra data between each position
				colorFormat->pointer// offset of first element
		);
	}

	// Finally! Draw!
	if(mesh->getElementData() == NULL)
	{
		// Use old style rendering
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	else
	{
		// Use elements for rendering
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getElementIBOHandle());
		int size;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	}
	if(colorFormat != NULL)
	{
		glDisableVertexAttribArray(colorHandle);
	}
	glDisableVertexAttribArray(vertexHandle);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief Displays everything and swaps buffers
 */
void RenderContext::swapBuffers() const
{
	glutSwapBuffers();
}

/**
 * @brief Creates a buffer on the graphics card
 * @param data Raw data to push
 * @param length Length of the data array
 * @param bufferHandle Handle of a buffer to overwrite. If this equals GL_INVALID_VALUE a new buffer is created.
 * @param usage Specifies the expected usage pattern, defaults to GL_STATIC_DRAW
 * @param type Specifies buffer type, i.e. vertex buffer or index buffer, defaults to GL_ARRAY_BUFFER
 * @return The handle of the created buffer object
 */
const GLuint RenderContext::createBuffer(void* data, int length,
		GLuint bufferHandle, GLenum usage, int type)
{
	// Check, if a new buffer needs to be created
	if (bufferHandle == GL_INVALID_VALUE)
	{
		glGenBuffers(1, &bufferHandle);
	}
	// Bind buffer, write data, unbind buffer
	glBindBuffer(type, bufferHandle);
	glBufferData(type, length, data, usage);
	glBindBuffer(type, 0);
	return bufferHandle;
}

}
/* namespace DBGL */
