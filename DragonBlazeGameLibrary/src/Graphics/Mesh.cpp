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
	_pUVFormat = NULL;
	_UVVBOHandle = GL_INVALID_VALUE;
	_pTexture = NULL;
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

	// Delete uv data
	delete _pUVFormat;
	_pUVFormat = NULL;
	glDeleteBuffers(1, &_UVVBOHandle);

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
 * @brief Adds some UV coordinates to the mesh
 * @param uvData Raw uv coordinates
 * @param length Length of the uvData array
 * @param attrFormat Format of the uvData array
 * @attention Both heap objects will be maintained by the Mesh class (includes delete)
 */
void Mesh::setUVData(GLfloat* uvData, int length, AttributeFormat* attrFormat)
{
	delete _pUVFormat;
	_pUVFormat = attrFormat;
	_UVVBOHandle = RenderContext::createBuffer(uvData, length, _UVVBOHandle);
}

/**
 * @return Attribute format of the UV coordinate data
 */
Mesh::AttributeFormat* Mesh::getUVFormat() const
{
	return _pUVFormat;
}

/**
 * @return Handle of the VBO where the UVs are stored
 */
GLuint Mesh::getUVVBOHandle() const
{
	return _UVVBOHandle;
}

/**
 * @brief Makes the mesh render using the passed texture
 * @param tex Texture to use
 * @attention You need to manage the passed texture by yourself!
 */
void Mesh::setTexture(Texture* tex)
{
	_pTexture = tex;
}

/**
 * @return Texture used for rendering or NULL in case none
 */
Texture* Mesh::getTexture() const
{
	return _pTexture;
}

/**
 * Creates a new Mesh object that has all the necessary data to display a cube
 * @return Pointer to the newly created mesh object
 */
Mesh* Mesh::createCube()
{
	// Define vertices
	GLfloat cubeVertices[] =
	{ -1.0, -1.0, 1.0, // front
			1.0, -1.0, 1.0, //
			1.0, 1.0, 1.0, //
			-1.0, 1.0, 1.0, //
			-1.0, 1.0, 1.0, // top
			1.0, 1.0, 1.0, //
			1.0, 1.0, -1.0, //
			-1.0, 1.0, -1.0, //
			1.0, -1.0, -1.0, // back
			-1.0, -1.0, -1.0, //
			-1.0, 1.0, -1.0, //
			1.0, 1.0, -1.0, //
			-1.0, -1.0, -1.0, // bottom
			1.0, -1.0, -1.0, //
			1.0, -1.0, 1.0, //
			-1.0, -1.0, 1.0, //
			-1.0, -1.0, -1.0, // left
			-1.0, -1.0, 1.0, //
			-1.0, 1.0, 1.0, //
			-1.0, 1.0, -1.0, //
			1.0, -1.0, 1.0, // right
			1.0, -1.0, -1.0, //
			1.0, 1.0, -1.0, //
			1.0, 1.0, 1.0, //
			};
	AttributeFormat* vertexFormat = new AttributeFormat();
	vertexFormat->size = 3;
	vertexFormat->type = GL_FLOAT;
	vertexFormat->normalized = GL_FALSE;
	vertexFormat->stride = 0;
	vertexFormat->pointer = 0;
	Mesh* cube = new Mesh(cubeVertices, sizeof(cubeVertices), vertexFormat);

	// Define some colors
	GLfloat cubeColors[3 * 4 * 6];
	for (int i = 0; i < 3 * 4 * 6; i++)
		cubeColors[i] = 0.9f;
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
			4, 5, 6, // top
			6, 7, 4, //
			8, 9, 10, // back
			10, 11, 8, //
			12, 13, 14, // bottom
			14, 15, 12, //
			16, 17, 18, // left
			18, 19, 16, //
			20, 21, 22, // right
			22, 23, 20, //
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
			0, 1, 0, // 10 Top
			0, 1, 0, // 11
			0, 1, 0, // 14
			0, 1, 0, // 15
			0, 0, -1, // 4 Back
			0, 0, -1, // 5
			0, 0, -1, // 6
			0, 0, -1, // 7
			0, -1, 0, // 8 Bottom
			0, -1, 0, // 9
			0, -1, 0, // 12
			0, -1, 0, // 13
			-1, 0, 0, // 16 Left
			-1, 0, 0, // 19
			-1, 0, 0, // 20
			-1, 0, 0, // 23
			1, 0, 0, // 21 Right
			1, 0, 0, // 22
			1, 0, 0, // 17
			1, 0, 0, // 18
			};
	Mesh::AttributeFormat* normalFormat = new Mesh::AttributeFormat();
	normalFormat->size = 3;
	normalFormat->type = GL_FLOAT;
	normalFormat->normalized = GL_TRUE;
	normalFormat->stride = 0;
	normalFormat->pointer = 0;
	cube->setNormalData(normals, sizeof(normals), normalFormat);

	// Define UVs
	GLfloat uvs[2 * 4 * 6] =
	{ 0.0, 0.0, // front
			1.0, 0.0, //
			1.0, 1.0, //
			0.0, 1.0, //
			};
	for (int i = 1; i < 6; i++)
		memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));
	Mesh::AttributeFormat* uvFormat = new Mesh::AttributeFormat();
	uvFormat->size = 2;
	uvFormat->type = GL_FLOAT;
	uvFormat->normalized = GL_TRUE;
	uvFormat->stride = 0;
	uvFormat->pointer = 0;
	cube->setUVData(uvs, sizeof(uvs), uvFormat);

	return cube;
}

/**
 * Creates a new Mesh object representing a four-sided pyramid
 * @return Pointer to the newly created mesh object
 */
Mesh* Mesh::createPyramid()
{
	// Define vertices
	GLfloat vertices[] =
	{ -1, -1, 1, // Front lower left 0
			1, -1, 1, // Front lower right 1
			0, 1, 0, // Front top 2
			1, -1, 1, // Right lower left 3
			1, -1, -1, // Right lower right 4
			0, 1, 0, // Right top 5
			1, -1, -1, // Back lower left 6
			-1, -1, -1, // Back lower right 7
			0, 1, 0, // Back top 8
			-1, -1, -1, // Left lower left 9
			-1, -1, 1, // Left lower right 10
			0, 1, 0, // Left top 11
			-1, -1, 1, // Bottom front left 12
			1, -1, 1, // Bottom front right 13
			-1, -1, -1, // Bottom back left 14
			1, -1, 1, // Bottom front right 15
			1, -1, -1, // Bottom back right 16
			-1, -1, -1, // Bottom back left 17
			};
	AttributeFormat* vertexFormat = new AttributeFormat();
	vertexFormat->size = 3;
	vertexFormat->type = GL_FLOAT;
	vertexFormat->normalized = GL_FALSE;
	vertexFormat->stride = 0;
	vertexFormat->pointer = 0;
	Mesh* mesh = new Mesh(vertices, sizeof(vertices), vertexFormat);

	// Define some colors
	GLfloat colors[] =
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
			};
	Mesh::AttributeFormat* colorFormat = new Mesh::AttributeFormat();
	colorFormat->size = 3;
	colorFormat->type = GL_FLOAT;
	colorFormat->normalized = GL_FALSE;
	colorFormat->stride = 0;
	colorFormat->pointer = 0;
	mesh->setColorData(colors, sizeof(colors), colorFormat);

	// Define elements
	GLushort elements[] =
	{ 0, 1, 2, // front
			3, 4, 5, // right
			6, 7, 8, // back
			9, 10, 11, // left
			12, 13, 14, // bottom left
			15, 16, 17, // bottom right
			};
	mesh->_elementIBOHandle = RenderContext::createBuffer(elements,
			sizeof(elements), GL_INVALID_VALUE,
			GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

	// Define normals
	GLfloat normals[] =
	{ 0, 0.4472, 0.8944, // front
			0, 0.4472, 0.8944, // front
			0, 0.4472, 0.8944, // front
			0.8944, 0.4472, 0, // right
			0.8944, 0.4472, 0, // right
			0.8944, 0.4472, 0, // right
			0, 0.4472, -0.8944, // back
			0, 0.4472, -0.8944, // back
			0, 0.4472, -0.8944, // back
			-0.8944, 0.4472, 0, // left
			-0.8944, 0.4472, 0, // left
			-0.8944, 0.4472, 0, // left
			0, -1, 0, // bottom
			0, -1, 0, // bottom
			0, -1, 0, // bottom
			0, -1, 0, // bottom
			0, -1, 0, // bottom
			0, -1, 0, // bottom
			};
	Mesh::AttributeFormat* normalFormat = new Mesh::AttributeFormat();
	normalFormat->size = 3;
	normalFormat->type = GL_FLOAT;
	normalFormat->normalized = GL_TRUE;
	normalFormat->stride = 0;
	normalFormat->pointer = 0;
	mesh->setNormalData(normals, sizeof(normals), normalFormat);

	return mesh;
}

} /* namespace DBGL */
