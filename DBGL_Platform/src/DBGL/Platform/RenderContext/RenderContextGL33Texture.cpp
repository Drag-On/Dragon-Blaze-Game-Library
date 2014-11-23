//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/RenderContext/RenderContextGL33Texture.h"

namespace dbgl
{
    RenderContextGL33Texture::RenderContextGL33Texture(ITexture* texture, bool createDepthBuf)
    {
	if(!isBound())
	    bind();

	TextureGL33* tex = dynamic_cast<TextureGL33*>(texture);
	if(!tex)
	    throw std::invalid_argument("RenderContextGL33Texture can only handle OpenGL textures!");
	m_pTex = tex;

	// Create framebuffer object
	glGenFramebuffers(1, &m_frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

	// Create depth buffer
	if (createDepthBuf)
	{
	    glGenRenderbuffers(1, &m_depthBufferId);
	    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferId);
	    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, tex->getWidth(), tex->getHeight());
	    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferId);
	}

	// Configure framebuffer to use the passed texture
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex->getHandle(), 0);
	GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	// Check for errors
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
	    throw std::runtime_error(
		    "Framebuffer could not be created. Therefore the created render context will draw to the screen instead of the passed texture.");
	    glDeleteFramebuffers(1, &m_frameBufferId);
	}
    }

    RenderContextGL33Texture::~RenderContextGL33Texture()
    {
    }

    int RenderContextGL33Texture::getWidth()
    {
	return m_pTex->getWidth();
    }

    int RenderContextGL33Texture::getHeight()
    {
	return m_pTex->getHeight();
    }

}
