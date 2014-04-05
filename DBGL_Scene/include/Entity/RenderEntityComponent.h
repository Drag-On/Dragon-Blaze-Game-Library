//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RENDERENTITYCOMPONENT_H_
#define RENDERENTITYCOMPONENT_H_

#include "EntityComponent.h"
#include "TransformEntityComponent.h"
#include "Rendering/Renderable.h"
#include "Rendering/SceneRenderContext.h"

namespace dbgl
{
    /**
     * @brief Holds renderable geometry
     */
    class RenderEntityComponent: public EntityComponent
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~RenderEntityComponent();
	    /**
	     * @brief Initializes this render component
	     * @param renderable Renderable to get data from
	     */
	    void init(Renderable const& renderable);
	    /**
	     * @brief Updates this component
	     * @param deltaTime Time since last update
	     */
	    virtual void update(std::map<std::type_index, EntityComponent*> const& components, double deltaTime);
	    /**
	     * @brief Renders everything to the passed render context
	     * @param rc Render context to draw to
	     */
	    void render(SceneRenderContext const* rc);
	private:
	    Renderable* m_pRenderable;
    };
}

#endif /* RENDERENTITYCOMPONENT_H_ */
