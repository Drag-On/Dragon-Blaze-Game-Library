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
 * @attention The attrFormat will be maintained by the Mesh class (includes deleting), the vertices pointer
 * is used only temporarily (can be initialized on Stack)
 */
Mesh::Mesh(GLfloat* vertices, int length, Mesh::AttributeFormat* attrFormat)
{
	_pVertexFormat = attrFormat;
	_vertexVBOHandle = RenderContext::createBuffer(vertices, length);
	_pColorFormat = NULL;
	_colorVBOHandle = GL_INVALID_VALUE;
	_elementIBOHandle = GL_INVALID_VALUE;
	_pNormalFormat = NULL;
	_normalVBOHandle = GL_INVALID_VALUE;
}

/**
 * Destructor
 */
Mesh::~Mesh()
{
	// Delete vertex data
	delete _pVertexFormat;
	_pVertexFormat = NULL;
	glDeleteBuffers(1, &_vertexVBOHandle);

	// Delete color data
	delete _pColorFormat;
	_pColorFormat = NULL;
	glDeleteBuffers(1, &_colorVBOHandle);

	// Delete normal data
	delete _pNormalFormat;
	_pNormalFormat = NULL;
	glDeleteBuffers(1, &_normalVBOHandle);

	// Delete element data
	glDeleteBuffers(1, &_elementIBOHandle);
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
	delete _pColorFormat;
	_pColorFormat = attrFormat;
	_colorVBOHandle = RenderContext::createBuffer(colorData, length,
			_colorVBOHandle);
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
 * @return Handle of the IBO where the elements are stored
 */
GLuint Mesh::getElementIBOHandle() const
{
	return _elementIBOHandle;
}

/**
 * @brief Adds some normal data to the mesh
 * @param normalData Raw normal data
 * @param length Length of the normalData array
 * @param attrFormat Format of the normalData array
 * @attention Both heap objects will be maintained by the Mesh class (includes delete)
 */
void Mesh::setNormalData(GLfloat* normalData, int length,
		AttributeFormat* attrFormat)
{
	delete _pNormalFormat;
	_pNormalFormat = attrFormat;
	_normalVBOHandle = RenderContext::createBuffer(normalData, length,
			_normalVBOHandle);
}

/**
 * @return Attribute format of the normal data
 */
Mesh::AttributeFormat* Mesh::getNormalFormat() const
{
	return _pNormalFormat;
}

/**
 * @return Handle of the VBO where the normal data is stored
 */
GLuint Mesh::getNormalVBOHandle() const
{
	return _normalVBOHandle;
}

/**
 * Creates a new Mesh object that has all the necessary data to display a cube
 * @return Pointer to the newly created mesh object
 */
Mesh* Mesh::createCube()
{
	// Define vertices
	GLfloat cubeVertices[] =
	{ -1.0, -1.0, 1.0, // Front lower left = 0
			1.0, -1.0, 1.0, // Front lower right = 1
			1.0, 1.0, 1.0, // Front upper right = 2
			-1.0, 1.0, 1.0, // Front upper left = 3
			-1.0, -1.0, -1.0, // Back lower left = 4
			1.0, -1.0, -1.0, // Back lower right = 5
			1.0, 1.0, -1.0, // Back upper right = 6
			-1.0, 1.0, -1.0, // Back upper left = 7
			-1.0, -1.0, 1.0, // Front lower left = 8
			1.0, -1.0, 1.0, // Front lower right = 9
			1.0, 1.0, 1.0, // Front upper right = 10
			-1.0, 1.0, 1.0, // Front upper left = 11
			-1.0, -1.0, -1.0, // Back lower left = 12
			1.0, -1.0, -1.0, // Back lower right = 13
			1.0, 1.0, -1.0, // Back upper right = 13
			-1.0, 1.0, -1.0, // Back upper left = 15
			-1.0, -1.0, 1.0, // Front lower left = 16
			1.0, -1.0, 1.0, // Front lower right = 17
			1.0, 1.0, 1.0, // Front upper right = 18
			-1.0, 1.0, 1.0, // Front upper left = 19
			-1.0, -1.0, -1.0, // Back lower left = 20
			1.0, -1.0, -1.0, // Back lower right = 21
			1.0, 1.0, -1.0, // Back upper right = 22
			-1.0, 1.0, -1.0, // Back upper left = 23
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
	{ 0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
			0.9, 0.9, 0.9, //
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
			11, 10, 14, // top
			14, 15, 11, //
			7, 6, 5, // back
			5, 4, 7, //
			12, 13, 9, // bottom
			9, 8, 12, //
			20, 16, 19, // left
			19, 23, 20, //
			17, 21, 22, // right
			22, 18, 17, //
			};
	cube->_elementIBOHandle = RenderContext::createBuffer(elements,
			sizeof(elements), GL_INVALID_VALUE,
			GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

	// Define normals
	GLfloat normals[] =
	{ 0, 0, 1, // 0 Front
			0, 0, 1, // 1
			0, 0, 1, // 2
			0, 0, 1, // 3
			0, 0, -1, // 4 Back
			0, 0, -1, // 5
			0, 0, -1, // 6
			0, 0, -1, // 7
			0, -1, 0, // 8 Bottom
			0, -1, 0, // 9
			0, 1, 0, // 10 Top
			0, 1, 0, // 11
			0, -1, 0, // 12 Bottom
			0, -1, 0, // 13
			0, 1, 0, // 14 Top
			0, 1, 0, // 15
			-1, 0, 0, // 16 Left
			1, 0, 0, // 17 Right
			1, 0, 0, // 18
			-1, 0, 0, // 19 Left
			-1, 0, 0, // 20
			1, 0, 0, // 21 Right
			1, 0, 0, // 22
			-1, 0, 0, // 23 Left
			};
	Mesh::AttributeFormat* normalFormat = new Mesh::AttributeFormat();
	normalFormat->size = 3;
	normalFormat->type = GL_FLOAT;
	normalFormat->normalized = GL_TRUE;
	normalFormat->stride = 0;
	normalFormat->pointer = 0;
	cube->setNormalData(normals, sizeof(normals), normalFormat);

	return cube;
}

} /* namespace DBGL */
