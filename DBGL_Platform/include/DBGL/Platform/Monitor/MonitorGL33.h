//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MONITORGL33_H_
#define MONITORGL33_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IMonitor.h"

namespace dbgl
{
    /**
     * @brief IMonitor implementation for OpenGL 3.3
     */
    class MonitorGL33: public IMonitor
    {
	public:
	    virtual ~MonitorGL33() = default;
	    virtual void getResolution(int& width, int& height);
    };
}

#endif /* MONITORGL33_H_ */
