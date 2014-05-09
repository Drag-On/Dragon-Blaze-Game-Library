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
#include "AbstractRenderer.h"
#include "NullRenderer.h"

namespace dbgl
{
    class OpenGL3Renderer : public NullRenderer // AbstractRenderer
    {
	public:
	    virtual ~OpenGL3Renderer();
	    virtual VertexBufferId genVertexBuffer(BufferType type, unsigned int size, const void* data);
	    virtual void delVertexBuffer(VertexBufferId id);
	    virtual IndexBufferId genIndexBuffer(BufferType type, unsigned int size, const void* data);
	    void delIndexBuffer(IndexBufferId id);
//	    virtual void useVertexBuffer(VertexBufferId vertBuffer);
//	    virtual void endUseVertexBuffer(VertexBufferId vertBuffer);
//	    virtual void useIndexBuffer(IndexBufferId indexBuffer);
//	    virtual void endUseIndexBuffer(IndexBufferId indexBuffer);
//	    virtual void drawElements(PolygonMode mode);
	private:
	    GLenum convertBufferType(BufferType type);

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

	    std::map<VertexBufferId, VertexBuffer> m_vertexBuffers;
	    std::map<IndexBufferId, IndexBuffer> m_indexBuffers;
    };
}



#endif /* OPENGL3RENDERER_H_ */
