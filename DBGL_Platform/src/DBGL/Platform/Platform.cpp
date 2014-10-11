//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Platform.h"

namespace dbgl
{
    Platform::IType* Platform::s_pType = nullptr;

    template<class Type> void Platform::init()
    {
	if (s_pType != nullptr)
	    throw "Platform already initialized!";
	else
	    s_pType = new Type {};
    }

    void Platform::destroy()
    {
	delete s_pType;
	s_pType = nullptr;
    }

    auto Platform::get() -> IType*
    {
	return s_pType;
    }
}
