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

#include "AbstractRenderer.h"
#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    class NullRenderer: public AbstractRenderer
    {
	public:
	    virtual ~NullRenderer();
	    virtual VertexBufferId genVertexBuffer(BufferType type, unsigned int size, const void* data);
	    virtual void delVertexBuffer(VertexBufferId id);
	    virtual IndexBufferId genIndexBuffer(BufferType type, unsigned int size, const void* data);
	    virtual void delIndexBuffer(IndexBufferId id);
	    virtual VertexFormatId regVertexFormat(AttribType type, unsigned int size, AttribFormat format);
	    virtual void useVertexBuffer(VertexBufferId vertBuffer, VertexFormatId vertFormat);
	    virtual void endUseVertexBuffer(VertexBufferId vertBuffer, VertexFormatId vertFormat);
	    virtual void useIndexBuffer(IndexBufferId indexBuffer);
	    virtual void endUseIndexBuffer(IndexBufferId indexBuffer);
	    virtual void drawElements(PolygonMode mode);
    };
}

#endif /* NULLRENDERER_H_ */
