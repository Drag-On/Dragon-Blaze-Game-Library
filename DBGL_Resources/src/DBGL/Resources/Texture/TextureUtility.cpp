//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Texture/TextureUtility.h"
#include "DBGL/Platform/Texture/ITextureCommands.h"

namespace dbgl
{
	TextureUtility::ImageData::ImageData(unsigned char* imgData, unsigned int width, unsigned int height) :
			m_width { width }, m_height { height }
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
		delete[] m_pPixels;
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
		if (this != &other)
		{
			m_height = other.m_height;
			m_width = other.m_width;
			delete[] m_pPixels;
			m_pPixels = new Color[m_width * m_height];
			std::copy(other.m_pPixels, other.m_pPixels + m_height * m_width, m_pPixels);
		}
		return *this;
	}

	auto TextureUtility::ImageData::operator=(ImageData&& other) -> ImageData&
	{
		if (this != &other)
		{
			m_height = other.m_height;
			m_width = other.m_width;
			delete[] m_pPixels;
			m_pPixels = other.m_pPixels;
			other.m_pPixels = nullptr;
			other.m_height = 0;
			other.m_width = 0;
		}
		return *this;
	}

	auto TextureUtility::createImageData(ITexture* tex) -> ImageData
	{
		tex->bind();
		unsigned int width = Platform::get()->curTexture()->getWidth();
		unsigned int height = Platform::get()->curTexture()->getHeight();
		const unsigned int size = width * height * 4;
		unsigned char buffer[size] { };
		Platform::get()->curTexture()->setRowAlignment(ITextureCommands::RowAlignment::PACK, 1);
		Platform::get()->curTexture()->getPixelData(ITextureCommands::PixelFormat::RGBA,
				ITextureCommands::PixelType::UBYTE, reinterpret_cast<char*>(&buffer[0]), 0);
		ImageData img { &buffer[0], width, height };
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
		tex->bind();
		Platform::get()->curTexture()->setRowAlignment(ITextureCommands::RowAlignment::UNPACK, 1);
		Platform::get()->curTexture()->write(0, img.getWidth(), img.getHeight(), ITextureCommands::PixelFormat::RGBA,
				ITextureCommands::PixelType::UBYTE, img.m_pPixels);
	}
}
