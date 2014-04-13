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
#include "Mesh/Mesh.h"
#include "ShaderProgram.h"
#include "Texture/Texture.h"
#include "System/Log/Log.h"

namespace dbgl
{
    class Window;

    /**
     * @brief The RenderContext serves as the main rendering authority.
     * @details All objects that are supposed to be displayed need to be passed to an instance
     * 		of this class.
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
	    virtual ~RenderContext();
	    /**
	     * @brief Draws a mesh using the currently bound shader
	     * @param mesh Mesh to draw
	     */
	    virtual void draw(Mesh const& mesh) const;
	    /**
	     * @brief Updates this render context
	     * @param width New width of of the framebuffer
	     * @param height New height of the framebuffer
	     */
	    void changeSize(unsigned int width, unsigned int height);
	protected:
	    /**
	     * @brief Updates the render context's cached values, needed once per frame
	     */
	    virtual void preRender();
	    /**
	     * @brief Called after rendering has been done
	     */
	    virtual void postRender();

	    unsigned int m_frameWidth, m_frameHeight;
	private:
	    /**
	     * @brief Renders a mesh to the current context, assuming everything has
	     * 	      been set up accordingly. This method does not touch any matrices,
	     * 	      shaders, or other stuff. It just renders the mesh to whatever has
	     * 	      been set up before.
	     * @param mesh Pointer to the mesh to render
	     */
	    void renderMesh(Mesh const& mesh) const;

	    // Window::preRender can access internals - only for preRender() method
	    friend class Window;
    };
}

#endif /* RENDERCONTEXT_H_ */
