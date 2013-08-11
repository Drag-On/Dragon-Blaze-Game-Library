/*
 * Mesh.cpp
 *
 *  Created on: 10.08.2013
 *      Author: Drag-On
 */

#include "Mesh.h"

namespace DBGL
{

/**
 * Constructor
 * @param vertices Array containing vertex position data.
 * @param length Length of the vertices array
 * @param attrFormat Format of the vertex array
 * @attention Both heap objects will be maintained by the Mesh class (includes deleting)
 */
Mesh::Mesh(GLfloat* vertices, int length, Mesh::AttributeFormat* attrFormat)
{
	_pVertices = vertices;
	_pVertexFormat = attrFormat;
	_vertexVBOHandle = RenderContext::createVBO(_pVertices, length);
	_pColors = NULL;
	_pColorFormat = NULL;
	_colorVBOHandle = 0;
}

/**
 * Destructor
 */
Mesh::~Mesh()
{
	// Delete vertex data
	delete _pVertices;
	_pVertices = NULL;
	delete _pVertexFormat;
	_pVertexFormat = NULL;
	glDeleteBuffers(1, &_vertexVBOHandle);

	// Delete color data
	delete _pColorFormat;
	_pColorFormat = NULL;
	delete _pColorFormat;
	_pColorFormat = NULL;
	glDeleteBuffers(1, &_colorVBOHandle);
}

/**
 * @return Vertex array
 */
GLfloat* Mesh::getVertices() const
{
	return _pVertices;
}

/**
 * @return Attribute format
 */
Mesh::AttributeFormat* Mesh::getVertexFormat() const
{
	return _pVertexFormat;
}

/**
 * Handle of the VBO where the vertex data is stored
 */
GLuint Mesh::getVertexVBOHandle() const
{
	return _vertexVBOHandle;
}

/**
 * @brief Adds some color data to the mesh
 * @param colorData Raw color data
 * @param length Length of the colorData array
 * @param attrFormat Format of the colorData array
 * @attention Both heap objects will be maintained by the Mesh class (includes delete)
 */
void Mesh::setColorData(GLfloat* colorData, int length,
		AttributeFormat* attrFormat)
{
	_pColors = colorData;
	_pColorFormat = attrFormat;
	_colorVBOHandle = RenderContext::createVBO(_pColors, length);
}

/**
 * @return Color data array
 */
GLfloat* Mesh::getColorData() const
{
	return _pColors;
}

/**
 * @return Attribute format of the color data
 */
Mesh::AttributeFormat* Mesh::getColorFormat() const
{
	return _pColorFormat;
}

/**
 * @return Handle of the VBO where the color data is stored
 */
GLuint Mesh::getColorVBOHandle() const
{
	return _colorVBOHandle;
}

} /* namespace DBGL */
