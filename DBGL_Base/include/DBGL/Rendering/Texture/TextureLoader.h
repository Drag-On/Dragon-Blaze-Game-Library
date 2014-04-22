//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

#include <string>
#include "DBGL/System/Bitmask/Bitmask.h"

namespace dbgl
{
    class Texture;

    /**
     * @brief Interface for all texture loaders
     */
    class TextureLoader
    {
	public:
	    virtual ~TextureLoader() {};
	    /**
	     * @brief Loads the texture from hard disk
	     * @param path Path of the texture
	     * @param flags Special behavior that may be requested from the loader
	     * @return The loaded texture if everything went right, otherwise NULL
	     */
	    virtual Texture* load(std::string path, Bitmask<> flags = 0) = 0;
	private:
    };
}

#endif /* TEXTURELOADER_H_ */
