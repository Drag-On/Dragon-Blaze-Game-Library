//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TIMERGL33_H_
#define TIMERGL33_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ITimer.h"

namespace dbgl
{
    class TimerGL33: public ITimer
    {
	public:
	    virtual ~TimerGL33() = default;
	    virtual double getTime();
	    virtual double getDelta();
    };
}

#endif /* TIMERGL33_H_ */
