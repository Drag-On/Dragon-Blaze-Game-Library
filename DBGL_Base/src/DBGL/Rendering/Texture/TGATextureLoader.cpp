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
    Texture* TGATextureLoader::load(std::string path, Bitmask /* flags */)
    {
	GLuint texID;
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
		LOG->warning("TGA files with palettes currently not supported.");
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
		    LOG->warning("TGA files in other modes than uncompressed RGB or monochrome currently not supported.");
		    file.close();
		    return BogusTextureLoader().load("");
		}
		else
		{
//		    unsigned short int paletteStart = 0, paletteLength = 0, originX = 0, originY = 0;
		    for(int i = 0; i < 2; i++)
		    {
//			// Palette start, usually 0
//			paletteStart = (paletteStart << 8) | header[3 + i];
//			// Amount of colors in palette
//			paletteLength = (paletteLength << 8) | header[5 + i];
//			// Coordinates for origin
//			originX = (originX << 8) | header[8 + i];
//			originY = (originY) | header[10 + i];
			// Image resolution
			width = (width << 8) | header[12 + i];
			height = (height << 8) | header[14 + i];
		    }
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
	glGenTextures(1, &texID);
	// Bind texture
	glBindTexture(GL_TEXTURE_2D, texID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLint intFormat = colorMode == 3 ? GL_RGB : GL_RGBA;
	GLint format = colorMode == 3 ? GL_BGR_EXT : GL_BGRA_EXT;
	glTexImage2D(GL_TEXTURE_2D, 0, intFormat, width, height, 0, format,
	GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	delete[] image;

	return new Texture(texID);
    }
}
