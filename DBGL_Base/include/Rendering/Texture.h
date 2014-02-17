//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Log/Log.h"

namespace dbgl
{
    class Texture
    {
	public:
	    /**
	     * @brief File types of textures that can be loaded
	     */
	    enum Type
	    {
		DDS,//!< DDS
	    };
	    /**
	     * @brief Constructs a new texture
	     * @param type Texture type
	     * @param path File path
	     */
	    Texture(Type type, std::string path);
	    /**
	     * @brief Clean up used memory
	     */
	    ~Texture();
	    /**
	     * @return GL texture handle
	     */
	    GLuint getTextureHandle();
	private:
	    /**
	     * @brief Loads a DXT1-, DXT3-, or DXT5-compressed DDS file from disk
	     * @param path Path of the file to load
	     * @return True in case the file has been loaded succesfully, otherwise false
	     */
	    bool loadDDS(std::string path);

	    /**
	     * @brief GL texture handle
	     */
	    GLuint _textureId;

	    /**
	     * @brief DXT formats that can be loaded
	     */
	    enum DXTType
	    {
		FOURCC_DXT1 = 0x31545844,//!< FOURCC_DXT1
		FOURCC_DXT3 = 0x33545844,//!< FOURCC_DXT3
		FOURCC_DXT5 = 0x35545844,//!< FOURCC_DXT5
	    };
    };
}

#endif /* TEXTURE_H_ */
