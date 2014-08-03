//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Sprite/BitmapFont.h"

namespace dbgl
{
    BitmapFont::BitmapFont(std::string const& filename)
    {
	load(filename);
    }

    BitmapFont::BitmapFont(BitmapFont const& other)
    {
	m_pTexture = new Texture{*other.m_pTexture};
	m_pSprite = new Sprite{*other.m_pSprite};
    }

    BitmapFont::~BitmapFont()
    {
	delete m_pTexture;
	delete m_pSprite;
    }

    BitmapFont& BitmapFont::operator=(BitmapFont const& other)
    {
	if(this != &other)
	{
	    delete m_pTexture;
	    delete m_pSprite;
	    m_pTexture = new Texture{*other.m_pTexture};
	    m_pSprite = new Sprite{*other.m_pSprite};
	}
	return *this;
    }

    unsigned int BitmapFont::getWidth(std::string text) const
    {
	// Iterate over all characters and add up their widths
	unsigned int width = 0;
	for(char& c : text)
	{
	    width += m_widths[static_cast<int>(c)];
	}
	return width;
    }

    bool BitmapFont::load(std::string const& filename)
    {
	// Variables to store data in
	char headDat[headerSize]{};
	char* img = nullptr;
	// Stream to read from
	std::fstream in{};
	// Open file
	in.open(filename.c_str(), std::ios_base::binary | std::ios_base::in);
	// Everything alright?
	if(!in.is_open())
	    return false;
	// Read in header
	in.read(&(headDat[0]), headerSize);
	m_header.id1 = headDat[0];
	m_header.id2 = headDat[1];
	m_header.imgWidth = (headDat[2]<<0) | (headDat[3]<<8) | (headDat[4]<<16) | (headDat[5]<<24);
	m_header.imgHeight = (headDat[6]<<0) | (headDat[7]<<8) | (headDat[8]<<16) | (headDat[9]<<24);
	m_header.cellWidth = (headDat[10]<<0) | (headDat[11]<<8) | (headDat[12]<<16) | (headDat[13]<<24);
	m_header.cellHeight = (headDat[14]<<0) | (headDat[15]<<8) | (headDat[16]<<16) | (headDat[17]<<24);
	m_header.bpp = headDat[18];
	m_header.base = headDat[19];
	// Check if valid
	if(m_header.id1 != 0xBF || m_header.id2 != 0xF2)
	{
	    in.close();
	    LOG.error("Invalid BFF2 bitmap font file \"%\".", filename.c_str());
	    return false;
	}
	// Reject unsupported bpp values
	if(m_header.bpp != 8 && m_header.bpp != 24 && m_header.bpp != 32)
	{
	    in.close();
	    LOG.error("Bitmap font file \"%\" has unsupported amount of bits per pixel.", filename.c_str());
	    return false;
	}
	// Read in array with width of each character
	in.read(&(m_widths[0]), 256);
	// Read in texture
	long long int texDataSize = (m_header.imgWidth * m_header.imgHeight) * (m_header.bpp / 8);
	img = new char[texDataSize];
	if(!img)
	{
	    in.close();
	    LOG.error("Unable to allocate memory for bitmap font file \"%\".", filename.c_str());
	    return false;
	}
	in.read(img, texDataSize);
	in.close();

	// Create texture
	GLuint texId = GL_INVALID_VALUE;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Tex creation params are dependent on BPP
	switch (m_header.bpp)
	{
	    case 8:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_header.imgWidth, m_header.imgHeight, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, img);
		break;
	    case 24:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_header.imgWidth, m_header.imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		break;
	    case 32:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_header.imgWidth, m_header.imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
		break;
	    default:
		// Should never get here
		LOG.error("Bitmap font file \"%\" corrupt.", filename.c_str());
		break;
	}
	m_pTexture = new Texture {texId};
	m_pSprite = new Sprite {m_pTexture};

	delete [] img;
	return true;
    }
}
