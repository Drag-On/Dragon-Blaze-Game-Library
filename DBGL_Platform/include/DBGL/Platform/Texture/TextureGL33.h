//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEXTUREGL33_H_
#define TEXTUREGL33_H_

#include <stdexcept>
#include <GL/glew.h>
#include "ITexture.h"

namespace dbgl
{
    /**
     * @brief OpenGL 3.3 implementation of the texture class
     */
    class TextureGL33 : public ITexture
    {
	public:
	    /**
	     * @brief Constructor
	     * @param type Texture type
	     */
	    TextureGL33(Type type);
	    virtual ~TextureGL33();
	    virtual void bind(unsigned int unit = 0);
	    virtual void write(unsigned int level, unsigned int width, unsigned int height,
		    PixelFormat format, PixelType type, void const* data);
	    virtual void writeCompressed(unsigned int level, unsigned int width, unsigned int height,
		    PixelFormatCompressed format, unsigned int size, void const* data);
	    virtual void setRowAlignment(RowAlignment type, unsigned int align);
	    virtual void setMinFilter(MinFilter filter);
	    virtual void setMagFilter(MagFilter filter);
	    virtual void generateMipMaps();
	    virtual void getSize(unsigned int& width, unsigned int& height, unsigned int level = 0);
	    virtual unsigned int getWidth() const;
	    virtual unsigned int getHeight() const;
	    virtual void getPixelData(PixelFormat format, PixelType type, char* buffer, unsigned int level = 0) const;
	    /**
	     * @return Internal texture handle
	     */
	    GLuint getHandle() const;

	    /**
	     * @brief Converts PixelFormat into OpenGL values
	     * @param format Format to convert
	     * @return OpenGL equivalent of \p format
	     */
	    static GLint pixelFormat2GL(PixelFormat format);
	    /**
	     * @brief Calculates the size of a pixel format
	     * @param format Format to check
	     * @return Amount of components of \p format
	     */
	    static unsigned int pixelFormatSize(PixelFormat format);
	    /**
	     * @brief Converts PixelType into OpenGL values
	     * @param type Type to convert
	     * @return OpenGL equivalent of \p type
	     */
	    static GLenum pixelType2GL(PixelType type);
	    /**
	     * @brief Converts RowAlignment into OpenGL values
	     * @param align Alignment to convert
	     * @return OpenGL equivalent of \p align
	     */
	    static GLenum rowAlignment2GL(RowAlignment align);
	    /**
	     * @brief Converts MinFilter into OpenGL values
	     * @param filter Filter to convert
	     * @return OpenGL equivalent of \p filter
	     */
	    static GLenum minFilter2GL(MinFilter filter);
	    /**
	     * @brief Converts MagFilter into OpenGL values
	     * @param filter Filter to convert
	     * @return OpenGL equivalent of \p filter
	     */
	    static GLenum magFilter2GL(MagFilter filter);
	    /**
	     * @brief Converts PixelFormatCompressed into OpenGL values
	     * @param format Format to convert
	     * @return OpenGL equivalent of \p format
	     */
	    static GLenum compPixelFormat2GL(PixelFormatCompressed format);
	    /**
	     * @brief Checks if a pixel format suppports alpha
	     * @param format Format to check
	     * @return True in case \p format supports alpha values, otherwise false
	     */
	    static bool hasAlpha(PixelFormat format);
	    /**
	     * @brief Converts ITexture::Type into OpenGL values
	     * @param type Texture type to convert
	     * @return OpenGL equivalent of \p type
	     */
	    static GLenum texType2GL(Type type);
	    /**
	     * @brief Converts integers into OpenGL texture unit constants
	     * @param unit Texture unit to convert
	     * @return OpenGL equivalent of \p unit
	     */
	    static GLenum texUnit2GL(unsigned int unit);

	private:
	    GLuint m_id;
	    Type m_type;
	    unsigned int m_width = 0, m_height = 0;
	    unsigned int m_rowAlignmentPack = 4;
	    unsigned int m_rowAlignmentUnpack = 4;

	    static TextureGL33* s_pBoundTex;
    };
}

#endif /* TEXTUREGL33_H_ */
