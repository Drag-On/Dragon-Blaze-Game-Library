//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/GL/GLProvider.h"
#include "DBGL/Platform/GL/GLOpenGL33.h"

namespace dbgl
{
    IGL* GLProvider::s_pGL = nullptr;

    void GLProvider::init(API api)
    {
	if (s_pGL == nullptr)
	{
	    switch (api)
	    {
		case GLProvider::API::OpenGL33:
		    s_pGL = new GLOpenGL33 {};
		    break;
	    }
	}
    }

    IGL* GLProvider::get()
    {
	return s_pGL;
    }

    void GLProvider::free()
    {
	delete s_pGL;
    }
}
