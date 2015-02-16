//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Platform.h"

namespace dbgl
{
    Platform::IImplementation* Platform::s_pType = nullptr;

    void Platform::destroy()
    {
	delete s_pType;
	s_pType = nullptr;
    }

    auto Platform::get() -> IImplementation*
    {
	return s_pType;
    }
}
