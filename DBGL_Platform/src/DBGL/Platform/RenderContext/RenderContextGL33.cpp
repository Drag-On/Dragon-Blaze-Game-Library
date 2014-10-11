//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/RenderContext/RenderContextGL33.h"

namespace dbgl
{
    GLuint RenderContextGL33::s_curFrameBufferId = 0;

    RenderContextGL33::~RenderContextGL33()
    {
	// Note: 0 (the screen) is silently ignored by glDeleteFramebuffers
	glDeleteFramebuffers(1, &m_frameBufferId);
	glDeleteRenderbuffers(1, &m_depthBufferId);
    }

    void RenderContextGL33::clear(int bitmask)
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before modifying its buffers.");
	GLbitfield flags = 0;
	if (bitmask & Buffer::COLOR)
	    flags |= GL_COLOR_BUFFER_BIT;
	if (bitmask & Buffer::DEPTH)
	    flags |= GL_DEPTH_BUFFER_BIT;
	if (bitmask & Buffer::STENCIL)
	    flags |= GL_STENCIL_BUFFER_BIT;
	glClear(flags);
    }

    void RenderContextGL33::setDepthTest(DepthTestValue val)
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before modifying depth testing.");
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
		throw std::invalid_argument("Invalid value for depth testing.");
		return;
	}
	m_curDepthTestVal = val;
    }

    auto RenderContextGL33::getDepthTest() const -> DepthTestValue
    {
	return m_curDepthTestVal;
    }

    void RenderContextGL33::setAlphaBlend(AlphaBlendValue src, AlphaBlendValue dest)
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before modifying alpha blending.");
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
	    glDisable(GL_BLEND);
	    m_curSrcAlphaBlendVal = m_curDestAlphaBlendVal = AlphaBlendValue::Zero;
	    throw std::invalid_argument("Invalid value for alpha blending.");
	}
	m_curSrcAlphaBlendVal = src;
	m_curDestAlphaBlendVal = dest;
    }

    auto RenderContextGL33::getSrcAlphaBlend() const -> AlphaBlendValue
    {
	return m_curSrcAlphaBlendVal;
    }

    auto RenderContextGL33::getDestAlphaBlend() const -> AlphaBlendValue
    {
	return m_curDestAlphaBlendVal;
    }

    void RenderContextGL33::setFaceCulling(FaceCullingValue val)
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before modifying culling settings.");
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
		throw std::invalid_argument("Unkown value for face culling.");
		return;
	}
	m_curFaceCullingVal = val;
    }

    auto RenderContextGL33::getFaceCulling() const -> FaceCullingValue
    {
	return m_curFaceCullingVal;
    }

    void RenderContextGL33::bind()
    {
	if(m_frameBufferId != s_curFrameBufferId)
	{
	    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);
	    s_curFrameBufferId = m_frameBufferId;
	}
    }

    bool RenderContextGL33::isBound() const
    {
	return s_curFrameBufferId == m_frameBufferId;
    }

    GLenum RenderContextGL33::translateAlphaBlendValue(AlphaBlendValue val) const
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
}
