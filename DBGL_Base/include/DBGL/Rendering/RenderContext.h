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
#include "DBGL/System/Log/Log.h"

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
	     * @brief Types of buffers attached to the render context
	     */
	    enum Buffer : char
	    {
		COLOR = 1 << 0,   //!< COLOR
		DEPTH = 1 << 1,   //!< DEPTH
		STENCIL = 1 << 2, //!< STENCIL
	    };
	    /**
	     * @brief Options that can be set for depth testing
	     */
	    enum class DepthTestValue
	    {
		Off,    //!< Off
		Less,   //!< Less
		Greater,//!< Greater
	    };
	    /**
	     * @brief Options that can be set for alpha blending
	     */
	    enum class AlphaBlendValue
	    {
		Off,             //!< Off
		SrcAlpha,        //!< SrcAlpha
		OneMinusSrcAlpha,//!< OneMinusSrcAlpha
	    };
	    /**
	     * @brief Options that can be set for face culling
	     */
	    enum class FaceCullingValue
	    {
		Off,//!< Off
		On, //!< On
	    };


	    /**
	     * @brief Creates a new render context
	     * @param frameWidth New width of of the framebuffer
	     * @param frameHeight New height of the framebuffer
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
	    /**
	     * @brief Provides the render width
	     * @return Width of the render context
	     */
	    unsigned int getWidth() const;
	    /**
	     * @brief Provides the render height
	     * @return Height of the render context
	     */
	    unsigned int getHeight() const;
	    /**
	     * @brief Clear a buffer
	     * @param Buffers to clear (type RenderContext::Buffer)
	     */
	    void clear(Bitmask<char> buf) const;
	    /**
	     * @brief Sets the depth testing behavior
	     * @param val Value to set
	     */
	    void setDepthTest(DepthTestValue val) const;
	    /**
	     * @brief Sets the alpha blending behavior
	     * @param val Value to set
	     */
	    void setAlphaBlend(AlphaBlendValue val) const;
	    /**
	     * @brief Sets the face culling behavior
	     * @param val Value to set
	     */
	    void setFaceCulling(FaceCullingValue val) const;
	protected:
	    /**
	     * @brief Updates the render context's cached values, needed once per frame
	     */
	    virtual void preRender();
	    /**
	     * @brief Called after rendering has been done
	     */
	    virtual void postRender();

	    /**
	     * @brief Width of the frame
	     */
	    unsigned int m_frameWidth;
	    /**
	     * @brief Height of the frame
	     */
	    unsigned int m_frameHeight;
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
