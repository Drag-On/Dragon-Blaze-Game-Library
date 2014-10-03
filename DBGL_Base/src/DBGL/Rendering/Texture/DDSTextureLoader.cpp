//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Texture/DDSTextureLoader.h"

namespace dbgl
{
    Texture* DDSTextureLoader::load(std::string path, Bitmask<> flags, TextureLoader::Filtering filtering)
    {
	IGL::TextureHandle handle = IGL::InvalidTextureHandle;
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
		LOG.warning("File % is not a valid DDS file", path.c_str());
		file.close();
		return BogusTextureLoader().load("");
	    }
	    else
	    {
		// Read header
		char header[124];
		file.read(header, 124);
		unsigned int height = (header[8]<<0) | (header[9]<<8) | (header[10]<<16) | (header[11]<<24);
		unsigned int width = (header[12]<<0) | (header[13]<<8) | (header[14]<<16) | (header[15]<<24);
		unsigned int linearSize = (header[16]<<0) | (header[17]<<8) | (header[18]<<16) | (header[19]<<24);
		unsigned int mipMapCount = (header[24]<<0) | (header[25]<<8) | (header[26]<<16) | (header[27]<<24);
		unsigned int fourCC = (header[80]<<0) | (header[81]<<8) | (header[82]<<16) | (header[83]<<24);
		// Read mipmaps
		unsigned int bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		char* buffer = new char[bufsize];
		file.read(buffer, bufsize);
		// Close file
		file.close();
		// Analyze data
		IGL::PixelFormatCompressed format;
		switch (fourCC)
		{
		    case FOURCC_DXT1:
			format = IGL::PixelFormatCompressed::COMP_DXT1;
			break;
		    case FOURCC_DXT3:
			format = IGL::PixelFormatCompressed::COMP_DXT3;
			break;
		    case FOURCC_DXT5:
			format = IGL::PixelFormatCompressed::COMP_DXT5;
			break;
		    default:
			LOG.warning("File % is not DXT1-, DXT3- or DXT5-compressed", path.c_str());
			delete[] buffer;
			return nullptr;
			break;
		}
		// Create OpenGL texture
		handle = GLProvider::get()->texGenerate(IGL::TextureType::TEX2D);
		// Bind texture
		GLProvider::get()->texBind(handle);
		GLProvider::get()->texSetRowAlignment(IGL::RowAlignment::UNPACK, 1); // TODO: Check if always 1?
		unsigned int offset { 0 };
		unsigned int blockSize{ (format == IGL::PixelFormatCompressed::COMP_DXT1) ? 8 : 16 };
		// Load mipmaps
		for (unsigned int level = 0;
			level < mipMapCount && (width || height); ++level)
		{
		    if(flags.isSet(Texture::FlipVertically))
		    {
			// Vertically flip texture to fit OpenGL needs
			ddsFlipVertically(buffer, offset, width, height, blockSize, fourCC);
		    }
		    // Send compressed image to GL
		    unsigned int size { ((width + 3) / 4) * ((height + 3) / 4) * blockSize };
		    GLProvider::get()->texWriteCompressed(level, width, height, format, size, buffer + offset);
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
		// Set filtering when magnifying
		GLProvider::get()->texSetMagFilter(filterMag);
		// Set filtering when minifying
		GLProvider::get()->texSetMinFilter(filterMin);
		// In case the file doesn't have mipmaps generate some
		if(mipMapCount == 1)
		    GLProvider::get()->texGenerateMipMaps();
		delete[] buffer;
	    }
	    return new Texture(handle);
	}
	LOG.warning("Texture file % could not be opened.", path.c_str());
	return BogusTextureLoader().load("");
    }

    void DDSTextureLoader::ddsFlipVertically(char* buffer, unsigned int offset, unsigned int width,
	    unsigned int height, unsigned int blockSize, unsigned int fourCC)
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

     void DDSTextureLoader::ddsFlipDXT1Block(unsigned char *data)
     {
 	std::swap(data[4], data[7]);
 	std::swap(data[5], data[6]);
     }

     void DDSTextureLoader::ddsFlipDXT3Block(unsigned char *data)
     {
 	std::swap(data[0], data[6]);
 	std::swap(data[1], data[7]);
 	std::swap(data[2], data[4]);
 	std::swap(data[3], data[5]);
 	ddsFlipDXT1Block(data + 8);
     }

     void DDSTextureLoader::ddsFlipDXT5Block(unsigned char *data)
     {
 	unsigned int row0_1 = data[2] + 256 * (data[3] + 256 * data[4]);
 	unsigned int row2_3 = data[5] + 256 * (data[6] + 256 * data[7]);
	unsigned int row1_0 = ((row0_1 & 0x000fff) << 12) | ((row0_1 & 0xfff000) >> 12);
	unsigned int row3_2 = ((row2_3 & 0x000fff) << 12) | ((row2_3 & 0xfff000) >> 12);
 	data[2] = row3_2 & 0xff;
 	data[3] = (row3_2 & 0xff00) >> 8;
 	data[4] = (row3_2 & 0xff0000) >> 16;
 	data[5] = row1_0 & 0xff;
 	data[6] = (row1_0 & 0xff00) >> 8;
 	data[7] = (row1_0 & 0xff0000) >> 16;
 	ddsFlipDXT1Block(data + 8);
     }
}
