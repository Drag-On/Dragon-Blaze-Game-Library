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
    GLuint RenderContext::curFrameBufferId = 0;

    RenderContext::RenderContext(unsigned int frameWidth, unsigned int frameHeight) :
	    m_frameWidth(frameWidth), m_frameHeight(frameHeight)
    {
    }

    RenderContext::RenderContext(Texture const& tex, bool createDepthBuf) : m_frameWidth(tex.getWidth()), m_frameHeight(tex.getHeight())
    {
	// Create framebuffer object
	glGenFramebuffers(1, &m_frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

	// Create depth buffer
	if(createDepthBuf)
	{
	    glGenRenderbuffers(1, &m_depthBufferId);
	    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferId);
	    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_frameWidth, m_frameHeight);
	    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferId);
	}

	// Configure framebuffer to use the passed texture
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex.getHandle(), 0);
	GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	// Check for errors
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
	    LOG.error("Framebuffer could not be created. Therefore the created render context will draw to the screen instead of the passed texture.");
	    glDeleteFramebuffers(1, &m_frameBufferId);
	}
    }

    RenderContext::~RenderContext()
    {
	// Note: 0 (the screen) is silently ignored by glDeleteFramebuffers
	glDeleteFramebuffers(1, &m_frameBufferId);
    }

    void RenderContext::draw(Mesh const& mesh) const
    {
	bindContext();
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

    void RenderContext::saveSnapshot(std::string filename) const
    {
	// Make sure this context is currently bound
	bindContext();
	// Allocate buffer
	unsigned int imgDataSize { getWidth() * getHeight() * 3 };
	char* bmpBuf = new char[imgDataSize];
	if(!bmpBuf)
	    return;
	// Copy pixel data to buffer
	glReadPixels(0, 0, getWidth(), getHeight(), GL_BGR, GL_UNSIGNED_BYTE, bmpBuf);
	// Open file stream
	std::ofstream file(filename, std::fstream::out | std::fstream::binary | std::fstream::trunc);
	if(!file.good())
	    return;
	// Write file header
	struct FileHeaderBMP
	{
		uint16_t id = 0x4D42;
		uint32_t fileSize = 0;
		uint32_t res = 0;
		uint32_t off = 54;
	} fileHeader{};
	fileHeader.fileSize = imgDataSize;
	file.write(reinterpret_cast<const char*>(&fileHeader.id), sizeof(uint16_t)); // "BM"
	file.write(reinterpret_cast<const char*>(&fileHeader.fileSize), sizeof(uint32_t)); // File size
	file.write(reinterpret_cast<const char*>(&fileHeader.res), sizeof(uint32_t)); // Reserved
	file.write(reinterpret_cast<const char*>(&fileHeader.off), sizeof(uint32_t)); // Offset to image data
	// Write info header
	struct InfoHeaderBMP
	{
		uint32_t size = 40;
		int32_t width = 0;
		int32_t height = 0;
		uint16_t panes = 1;
		uint16_t bpp = 24;
		uint32_t compr = 0;
		uint32_t imgSize = 0;
		int32_t xPixPerMeter = 0;
		int32_t yPixPerMeter = 0;
		uint32_t indexClr = 0;
		uint32_t clr = 0;
	} infoHeader{};
	infoHeader.width = static_cast<int32_t>(getWidth());
	infoHeader.height = static_cast<int32_t>(getHeight());
	file.write(reinterpret_cast<const char*>(&infoHeader.size), sizeof(uint32_t)); // Size of info header
	file.write(reinterpret_cast<const char*>(&infoHeader.width), sizeof(int32_t)); // Width in pixels
	file.write(reinterpret_cast<const char*>(&infoHeader.height), sizeof(int32_t)); // Height in pixels
	file.write(reinterpret_cast<const char*>(&infoHeader.panes), sizeof(uint16_t)); // Color planes (unused)
	file.write(reinterpret_cast<const char*>(&infoHeader.bpp), sizeof(uint16_t)); // BPP
	file.write(reinterpret_cast<const char*>(&infoHeader.compr), sizeof(uint32_t)); // Not compressed
	file.write(reinterpret_cast<const char*>(&infoHeader.imgSize), sizeof(uint32_t)); // Size of image data (unused)
	file.write(reinterpret_cast<const char*>(&infoHeader.xPixPerMeter), sizeof(int32_t)); // X pixel per meter (unused)
	file.write(reinterpret_cast<const char*>(&infoHeader.yPixPerMeter), sizeof(int32_t)); // Y pixel per meter (unused)
	file.write(reinterpret_cast<const char*>(&infoHeader.indexClr), sizeof(uint32_t)); // Amount of indexed colors (no indexing)
	file.write(reinterpret_cast<const char*>(&infoHeader.clr), sizeof(uint32_t)); // Use all colors
	// Write actual image
	file.write(bmpBuf, imgDataSize);
	file.close();

	delete [] bmpBuf;
    }

    void RenderContext::clear(Bitmask<char> buf) const
    {
	bindContext();
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
	bindContext();
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
	bindContext();
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
	bindContext();
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
	bindContext();
	glViewport(0, 0, m_frameWidth, m_frameHeight);
    }

    void RenderContext::postRender()
    {
    }

    void RenderContext::bindContext() const
    {
	if(m_frameBufferId != curFrameBufferId)
	{
	    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);
	    curFrameBufferId = m_frameBufferId;
	}
    }
}

