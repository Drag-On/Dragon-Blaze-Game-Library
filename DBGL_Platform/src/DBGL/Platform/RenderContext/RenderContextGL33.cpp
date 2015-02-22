//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/RenderContext/RenderContextGL33.h"
#include "DBGL/Platform/Texture/TextureCommandsGL33.h"

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
		if (!isBound())
			bind();
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
		if (!isBound())
			bind();
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
		if (!isBound())
			bind();
		if (src == AlphaBlendValue::Zero && dest == AlphaBlendValue::Zero)
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
		if (glGetError() != GL_NO_ERROR)
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
		if (!isBound())
			bind();
		switch (val)
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
			throw std::invalid_argument("Unknown value for face culling.");
			return;
		}
		m_curFaceCullingVal = val;
	}

	auto RenderContextGL33::getFaceCulling() const -> FaceCullingValue
	{
		return m_curFaceCullingVal;
	}

	void RenderContextGL33::setDrawMode(DrawMode mode)
	{
		GLenum glMode = GL_FILL;
		switch(mode)
		{
		case DrawMode::Fill:
			glMode = GL_FILL;
			break;
		case DrawMode::Line:
			glMode = GL_LINE;
			break;
		case DrawMode::Point:
			glMode = GL_POINT;
			break;
		default:
			throw std::invalid_argument("Unknown value for draw mode.");
			return;
		}
		glPolygonMode(GL_FRONT_AND_BACK, glMode);
	}

	auto RenderContextGL33::getDrawMode() const -> DrawMode
	{
		GLint current[2];
		glGetIntegerv(GL_POLYGON_MODE, current);
		switch(current[0])
		{
		case GL_FILL:
			return DrawMode::Fill;
		case GL_LINE:
			return DrawMode::Line;
		case GL_POINT:
			return DrawMode::Point;
		default:
			throw std::invalid_argument("Unknown value for draw mode.");
		}
	}

	void RenderContextGL33::setMultisampling(bool msaa)
	{
		if (!isBound())
			bind();
		if (msaa)
			glEnable(GL_MULTISAMPLE);
		else
			glDisable(GL_MULTISAMPLE);
		m_msaaEnabled = msaa;
	}

	bool RenderContextGL33::getMultisampling() const
	{
		return m_msaaEnabled;
	}

	std::array<float, 3> RenderContextGL33::getClearColor() const
	{
		return m_clearcolor;
	}

	void RenderContextGL33::setClearColor(std::array<float, 3> color)
	{
		if (!isBound())
			bind();
		m_clearcolor = color;
		glClearColor(m_clearcolor[0], m_clearcolor[1], m_clearcolor[2], 0);
	}

	void RenderContextGL33::bind()
	{
		if (m_frameBufferId != s_curFrameBufferId)
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
		if (!isBound())
			bind();
		glViewport(x, y, width, height);
	}

	void RenderContextGL33::readPixels(int x, int y, int width, int height, ITextureCommands::PixelFormat format,
			ITextureCommands::PixelType type, unsigned int bufsize, char* buf)
	{
		if (!isBound())
			bind();
		// Allocate buffer
		unsigned int imgDataSize { width * height * TextureCommandsGL33::pixelFormatSize(format) };
		if (!buf || bufsize < imgDataSize)
			return;
		// Copy pixel data to buffer
		glReadPixels(x, y, width, height, TextureCommandsGL33::pixelFormat2GL(format), TextureCommandsGL33::pixelType2GL(type), buf);
	}

	void RenderContextGL33::drawMesh(IMesh* mesh)
	{
		if (!isBound())
			bind();

		MeshGL33* pMesh = dynamic_cast<MeshGL33*>(mesh);
		if (pMesh == nullptr)
			throw std::invalid_argument("Cannot render null mesh.");

		// Bind vertex buffer : 0
		if (pMesh->getVertexCount() > 0)
		{
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, pMesh->getVertexHandle());
			glVertexAttribPointer(0,	// attribute
					3,			// size
					GL_FLOAT,		// type
					GL_FALSE,		// normalized?
					0,			// stride
					(void*) 0);		// offset
		}
		// Bind UV buffer : 1
		if (pMesh->getUVCount() > 0)
		{
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, pMesh->getUVHandle());
			glVertexAttribPointer(1,	// attribute
					2,			// size
					GL_FLOAT,		// type
					GL_FALSE,		// normalized?
					0,			// stride
					(void*) 0);		// offset
		}
		// Bind normal buffer : 2
		if (pMesh->getNormalCount() > 0)
		{
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, pMesh->getNormalHandle());
			glVertexAttribPointer(2,	// attribute
					3,			// size
					GL_FLOAT,		// type
					GL_FALSE,		// normalized?
					0,			// stride
					(void*) 0);		// offset
		}
		// Bind tangent buffer : 3
		if (pMesh->getTangentCount() > 0)
		{
			glEnableVertexAttribArray(3);
			glBindBuffer(GL_ARRAY_BUFFER, pMesh->getTangentHandle());
			glVertexAttribPointer(3,	// attribute
					3,			// size
					GL_FLOAT,		// type
					GL_FALSE,		// normalized?
					0,			// stride
					(void*) 0);		// offset
		}
		// Bind bitangent buffer : 4
		if (pMesh->getBitangentCount() > 0)
		{
			glEnableVertexAttribArray(4);
			glBindBuffer(GL_ARRAY_BUFFER, pMesh->getBitangentHandle());
			glVertexAttribPointer(4,	// attribute
					3,			// size
					GL_FLOAT,		// type
					GL_FALSE,		// normalized?
					0,			// stride
					(void*) 0);		// offset
		}
		if (pMesh->getIndexCount() > 0)
		{
			// Index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pMesh->getIndexHandle());
			// Draw!
			glDrawElements(GL_TRIANGLES,	// mode
					pMesh->getIndexCount(),	// count
					GL_UNSIGNED_SHORT,		// type
					(void*) 0);			// offset
		}

		// Disable buffers
		if (pMesh->getVertexCount() > 0)
			glDisableVertexAttribArray(0);
		if (pMesh->getUVCount() > 0)
			glDisableVertexAttribArray(1);
		if (pMesh->getNormalCount() > 0)
			glDisableVertexAttribArray(2);
		if (pMesh->getTangentCount() > 0)
			glDisableVertexAttribArray(3);
		if (pMesh->getBitangentCount() > 0)
			glDisableVertexAttribArray(4);
	}

	GLenum RenderContextGL33::alphaBlendValue2GL(AlphaBlendValue val)
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
