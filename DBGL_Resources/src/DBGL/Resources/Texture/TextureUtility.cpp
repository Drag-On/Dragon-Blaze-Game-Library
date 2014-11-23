//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Texture/TextureUtility.h"

namespace dbgl
{
    TextureUtility::ImageData::ImageData(unsigned char* imgData, unsigned int width, unsigned int height) : m_width{width}, m_height{height}
    {
	m_pPixels = new Color[width * height];
	for (unsigned y = 0; y < height; y++)
	{
	    for (unsigned x = 0; x < width; x++)
	    {
		m_pPixels[x + y * width].setRed(imgData[4 * (x + y * width) + 0]);
		m_pPixels[x + y * width].setGreen(imgData[4 * (x + y * width) + 1]);
		m_pPixels[x + y * width].setBlue(imgData[4 * (x + y * width) + 2]);
		m_pPixels[x + y * width].setAlpha(imgData[4 * (x + y * width) + 3]);
	    }
	}
    }

    TextureUtility::ImageData::ImageData(ImageData const& other)
    {
	m_height = other.m_height;
	m_width = other.m_width;
	m_pPixels = new Color[m_width * m_height];
	std::copy(other.m_pPixels, other.m_pPixels + m_height * m_width, m_pPixels);
    }

    TextureUtility::ImageData::ImageData(ImageData&& other)
    {
	m_height = std::move(other.m_height);
	m_width = std::move(other.m_width);
	m_pPixels = other.m_pPixels;
	other.m_pPixels = nullptr;
	other.m_height = 0;
	other.m_width = 0;
    }

    TextureUtility::ImageData::~ImageData()
    {
	delete [] m_pPixels;
    }

    auto TextureUtility::ImageData::getPixel(unsigned int x, unsigned int y) const -> Color const&
    {
	return m_pPixels[x + y * m_height];
    }

    void TextureUtility::ImageData::setPixel(unsigned int x, unsigned int y, Color const& color)
    {
	m_pPixels[x + y * m_height] = color;
    }

    unsigned int TextureUtility::ImageData::getWidth() const
    {
	return m_width;
    }

    unsigned int TextureUtility::ImageData::getHeight() const
    {
	return m_height;
    }

    auto TextureUtility::ImageData::operator=(ImageData const& other) -> ImageData&
    {
	if(this != &other)
	{
	    m_height = other.m_height;
	    m_width = other.m_width;
	    delete [] m_pPixels;
	    m_pPixels = new Color[m_width * m_height];
	    std::copy(other.m_pPixels, other.m_pPixels + m_height * m_width, m_pPixels);
	}
	return *this;
    }

    auto TextureUtility::ImageData::operator=(ImageData&& other) -> ImageData&
    {
	if(this != &other)
	{
	    m_height = other.m_height;
	    m_width = other.m_width;
	    delete [] m_pPixels;
	    m_pPixels = other.m_pPixels;
	    other.m_pPixels = nullptr;
	    other.m_height = 0;
	    other.m_width = 0;
	}
	return *this;
    }

    auto TextureUtility::createImageData(ITexture* tex) -> ImageData
    {
	char* buffer = new char[tex->getHeight() * tex->getWidth() * 4];
	tex->setRowAlignment(ITexture::RowAlignment::PACK, 1);
	tex->getPixelData(ITexture::PixelFormat::RGBA, ITexture::PixelType::UBYTE, buffer, 0);
	ImageData img{reinterpret_cast<unsigned char*>(buffer), tex->getWidth(), tex->getHeight()};
	delete [] buffer;
	return img;
    }

    ITexture* TextureUtility::createTexture(ImageData const& img)
    {
	auto tex = Platform::get()->createTexture(ITexture::Type::TEX2D);
	replaceTexture(tex, img);
	return tex;
    }

    void TextureUtility::replaceTexture(ITexture* tex, ImageData const& img)
    {
	tex->setRowAlignment(ITexture::RowAlignment::UNPACK, 1);
	tex->write(0, img.getWidth(), img.getHeight(), ITexture::PixelFormat::RGBA, ITexture::PixelType::UBYTE, img.m_pPixels);
    }
}
