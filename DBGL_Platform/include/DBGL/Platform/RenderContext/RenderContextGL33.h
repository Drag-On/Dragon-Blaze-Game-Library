//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
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
	/**
	 * @brief Common functionality for render contexts using OpenGL 3.3
	 */
	class RenderContextGL33: public IRenderContext
	{
	public:
		/**
		 * @brief Destructor
		 */
		virtual ~RenderContextGL33();
		/**
		 * @copydoc IRenderContext::clear()
		 */
		virtual void clear(int bitmask);
		/**
		 * @copydoc IRenderContext::setDepthTest()
		 */
		virtual void setDepthTest(DepthTestValue val);
		/**
		 * @copydoc IRenderContext::getDepthTest()
		 */
		virtual DepthTestValue getDepthTest() const;
		/**
		 * @copydoc IRenderContext::setAlphaBlend()
		 */
		virtual void setAlphaBlend(AlphaBlendValue src, AlphaBlendValue dest);
		/**
		 * @copydoc IRenderContext::getSrcAlphaBlend()
		 */
		virtual AlphaBlendValue getSrcAlphaBlend() const;
		/**
		 * @copydoc IRenderContext::getDestAlphaBlend()
		 */
		virtual AlphaBlendValue getDestAlphaBlend() const;
		/**
		 * @copydoc IRenderContext::setFaceCulling()
		 */
		virtual void setFaceCulling(FaceCullingValue val);
		/**
		 * @copydoc IRenderContext::getFaceCulling()
		 */
		virtual FaceCullingValue getFaceCulling() const;
		/**
		 * @copydoc IRenderContext::setDrawMode()
		 */
		virtual void setDrawMode(DrawMode mode);
		/**
		 * @copydoc IRenderContext::getDrawMode()
		 */
		virtual DrawMode getDrawMode() const;
		/**
		 * @copydoc IRenderContext::setLineWidth()
		 */
		virtual void setLineWidth(float width);
		/**
		 * @copydoc IRenderContext::getLineWidth()
		 */
		virtual float getLineWidth() const;
		/**
		 * @copydoc IRenderContext::setLineAntialiasing()
		 */
		virtual void setLineAntialiasing(bool smooth);
		/**
		 * @copydoc IRenderContext::getLineAntialiasing()
		 */
		virtual bool getLineAntialiasing() const;
		/**
		 * @copydoc IRenderContext::setPointSize()
		 */
		virtual void setPointSize(float size);
		/**
		 * @copydoc IRenderContext::getPointSize()
		 */
		virtual float getPointSize() const;
		/**
		 * @copydoc IRenderContext::enableDepthBuffer()
		 */
		virtual void enableDepthBuffer(bool enable);
		/**
		 * @copydoc IRenderContext::isDepthBufferEnabled()
		 */
		virtual bool isDepthBufferEnabled() const;
		/**
		 * @copydoc IRenderContext::enableColorBuffer()
		 */
		virtual void enableColorBuffer(bool red, bool green, bool blue, bool alpha);
		/**
		 * @copydoc IRenderContext::isColorBufferEnabled()
		 */
		virtual std::array<bool, 4> isColorBufferEnabled() const;
		/**
		 * @copydoc IRenderContext::setMultisampling()
		 */
		virtual void setMultisampling(bool msaa);
		/**
		 * @copydoc IRenderContext::getMultisampling()
		 */
		virtual bool getMultisampling() const;
		/**
		 * @copydoc IRenderContext::getClearColor()
		 */
		virtual std::array<float, 3> getClearColor() const;
		/**
		 * @copydoc IRenderContext::setClearColor()
		 */
		virtual void setClearColor(std::array<float, 3> color);
		/**
		 * @copydoc IRenderContext::bind()
		 */
		virtual void bind();
		/**
		 * @copydoc IRenderContext::isBound()
		 */
		virtual bool isBound() const;
		/**
		 * @copydoc IRenderContext::viewport()
		 */
		virtual void viewport(unsigned int x, unsigned int y,
				unsigned int width, unsigned int height);
		/**
		 * @copydoc IRenderContext::readPixels()
		 */
		virtual void readPixels(int x, int y, int width, int height,
				ITextureCommands::PixelFormat format, ITextureCommands::PixelType type,
				unsigned int bufsize, char* buf);
		/**
		 * @copydoc IRenderContext::drawMesh()
		 */
		virtual void drawMesh(IMesh* mesh);

		/**
		 * Converts AlphaBlendValue into OpenGL enums
		 * @param val Value to convert
		 * @return The OpenGL equivalent of \p val
		 */
		static GLenum alphaBlendValue2GL(AlphaBlendValue val);

	protected:
		/**
		 * @brief Current depth test value
		 */
		DepthTestValue m_curDepthTestVal = DepthTestValue::Always;
		/**
		 * @brief Current source alpha blend value
		 */
		AlphaBlendValue m_curSrcAlphaBlendVal = AlphaBlendValue::Zero;
		/**
		 * @brief Current destination alpha blend value
		 */
		AlphaBlendValue m_curDestAlphaBlendVal = AlphaBlendValue::Zero;
		/**
		 * @brief Current face culling value
		 */
		FaceCullingValue m_curFaceCullingVal = FaceCullingValue::Off;
		/**
		 * @brief Internal frame buffer handle
		 */
		GLuint m_frameBufferId = 0; // 0 = screen frame buffer
		/**
		 * @brief Internal depth buffer handle
		 */
		GLuint m_depthBufferId = 0; // 0 = screen depth buffer
		/**
		 * @brief Current clear color
		 */
		std::array<float, 3> m_clearcolor { { 0.0f, 0.0f, 0.0f } };
		/**
		 * @brief Caches if multisampling is enabled
		 */
		bool m_msaaEnabled = false;

		/**
		 * @brief Currently bound frame buffer
		 */
		static GLuint s_curFrameBufferId;
	};
}

#endif /* RENDERCONTEXTGL33_H_ */
