//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/RenderContext.h"

namespace dbgl
{
    GLuint RenderContext::vertexArrayId; // Actual static definition

    RenderContext::RenderContext()
    {
    }

    RenderContext::~RenderContext()
    {
    }

    void RenderContext::addViewport(Viewport const& viewport)
    {
	_viewports.push_back(viewport);
    }

    void RenderContext::draw(const Mesh* mesh) const
    {
	// TODO: Check viewports
	// TODO: Matrices...
	renderMesh(mesh);
    }

    void RenderContext::init(bool depthTest, bool faceCulling)
    {
	// Enable depth test?
	if (depthTest)
	{
	    glEnable(GL_DEPTH_TEST);
	    glDepthFunc(GL_LESS);
	}

	// Cull triangles that are not facing the camera?
	if (faceCulling)
	    glEnable(GL_CULL_FACE);

	// Create vertex array
	glGenVertexArrays(1, &RenderContext::vertexArrayId);
	glBindVertexArray(RenderContext::vertexArrayId);
    }

    void RenderContext::destroy()
    {
	glDeleteVertexArrays(1, &RenderContext::vertexArrayId);
    }

    void RenderContext::renderMesh(const Mesh* mesh) const
    {
	// Bind vertex buffer : 0
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->_vertexBuffer);
	glVertexAttribPointer(0,	// attribute
		3,			// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,			// stride
		(void*) 0);		// offset

	// Bind UV buffer : 1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->_uvBuffer);
	glVertexAttribPointer(1,	// attribute
		2,			// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,			// stride
		(void*) 0);		// offset

	// Bind normal buffer : 2
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->_normalBuffer);
	glVertexAttribPointer(2,	// attribute
		3,			// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,			// stride
		(void*) 0);		// offset

	// Bind color buffer : 3
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->_colorBuffer);
	glVertexAttribPointer(3,	// attribute
		3,			// size
		GL_FLOAT,		// type
		GL_FALSE,		// normalized?
		0,			// stride
		(void*) 0);		// offset

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->_indexBuffer);

	// Draw!
	glDrawElements(GL_TRIANGLES,	// mode
		mesh->_indices.size(),	// count
		GL_UNSIGNED_SHORT,	// type
		(void*) 0);		// offset

	// Disable buffers
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
    }
}

