//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/RenderContext.h"

namespace dbgl
{
    RenderContext::RenderContext(unsigned int frameWidth, unsigned int frameHeight) :
	    m_frameWidth(frameWidth), m_frameHeight(frameHeight)
    {
    }

    RenderContext::~RenderContext()
    {
    }

    void RenderContext::draw(Mesh const& mesh) const
    {
	// Render mesh
	renderMesh(mesh);
    }

    void RenderContext::changeSize(unsigned int width, unsigned int height)
    {
	m_frameWidth = width;
	m_frameHeight = height;
    }

    unsigned int RenderContext::getWidth() const
    {
	return m_frameWidth;
    }

    unsigned int RenderContext::getHeight() const
    {
	return m_frameHeight;
    }

    void RenderContext::clear(Bitmask<char> buf) const
    {
	GLbitfield flags = 0;
	if(buf.isSet(Buffer::COLOR))
	    flags |= GL_COLOR_BUFFER_BIT;
	if(buf.isSet(Buffer::DEPTH))
	    flags |= GL_DEPTH_BUFFER_BIT;
	if(buf.isSet(Buffer::STENCIL))
	    flags |= GL_STENCIL_BUFFER_BIT;
	glClear(flags);
    }

    void RenderContext::renderMesh(Mesh const& mesh) const
    {
	// Bind vertex buffer : 0
	if (mesh.m_vertices.size() > 0)
	{
	    glEnableVertexAttribArray(0);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexBuffer);
	    glVertexAttribPointer(0,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Bind UV buffer : 1
	if (mesh.m_uv.size() > 0)
	{
	    glEnableVertexAttribArray(1);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_uvBuffer);
	    glVertexAttribPointer(1,	// attribute
		    2,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Bind normal buffer : 2
	if (mesh.m_normals.size() > 0)
	{
	    glEnableVertexAttribArray(2);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_normalBuffer);
	    glVertexAttribPointer(2,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Bind tangent buffer : 3
	if (mesh.m_tangents.size() > 0)
	{
	    glEnableVertexAttribArray(3);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_tangentBuffer);
	    glVertexAttribPointer(3,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Bind bitangent buffer : 4
	if (mesh.m_bitangents.size() > 0)
	{
	    glEnableVertexAttribArray(4);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh.m_bitangentBuffer);
	    glVertexAttribPointer(4,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_indexBuffer);

	// Draw!
	glDrawElements(GL_TRIANGLES,	// mode
		mesh.m_indices.size(),	// count
		GL_UNSIGNED_SHORT,	// type
		(void*) 0);		// offset

	// Disable buffers
	if (mesh.m_vertices.size() > 0)
	    glDisableVertexAttribArray(0);
	if (mesh.m_uv.size() > 0)
	    glDisableVertexAttribArray(1);
	if (mesh.m_normals.size() > 0)
	    glDisableVertexAttribArray(2);
	if (mesh.m_tangents.size() > 0)
	    glDisableVertexAttribArray(3);
	if (mesh.m_bitangents.size() > 0)
	    glDisableVertexAttribArray(4);
    }

    void RenderContext::preRender()
    {
	glViewport(0, 0, m_frameWidth, m_frameHeight);
    }

    void RenderContext::postRender()
    {
    }
}

