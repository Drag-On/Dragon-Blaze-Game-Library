//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Renderer/NullRenderer.h"

namespace dbgl
{
    NullRenderer::~NullRenderer()
    {
	LOG->debug("Destructing renderer.");
    }

    auto NullRenderer::genVertexBuffer(BufferType type, unsigned int size, const void* /* data */) -> VertexBufferId
    {
	LOG->debug("Generating vertex buffer of type %d, size %d.", type, size);
	return 0;
    }

    void NullRenderer::delVertexBuffer(VertexBufferId id)
    {
	LOG->debug("Deleting vertex buffer %d.", id);
    }

    auto NullRenderer::genIndexBuffer(BufferType type, unsigned int size, const void* /* data */) -> IndexBufferId
    {
	LOG->debug("Generating index buffer of type %d, size %d.", type, size);
	return 0;
    }

    void NullRenderer::delIndexBuffer(IndexBufferId id)
    {
	LOG->debug("Deleting index buffer %d.", id);
    }

    void NullRenderer::useVertexBuffer(VertexBufferId vertBuffer)
    {
	LOG->debug("Using vertex buffer %d.", vertBuffer);
    }

    void NullRenderer::endUseVertexBuffer(VertexBufferId vertBuffer)
    {
	LOG->debug("Ending use of vertex buffer %d.", vertBuffer);
    }

    void NullRenderer::useIndexBuffer(IndexBufferId indexBuffer)
    {
	LOG->debug("Using index buffer %d.", indexBuffer);
    }

    void NullRenderer::endUseIndexBuffer(IndexBufferId indexBuffer)
    {
	LOG->debug("Ending use of index buffer %d.", indexBuffer);
    }

    void NullRenderer::drawElements(PolygonMode /* mode */)
    {
	LOG->debug("Drawing elements.");
    }
}
