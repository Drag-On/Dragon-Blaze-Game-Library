//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Texture/TextureGL33.h"

namespace dbgl
{
    TextureGL33* TextureGL33::s_pBoundTex = nullptr;

    TextureGL33::TextureGL33(Type type) : m_type{type}
    {
	glGenTextures(1, &m_id);
    }

    TextureGL33::~TextureGL33()
    {
	glDeleteTextures(1, &m_id);
    }

    void TextureGL33::bind(unsigned int unit)
    {
	if(s_pBoundTex != this)
	{
	    glActiveTexture(texUnit2GL(unit));
	    glBindTexture(texType2GL(m_type), m_id);
	    s_pBoundTex = this;
	}
    }

    void TextureGL33::write(unsigned int level, unsigned int width, unsigned int height, PixelFormat format,
	    PixelType type, void const* data)
    {
	if(s_pBoundTex != this)
	    throw("Texture not bound!");
	GLint intFormatgl = hasAlpha(format) ? GL_RGBA : GL_RGB;
	GLint formatgl = pixelFormat2GL(format);
	glTexImage2D(texType2GL(m_type), level, intFormatgl, width, height, 0, formatgl, pixelType2GL(type),
		data);
	// Update cached tex size
	GLint temp { 0 };
	glGetTexLevelParameteriv(texType2GL(m_type), 0, GL_TEXTURE_WIDTH, &temp);
	m_width = temp;
	glGetTexLevelParameteriv(texType2GL(m_type), 0, GL_TEXTURE_HEIGHT, &temp);
	m_height = temp;
    }

    void TextureGL33::writeCompressed(unsigned int level, unsigned int width, unsigned int height,
    		    PixelFormatCompressed format, unsigned int size, void const* data)
    {
	if (s_pBoundTex != this)
	    throw("Texture not bound!");
	auto glFormat = compPixelFormat2GL(format);
	glCompressedTexImage2D(texType2GL(m_type), level, glFormat, width, height, 0, size, data);
    }

    void TextureGL33::setRowAlignment(RowAlignment type, unsigned int align)
    {
	glPixelStorei(rowAlignment2GL(type), align);
    }

    void TextureGL33::setMinFilter(MinFilter filter)
    {
	if(s_pBoundTex != this)
	    throw("Texture not bound!");
	glTexParameteri(texType2GL(m_type), GL_TEXTURE_MIN_FILTER, minFilter2GL(filter));
    }

    void TextureGL33::setMagFilter(MagFilter filter)
    {
	if(s_pBoundTex != this)
	    throw("Texture not bound!");
	glTexParameteri(texType2GL(m_type), GL_TEXTURE_MAG_FILTER, magFilter2GL(filter));
    }

    void TextureGL33::generateMipMaps()
    {
	if(s_pBoundTex != this)
	    throw("Texture not bound!");
	glGenerateMipmap(texType2GL(m_type));
    }

    void TextureGL33::getSize(unsigned int& width, unsigned int& height, unsigned int level)
    {
	if(s_pBoundTex != this)
	    throw("Texture not bound!");
	GLint temp{};
	glGetTexLevelParameteriv(texType2GL(m_type), level, GL_TEXTURE_WIDTH, &temp);
	width = temp;
	glGetTexLevelParameteriv(texType2GL(m_type), level, GL_TEXTURE_HEIGHT, &temp);
	height = temp;
    }

    unsigned int TextureGL33::getWidth() const
    {
	return m_width;
    }

    unsigned int TextureGL33::getHeight() const
    {
	return m_height;
    }

    GLint TextureGL33::pixelFormat2GL(PixelFormat format)
    {
	switch(format)
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

    unsigned int TextureGL33::pixelFormatSize(PixelFormat format)
    {
	switch(format)
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

    GLenum TextureGL33::pixelType2GL(PixelType type)
    {
	switch(type)
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

    GLenum TextureGL33::rowAlignment2GL(RowAlignment align)
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

    GLenum TextureGL33::minFilter2GL(MinFilter filter)
    {
	switch(filter)
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

    GLenum TextureGL33::magFilter2GL(MagFilter filter)
    {
	switch(filter)
	{
	    case MagFilter::LINEAR:
		return GL_LINEAR;
	    case MagFilter::NEAREST:
		return GL_NEAREST;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum TextureGL33::compPixelFormat2GL(PixelFormatCompressed format)
    {
	switch(format)
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

    bool TextureGL33::hasAlpha(PixelFormat format)
    {
	return format == PixelFormat::BGRA || format == PixelFormat::RGBA;
    }

    GLenum TextureGL33::texType2GL(Type type)
    {
	switch(type)
	{
	    case Type::TEX2D:
		return GL_TEXTURE_2D;
	    default:
		return GL_INVALID_ENUM;
	}
    }

    GLenum TextureGL33::texUnit2GL(unsigned int unit)
    {
	switch(unit)
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

