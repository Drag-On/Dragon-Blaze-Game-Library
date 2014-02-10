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

    void Mesh::render()
    {
	// Bind vertex buffer : 0
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0,	// attribute
		3,			// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,			// stride
		(void*) 0);		// offset

	// Bind UV buffer : 1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer(1,	// attribute
		2,			// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,			// stride
		(void*) 0);		// offset

	// Bind normal buffer : 2
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glVertexAttribPointer(2,	// attribute
		3,			// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,			// stride
		(void*) 0);		// offset

	// Bind color buffer : 3
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glVertexAttribPointer(3,	// attribute
		3,			// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,			// stride
		(void*) 0);		// offset

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

	// Draw!
	glDrawElements(GL_TRIANGLES,	// mode
		_indices.size(),	// count
		GL_UNSIGNED_SHORT,	// type
		(void*) 0);		// offset

	// Disable buffers
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
    }

    Mesh* Mesh::makePlane()
    {
	Mesh* mesh = new Mesh();
	mesh->_vertices = { -1, -1, 0, -1, 1, 0, 1, 1, 0, 1, -1, 0 };
	mesh->_vertexBuffer = generateBuffer();
	fillBuffer(mesh->_vertexBuffer, GL_ARRAY_BUFFER, mesh->_vertices.size(),
		&mesh->_vertices[0], GL_STATIC_DRAW);
	mesh->_normals = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 };
	mesh->_normalBuffer = generateBuffer();
	fillBuffer(mesh->_normalBuffer, GL_ARRAY_BUFFER, mesh->_normals.size(),
		&mesh->_normals[0], GL_STATIC_DRAW);
	mesh->_color = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	mesh->_colorBuffer = generateBuffer();
	fillBuffer(mesh->_colorBuffer, GL_ARRAY_BUFFER, mesh->_color.size(),
		&mesh->_color[0], GL_STATIC_DRAW);
	mesh->_uv = { -1, -1, -1, 1, 1, 1, 1, -1 };
	mesh->_uvBuffer = generateBuffer();
	fillBuffer(mesh->_uvBuffer, GL_ARRAY_BUFFER, mesh->_uv.size(),
		&mesh->_uv[0], GL_STATIC_DRAW);
	mesh->_indices = { 0, 1, 2, 0, 2, 3 };
	mesh->_indexBuffer = generateBuffer();
	fillBuffer(mesh->_indexBuffer, GL_ELEMENT_ARRAY_BUFFER,
		mesh->_indices.size(), &mesh->_indices[0], GL_STATIC_DRAW);
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

