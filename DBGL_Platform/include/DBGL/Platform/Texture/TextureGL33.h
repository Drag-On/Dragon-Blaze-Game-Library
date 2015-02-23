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
	    /**
	     * @brief Copy constructor
	     * @param copy Texture to copy
	     */
	    TextureGL33(TextureGL33 const& copy);
	    /**
	     * @brief Copy-assignment operator
	     * @param copy Texture to copy
	     * @return This texture
	     */
	    TextureGL33& operator=(TextureGL33 const& copy);
	    virtual ~TextureGL33();
	    virtual void bind() const;
	    virtual Type getType() const;
	    virtual ITexture* clone() const;

	    /**
	     * @return Internal texture handle
	     */
	    GLuint getHandle() const;

	private:
	    GLuint m_id;
	    Type m_type;
    };
}

#endif /* TEXTUREGL33_H_ */
