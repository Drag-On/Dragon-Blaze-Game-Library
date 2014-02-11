//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/Mesh.h"

namespace dbgl
{
    Mesh::~Mesh()
    {
	// Properly delete all buffers
	if (_indexBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_indexBuffer);
	if (_vertexBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_vertexBuffer);
	if (_normalBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_normalBuffer);
	if (_colorBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_colorBuffer);
	if (_uvBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_uvBuffer);
    }

    Mesh* Mesh::makeTriangle()
    {
	Mesh* mesh = new Mesh();
	mesh->_vertices =
	{   -1, -1, 0, 1, -1, 0, 0, 1, 0};
	mesh->_vertexBuffer = generateBuffer();
	fillBuffer(mesh->_vertexBuffer, GL_ARRAY_BUFFER,
		mesh->_vertices.size() * sizeof(GLfloat), &mesh->_vertices[0],
		GL_STATIC_DRAW);
	mesh->_normals =
	{   0, 0, 1, 0, 0, 1, 0, 0, 1};
	mesh->_normalBuffer = generateBuffer();
	fillBuffer(mesh->_normalBuffer, GL_ARRAY_BUFFER,
		mesh->_normals.size() * sizeof(GLfloat), &mesh->_normals[0],
		GL_STATIC_DRAW);
	mesh->_color =
	{   1, 1, 1, 1, 1, 1, 1, 1, 1};
	mesh->_colorBuffer = generateBuffer();
	fillBuffer(mesh->_colorBuffer, GL_ARRAY_BUFFER,
		mesh->_color.size() * sizeof(GLfloat), &mesh->_color[0],
		GL_STATIC_DRAW);
	mesh->_uv =
	{   -1, -1, -1, 1, 1, 0};
	mesh->_uvBuffer = generateBuffer();
	fillBuffer(mesh->_uvBuffer, GL_ARRAY_BUFFER,
		mesh->_uv.size() * sizeof(GLfloat), &mesh->_uv[0],
		GL_STATIC_DRAW);
	mesh->_indices =
	{   0, 1, 2};
	mesh->_indexBuffer = generateBuffer();
	fillBuffer(mesh->_indexBuffer, GL_ELEMENT_ARRAY_BUFFER,
		mesh->_indices.size() * sizeof(unsigned short),
		&mesh->_indices[0], GL_STATIC_DRAW);
	return mesh;
    }

    Mesh* Mesh::makePlane()
    {
	Mesh* mesh = new Mesh();
	mesh->_vertices =
	{   -1, -1, 0, -1, 1, 0, 1, 1, 0, 1, -1, 0};
	mesh->_vertexBuffer = generateBuffer();
	fillBuffer(mesh->_vertexBuffer, GL_ARRAY_BUFFER,
		mesh->_vertices.size() * sizeof(GLfloat), &mesh->_vertices[0],
		GL_STATIC_DRAW);
	mesh->_normals =
	{   0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
	mesh->_normalBuffer = generateBuffer();
	fillBuffer(mesh->_normalBuffer, GL_ARRAY_BUFFER,
		mesh->_normals.size() * sizeof(GLfloat), &mesh->_normals[0],
		GL_STATIC_DRAW);
	mesh->_color =
	{   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	mesh->_colorBuffer = generateBuffer();
	fillBuffer(mesh->_colorBuffer, GL_ARRAY_BUFFER,
		mesh->_color.size() * sizeof(GLfloat), &mesh->_color[0],
		GL_STATIC_DRAW);
	mesh->_uv =
	{   -1, -1, -1, 1, 1, 1, 1, -1};
	mesh->_uvBuffer = generateBuffer();
	fillBuffer(mesh->_uvBuffer, GL_ARRAY_BUFFER,
		mesh->_uv.size() * sizeof(GLfloat), &mesh->_uv[0],
		GL_STATIC_DRAW);
	mesh->_indices =
	{   0, 2, 1, 0, 3, 2};
	mesh->_indexBuffer = generateBuffer();
	fillBuffer(mesh->_indexBuffer, GL_ELEMENT_ARRAY_BUFFER,
		mesh->_indices.size() * sizeof(unsigned short),
		&mesh->_indices[0], GL_STATIC_DRAW);
	return mesh;
    }

    Mesh::Mesh()
    {
	_vertexBuffer = GL_INVALID_VALUE;
	_colorBuffer = GL_INVALID_VALUE;
	_indexBuffer = GL_INVALID_VALUE;
	_normalBuffer = GL_INVALID_VALUE;
	_uvBuffer = GL_INVALID_VALUE;
    }

    GLuint Mesh::generateBuffer()
    {
	GLuint buffer;
	glGenBuffers(1, &buffer);
	return buffer;
    }

    void Mesh::fillBuffer(GLuint buffer, GLenum target, GLsizeiptr size,
	    const GLvoid* data, GLenum usage)
    {
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, usage);
    }
}

