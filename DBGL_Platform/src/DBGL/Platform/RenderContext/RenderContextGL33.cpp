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
	if (!isBound())
	    bind();
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
	GLenum sfactor = alphaBlendValue2GL(src), dfactor = alphaBlendValue2GL(dest);
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

    void RenderContextGL33::setMultisampling(bool msaa)
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before modifying multisampling settings.");
	if(msaa)
	    glEnable(GL_MULTISAMPLE);
	else
	    glDisable(GL_MULTISAMPLE);
    }

    bool RenderContextGL33::getMultisampling() const
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before retrieving multisampling settings.");
	return glIsEnabled(GL_MULTISAMPLE);
    }

    std::array<float, 3> RenderContextGL33::getClearColor() const
    {
	return m_clearcolor;
    }

    void RenderContextGL33::setClearColor(std::array<float, 3> color)
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before modifying clear color.");
	m_clearcolor = color;
	glClearColor(m_clearcolor[0], m_clearcolor[1], m_clearcolor[2], 0);
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

    void RenderContextGL33::viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before modifying viewport");
	glViewport(x, y, width, height);
    }

    void RenderContextGL33::readPixels(int x, int y, int width, int height, PixelFormat format, PixelType type,
    		    unsigned int bufsize, char* buf)
    {
	if(!isBound())
	    throw std::runtime_error("Need to bind render context before reading pixels.");
	// Allocate buffer
	unsigned int imgDataSize { width * height * pixelFormatSize(format) };
	if(!buf || bufsize < imgDataSize)
	    return;
	// Copy pixel data to buffer
	glReadPixels(x, y, width, height, pixelFormat2GL(format), pixelType2GL(type), buf);
    }

    void RenderContextGL33::drawMesh(IMesh* mesh)
    {
	MeshGL33* pMesh = dynamic_cast<MeshGL33*> (mesh);
	if(pMesh == nullptr)
	    throw std::invalid_argument("Cannot render null mesh.");

	// Bind vertex buffer : 0
	if (pMesh->m_vertices.size() > 0)
	{
	    glEnableVertexAttribArray(0);
	    glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_vertexBuffer);
	    glVertexAttribPointer(0,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}
	// Bind UV buffer : 1
	if (pMesh->m_uv.size() > 0)
	{
	    glEnableVertexAttribArray(1);
	    glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_uvBuffer);
	    glVertexAttribPointer(1,	// attribute
		    2,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}
	// Bind normal buffer : 2
	if (pMesh->m_normals.size() > 0)
	{
	    glEnableVertexAttribArray(2);
	    glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_normalBuffer);
	    glVertexAttribPointer(2,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}
	// Bind tangent buffer : 3
	if (pMesh->m_tangents.size() > 0)
	{
	    glEnableVertexAttribArray(3);
	    glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_tangentBuffer);
	    glVertexAttribPointer(3,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}
	// Bind bitangent buffer : 4
	if (pMesh->m_bitangents.size() > 0)
	{
	    glEnableVertexAttribArray(4);
	    glBindBuffer(GL_ARRAY_BUFFER, pMesh->m_bitangentBuffer);
	    glVertexAttribPointer(4,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}
	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indexBuffer);
	// Draw!
	glDrawElements(GL_TRIANGLES,	// mode
		pMesh->m_indices.size(),// count
		GL_UNSIGNED_SHORT,	// type
		(void*) 0);		// offset

	// Disable buffers
	if (pMesh->m_vertices.size() > 0)
	    glDisableVertexAttribArray(0);
	if (pMesh->m_uv.size() > 0)
	    glDisableVertexAttribArray(1);
	if (pMesh->m_normals.size() > 0)
	    glDisableVertexAttribArray(2);
	if (pMesh->m_tangents.size() > 0)
	    glDisableVertexAttribArray(3);
	if (pMesh->m_bitangents.size() > 0)
	    glDisableVertexAttribArray(4);
    }

    GLenum RenderContextGL33::alphaBlendValue2GL(AlphaBlendValue val) const
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

    GLint RenderContextGL33::pixelFormat2GL(PixelFormat format) const
    {
	switch(format)
	{
	    case PixelFormat::BGR:
		return GL_BGR;
	    case PixelFormat::BGRA:
		return GL_BGRA;
	    case PixelFormat::RGB:
		return GL_RGB;
	    case PixelFormat::RGBA:
		return GL_RGBA;
	    case PixelFormat::LUMINANCE:
		return GL_LUMINANCE;
	    default:
		return -1;
	}
    }

    unsigned int RenderContextGL33::pixelFormatSize(PixelFormat format) const
    {
	switch(format)
	{
	    case PixelFormat::LUMINANCE:
		return 1;
	    case PixelFormat::BGR:
	    case PixelFormat::RGB:
		return 3;
	    case PixelFormat::BGRA:
	    case PixelFormat::RGBA:
		return 4;
	    default:
		return 0;
	}
    }

    GLenum RenderContextGL33::pixelType2GL(PixelType type) const
    {
	switch(type)
	{
	    case PixelType::BYTE:
		return GL_BYTE;
	    case PixelType::FLOAT:
		return GL_FLOAT;
	    case PixelType::INT:
		return GL_INT;
	    case PixelType::SHORT:
		return GL_SHORT;
	    case PixelType::UBYTE:
		return GL_UNSIGNED_BYTE;
	    case PixelType::UINT:
		return GL_UNSIGNED_INT;
	    case PixelType::USHORT:
		return GL_UNSIGNED_SHORT;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum RenderContextGL33::rowAlignment2GL(RowAlignment align) const
    {
	switch (align)
	{
	    case RowAlignment::PACK:
		return GL_PACK_ALIGNMENT;
	    case RowAlignment::UNPACK:
		return GL_UNPACK_ALIGNMENT;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum RenderContextGL33::minFilter2GL(MinFilter filter) const
    {
	switch(filter)
	{
	    case MinFilter::LINEAR:
		return GL_LINEAR;
	    case MinFilter::LINEAR_MIPMAP_LINEAR:
		return GL_LINEAR_MIPMAP_LINEAR;
	    case MinFilter::LINEAR_MIPMAP_NEAREST:
		return GL_LINEAR_MIPMAP_NEAREST;
	    case MinFilter::NEAREST:
		return GL_NEAREST;
	    case MinFilter::NEAREST_MIPMAP_LINEAR:
		return GL_NEAREST_MIPMAP_LINEAR;
	    case MinFilter::NEAREST_MIPMAP_NEAREST:
		return GL_NEAREST_MIPMAP_NEAREST;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum RenderContextGL33::magFilter2GL(MagFilter filter) const
    {
	switch(filter)
	{
	    case MagFilter::LINEAR:
		return GL_LINEAR;
	    case MagFilter::NEAREST:
		return GL_NEAREST;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum RenderContextGL33::compPixelFormat2GL(PixelFormatCompressed format) const
    {
	switch(format)
	{
	    case PixelFormatCompressed::COMP_DXT1:
		return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	    case PixelFormatCompressed::COMP_DXT3:
		return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	    case PixelFormatCompressed::COMP_DXT5:
		return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	    default:
		return GL_INVALID_ENUM;
	}
    }
}
