//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TGATEXTURELOADER_H_
#define TGATEXTURELOADER_H_

#include <string>
#include <iostream>
#include <fstream>
#include "TextureLoader.h"
#include "BogusTextureLoader.h"

namespace dbgl
{
    /**
     * @brief Capable of loading uncompressed TGA files
     */
    class TGATextureLoader : public TextureLoader
    {
	public:
	    virtual ~TGATextureLoader() {};
	    virtual Texture* load(std::string path, Bitmask flags = 0);
	private:
    };
}



#endif /* TGATEXTURELOADER_H_ */
