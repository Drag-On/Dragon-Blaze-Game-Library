//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/Texture.h"

namespace dbgl
{
    Texture::Texture(const Type type, const std::string path)
    {
	bool success = false;
	switch (type)
	{
	    case BOGUS:
		success = createBogus();
		break;
	    case DDS:
		success = loadDDS(path, false);
		break;
	    case DDS_VERTICAL_FLIP:
		success = loadDDS(path, true);
		break;
	    case TGA:
		success = loadTGA(path);
		break;
	}
	if (!success)
	{
	    LOG->warning("Texture %s not loaded!", path.c_str());
	    m_textureId = 0;
	}
    }

    Texture::~Texture()
    {
	glDeleteTextures(1, &m_textureId);
    }

    GLuint Texture::getTextureHandle()
    {
	return m_textureId;
    }

    bool Texture::createBogus()
    {
	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	unsigned char data[3] = {
		255, 255, 255
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_BGR,
	GL_UNSIGNED_BYTE, &data);
	return true;
    }

    bool Texture::loadDDS(const std::string path, bool vertFlip)
    {
	bool result = false;
	// Read file
	std::ifstream file;
	file.open(path.c_str(), std::ios::in | std::ios::binary);
	if (file.is_open())
	{
	    file.seekg(0, std::ios::beg);
	    // File identification
	    char filecode[4];
	    file.read(filecode, 4);
	    if (strncmp(filecode, "DDS ", 4) != 0)
	    {
		LOG->warning("File %s is not a valid DDS file", path.c_str());
		file.close();
		result = false;
	    }
	    else
	    {
		// Read header
		char header[124];
		file.read(header, 124);
		unsigned int height = *(unsigned int*) &(header[8]);
		unsigned int width = *(unsigned int*) &(header[12]);
		unsigned int linearSize = *(unsigned int*) &(header[16]);
		unsigned int mipMapCount = *(unsigned int*) &(header[24]);
		unsigned int fourCC = *(unsigned int*) &(header[80]);
		// Read mipmaps
		unsigned int bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		char* buffer = new char[bufsize];
		file.read(buffer, bufsize);
		// Close file
		file.close();
		// Analyze data
		unsigned int format;
		result = true;
		switch (fourCC)
		{
		    case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		    case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		    case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		    default:
			LOG->warning("File %s is not DXT1-, DXT3- or DXT5-compressed", path.c_str());
			delete[] buffer;
			result = false;
			break;
		}
		if (result) // If everything went right so far pass loaded texture to GL
		{
		    // Create OpenGL texture
		    glGenTextures(1, &m_textureId);
		    // Bind texture
		    glBindTexture(GL_TEXTURE_2D, m_textureId);
		    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		    unsigned int offset = 0;
		    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		    // Load mipmaps
		    for (unsigned int level = 0;
			    level < mipMapCount && (width || height); ++level)
		    {
			if(vertFlip)
			{
			    // Vertically flip texture to fit OpenGL needs
			    ddsFlipVertically(buffer, offset, width, height, blockSize, fourCC);
			}
			// Send compressed image to GL
			unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width,
				height, 0, size, buffer + offset);
			// Prepare for next mipmap
			offset += size;
			width /= 2;
			height /= 2;
			// If the texture is not squared, width or height might become 0
			// All mipmaps must have at least a width and height of 1
			if (width < 1)
			    width = 1;
			if (height < 1)
			    height = 1;
		    }
		    // In case the file doesn't have mipmaps generate some
		    if(mipMapCount == 1)
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		delete[] buffer;
	    }
	}
	else
	{
	    LOG->warning("Texture file %s could not be opened.", path.c_str());
	    result = false;
	}
	if (!result)
	{
	    // If something went wrong simply create a 1x1 white texture
	    // This makes sure the shader is not totally lost and at least
	    // *something* shows up on screen
	    createBogus();
	}
	return result;
    }

    bool Texture::loadTGA(const std::string path)
    {
	bool result = false;
	// Read file
	std::ifstream file;
	file.open(path.c_str(), std::ios::in | std::ios::binary);
	char* image = NULL;
	unsigned short int width, height;
	int colorMode;
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
		result = false;
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
		    result = false;
		}
		else
		{
//		    // Palette start, usually 0
//		    unsigned short int paletteStart = *(unsigned short int*) &header[3];
//		    // Amount of colors in palette
//		    unsigned short int paletteLength = *(unsigned short int*) &header[5];
//		    // Size of one palette entry
//		    unsigned char paletteEntrySize = header[7];
//		    // Coordinates for origin
//		    unsigned short int originX = *(unsigned short int*) &header[8];
//		    unsigned short int originY = *(unsigned short int*) &header[10];
		    // Image resolution
		    width = *(unsigned short int*) &header[12];
		    height = *(unsigned short int*) &header[14];
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
		    result = true;
		}
	    }
	}

	// If everything went right so far pass loaded texture to GL
	if (result)
	{
	    // Create OpenGL texture
	    glGenTextures(1, &m_textureId);
	    // Bind texture
	    glBindTexture(GL_TEXTURE_2D, m_textureId);
	    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	    GLint intFormat = colorMode == 3 ? GL_RGB : GL_RGBA;
	    GLint format = colorMode == 3 ? GL_BGR_EXT : GL_BGRA_EXT;
	    glTexImage2D(GL_TEXTURE_2D, 0, intFormat, width, height, 0, format,
		    GL_UNSIGNED_BYTE, image);
	    glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
	    // If something went wrong simply create a 1x1 white texture
	    // This makes sure the shader is not totally lost and at least
	    // *something* shows up on screen
	    createBogus();
	}
	delete[] image;

	return result;
    }

    void Texture::ddsFlipVertically(char* buffer, unsigned int offset,
	    unsigned int width, unsigned int height, unsigned int blockSize,
	    unsigned int fourCC)
    {
	unsigned int bytesInARow = ((width + 3) / 4) * blockSize;
	unsigned char* temp = new unsigned char[bytesInARow];
	unsigned char* sourceRow = (unsigned char*) buffer + offset;
	unsigned char* destinationRow = (unsigned char*) buffer + offset
		+ ((height + 3) / 4 - 1) * bytesInARow;
	for (unsigned int i = 0; i < (height + 3) / 4 / 2; i++)
	{
	    // Swap source row with appropriate mirror row
	    memcpy(temp, destinationRow, bytesInARow);
	    memcpy(destinationRow, sourceRow, bytesInARow);
	    memcpy(sourceRow, temp, bytesInARow);
	    // Also swap pixels in blocks
	    switch (fourCC)
	    {
		case FOURCC_DXT1:
		{
		    for (unsigned int j = 0; j < bytesInARow / blockSize; j++)
		    {
			ddsFlipDXT1Block(sourceRow + j * blockSize);
			ddsFlipDXT1Block(destinationRow + j * blockSize);
		    }
		    break;
		}
		case FOURCC_DXT3:
		{
		    for (unsigned int j = 0; j < bytesInARow / blockSize; j++)
		    {
			ddsFlipDXT3Block(sourceRow + j * blockSize);
			ddsFlipDXT3Block(destinationRow + j * blockSize);
		    }
		    break;
		}
		case FOURCC_DXT5:
		{
		    for (unsigned int j = 0; j < bytesInARow / blockSize; j++)
		    {
			ddsFlipDXT5Block(sourceRow + j * blockSize);
			ddsFlipDXT5Block(destinationRow + j * blockSize);
		    }
		    break;
		}
	    }
	    sourceRow += bytesInARow;
	    destinationRow -= bytesInARow;
	}
	delete[] temp; // Vertical flipping done
    }

    void Texture::ddsFlipDXT1Block(unsigned char *data)
    {
	std::swap(data[4], data[7]);
	std::swap(data[5], data[6]);
    }

    void Texture::ddsFlipDXT3Block(unsigned char *data)
    {
	std::swap(data[0], data[6]);
	std::swap(data[1], data[7]);
	std::swap(data[2], data[4]);
	std::swap(data[3], data[5]);
	ddsFlipDXT1Block(data + 8);
    }

    void Texture::ddsFlipDXT5Block(unsigned char *data)
    {
	unsigned int row0_1 = data[2] + 256 * (data[3] + 256 * data[4]);
	unsigned int row2_3 = data[5] + 256 * (data[6] + 256 * data[7]);
	unsigned int row1_0 = ((row0_1 & 0x000fff) << 12)
		| ((row0_1 & 0xfff000) >> 12);
	unsigned int row3_2 = ((row2_3 & 0x000fff) << 12)
		| ((row2_3 & 0xfff000) >> 12);
	data[2] = row3_2 & 0xff;
	data[3] = (row3_2 & 0xff00) >> 8;
	data[4] = (row3_2 & 0xff0000) >> 16;
	data[5] = row1_0 & 0xff;
	data[6] = (row1_0 & 0xff00) >> 8;
	data[7] = (row1_0 & 0xff0000) >> 16;
	ddsFlipDXT1Block(data + 8);
    }
}

