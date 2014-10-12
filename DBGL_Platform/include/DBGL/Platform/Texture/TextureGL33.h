//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEXTUREGL33_H_
#define TEXTUREGL33_H_

#include <GL/glew.h>
#include "ITexture.h"

namespace dbgl
{
    class TextureGL33 : public ITexture
    {
	public:
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

	private:
	    GLuint m_id;
	    Type m_type;
	    unsigned int m_width = 0, m_height = 0;

	    static TextureGL33* s_pBoundTex;

	    static GLint pixelFormat2GL(PixelFormat format);
	    static unsigned int pixelFormatSize(PixelFormat format);
	    static GLenum pixelType2GL(PixelType type);
	    static GLenum rowAlignment2GL(RowAlignment align);
	    static GLenum minFilter2GL(MinFilter filter);
	    static GLenum magFilter2GL(MagFilter filter);
	    static GLenum compPixelFormat2GL(PixelFormatCompressed format);
	    static bool hasAlpha(PixelFormat format);
	    static GLenum texType2GL(Type type);
	    static GLenum texUnit2GL(unsigned unit);

	    friend class RenderContextGL33;
    };
}

#endif /* TEXTUREGL33_H_ */
