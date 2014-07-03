//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Renderer/Renderer.h"

namespace dbgl
{
    Renderer* Renderer::pInstance = nullptr;

    Renderer* Renderer::get()
    {
	return pInstance;
    }

    void Renderer::set(Renderer* renderer)
    {
	if(pInstance != nullptr)
	    delete pInstance;
	pInstance = renderer;
    }
}
