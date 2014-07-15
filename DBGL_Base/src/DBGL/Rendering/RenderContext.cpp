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
    RenderContext::RenderContext(unsigned int frameWidth,
	    unsigned int frameHeight) :
	    m_frameWidth(frameWidth), m_frameHeight(frameHeight)
    {
	m_verticesFormatId = Renderer::get()->regVertexFormat(0, 3, Renderer::AttribFormat::FLOAT);
	m_uvFormatId = Renderer::get()->regVertexFormat(1, 2, Renderer::AttribFormat::FLOAT);
	m_normalsFormatId = Renderer::get()->regVertexFormat(2, 3, Renderer::AttribFormat::FLOAT);
	m_tangentsFormatId = Renderer::get()->regVertexFormat(3, 3, Renderer::AttribFormat::FLOAT);
	m_bitangentsFormatId = Renderer::get()->regVertexFormat(4, 3, Renderer::AttribFormat::FLOAT);
    }

    RenderContext::~RenderContext()
    {
    }

    void RenderContext::draw(Mesh const& mesh) const
    {
	// Render mesh
	renderMesh(mesh);
    }

    void RenderContext::changeSize(unsigned int width, unsigned int height)
    {
	m_frameWidth = width;
	m_frameHeight = height;
    }

    void RenderContext::renderMesh(Mesh const& mesh) const
    {
	// Bind vertex buffer : 0
	if (mesh.m_vertices.size() > 0)
	    Renderer::get()->useVertexBuffer(mesh.m_vertexBuffer, m_verticesFormatId);

	// Bind UV buffer : 1
	if (mesh.m_uv.size() > 0)
	    Renderer::get()->useVertexBuffer(mesh.m_uvBuffer, m_uvFormatId);

	// Bind normal buffer : 2
	if (mesh.m_normals.size() > 0)
	    Renderer::get()->useVertexBuffer(mesh.m_normalBuffer, m_normalsFormatId);

	// Bind tangent buffer : 3
	if (mesh.m_tangents.size() > 0)
	    Renderer::get()->useVertexBuffer(mesh.m_tangentBuffer, m_tangentsFormatId);

	// Bind bitangent buffer : 4
	if (mesh.m_bitangents.size() > 0)
	    Renderer::get()->useVertexBuffer(mesh.m_bitangentBuffer, m_bitangentsFormatId);

	// Index buffer
	Renderer::get()->useIndexBuffer(mesh.m_indexBuffer);

	// Draw!
	Renderer::get()->drawElements(Renderer::PolygonMode::TRIANGLE, mesh.m_indices.size(), Renderer::AttribFormat::SHORT);

	// Disable buffers
	if (mesh.m_vertices.size() > 0)
	    Renderer::get()->endUseVertexBuffer(mesh.m_vertexBuffer, m_verticesFormatId);
	if (mesh.m_uv.size() > 0)
	    Renderer::get()->endUseVertexBuffer(mesh.m_uvBuffer, m_uvFormatId);
	if (mesh.m_normals.size() > 0)
	    Renderer::get()->endUseVertexBuffer(mesh.m_normalBuffer, m_normalsFormatId);
	if (mesh.m_tangents.size() > 0)
	    Renderer::get()->endUseVertexBuffer(mesh.m_tangentBuffer, m_tangentsFormatId);
	if (mesh.m_bitangents.size() > 0)
	    Renderer::get()->endUseVertexBuffer(mesh.m_bitangentBuffer, m_bitangentsFormatId);
	Renderer::get()->endUseIndexBuffer(mesh.m_indexBuffer);
    }

    void RenderContext::preRender()
    {
	glViewport(0, 0, m_frameWidth, m_frameHeight);
    }

    void RenderContext::postRender()
    {
    }
}

