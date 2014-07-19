//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "Entity.h"
#include "DBGL/Rendering/RenderContext.h"

namespace dbgl
{
    class RenderComponent : Entity::Component
    {
	public:
	    /**
	     * @brief Initializes this render component
	     */
	    void init(); // TODO: Take render info like shader, texture ...
	    /**
	     * @brief Updates this component
	     * @param deltaTime Time since last update
	     */
	    virtual void update(Entity* owner, double deltaTime);
	    /**
	     * @brief Called upon render process
	     * @param rc RenderContext to draw to
	     */
	    virtual void render(Entity* owner, RenderContext const* rc) = 0;
	    /**
	     * @brief Determines whether this component wants to be updated
	     * @return True if needs to be updated, otherwise false
	     */
	    virtual bool needUpdate() const = 0;
	    /**
	     * @brief Determines whether this component wants to be rendered
	     * @return True if needs to be rendered, otherwise false
	     */
	    virtual bool needRender() const = 0;
	private:
    };
}



#endif /* RENDERCOMPONENT_H_ */
