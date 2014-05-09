//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Renderer/OpenGL3Renderer.h"

namespace dbgl
{
    OpenGL3Renderer::~OpenGL3Renderer()
    {
	// Delete all buffers that are still left
	for(auto it = m_vertexBuffers.begin(); it != m_vertexBuffers.end(); ++it)
	    m_vertexBuffers.erase(it->first);
	for(auto it = m_indexBuffers.begin(); it != m_indexBuffers.end(); ++it)
	    m_indexBuffers.erase(it->first);
    }

    auto OpenGL3Renderer::genVertexBuffer(BufferType type, unsigned int size, const void* data) -> VertexBufferId
    {
	static VertexBufferId nextId = 0;
	// Create buffer
	GLuint buffer;
	glGenBuffers(1, &buffer);
	if (buffer != GL_INVALID_VALUE)
	{
	    if (size > 0)
	    {
		// Fill
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, data, convertBufferType(type));
	    }
	    // Store mapping between OpenGL identifiers and our identifiers
	    m_vertexBuffers[nextId] = { buffer, static_cast<GLsizei>(size) };
	    nextId++;
	    return nextId - 1;
	}
	return INVALID_VERTEX_BUFFER;
    }

    void OpenGL3Renderer::delVertexBuffer(VertexBufferId id)
    {
	auto it = m_vertexBuffers.find(id);
	if(it != m_vertexBuffers.end())
	{
	    auto glId = it->first;
	    glDeleteBuffers(1, &glId);
	    m_vertexBuffers.erase(it);
	}
    }

    auto OpenGL3Renderer::genIndexBuffer(BufferType type, unsigned int size, const void* data) -> IndexBufferId
    {
	static IndexBufferId nextId = 0;
	// Create buffer
	GLuint buffer;
	glGenBuffers(1, &buffer);
	if (buffer != GL_INVALID_VALUE)
	{
	    if (size > 0)
	    {
		// Fill
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, convertBufferType(type));
	    }
	    // Store mapping between OpenGL identifiers and our identifiers
	    m_indexBuffers[nextId] = { buffer, static_cast<GLsizei>(size) };
	    nextId++;
	    return nextId - 1;
	}
	return INVALID_INDEX_BUFFER;
    }

    void OpenGL3Renderer::delIndexBuffer(IndexBufferId id)
    {
	auto it = m_indexBuffers.find(id);
	if(it != m_indexBuffers.end())
	{
	    auto glId = it->first;
	    glDeleteBuffers(1, &glId);
	    m_indexBuffers.erase(it);
	}
    }

    GLenum OpenGL3Renderer::convertBufferType(BufferType type)
    {
	switch(type)
	{
	    case BufferType::STATIC:
		return GL_STATIC_DRAW;
	    case BufferType::DYNAMIC:
		return GL_DYNAMIC_DRAW;
	}
	return GL_INVALID_ENUM;
    }
}
