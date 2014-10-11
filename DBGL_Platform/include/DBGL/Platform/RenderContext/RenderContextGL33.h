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
	    virtual void readPixels(int x, int y, int width, int height, PixelFormat format, PixelType type,
		    unsigned int bufsize, char* buf);

	protected:
	    DepthTestValue m_curDepthTestVal = DepthTestValue::Always;
	    AlphaBlendValue m_curSrcAlphaBlendVal = AlphaBlendValue::Zero;
	    AlphaBlendValue m_curDestAlphaBlendVal = AlphaBlendValue::Zero;
	    FaceCullingValue m_curFaceCullingVal = FaceCullingValue::Off;
	    GLuint m_frameBufferId = 0; // 0 = screen frame buffer
	    GLuint m_depthBufferId = 0; // 0 = screen depth buffer
	    std::array<float, 3> m_clearcolor{{0.0f, 0.0f, 0.0f}};

	    GLenum alphaBlendValue2GL(AlphaBlendValue val) const;
	    GLint pixelFormat2GL(PixelFormat format) const;
	    unsigned int pixelFormatSize(PixelFormat format) const;
	    GLenum pixelType2GL(PixelType type) const;
	    GLenum rowAlignment2GL(RowAlignment align) const;
	    GLenum minFilter2GL(MinFilter filter) const;
	    GLenum magFilter2GL(MagFilter filter) const;
	    GLenum compPixelFormat2GL(PixelFormatCompressed format) const;

	    static GLuint s_curFrameBufferId;
    };
}

#endif /* RENDERCONTEXTGL33_H_ */
