//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef OPENGL3RENDERER_H_
#define OPENGL3RENDERER_H_

#include <GL/glew.h>
#include <map>
#include "Renderer.h"
#include "NullRenderer.h"

namespace dbgl
{
    class OpenGL3Renderer : public NullRenderer // AbstractRenderer
    {
	public:
	    virtual ~OpenGL3Renderer();
	    virtual VertexBufferId genVertexBuffer(BufferType type, unsigned int size, const void* data);
	    virtual void delVertexBuffer(VertexBufferId id);
	    virtual void fillVertexBuffer(VertexBufferId id, BufferType type, unsigned int size, const void* data);
	    virtual IndexBufferId genIndexBuffer(BufferType type, unsigned int size, const void* data);
	    void delIndexBuffer(IndexBufferId id);
	    virtual void fillIndexBuffer(IndexBufferId id, BufferType type, unsigned int size, const void* data);
	    virtual VertexFormatId regVertexFormat(AttribId id, unsigned int size, AttribFormat format);
	    virtual void useVertexBuffer(VertexBufferId vertBuffer, VertexFormatId vertFormat);
	    virtual void endUseVertexBuffer(VertexBufferId vertBuffer, VertexFormatId vertFormat);
	    virtual void useIndexBuffer(IndexBufferId indexBuffer);
	    virtual void endUseIndexBuffer(IndexBufferId indexBuffer);
	    virtual void drawElements(PolygonMode mode, unsigned int size, AttribFormat format);
	    virtual void changeViewport(unsigned int width, unsigned int height);
	    virtual TextureBuffer2dId genTextureBuffer2d(unsigned int width, unsigned int height, const void* data,
		    unsigned int level, TextureFormat texFormat, AttribFormat format);
	    virtual void delTextureBuffer2d(TextureBuffer2dId id);
	    virtual void fillTextureBuffer2d(TextureBuffer2dId id, unsigned int width, unsigned int height,
		    const void* data, unsigned int level, TextureFormat texFormat, AttribFormat format);
	private:
	    GLenum convertBufferType(BufferType type);
	    GLenum convertAttributeFormat(AttribFormat format, bool unsign = false);
	    GLenum convertPolygonMode(PolygonMode mode);
	    GLenum convertTextureFormat(TextureFormat format);

	    struct IndexBuffer
	    {
		    GLuint id;
		    GLsizei size;
	    };
	    struct VertexBuffer
	    {
		    GLuint id;
		    GLsizei size;
	    };
	    using TextureBuffer2d = GLuint;

	    std::map<VertexBufferId, VertexBuffer> m_vertexBuffers;
	    std::map<IndexBufferId, IndexBuffer> m_indexBuffers;
	    std::map<VertexFormatId, VertexFormat> m_vertexFormats;
	    std::map<TextureBuffer2dId, TextureBuffer2d> m_tex2dBuffers;
    };
}



#endif /* OPENGL3RENDERER_H_ */
