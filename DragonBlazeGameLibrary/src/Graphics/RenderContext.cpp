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
	_pCurShader = NULL;
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
		_pCurShader = shader;
		glUseProgram(_pCurShader->getHandle());
	}
}

/**
 * @brief Renders a mesh to screen using the currently active shader program
 * @param mesh Mesh to render
 */
void RenderContext::render(Mesh* mesh)
{
	// Check if there is a shader in use
	if (_pCurShader == NULL)
	{
		LOG->warning("Tried to render mesh without active shader program.");
		return;
	}

	// Pass vertex data
	Mesh::AttributeFormat* vertexFormat = mesh->getVertexFormat();
	int vertexHandle = _pCurShader->getAttributeHandle(ATTRIBUTE_VERTEX);
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
	int colorHandle = -1;
	if(_pCurShader->checkAttributeExists(ATTRIBUTE_COLOR))
	{
		colorHandle = _pCurShader->getAttributeHandle(ATTRIBUTE_COLOR);
		if(mesh->getColorVBOHandle() != GL_INVALID_VALUE)
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
	}

	// Pass normal data
	Mesh::AttributeFormat* normalFormat = NULL;
	int normalHandle = -1;
	if(_pCurShader->checkAttributeExists(ATTRIBUTE_NORMAL))
	{
		normalHandle = _pCurShader->getAttributeHandle(ATTRIBUTE_NORMAL);
		if(mesh->getNormalVBOHandle() != GL_INVALID_VALUE)
		{
			normalFormat = mesh->getNormalFormat();
			glEnableVertexAttribArray(normalHandle);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->getNormalVBOHandle());

			// Describe the color array format
			glVertexAttribPointer(normalHandle,// attribute
					normalFormat->size,// number of elements per vertex
					normalFormat->type,// the type of each element
					normalFormat->normalized,// normalize?
					normalFormat->stride,// no extra data between each position
					normalFormat->pointer// offset of first element
			);
		}
	}

	// Pass uv data
	Mesh::AttributeFormat* uvFormat = NULL;
	int uvHandle = -1;
	if(_pCurShader->checkAttributeExists(ATTRIBUTE_UV))
	{
		uvHandle = _pCurShader->getAttributeHandle(ATTRIBUTE_UV);
		if(mesh->getUVVBOHandle() != GL_INVALID_VALUE)
		{
			uvFormat = mesh->getUVFormat();
			glEnableVertexAttribArray(uvHandle);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->getUVVBOHandle());

			// Describe the color array format
			glVertexAttribPointer(uvHandle,// attribute
					uvFormat->size,// number of elements per vertex
					uvFormat->type,// the type of each element
					uvFormat->normalized,// normalize?
					uvFormat->stride,// no extra data between each position
					uvFormat->pointer// offset of first element
			);
		}
	}

	// Pass texture if any
	Texture* tex = mesh->getTexture();
	if(tex != NULL && _pCurShader->checkUniformExists(UNIFORM_TEXDIFFUSE))
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex->getTextureHandle());
		_pCurShader->setUniformSampler(_pCurShader->getUniformHandle(UNIFORM_TEXDIFFUSE), 0);
	}

	// Instruct shader with matrices
	if(_pCurShader->checkUniformExists(UNIFORM_MODEL))
	{
		int uniformModelHandle = _pCurShader->getUniformHandle(UNIFORM_MODEL);
		float* pModelMatrix = glm::value_ptr(_modelMat);
		_pCurShader->setUniformFloatMatrix4Array(uniformModelHandle, 1, GL_FALSE, pModelMatrix);
	}
	if(_pCurShader->checkUniformExists(UNIFORM_VIEW))
	{
		int uniformViewHandle = _pCurShader->getUniformHandle(UNIFORM_VIEW);
		float* pViewMatrix = glm::value_ptr(_viewMat);
		_pCurShader->setUniformFloatMatrix4Array(uniformViewHandle, 1, GL_FALSE, pViewMatrix);
	}
	if(_pCurShader->checkUniformExists(UNIFORM_PROJECTION))
	{
		int uniformProjectionHandle = _pCurShader->getUniformHandle(UNIFORM_PROJECTION);
		float* pProjectionMatrix = glm::value_ptr(_projectionMat);
		_pCurShader->setUniformFloatMatrix4Array(uniformProjectionHandle, 1, GL_FALSE, pProjectionMatrix);
	}
	if(_pCurShader->checkUniformExists(UNIFORM_MVP))
	{
		int uniformMVPHandle = _pCurShader->getUniformHandle(UNIFORM_MVP);
		glm::mat4 mvp = _projectionMat * _viewMat * _modelMat;
		float* pMVPMatrix = glm::value_ptr(mvp);
		_pCurShader->setUniformFloatMatrix4Array(uniformMVPHandle, 1, GL_FALSE, pMVPMatrix);
	}
	if(_pCurShader->checkUniformExists(UNIFORM_ITMV))
	{
		int uniformITMVHandle = _pCurShader->getUniformHandle(UNIFORM_ITMV);
		glm::mat4 itmv = glm::transpose(glm::inverse(_viewMat * _modelMat));
		float* pITMVMatrix = glm::value_ptr(itmv);
		_pCurShader->setUniformFloatMatrix4Array(uniformITMVHandle, 1, GL_FALSE, pITMVMatrix);
	}

	// Finally! Draw!
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	if(mesh->getElementIBOHandle() == GL_INVALID_VALUE)
	{
		// Use old style rendering
		glDrawArrays(GL_TRIANGLES, 0, size/sizeof(GLushort));
	}
	else
	{
		// Use elements for rendering
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getElementIBOHandle());
		glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	}
	if(colorFormat != NULL)
	{
		glDisableVertexAttribArray(colorHandle);
	}
	if(normalFormat != NULL)
	{
		glDisableVertexAttribArray(normalHandle);
	}
	if(uvFormat != NULL)
	{
		glDisableVertexAttribArray(uvHandle);
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
 * @brief Sets the model matrix
 * @param modelMat New model matrix
 */
void RenderContext::setModelMatrix(glm::mat4 modelMat)
{
	_modelMat = modelMat;
}

/**
 * @return The model matrix
 */
glm::mat4 RenderContext::getModelMatrix() const
{
	return _modelMat;
}

/**
 * @brief Sets the view matrix
 * @param viewMat New view matrix
 */
void RenderContext::setViewMatrix(glm::mat4 viewMat)
{
	_viewMat = viewMat;
}

/**
 * @return The view matrix
 */
glm::mat4 RenderContext::getViewMatrix() const
{
	return _viewMat;
}

/**
 * @brief Sets the projection matrix
 * @param projectionMat New projection matrix
 */
void RenderContext::setProjectionMatrix(glm::mat4 projectionMat)
{
	_projectionMat = projectionMat;
}

/**
 * @return The peojection matrix
 */
glm::mat4 RenderContext::getProjectionMatrix() const
{
	return _projectionMat;
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
