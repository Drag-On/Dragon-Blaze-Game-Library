//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RENDERCONTEXTGL33_H_
#define RENDERCONTEXTGL33_H_

#include <stdexcept>
#include <GL/glew.h>
#include "IRenderContext.h"
#include "DBGL/Platform/Mesh/MeshGL33.h"
#include "DBGL/Platform/Texture/TextureGL33.h"

namespace dbgl
{
    class RenderContextGL33 : public IRenderContext
    {
	public:
	    virtual ~RenderContextGL33();
	    virtual void clear(int bitmask);
	    virtual void setDepthTest(DepthTestValue val);
	    virtual DepthTestValue getDepthTest() const;
	    virtual void setAlphaBlend(AlphaBlendValue src, AlphaBlendValue dest);
	    virtual AlphaBlendValue getSrcAlphaBlend() const;
	    virtual AlphaBlendValue getDestAlphaBlend() const;
	    virtual void setFaceCulling(FaceCullingValue val);
	    virtual FaceCullingValue getFaceCulling() const;
	    virtual void setMultisampling(bool msaa);
	    virtual bool getMultisampling() const;
	    virtual std::array<float, 3> getClearColor() const;
	    virtual void setClearColor(std::array<float, 3> color);
	    virtual void bind();
	    virtual bool isBound() const;
	    virtual void viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
	    virtual void readPixels(int x, int y, int width, int height, ITexture::PixelFormat format,
		    ITexture::PixelType type, unsigned int bufsize, char* buf);
	    virtual void drawMesh(IMesh* mesh);

	protected:
	    DepthTestValue m_curDepthTestVal = DepthTestValue::Always;
	    AlphaBlendValue m_curSrcAlphaBlendVal = AlphaBlendValue::Zero;
	    AlphaBlendValue m_curDestAlphaBlendVal = AlphaBlendValue::Zero;
	    FaceCullingValue m_curFaceCullingVal = FaceCullingValue::Off;
	    GLuint m_frameBufferId = 0; // 0 = screen frame buffer
	    GLuint m_depthBufferId = 0; // 0 = screen depth buffer
	    std::array<float, 3> m_clearcolor{{0.0f, 0.0f, 0.0f}};

	    static GLenum alphaBlendValue2GL(AlphaBlendValue val);

	    static GLuint s_curFrameBufferId;
    };
}

#endif /* RENDERCONTEXTGL33_H_ */
