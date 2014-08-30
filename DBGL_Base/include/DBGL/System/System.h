//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DBGL/System/IDbglApplication.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/Window/WindowManager.h"

namespace dbgl
{
    /**
     * @brief Sets up DBGL
     */
    void initialize();
    /**
     * @brief Sets up DBGL
     * @param app Pointer to instance of a class derived from DBGLApplication
     */
    void initialize(IDbglApplication* app);
    /**
     * @brief Terminates DBGL and frees some remaining memory
     */
    void terminate();
    /**
     * @brief Checks if dbgl is up and running
     * @return true in case everything is allright, otherwise false
     */
    bool isRunning();
    /**
     * @brief Updates everything within dbgl. Every call equals one "frame"
     */
    void update();
}

#endif /* SYSTEM_H_ */
