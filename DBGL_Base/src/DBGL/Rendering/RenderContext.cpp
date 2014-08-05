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
	if (buf.isSet(Buffer::COLOR))
	    flags |= GL_COLOR_BUFFER_BIT;
	if (buf.isSet(Buffer::DEPTH))
	    flags |= GL_DEPTH_BUFFER_BIT;
	if (buf.isSet(Buffer::STENCIL))
	    flags |= GL_STENCIL_BUFFER_BIT;
	glClear(flags);
    }

    void RenderContext::setDepthTest(DepthTestValue val)
    {
	switch (val)
	{
	    case DepthTestValue::Always:
		glDisable(GL_DEPTH_TEST);
		break;
	    case DepthTestValue::Never:
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_NEVER);
		break;
	    case DepthTestValue::Less:
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		break;
	    case DepthTestValue::LessEqual:
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		break;
	    case DepthTestValue::Greater:
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_GREATER);
		break;
	    case DepthTestValue::GreaterEqual:
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_GEQUAL);
		break;
	    case DepthTestValue::Equal:
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_EQUAL);
		break;
	    case DepthTestValue::NotEqual:
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_NOTEQUAL);
		break;
	    default:
		LOG.warning("Unkown value for depth testing.");
		return;
	}
	m_curDepthTestVal = val;
    }

    auto RenderContext::getDepthTest() const -> DepthTestValue
    {
	return m_curDepthTestVal;
    }

    void RenderContext::setAlphaBlend(AlphaBlendValue src, AlphaBlendValue dest)
    {
	if(src == AlphaBlendValue::Zero && dest == AlphaBlendValue::Zero)
	{
	    glDisable(GL_BLEND);
	    m_curSrcAlphaBlendVal = src;
	    m_curDestAlphaBlendVal = dest;
	    return;
	}
	GLenum sfactor = translateAlphaBlendValue(src), dfactor = translateAlphaBlendValue(dest);
	glGetError(); // Clear last error
	glEnable(GL_BLEND);
	glBlendFunc(sfactor, dfactor);
	if(glGetError() != GL_NO_ERROR)
	{
	    LOG.warning("Unkown value for alpha blending.");
	    glDisable(GL_BLEND);
	    m_curSrcAlphaBlendVal = m_curDestAlphaBlendVal = AlphaBlendValue::Zero;
	    return;
	}
	m_curSrcAlphaBlendVal = src;
	m_curDestAlphaBlendVal = dest;
    }

    GLenum RenderContext::translateAlphaBlendValue(AlphaBlendValue val) const
    {
	switch (val)
	{
	    case AlphaBlendValue::Zero:
		return GL_ZERO;
	    case AlphaBlendValue::One:
		return GL_ONE;
	    case AlphaBlendValue::DstColor:
		return GL_DST_COLOR;
	    case AlphaBlendValue::OneMinusDstColor:
		return GL_ONE_MINUS_DST_COLOR;
	    case AlphaBlendValue::SrcAlpha:
		return GL_SRC_ALPHA;
	    case AlphaBlendValue::OneMinusSrcAlpha:
		return GL_ONE_MINUS_SRC_ALPHA;
	    case AlphaBlendValue::DstAlpha:
		return GL_DST_ALPHA;
	    case AlphaBlendValue::OneMinusDstAlpha:
		return GL_ONE_MINUS_DST_ALPHA;
	    case AlphaBlendValue::SrcAlphaSaturate:
		return GL_SRC_ALPHA_SATURATE;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    auto RenderContext::getSrcAlphaBlend() const -> AlphaBlendValue
    {
	return m_curSrcAlphaBlendVal;
    }

    auto RenderContext::getDestAlphaBlend() const -> AlphaBlendValue
    {
	return m_curDestAlphaBlendVal;
    }

    void RenderContext::setFaceCulling(FaceCullingValue val)
    {
	switch(val)
	{
	    case FaceCullingValue::Off:
		glDisable(GL_CULL_FACE);
		break;
	    case FaceCullingValue::Front:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	    case FaceCullingValue::Back:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	    case FaceCullingValue::FrontBack:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		break;
	    default:
		LOG.warning("Unkown value for face culling.");
		return;
	}
	m_curFaceCullingVal = val;
    }

    auto RenderContext::getFaceCulling() const -> FaceCullingValue
    {
	return m_curFaceCullingVal;
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

