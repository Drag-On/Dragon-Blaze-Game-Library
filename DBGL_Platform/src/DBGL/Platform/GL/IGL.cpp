//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/GL/IGL.h"

namespace dbgl
{
    IGL::IGL()
    {
	static bool initialized { false };
	if(initialized)
	    throw("Can't have more than one graphics layer.");
	initialized = true;
    }
}
