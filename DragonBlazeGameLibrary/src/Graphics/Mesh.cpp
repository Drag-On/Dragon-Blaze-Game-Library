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
	_vertexVBOHandle = RenderContext::createBuffer(_pVertices, length);
	_pColors = NULL;
	_pColorFormat = NULL;
	_colorVBOHandle = GL_INVALID_VALUE;
	_pElements = NULL;
	_elementIBOHandle = GL_INVALID_VALUE;
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

	// Delete element data
	delete _pElements;
	_pElements = NULL;
	glDeleteBuffers(1, &_elementIBOHandle);
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
	_colorVBOHandle = RenderContext::createBuffer(_pColors, length,
			_colorVBOHandle);
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

/**
 * @return Element data array
 */
GLushort* Mesh::getElementData() const
{
	return _pElements;
}

/**
 * @return Handle of the IBO where the elements are stored
 */
GLuint Mesh::getElementIBOHandle() const
{
	return _elementIBOHandle;
}

/**
 * Creates a new Mesh object that has all the necessary data to display a cube
 * @return Pointer to the newly created mesh object
 */
Mesh* Mesh::createCube()
{
// Define vertices
	GLfloat cubeVertices[] =
	{ -1.0, -1.0, 1.0, //
			1.0, -1.0, 1.0, //
			1.0, 1.0, 1.0, //
			-1.0, 1.0, 1.0, //
			-1.0, -1.0, -1.0, //
			1.0, -1.0, -1.0, //
			1.0, 1.0, -1.0, //
			-1.0, 1.0, -1.0, //
			};
	AttributeFormat* vertexFormat = new AttributeFormat();
	vertexFormat->size = 3;
	vertexFormat->type = GL_FLOAT;
	vertexFormat->normalized = GL_FALSE;
	vertexFormat->stride = 0;
	vertexFormat->pointer = 0;
	Mesh* cube = new Mesh(cubeVertices, sizeof(cubeVertices), vertexFormat);

// Define some colors
	GLfloat cubeColors[] =
	{ 1.0, 0.0, 0.0, //
			0.0, 1.0, 0.0, //
			0.0, 0.0, 1.0, //
			1.0, 1.0, 1.0, //
			1.0, 0.0, 0.0, //
			0.0, 1.0, 0.0, //
			0.0, 0.0, 1.0, //
			1.0, 1.0, 1.0, //
			};
	Mesh::AttributeFormat* colorFormat = new Mesh::AttributeFormat();
	colorFormat->size = 3;
	colorFormat->type = GL_FLOAT;
	colorFormat->normalized = GL_FALSE;
	colorFormat->stride = 0;
	colorFormat->pointer = 0;
	cube->setColorData(cubeColors, sizeof(cubeColors), colorFormat);

// Define elements
	GLushort elements[] =
	{ 0, 1, 2, // front
			2, 3, 0, //
			3, 2, 6, // top
			6, 7, 3, //
			7, 6, 5, // back
			5, 4, 7, //
			4, 5, 1, // bottom
			1, 0, 4, //
			4, 0, 3, // left
			3, 7, 4, //
			1, 5, 6, // right
			6, 2, 1, //
			};
	cube->_pElements = elements;
	cube->_elementIBOHandle = RenderContext::createBuffer(elements,
			sizeof(elements), GL_INVALID_VALUE,
			GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

	return cube;
}

} /* namespace DBGL */
