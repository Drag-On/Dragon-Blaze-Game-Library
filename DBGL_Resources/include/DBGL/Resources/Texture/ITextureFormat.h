//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ITEXTUREFORMATLOADER_H_
#define ITEXTUREFORMATLOADER_H_

#include "DBGL/Platform/Texture/ITexture.h"

namespace dbgl
{
    class ITextureFormat
    {
	public:
	    enum class Ability
	    {
		LOAD,
		SAVE,
	    };
    };
}

#endif /* ITEXTUREFORMATLOADER_H_ */
