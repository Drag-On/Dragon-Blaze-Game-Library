//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Utility/TextureUtility.h"

namespace dbgl
{
    TextureUtility::ImageData::ImageData(char* imgData, unsigned int width, unsigned int height) : m_width{width}, m_height{height}
    {
	m_pPixels = new PixelData[width * height];
	for (unsigned y = 0; y < height; y++)
	{
	    for (unsigned x = 0; x < width; x++)
	    {
		m_pPixels[x + y * width].r = imgData[4 * (x + y * width) + 0];
		m_pPixels[x + y * width].g = imgData[4 * (x + y * width) + 1];
		m_pPixels[x + y * width].b = imgData[4 * (x + y * width) + 2];
		m_pPixels[x + y * width].a = imgData[4 * (x + y * width) + 3];
	    }
	}
    }

    TextureUtility::ImageData::~ImageData()
    {
	delete [] m_pPixels;
    }

    auto TextureUtility::ImageData::getPixel(unsigned int x, unsigned int y) -> PixelData&
    {
	return m_pPixels[x + y * m_height];
    }

    unsigned int TextureUtility::ImageData::getWidth() const
    {
	return m_width;
    }

    unsigned int TextureUtility::ImageData::getHeight() const
    {
	return m_height;
    }

    auto TextureUtility::createImageData(ITexture* tex) -> ImageData
    {
	char* buffer = new char[tex->getHeight() * tex->getWidth() * 4];
	tex->setRowAlignment(ITexture::RowAlignment::PACK, 1);
	tex->getPixelData(ITexture::PixelFormat::RGBA, ITexture::PixelType::UBYTE, buffer, 0);
	ImageData img{buffer, tex->getWidth(), tex->getHeight()};
	delete [] buffer;
	return img;
    }
}
