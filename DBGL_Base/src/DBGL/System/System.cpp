//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/System.h"

namespace dbgl
{
    /**
     * @brief Used if a DBGLApplication is passed to initialize()
     */
    static IDbglApplication* pApp = nullptr;

    void initialize()
    {
	// Initialize graphics layer
	GLProvider::init(GLProvider::API::OpenGL33);
    }

    void initialize(IDbglApplication* app)
    {
	initialize();
	app->init();
	pApp = app;
    }

    void terminate()
    {
	if(pApp != nullptr)
	    pApp->terminate();

	// Terminate windows
	WindowManager::get()->terminate();

	GLProvider::free();
    }

    bool isRunning()
    {
	return WindowManager::get()->isRunning();
    }

    void update()
    {
	WindowManager::get()->update();
    }
}
