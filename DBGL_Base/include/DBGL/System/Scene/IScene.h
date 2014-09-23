//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ISCENE_H_
#define ISCENE_H_

#include "DBGL/Window/Window.h"

namespace dbgl
{
    /**
     * @brief Pure virtual interface class for all scenes
     */
    class IScene
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~IScene() = default;
	    /**
	     * @brief Called when the scene is being entered
	     */
	    virtual void enter() = 0;
	    /**
	     * @brief Called once per frame, update everything
	     * @param args Update arguments
	     */
	    virtual void update(Window::UpdateEventArgs const& args) = 0;
	    /**
	     * @brief Called once per frame, render everything
	     * @param args Render arguments
	     */
	    virtual void render(Window::RenderEventArgs const& args) = 0;
	    /**
	     * @brief Called when the scene is being left
	     */
	    virtual void leave() = 0;
    };
}

#endif /* ISCENE_H_ */
