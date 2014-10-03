//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Texture/TGATextureLoader.h"

namespace dbgl
{
    Texture* TGATextureLoader::load(std::string path, Bitmask<> /* flags */, TextureLoader::Filtering filtering)
    {
	// Read file
	std::ifstream file;
	file.open(path.c_str(), std::ios::in | std::ios::binary);
	char* image = NULL;
	unsigned short int width = 0, height = 0;
	int colorMode = 0;
	if (file.is_open())
	{
	    file.seekg(0, std::ios::beg);

	    // File header
	    char header[18];
	    file.read(header, 18);
	    // Length of Image ID field
//	    unsigned char imageIDLen = header[0];
	    // Color palette
	    // 0 = no palette, 1 = palette
	    unsigned char colorPaletteType = header[1];
	    if (colorPaletteType != 0)
	    {
		LOG.warning("TGA files with palettes currently not supported.");
		file.close();
		return BogusTextureLoader().load("");
	    }
	    else
	    {
		// Image type
		// 0 = no img, 1 = indexed, 2 = RGB, 3 = monochrome, 9-11 run-length coded
		unsigned char imageType = header[2];
		if(imageType != 2 && imageType != 3)
		{
		    LOG.warning("TGA files in other modes than uncompressed RGB or monochrome currently not supported.");
		    file.close();
		    return BogusTextureLoader().load("");
		}
		else
		{
//		    unsigned short int paletteStart = 0, paletteLength = 0, originX = 0, originY = 0;
//		    paletteStart = (header[3]<<0) | (header[4]<<8);
//		    paletteLength = (header[5]<<0) | (header[6]<<8);
//		    originX = (header[8]<<0) | (header[9]<<8);
//		    originY = (header[10]<<0) | (header[11]<<8);
		    width = (header[12]<<0) | (header[13]<<8);
		    height = (header[14]<<0) | (header[15]<<8);
//		    // Size of one palette entry
//		    unsigned char paletteEntrySize = header[7];
		    // Bits per pixel
		    unsigned char bitDepth = header[16];
		    // Attribute byte
		    // 0-3: Amount of attribute bits per pixel
		    //   4: Horizontal position of origin (0 = left, 1 = right)
		    //   5: Vertical position of origin (0 = down, 1 = up)
		    // 6-7: 0
//		    unsigned char attribute = header[17];

		    // File contents
		    // Image identification
//		    char* imageID = new char[imageIDLen];
//		    file.read(imageID, imageIDLen);
		    // Color palette
//		    char* colorPalette = new char[paletteLength];
//		    file.read(colorPalette, paletteLength);
		    // Actual image data
		    // Calculate color mode; 3 = BGR, 4 = BGRA
		    colorMode = bitDepth / 8;
		    unsigned int imageDataLength = width * height * colorMode;
		    image = new char[imageDataLength];
		    file.read(image, imageDataLength);

		    // Close file
		    file.close();

//		    delete [] imageID;
//		    delete [] colorPalette;
		}
	    }
	}

	// Create OpenGL texture
	auto handle = GLProvider::get()->texGenerate(IGL::TextureType::TEX2D);
	// Bind texture
	GLProvider::get()->texBind(handle);

	GLProvider::get()->texSetRowAlignment(IGL::RowAlignment::UNPACK, 1); // TODO: Check if always 1?
	auto format = colorMode == 3 ? IGL::PixelFormat::BGR : IGL::PixelFormat::BGRA;
	GLProvider::get()->texWrite(0, width, height, format, IGL::PixelType::UBYTE, image);
	// Select filtering algorithm
	IGL::MagFilter filterMag = IGL::MagFilter::NEAREST;
	IGL::MinFilter filterMin = IGL::MinFilter::NEAREST_MIPMAP_NEAREST;
	switch(filtering)
	{
	    case TextureLoader::Filtering::LINEAR:
		filterMag = IGL::MagFilter::LINEAR;
		filterMin = IGL::MinFilter::LINEAR_MIPMAP_LINEAR;
		break;
	    default:
		break;
	}
	// Linear filtering when magnifying
	GLProvider::get()->texSetMagFilter(filterMag);
	// Linear blending when minifying
	GLProvider::get()->texSetMinFilter(filterMin);
	GLProvider::get()->texGenerateMipMaps();

	delete[] image;

	return new Texture(handle);
    }
}
