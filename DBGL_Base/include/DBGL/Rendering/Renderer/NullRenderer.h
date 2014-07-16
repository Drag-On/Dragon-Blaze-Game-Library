//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef NULLRENDERER_H_
#define NULLRENDERER_H_

#include "Renderer.h"
#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    class NullRenderer: public Renderer
    {
	public:
	    virtual ~NullRenderer();
	    virtual VertexBufferId genVertexBuffer(BufferType type, unsigned int size, const void* data);
	    virtual void delVertexBuffer(VertexBufferId id);
	    virtual void fillVertexBuffer(VertexBufferId id, BufferType type, unsigned int size, const void* data);
	    virtual IndexBufferId genIndexBuffer(BufferType type, unsigned int size, const void* data);
	    virtual void delIndexBuffer(IndexBufferId id);
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
    };
}

#endif /* NULLRENDERER_H_ */
