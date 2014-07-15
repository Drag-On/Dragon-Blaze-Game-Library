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

    void OpenGL3Renderer::fillVertexBuffer(VertexBufferId id, BufferType type, unsigned int size, const void* data)
    {
	auto it = m_vertexBuffers.find(id);
	if(it != m_vertexBuffers.end())
	{
	    auto vertBuffer = it->second;
	    auto oglType = convertBufferType(type);
	    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer.id);
	    glBufferData(GL_ARRAY_BUFFER, size, data, oglType);
	    it->second.size = size;
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

    void OpenGL3Renderer::fillIndexBuffer(IndexBufferId id, BufferType type, unsigned int size, const void* data)
    {
	auto it = m_indexBuffers.find(id);
	if(it != m_indexBuffers.end())
	{
	    auto indexBuffer = it->second;
	    auto oglType = convertBufferType(type);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.id);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, oglType);
	    it->second.size = size;
	}
    }

    auto OpenGL3Renderer::regVertexFormat(AttribId id, unsigned int size, AttribFormat format) -> VertexFormatId
    {
	static VertexFormatId nextId = 0;
	m_vertexFormats[nextId] = {id, size, format};
	nextId++;
	return nextId - 1;
    }

    void OpenGL3Renderer::useVertexBuffer(VertexBufferId vertBuffer, VertexFormatId vertFormat)
    {
	auto vertFormatIt = m_vertexFormats.find(vertFormat);
	auto vertBufferIt = m_vertexBuffers.find(vertBuffer);
	if(vertFormatIt != m_vertexFormats.end() && vertBufferIt != m_vertexBuffers.end())
	{
	    auto format = vertFormatIt->second;
	    auto vertBuffer = vertBufferIt->second;
	    auto oGlFormat = convertAttributeFormat(format.format);
	    GLuint glType = static_cast<GLuint>(format.id);

	    glEnableVertexAttribArray(glType);
	    glBindBuffer(GL_ARRAY_BUFFER, vertBuffer.id);
	    glVertexAttribPointer(glType,	// attribute
		    vertBuffer.size,		// size
		    oGlFormat,			// type
		    GL_FALSE,			// normalized?
		    0,				// stride
		    (void*) 0);			// offset
	}
    }

    void OpenGL3Renderer::endUseVertexBuffer(VertexBufferId /* vertBuffer */, VertexFormatId vertFormat)
    {
	auto vertFormatIt = m_vertexFormats.find(vertFormat);
	if (vertFormatIt != m_vertexFormats.end())
	{
	    auto format = vertFormatIt->second;
	    GLuint glType = static_cast<GLuint>(format.id);
	    glDisableVertexAttribArray(glType);
	}
    }

    void OpenGL3Renderer::useIndexBuffer(IndexBufferId indexBuffer)
    {
	auto indexBufferIt = m_indexBuffers.find(indexBuffer);
	if(indexBufferIt != m_indexBuffers.end())
	{
	    auto indexBuffer = indexBufferIt->second;
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.id);
	}
    }

    void OpenGL3Renderer::endUseIndexBuffer(IndexBufferId /* indexBuffer */)
    {
    }

    void OpenGL3Renderer::drawElements(PolygonMode mode, unsigned int size, AttribFormat format)
    {
	glDrawElements(convertPolygonMode(mode),	// mode
		size,					// count
		convertAttributeFormat(format, true),	// type
		(void*) 0);				// offset
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

    GLenum OpenGL3Renderer::convertAttributeFormat(AttribFormat format, bool unsign)
    {
	switch(format)
	{
	    case AttribFormat::FLOAT:
		return GL_FLOAT;
	    case AttribFormat::SHORT:
		if(unsign)
		    return GL_UNSIGNED_SHORT;
		else
		    return GL_SHORT;
	    case AttribFormat::BYTE:
		if(unsign)
		    return GL_UNSIGNED_BYTE;
		else
		    return GL_BYTE;
	}
	return GL_INVALID_ENUM;
    }

    GLenum OpenGL3Renderer::convertPolygonMode(PolygonMode mode)
    {
	switch(mode)
	{
	    case PolygonMode::TRIANGLE:
		return GL_TRIANGLES;
	}
	return GL_INVALID_ENUM;
    }
}
