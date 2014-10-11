//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Mesh/MeshGL33.h"

namespace dbgl
{
    MeshGL33::~MeshGL33()
    {
    }

    auto MeshGL33::indices() -> std::vector<unsigned short>&
    {
	return m_indices;
    }

    auto MeshGL33::vertices() -> std::vector<Vertex>&
    {
	return m_vertices;
    }

    auto MeshGL33::normals() -> std::vector<Vertex>&
    {
	return m_normals;
    }

    auto MeshGL33::uvs() -> std::vector<UV>&
    {
	return m_uv;
    }

    auto MeshGL33::tangents() -> std::vector<Vertex>&
    {
	return m_tangents;
    }

    auto MeshGL33::bitangents() -> std::vector<Vertex>&
    {
	return m_bitangents;
    }

    void MeshGL33::setUsage(Usage usage)
    {
	m_usage = usage;
    }

    auto MeshGL33::getUsage() const-> Usage
    {
	return m_usage;
    }

    void MeshGL33::updateBuffers()
    {
	if (m_vertexBuffer == GL_INVALID_VALUE)
	    m_vertexBuffer = generateBuffer();
	fillBuffer(m_vertexBuffer, GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0],
		convertUsage(m_usage));
	if (m_indexBuffer == GL_INVALID_VALUE)
	    m_indexBuffer = generateBuffer();
	fillBuffer(m_indexBuffer, GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned short),
		&m_indices[0], convertUsage(m_usage));
	if (m_normals.size() > 0)
	{
	    if (m_normalBuffer == GL_INVALID_VALUE)
		m_normalBuffer = generateBuffer();
	    fillBuffer(m_normalBuffer, GL_ARRAY_BUFFER, m_normals.size() * sizeof(Vertex), &m_normals[0],
		    convertUsage(m_usage));
	}
	if (m_uv.size() > 0)
	{
	    if (m_uvBuffer == GL_INVALID_VALUE)
		m_uvBuffer = generateBuffer();
	    fillBuffer(m_uvBuffer, GL_ARRAY_BUFFER, m_uv.size() * sizeof(UV), &m_uv[0], GL_STATIC_DRAW);
	}
	if (m_tangents.size() > 0)
	{
	    if (m_tangentBuffer == GL_INVALID_VALUE)
		m_tangentBuffer = generateBuffer();
	    fillBuffer(m_tangentBuffer, GL_ARRAY_BUFFER, m_tangents.size() * sizeof(Vertex), &m_tangents[0],
		    GL_STATIC_DRAW);
	}
	if (m_bitangents.size() > 0)
	{
	    if (m_bitangentBuffer == GL_INVALID_VALUE)
		m_bitangentBuffer = generateBuffer();
	    fillBuffer(m_bitangentBuffer, GL_ARRAY_BUFFER, m_bitangents.size() * sizeof(Vertex),
		    &m_bitangents[0], GL_STATIC_DRAW);
	}
    }

    GLenum MeshGL33::convertUsage(Usage usage)
    {
	switch (usage)
	{
	    case Usage::DynamicCopy:
		return GL_DYNAMIC_COPY;
	    case Usage::DynamicDraw:
		return GL_DYNAMIC_DRAW;
	    case Usage::DynamicRead:
		return GL_DYNAMIC_READ;
	    case Usage::StaticCopy:
		return GL_STATIC_COPY;
	    case Usage::StaticDraw:
		return GL_STATIC_DRAW;
	    case Usage::StaticRead:
		return GL_STATIC_READ;
	    case Usage::StreamCopy:
		return GL_STREAM_COPY;
	    case Usage::StreamDraw:
		return GL_STREAM_DRAW;
	    case Usage::StreamRead:
		return GL_STREAM_READ;
	    default:
		return GL_INVALID_ENUM;
	}
	return GL_INVALID_ENUM;
    }

    GLuint MeshGL33::generateBuffer()
    {
	GLuint buffer {};
	glGenBuffers(1, &buffer);
	return buffer;
    }

    void MeshGL33::fillBuffer(GLuint buffer, GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
    {
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, usage);
    }
}
