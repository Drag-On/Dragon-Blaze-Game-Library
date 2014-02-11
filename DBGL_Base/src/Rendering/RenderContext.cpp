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
    GLuint RenderContext::vertexArrayId; // Actual definition

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

    template<typename T> void RenderContext::draw(Mesh const& mesh)
    {
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
}

