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
	    virtual void bind();
	    virtual bool isBound() const;

	protected:
	    DepthTestValue m_curDepthTestVal = DepthTestValue::Always;
	    AlphaBlendValue m_curSrcAlphaBlendVal = AlphaBlendValue::Zero;
	    AlphaBlendValue m_curDestAlphaBlendVal = AlphaBlendValue::Zero;
	    FaceCullingValue m_curFaceCullingVal = FaceCullingValue::Off;
	    GLuint m_frameBufferId = 0; // 0 = screen frame buffer
	    GLuint m_depthBufferId = 0; // 0 = screen depth buffer

	    GLenum translateAlphaBlendValue(AlphaBlendValue val) const;

	    static GLuint s_curFrameBufferId;
    };
}

#endif /* RENDERCONTEXTGL33_H_ */
