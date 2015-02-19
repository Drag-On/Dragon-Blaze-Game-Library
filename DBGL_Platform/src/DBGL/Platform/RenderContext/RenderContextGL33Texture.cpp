//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/RenderContext/RenderContextGL33Texture.h"

namespace dbgl
{
	RenderContextGL33Texture::RenderContextGL33Texture(unsigned int width, unsigned int height, bool createDepthBuf)
	{
		if (!isBound())
			bind();

		m_pTex = new TextureGL33 { ITexture::Type::TEX2D };

		// Create framebuffer object
		glGenFramebuffers(1, &m_frameBufferId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

		// Create depth buffer
		if (createDepthBuf)
		{
			glGenRenderbuffers(1, &m_depthBufferId);
			glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferId);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferId);
		}

		// Configure framebuffer to use the passed texture
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_pTex->getHandle(), 0);
		GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);

		// Check for errors
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw std::runtime_error(
					"Framebuffer could not be created. Therefore the created render context will draw to the screen instead of the passed texture.");
			glDeleteFramebuffers(1, &m_frameBufferId);
		}

		// Update stored dimensions
		m_width = width;
		m_height = height;
	}

	RenderContextGL33Texture::~RenderContextGL33Texture()
	{
	}

	int RenderContextGL33Texture::getWidth()
	{
		return m_width;
	}

	int RenderContextGL33Texture::getHeight()
	{
		return m_height;
	}

	ITexture* RenderContextGL33Texture::getTexture()
	{
		return m_pTex;
	}

}
