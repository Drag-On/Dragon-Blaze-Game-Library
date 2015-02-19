//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
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
		if (m_indexBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_indexBuffer);
		if (m_vertexBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_vertexBuffer);
		if (m_normalBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_normalBuffer);
		if (m_uvBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_uvBuffer);
		if (m_tangentBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_tangentBuffer);
		if (m_bitangentBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_bitangentBuffer);
	}

	auto MeshGL33::indices() -> std::vector<unsigned short>&
	{
		return m_indices;
	}

	auto MeshGL33::vertices() -> std::vector<Vec3f>&
	{
		return m_vertices;
	}

	auto MeshGL33::normals() -> std::vector<Vec3f>&
	{
		return m_normals;
	}

	auto MeshGL33::uvs() -> std::vector<Vec2f>&
	{
		return m_uv;
	}

	auto MeshGL33::tangents() -> std::vector<Vec3f>&
	{
		return m_tangents;
	}

	auto MeshGL33::bitangents() -> std::vector<Vec3f>&
	{
		return m_bitangents;
	}

	unsigned int MeshGL33::getIndexCount() const
	{
		return m_indexCount;
	}

	unsigned int MeshGL33::getVertexCount() const
	{
		return m_vertexCount;
	}

	unsigned int MeshGL33::getUVCount() const
	{
		return m_uvCount;
	}

	unsigned int MeshGL33::getNormalCount() const
	{
		return m_normalsCount;
	}

	unsigned int MeshGL33::getTangentCount() const
	{
		return m_tangentCount;
	}

	unsigned int MeshGL33::getBitangentCount() const
	{
		return m_bitangentCount;
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
		m_indexCount = m_indices.size();
		m_vertexCount = m_vertices.size();
		m_normalsCount = m_normals.size();
		m_uvCount = m_uv.size();
		m_tangentCount = m_tangents.size();
		m_bitangentCount = m_bitangents.size();
		if (m_vertexCount > 0)
		{
			if (m_vertexBuffer == GL_INVALID_VALUE)
				m_vertexBuffer = generateBuffer();
			fillBuffer(m_vertexBuffer, GL_ARRAY_BUFFER, m_vertexCount * sizeof(Vec3f), &m_vertices[0],
					convertUsage(m_usage));
		}
		else if (m_vertexBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_vertexBuffer);
		if (m_indexCount > 0)
		{
			if (m_indexBuffer == GL_INVALID_VALUE)
				m_indexBuffer = generateBuffer();
			fillBuffer(m_indexBuffer, GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned short), &m_indices[0],
					convertUsage(m_usage));
		}
		else if (m_indexBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_indexBuffer);
		if (m_normalsCount > 0)
		{
			if (m_normalBuffer == GL_INVALID_VALUE)
				m_normalBuffer = generateBuffer();
			fillBuffer(m_normalBuffer, GL_ARRAY_BUFFER, m_normalsCount * sizeof(Vec3f), &m_normals[0],
					convertUsage(m_usage));
		}
		else if (m_normalBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_normalBuffer);
		if (m_uvCount > 0)
		{
			if (m_uvBuffer == GL_INVALID_VALUE)
				m_uvBuffer = generateBuffer();
			fillBuffer(m_uvBuffer, GL_ARRAY_BUFFER, m_uvCount * sizeof(Vec2f), &m_uv[0], GL_STATIC_DRAW);
		}
		else if (m_uvBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_uvBuffer);
		if (m_tangentCount > 0)
		{
			if (m_tangentBuffer == GL_INVALID_VALUE)
				m_tangentBuffer = generateBuffer();
			fillBuffer(m_tangentBuffer, GL_ARRAY_BUFFER, m_tangentCount * sizeof(Vec3f), &m_tangents[0],
			GL_STATIC_DRAW);
		}
		else if (m_tangentBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_tangentBuffer);
		if (m_bitangentCount > 0)
		{
			if (m_bitangentBuffer == GL_INVALID_VALUE)
				m_bitangentBuffer = generateBuffer();
			fillBuffer(m_bitangentBuffer, GL_ARRAY_BUFFER, m_bitangentCount * sizeof(Vec3f), &m_bitangents[0],
					GL_STATIC_DRAW);
		}
		else if (m_bitangentBuffer != GL_INVALID_VALUE)
			glDeleteBuffers(1, &m_bitangentBuffer);
	}

	GLuint MeshGL33::getIndexHandle() const
	{
		return m_indexBuffer;
	}

	GLuint MeshGL33::getVertexHandle() const
	{
		return m_vertexBuffer;
	}

	GLuint MeshGL33::getNormalHandle() const
	{
		return m_normalBuffer;
	}

	GLuint MeshGL33::getUVHandle() const
	{
		return m_uvBuffer;
	}

	GLuint MeshGL33::getTangentHandle() const
	{
		return m_tangentBuffer;
	}

	GLuint MeshGL33::getBitangentHandle() const
	{
		return m_bitangentBuffer;
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
		GLuint buffer { };
		glGenBuffers(1, &buffer);
		return buffer;
	}

	void MeshGL33::fillBuffer(GLuint buffer, GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
	{
		glBindBuffer(target, buffer);
		glBufferData(target, size, data, usage);
	}
}
