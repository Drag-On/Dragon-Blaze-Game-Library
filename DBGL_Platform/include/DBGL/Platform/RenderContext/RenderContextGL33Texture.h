//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RENDERCONTEXTGL33TEXTURE_H_
#define RENDERCONTEXTGL33TEXTURE_H_

#include "RenderContextGL33.h"

namespace dbgl
{
    class RenderContextGL33Texture: public RenderContextGL33
    {
	public:
	    /**
	     * @brief Creates a new render context using a texture as output
	     * @param tex Texture to render to
	     * @param createDepthBuf Indicates if a depth buffer should be created
	     */
	    RenderContextGL33Texture(ITexture* tex, bool createDepthBuf = false);
	    virtual ~RenderContextGL33Texture();
	    virtual int getWidth();
	    virtual int getHeight();

	private:
	    TextureGL33* m_pTex = nullptr;
    };
}

#endif /* RENDERCONTEXTGL33TEXTURE_H_ */
