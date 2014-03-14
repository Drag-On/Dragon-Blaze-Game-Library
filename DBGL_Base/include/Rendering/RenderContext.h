//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RENDERCONTEXT_H_
#define RENDERCONTEXT_H_

#include <GL/glew.h>
#include <vector>
#include <algorithm>
#include "Mesh.h"
#include "Camera.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Renderable.h"
#include "System/Log/Log.h"

namespace dbgl
{
    class Window;

    /**
     * @brief The RenderContext serves as the main rendering authority.
     * @details All objects that are supposed to be displayed need to be passed to an instance
     * 		of this class. It will then take care of the model and render it to all
     * 		viewports where it is visible.
     */
    class RenderContext
    {
	public:
	    /**
	     * @brief Creates a new render context
	     * @param width New width of of the framebuffer
	     * @param height New height of the framebuffer
	     */
	    RenderContext(unsigned int frameWidth, unsigned int frameHeight);
	    /**
	     * @brief Cleans up memory
	     */
	    ~RenderContext();
	    /**
	     * @brief Adds a new viewport to this context which will then be drawn to
	     * @details Without a viewport you won't see anything!
	     * @param viewport New viewport object to add
	     */
	    void addViewport(Viewport* viewport);
	    /**
	     * @brief Removes the passed viewport from this render context
	     * @param viewport Viewport to remove
	     */
	    void removeViewport(Viewport* viewport);
	    /**
	     * @brief Draws a mesh to all viewports where it is visible
	     * @param entity Entity to draw
	     */
	    void draw(Renderable const& entity) const;
	    /**
	     * @brief Updates this render context
	     * @param width New width of of the framebuffer
	     * @param height New height of the framebuffer
	     */
	    void changeSize(unsigned int width, unsigned int height);
	private:
	    /**
	     * @brief Renders a mesh to the current context, assuming everything has
	     * 	      been set up accordingly. This method does not touch any matrices,
	     * 	      shaders, or other stuff. It just renders the mesh to whatever has
	     * 	      been set up before.
	     * @param mesh Pointer to the mesh to render
	     */
	    void renderMesh(const Mesh* mesh) const;
	    /**
	     * @brief Updates the render context's cached values, needed once per frame
	     */
	    void preRender();

	    unsigned int m_frameWidth, m_frameHeight;
	    std::vector<Viewport*> m_viewports;
	    // Window::preRender can access internals - only for update() method
	    friend class Window;
    };
}

#endif /* RENDERCONTEXT_H_ */
