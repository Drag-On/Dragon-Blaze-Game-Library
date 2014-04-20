//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SCENERENDERCONTEXT_H_
#define SCENERENDERCONTEXT_H_

#include <vector>
#include "Renderable.h"
#include "Viewport.h"
#include "DBGL/Rendering/Camera.h"
#include "DBGL/Rendering/RenderContext.h"

namespace dbgl
{
    class Window;

    class SceneRenderContext: public RenderContext
    {
	public:
	    /**
	     * @brief Creates a new render context
	     * @param width New width of of the framebuffer
	     * @param height New height of the framebuffer
	     */
	    SceneRenderContext(unsigned int frameWidth, unsigned int frameHeight);
	    /**
	     * @brief Cleans up memory
	     */
	    virtual ~SceneRenderContext();
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
	     * @brief Draws a entity to all viewports where it is visible
	     * @param entity Entity to draw
	     */
	    virtual void draw(Renderable const& entity) const;
	protected:
	    /**
	     * @brief Updates the render context's cached values, needed once per frame
	     */
	    virtual void preRender();
	private:
	    std::vector<Viewport*> m_viewports;

	    friend class Window;
    };
}

#endif /* SCENERENDERCONTEXT_H_ */
