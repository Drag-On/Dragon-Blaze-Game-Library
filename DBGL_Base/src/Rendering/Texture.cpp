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
    Texture::Texture(Type type, std::string path)
    {
	bool success = false;
	switch(type)
	{
	    case DDS:
		success = loadDDS(path);
		break;
	}
	if(!success)
	{
	    LOG->warning("Texture %s not loaded!", path.c_str());
	    _textureId = 0;
	}
    }

    Texture::~Texture()
    {
	glDeleteTextures(1, &_textureId);
    }

    bool Texture::loadDDS(std::string path)
    {
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
		return false;
	    }
	    // Read header
	    char header[124];
	    file.read(header, 124);
	    unsigned int height = *(unsigned int*) &(header[8]);
	    unsigned int width = *(unsigned int*) &(header[12]);
	    unsigned int linearSize = *(unsigned int*) &(header[16]);
	    unsigned int mipMapCount = *(unsigned int*) &(header[24]);
	    unsigned int fourCC = *(unsigned int*) &(header[80]);
	    // Read mipmaps
	    unsigned int bufsize =
		    mipMapCount > 1 ? linearSize * 2 : linearSize;
	    char* buffer = new char[bufsize];
	    file.read(buffer, bufsize);
	    // Close file
	    file.close();
	    // Analyze data
	    unsigned int format;
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
		    LOG->warning("File %s is not DXT1-, DXT3 or DXT5-compressed", path.c_str());
		    delete[] buffer;
		    return false;
	    }
	    // Create OpenGL texture
	    glGenTextures(1, &_textureId);
	    // Bind texture
	    glBindTexture(GL_TEXTURE_2D, _textureId);
	    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	    unsigned int blockSize =
		    (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	    unsigned int offset = 0;
	    // Load mipmaps
	    for (unsigned int level = 0;
		    level < mipMapCount && (width || height); ++level)
	    {
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4)
			* blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width,
			height, 0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
		// Fix for textures that are not power-of-two
		if(width < 1)
		    width = 1;
		if(height < 1)
		    height = 1;
	    }
	    delete[] buffer;
	    return true;
	}
	else
	{
	    LOG->warning("Texture file %s could not be opened.", path.c_str());
	    return false;
	}
    }
}

