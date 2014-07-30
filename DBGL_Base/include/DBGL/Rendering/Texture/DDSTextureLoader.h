//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef DDSTEXTURELOADER_H_
#define DDSTEXTURELOADER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Texture.h"

namespace dbgl
{
    /**
     * @brief Capable of loading DDS files in DXT-1, DXT-3 and DXT-5 format.
     * @details Note that DDS files come from the DirectX world and thus appear
     * 		vertically flipped in OpenGL. You probably want to specify
     * 		Texture::FlipVertically to flip them back.
     */
    class DDSTextureLoader : public TextureLoader
    {
	public:
	    virtual ~DDSTextureLoader() {};
	    virtual Texture* load(std::string path, Bitmask<> flags = 0, TextureLoader::Filtering filtering = TextureLoader::Filtering::LINEAR);
	private:
	    /**
	     * @brief Vertically flips a dds image (i.e. one mip map level)
	     * @param buffer Buffer with all the levels
	     * @param offset Offset to the beginning of the level to flip
	     * @param width Level width in blocks
	     * @param height Level height in blocks
	     * @param blockSize Block size
	     * @param fourCC Type of image
	     */
	    void ddsFlipVertically(char* buffer, unsigned int offset, unsigned int width,
		    unsigned int height, unsigned int blockSize, unsigned int fourCC);

	    /**
	     * @brief Vertically flips a DXT1 4x4 block
	     * @param data Block to flip
	     * @details Block Layout:
	     * 		Bit 0-1: color 0
	     * 		Bit 2-3: color 1
	     * 		Bit 4-7: 2 bit per pixel color bitmap
	     * 		Each of the bits 4-7 represents one line
	     */
	    void ddsFlipDXT1Block(unsigned char *data);

	    /**
	     * @brief Vertically flips a DXT3 4x4 block
	     * @param data Block to flip
	     * @details Block Layout:
	     * 		Bit 0-7: 4-Bit alpha bitmap
	     * 		Bit 8-15: DXT1 block
	     */
	    void ddsFlipDXT3Block(unsigned char *data);

	    /**
	     * @brief Vertically flips a DXT5 4x4 block
	     * @param data Block to flip
	     * @details Block Layout:
	     * 		Bit 0: Alpha 0
	     * 		Bit 1: Alpha 1
	     * 		Bit 2-7: 3-Bit Alpha Bitmap
	     * 		Bit 8-15: DXT1 block
	     */
	    void ddsFlipDXT5Block(unsigned char *data);

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



#endif /* DDSTEXTURELOADER_H_ */
