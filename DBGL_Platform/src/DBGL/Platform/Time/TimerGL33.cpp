//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Time/TimerGL33.h"

namespace dbgl
{
    double TimerGL33::getTime()
    {
	return glfwGetTime();
    }

    double TimerGL33::getDelta()
    {
	static double last = 0;
	double now = getTime();
	double step { now - last };
	last = now;
	return step;
    }
}
