//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SCENEAPPLICATION_H_
#define SCENEAPPLICATION_H_

#include <stack>
#include "SceneGraph.h"
#include "DBGL/System/DBGLApplication.h"
#include "DBGL/System/Entity/Entity.h"
#include "DBGL/Rendering/RenderContext.h"

namespace dbgl
{
    /**
     * @brief Basic application main class which structures entities into a scene graph to ease scene management
     */
    class SceneApplication : public DBGLApplication
    {
	public:
	    /**
	     * @brief Updates all entities
	     * @param deltaTime Time since last update
	     */
	    void update(float deltaTime);
	    /**
	     * @brief Renders all entities
	     * @param rc Render context to draw to
	     */
	    void render(RenderContext const* rc);
	protected:
	    /**
	     * @brief The scene graph
	     */
	    SceneGraph<Entity> m_sceneGraph;
    };
}



#endif /* SCENEAPPLICATION_H_ */
