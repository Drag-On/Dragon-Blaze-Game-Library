//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Sprite/BitmapFont.h"
#include "DBGL/Platform/Platform.h"

namespace dbgl
{
	BitmapFont::BitmapFont()
	{
#include"DefaultFont.imp"
		load(size, reinterpret_cast<const char*>(data));
	}

	BitmapFont::BitmapFont(std::string const& filename)
	{
		load(filename);
	}

	BitmapFont::BitmapFont(unsigned int size, char const* data)
	{
		load(size, data);
	}

	BitmapFont::BitmapFont(BitmapFont const& other)
	{
		m_pTexture = other.m_pTexture->clone();
		m_pSprite = new Sprite { *other.m_pSprite };
		m_header = other.m_header;
		m_rowPitch = other.m_rowPitch;
		std::copy(std::begin(other.m_widths), std::end(other.m_widths), std::begin(m_widths));
	}

	BitmapFont::~BitmapFont()
	{
		delete m_pTexture;
		delete m_pSprite;
	}

	BitmapFont& BitmapFont::operator=(BitmapFont const& other)
	{
		if (this != &other)
		{
			delete m_pTexture;
			delete m_pSprite;
			m_pTexture = other.m_pTexture->clone();
			m_pSprite = new Sprite { *other.m_pSprite };
		}
		return *this;
	}

	unsigned int BitmapFont::getWidth(std::string text) const
	{
		// Iterate over all characters and add up their widths
		unsigned int width = 0;
		for (char& c : text)
		{
			width += m_widths[static_cast<int>(c)];
		}
		return width;
	}

	unsigned int BitmapFont::getLineHeight() const
	{
		return m_header.cellHeight;
	}

	Sprite& BitmapFont::getSprite(char c)
	{
		unsigned int row = (c - m_header.base) / m_rowPitch;
		unsigned int col = (c - m_header.base) - row * m_rowPitch;
		Rectangle<unsigned int> rect { };
		rect.pos() = Vector2<unsigned int> { col * m_header.cellWidth, row * m_header.cellHeight };
		rect.extent() = Vector2<unsigned int> { static_cast<unsigned int>(m_widths[static_cast<int>(c)]),
				static_cast<unsigned int>(m_header.cellHeight) };
		m_pSprite->setRect(rect);
		return *m_pSprite;
	}

	void BitmapFont::drawText(IRenderContext* rc, IShaderProgram* shader, std::string const& text, unsigned int x,
			unsigned int y)
	{
		shader->use();
		unsigned int cursor = 0;
		for (char const& c : text)
		{
			// Check for uniforms
			auto transformId = shader->getUniformHandle("TRANSFORM_2D");
			auto screenResId = shader->getUniformHandle("v2_screenRes");
			auto diffuseId = shader->getUniformHandle("tex_diffuse");
			if (screenResId == IShaderProgram::InvalidUniformHandle
					|| transformId == IShaderProgram::InvalidUniformHandle
					|| diffuseId == IShaderProgram::InvalidUniformHandle)
				return;

			// Bind diffuse texture to unit 0
			m_pTexture->bind();
			Platform::get()->curTexture()->activateUnit(0);
			Platform::get()->curShaderProgram()->setUniformSampler(diffuseId, 0);

			// Set blend mode
			auto srcBlend = rc->getSrcAlphaBlend();
			auto destBlend = rc->getDestAlphaBlend();
			switch (m_header.bpp)
			{
			case 8:
				rc->setAlphaBlend(IRenderContext::AlphaBlendValue::SrcAlpha, IRenderContext::AlphaBlendValue::SrcAlpha);
				break;
			case 24:
				rc->setAlphaBlend(IRenderContext::AlphaBlendValue::Zero, IRenderContext::AlphaBlendValue::Zero);
				break;
			case 32:
				rc->setAlphaBlend(IRenderContext::AlphaBlendValue::One, IRenderContext::AlphaBlendValue::OneMinusSrcAlpha);
				break;
			}

			// Send to shader
			Mat3f transform = Mat3f::make2DTranslation(x + cursor, y);
			Platform::get()->curShaderProgram()->setUniformFloat2(screenResId, Vec2f { static_cast<float>(rc->getWidth()), static_cast<float>(rc->getHeight()) }.getDataPointer());
			Platform::get()->curShaderProgram()->setUniformFloatMatrix3Array(transformId, 1, false, transform.getDataPointer());
			rc->drawMesh(getSprite(c).getMesh());

			// Return to previous alpha blend values
			rc->setAlphaBlend(srcBlend, destBlend);
			// Move cursor right
			cursor += m_widths[static_cast<int>(c)];
		}
	}

	bool BitmapFont::load(std::string const& filename)
	{
		// Try to open the file
		std::ifstream input { filename, std::ifstream::in | std::ifstream::binary | std::ios::ate };
		if (!input.good())
		{
			LOG.warning("Unable to open file % for reading!", filename);
			input.close();
			return 1;
		}
		// Else read in data
		unsigned int filesize = input.tellg();
		input.seekg(0, std::ifstream::beg);
		char* data = new char[filesize];
		if (!data)
		{
			LOG.error("Unable to allocate sufficient memory!");
			input.close();
			return 1;
		}
		input.read(data, filesize);
		input.close();

		load(filesize, data);
		delete[] data;

		return true;
	}

	bool BitmapFont::load(unsigned int filesize, char const* data)
	{
		// Variables to store data in
		m_header.id1 = data[0];
		m_header.id2 = data[1];
		// Note: Sometimes the files are misformatted and contain negative values for width or height instead of positive ones
		m_header.imgWidth = std::abs((data[2] << 0) | (data[3] << 8) | (data[4] << 16) | (data[5] << 24));
		m_header.imgHeight = std::abs((data[6] << 0) | (data[7] << 8) | (data[8] << 16) | (data[9] << 24));
		m_header.cellWidth = (data[10] << 0) | (data[11] << 8) | (data[12] << 16) | (data[13] << 24);
		m_header.cellHeight = (data[14] << 0) | (data[15] << 8) | (data[16] << 16) | (data[17] << 24);
		m_header.bpp = data[18];
		m_header.base = data[19];
		// Check if valid
		if (m_header.id1 != 0xBF || m_header.id2 != 0xF2)
		{
			LOG.error("BFF2 bitmap font header invalid.");
			return false;
		}
		// Reject unsupported bpp values
		if (m_header.bpp != 8 && m_header.bpp != 24 && m_header.bpp != 32)
		{
			LOG.error("Bitmap font file has unsupported amount of bits per pixel.");
			return false;
		}
		m_rowPitch = m_header.imgWidth / m_header.cellWidth;
		// Read in array with width of each character
		std::memcpy(&m_widths, &data[20], 256);
		// Read in texture
		long long int texDataSize { (std::abs(m_header.imgWidth) * std::abs(m_header.imgHeight)) * (m_header.bpp / 8) };
		const char* img = data + 276;
		if (276 + texDataSize != filesize)
		{
			LOG.error("BFF2 bitmap font corrupt.");
			return false;
		}

		// Create texture
		m_pTexture = Platform::get()->createTexture(ITexture::Type::TEX2D);
		m_pTexture->bind();
		Platform::get()->curTexture()->setMagFilter(ITextureCommands::MagFilter::NEAREST);
		Platform::get()->curTexture()->setMinFilter(ITextureCommands::MinFilter::NEAREST);
		Platform::get()->curTexture()->setWrapMode(ITextureCommands::WrapDirection::S, ITextureCommands::WrapMode::CLAMP_TO_EDGE);
		Platform::get()->curTexture()->setWrapMode(ITextureCommands::WrapDirection::T, ITextureCommands::WrapMode::CLAMP_TO_EDGE);

		// Tex creation params depend on BPP
		switch (m_header.bpp)
		{
		case 8:
			Platform::get()->curTexture()->write(0, m_header.imgWidth, m_header.imgHeight,
					ITextureCommands::PixelFormat::LUMINANCE, ITextureCommands::PixelType::UBYTE, img);
			break;
		case 24:
			Platform::get()->curTexture()->write(0, m_header.imgWidth, m_header.imgHeight,
					ITextureCommands::PixelFormat::RGB, ITextureCommands::PixelType::UBYTE, img);
			break;
		case 32:
			Platform::get()->curTexture()->write(0, m_header.imgWidth, m_header.imgHeight,
					ITextureCommands::PixelFormat::RGBA, ITextureCommands::PixelType::UBYTE, img);
			break;
		default:
			// Should never get here
			LOG.error("BFF2 Bitmap font corrupt.");
			break;
		}
		m_pSprite = new Sprite { m_pTexture };
		m_pSprite->setFlipY(true);

		return true;
	}
}
