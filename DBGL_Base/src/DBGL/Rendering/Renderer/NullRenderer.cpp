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
	LOG.debug("Destructing renderer.");
    }

    auto NullRenderer::genVertexBuffer(BufferType type, unsigned int size, const void* /* data */) -> VertexBufferId
    {
	LOG.debug("Generating vertex buffer of type %, size %.", type==BufferType::STATIC?"Static":"Dynamic", size);
	return 0;
    }

    void NullRenderer::delVertexBuffer(VertexBufferId id)
    {
	LOG.debug("Deleting vertex buffer %.", id);
    }

    void NullRenderer::fillVertexBuffer(VertexBufferId id, BufferType type, unsigned int size, const void* /*data*/)
    {
	LOG.debug("Filling vertex buffer % of type % and size %.", id, type==BufferType::STATIC?"Static":"Dynamic", size);
    }

    auto NullRenderer::genIndexBuffer(BufferType type, unsigned int size, const void* /* data */) -> IndexBufferId
    {
	LOG.debug("Generating index buffer of type %, size %.", type==BufferType::STATIC?"Static":"Dynamic", size);
	return 0;
    }

    void NullRenderer::delIndexBuffer(IndexBufferId id)
    {
	LOG.debug("Deleting index buffer %.", id);
    }

    void NullRenderer::fillIndexBuffer(IndexBufferId id, BufferType type, unsigned int size, const void* /*data*/)
    {
	LOG.debug("Filling index buffer % of type % and size %.", id, type==BufferType::STATIC?"Static":"Dynamic", size);
    }

    auto NullRenderer::regVertexFormat(AttribId id, unsigned int size, AttribFormat /*format*/) -> VertexFormatId
    {
	LOG.debug("Registering vertex format with ID % and size %.", id, size);
	return 0;
    }

    void NullRenderer::useVertexBuffer(VertexBufferId vertBuffer, VertexFormatId /*vertFormat*/)
    {
	LOG.debug("Using vertex buffer %.", vertBuffer);
    }

    void NullRenderer::endUseVertexBuffer(VertexBufferId vertBuffer, VertexFormatId /*vertFormat*/)
    {
	LOG.debug("Ending use of vertex buffer %.", vertBuffer);
    }

    void NullRenderer::useIndexBuffer(IndexBufferId indexBuffer)
    {
	LOG.debug("Using index buffer %.", indexBuffer);
    }

    void NullRenderer::endUseIndexBuffer(IndexBufferId indexBuffer)
    {
	LOG.debug("Ending use of index buffer %.", indexBuffer);
    }

    void NullRenderer::drawElements(PolygonMode /* mode */, unsigned int size, AttribFormat /* format */)
    {
	LOG.debug("Drawing % elements.", size);
    }
}
