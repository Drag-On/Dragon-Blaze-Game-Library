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
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Log/Log.h"

namespace dbgl
{
    /**
     * @brief Used to load textures from hard disk
     */
    class Texture
    {
	public:
	    /**
	     * @brief File types of textures that can be loaded
	     */
	    enum Type
	    {
		DDS, //!< DDS
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
	     * @return True in case the file has been loaded successfully, otherwise false
	     */
	    bool loadDDS(std::string path);

	    /**
	     * @brief Vertically flips a DXT1 4x4 block
	     * @param data Block to flip
	     * @details Block Layout:
	     * 		Bit 0-1: color 0
	     * 		Bit 2-3: color 1
	     * 		Bit 4-7: 2 bit per pixel color bitmap
	     * 		Each of the bits 4-7 represents one line
	     */
	    static void ddsFlipDXT1Block(unsigned char *data);

	    /**
	     * @brief Vertically flips a DXT3 4x4 block
	     * @param data Block to flip
	     * @details Block Layout:
	     * 		Bit 0-7: 4-Bit alpha bitmap
	     * 		Bit 8-15: DXT1 block
	     */
	    static void ddsFlipDXT3Block(unsigned char *data);

	    /**
	     * @brief Vertically flips a DXT5 4x4 block
	     * @param data Block to flip
	     * @details Block Layout:
	     * 		Bit 0: Alpha 0
	     * 		Bit 1: Alpha 1
	     * 		Bit 2-7: 3-Bit Alpha Bitmap
	     * 		Bit 8-15: DXT1 block
	     */
	    static void ddsFlipDXT5Block(unsigned char *data);

	    /**
	     * @brief GL texture handle
	     */
	    GLuint _textureId;

	    /**
	     * @brief DXT formats that can be loaded
	     */
	    enum DXTType
	    {
		FOURCC_DXT1 = 0x31545844, //!< FOURCC_DXT1
		FOURCC_DXT3 = 0x33545844, //!< FOURCC_DXT3
		FOURCC_DXT5 = 0x35545844, //!< FOURCC_DXT5
	    };
    };
}

#endif /* TEXTURE_H_ */
