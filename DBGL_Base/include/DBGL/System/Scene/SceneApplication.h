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
#include "DBGL/System/System.h"
#include "DBGL/System/DBGLApplication.h"
#include "DBGL/System/Entity/Entity.h"
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Window/Window.h"

namespace dbgl
{
    /**
     * @brief Basic application main class which structures entities into a scene graph to ease scene management
     */
    class SceneApplication : public DBGLApplication
    {
	public:
	    virtual void init();
	    virtual void run();
	protected:
	    /**
	     * @brief Updates all entities
	     * @param args Update event arguments
	     */
	    virtual void update(Window::UpdateEventArgs const& args);
	    /**
	     * @brief Renders all entities
	     * @param args Render event arguments
	     */
	    virtual void render(Window::RenderEventArgs const& args);
	    /**
	     * @brief Returns the window used by this application
	     * @return A pointer to the used window
	     */
	    virtual Window* createWindow() = 0;
	    /**
	     * @brief Loads all required resources
	     */
	    virtual void loadResources() = 0;


	    /**
	     * @brief The scene graph
	     */
	    SceneGraph<Entity> m_sceneGraph;
	    /**
	     * @brief The used window
	     */
	    Window* m_pWindow;
    };
}

#endif /* SCENEAPPLICATION_H_ */
