//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Texture/TextureCommandsGL33.h"

namespace dbgl
{
	TextureGL33* TextureCommandsGL33::s_pCurTexture = nullptr;

	void TextureCommandsGL33::activateUnit(unsigned int unit)
	{
		glActiveTexture(texUnit2GL(unit));
	}

	void TextureCommandsGL33::write(unsigned int level, unsigned int width, unsigned int height, PixelFormat format,
			PixelType type, void const* data)
	{
		GLint intFormatgl = hasAlpha(format) ? GL_RGBA : GL_RGB;
		GLint formatgl = pixelFormat2GL(format);
		glGetError();
		glTexImage2D(texType2GL(s_pCurTexture->getType()), level, intFormatgl, width, height, 0, formatgl,
				pixelType2GL(type), data);
		auto err = glGetError();
		if (err != GL_NO_ERROR)
			throw std::runtime_error { std::string { "glTexImage2D failed: " }
					+ reinterpret_cast<const char*>(glewGetErrorString(err)) };
	}

	void TextureCommandsGL33::writeCompressed(unsigned int level, unsigned int width, unsigned int height,
			PixelFormatCompressed format, unsigned int size, void const* data)
	{
		auto glFormat = compPixelFormat2GL(format);
		glGetError();
		glCompressedTexImage2D(texType2GL(s_pCurTexture->getType()), level, glFormat, width, height, 0, size, data);
		auto err = glGetError();
		if (err != GL_NO_ERROR)
			throw std::runtime_error { std::string { "glCompressedTexImage2D failed: " }
					+ reinterpret_cast<const char*>(glewGetErrorString(err)) };
	}

	void TextureCommandsGL33::setRowAlignment(RowAlignment type, unsigned int align)
	{
		switch (type)
		{
		case RowAlignment::PACK:
			glPixelStorei(rowAlignment2GL(RowAlignment::PACK), align);
			break;
		case RowAlignment::UNPACK:
			glPixelStorei(rowAlignment2GL(RowAlignment::UNPACK), align);
			break;
		}
	}

	void TextureCommandsGL33::setMinFilter(MinFilter filter)
	{
		glTexParameteri(texType2GL(s_pCurTexture->getType()), GL_TEXTURE_MIN_FILTER, minFilter2GL(filter));
	}

	void TextureCommandsGL33::setMagFilter(MagFilter filter)
	{
		glTexParameteri(texType2GL(s_pCurTexture->getType()), GL_TEXTURE_MAG_FILTER, magFilter2GL(filter));
	}

	void TextureCommandsGL33::generateMipMaps()
	{
		glGenerateMipmap(texType2GL(s_pCurTexture->getType()));
	}

	void TextureCommandsGL33::getSize(unsigned int& width, unsigned int& height, unsigned int level)
	{
		GLint temp { };
		glGetTexLevelParameteriv(texType2GL(s_pCurTexture->getType()), level, GL_TEXTURE_WIDTH, &temp);
		width = temp;
		glGetTexLevelParameteriv(texType2GL(s_pCurTexture->getType()), level, GL_TEXTURE_HEIGHT, &temp);
		height = temp;
	}

	unsigned int TextureCommandsGL33::getWidth() const
	{
		GLint temp { 0 };
		glGetTexLevelParameteriv(texType2GL(s_pCurTexture->getType()), 0, GL_TEXTURE_WIDTH, &temp);
		return temp;
	}

	unsigned int TextureCommandsGL33::getHeight() const
	{
		GLint temp { 0 };
		glGetTexLevelParameteriv(texType2GL(s_pCurTexture->getType()), 0, GL_TEXTURE_HEIGHT, &temp);
		return temp;
	}

	void TextureCommandsGL33::getPixelData(PixelFormat format, PixelType type, char* buffer, unsigned int level) const
	{
		glGetError();
		glGetTexImage(texType2GL(s_pCurTexture->getType()), level, pixelFormat2GL(format), pixelType2GL(type), buffer);
		auto err = glGetError();
		if (err != GL_NO_ERROR)
			throw std::runtime_error { std::string { "glGetTexImage failed: " }
					+ reinterpret_cast<const char*>(glewGetErrorString(err)) };
	}

	GLint TextureCommandsGL33::pixelFormat2GL(PixelFormat format)
	{
		switch (format)
		{
		case PixelFormat::BGR:
			return GL_BGR;
		case PixelFormat::BGRA:
			return GL_BGRA;
		case PixelFormat::RGB:
			return GL_RGB;
		case PixelFormat::RGBA:
			return GL_RGBA;
		case PixelFormat::LUMINANCE:
			return GL_LUMINANCE;
		default:
			return -1;
		}
	}

	unsigned int TextureCommandsGL33::pixelFormatSize(PixelFormat format)
	{
		switch (format)
		{
		case PixelFormat::LUMINANCE:
			return 1;
		case PixelFormat::BGR:
		case PixelFormat::RGB:
			return 3;
		case PixelFormat::BGRA:
		case PixelFormat::RGBA:
			return 4;
		default:
			return 0;
		}
	}

	GLenum TextureCommandsGL33::pixelType2GL(PixelType type)
	{
		switch (type)
		{
		case PixelType::BYTE:
			return GL_BYTE;
		case PixelType::FLOAT:
			return GL_FLOAT;
		case PixelType::INT:
			return GL_INT;
		case PixelType::SHORT:
			return GL_SHORT;
		case PixelType::UBYTE:
			return GL_UNSIGNED_BYTE;
		case PixelType::UINT:
			return GL_UNSIGNED_INT;
		case PixelType::USHORT:
			return GL_UNSIGNED_SHORT;
		default:
			return GL_INVALID_ENUM;
		}
	}

	GLenum TextureCommandsGL33::rowAlignment2GL(RowAlignment align)
	{
		switch (align)
		{
		case RowAlignment::PACK:
			return GL_PACK_ALIGNMENT;
		case RowAlignment::UNPACK:
			return GL_UNPACK_ALIGNMENT;
		default:
			return GL_INVALID_ENUM;
		}
	}

	GLenum TextureCommandsGL33::minFilter2GL(MinFilter filter)
	{
		switch (filter)
		{
		case MinFilter::LINEAR:
			return GL_LINEAR;
		case MinFilter::LINEAR_MIPMAP_LINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
		case MinFilter::LINEAR_MIPMAP_NEAREST:
			return GL_LINEAR_MIPMAP_NEAREST;
		case MinFilter::NEAREST:
			return GL_NEAREST;
		case MinFilter::NEAREST_MIPMAP_LINEAR:
			return GL_NEAREST_MIPMAP_LINEAR;
		case MinFilter::NEAREST_MIPMAP_NEAREST:
			return GL_NEAREST_MIPMAP_NEAREST;
		default:
			return GL_INVALID_ENUM;
		}
	}

	GLenum TextureCommandsGL33::magFilter2GL(MagFilter filter)
	{
		switch (filter)
		{
		case MagFilter::LINEAR:
			return GL_LINEAR;
		case MagFilter::NEAREST:
			return GL_NEAREST;
		default:
			return GL_INVALID_ENUM;
		}
	}

	GLenum TextureCommandsGL33::compPixelFormat2GL(PixelFormatCompressed format)
	{
		switch (format)
		{
		case PixelFormatCompressed::COMP_DXT1:
			return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		case PixelFormatCompressed::COMP_DXT3:
			return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		case PixelFormatCompressed::COMP_DXT5:
			return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		default:
			return GL_INVALID_ENUM;
		}
	}

	bool TextureCommandsGL33::hasAlpha(PixelFormat format)
	{
		return format == PixelFormat::BGRA || format == PixelFormat::RGBA;
	}

	GLenum TextureCommandsGL33::texType2GL(ITexture::Type type)
	{
		switch (type)
		{
		case ITexture::Type::TEX2D:
			return GL_TEXTURE_2D;
		default:
			return GL_INVALID_ENUM;
		}
	}

	GLenum TextureCommandsGL33::texUnit2GL(unsigned int unit)
	{
		switch (unit)
		{
		case 0:
			return GL_TEXTURE0;
		case 1:
			return GL_TEXTURE1;
		case 2:
			return GL_TEXTURE2;
		case 3:
			return GL_TEXTURE3;
		case 4:
			return GL_TEXTURE4;
		case 5:
			return GL_TEXTURE5;
		case 6:
			return GL_TEXTURE6;
		case 7:
			return GL_TEXTURE7;
		case 8:
			return GL_TEXTURE8;
		case 9:
			return GL_TEXTURE9;
		case 10:
			return GL_TEXTURE10;
		case 11:
			return GL_TEXTURE11;
		case 12:
			return GL_TEXTURE12;
		case 13:
			return GL_TEXTURE13;
		case 14:
			return GL_TEXTURE14;
		case 15:
			return GL_TEXTURE15;
		case 16:
			return GL_TEXTURE16;
		case 17:
			return GL_TEXTURE17;
		case 18:
			return GL_TEXTURE18;
		case 19:
			return GL_TEXTURE19;
		case 20:
			return GL_TEXTURE20;
		case 21:
			return GL_TEXTURE21;
		case 22:
			return GL_TEXTURE22;
		case 23:
			return GL_TEXTURE23;
		case 24:
			return GL_TEXTURE24;
		case 25:
			return GL_TEXTURE25;
		case 26:
			return GL_TEXTURE26;
		case 27:
			return GL_TEXTURE27;
		case 28:
			return GL_TEXTURE28;
		case 29:
			return GL_TEXTURE29;
		case 30:
			return GL_TEXTURE30;
		case 31:
			return GL_TEXTURE31;
		default:
			return GL_INVALID_ENUM;
		}
	}
}
