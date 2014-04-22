//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef BOGUSTEXTURELOADER_H_
#define BOGUSTEXTURELOADER_H_

#include "Texture.h"
#include "TextureLoader.h"

namespace dbgl
{
    /**
     * @brief Fallback texture loader in case of errors. Creates a white texture
     * 	      of size 1 x 1.
     */
    class BogusTextureLoader: public TextureLoader
    {
	public:
	    Texture* load(std::string path, Bitmask<> flags = 0);
	private:
    };
}

#endif /* BOGUSTEXTURELOADER_H_ */
