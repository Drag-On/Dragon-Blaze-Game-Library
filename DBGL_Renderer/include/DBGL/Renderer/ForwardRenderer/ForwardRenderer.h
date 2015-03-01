//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_FORWARDRENDERER_FORWARDRENDERER_H_
#define INCLUDE_DBGL_RENDERER_FORWARDRENDERER_FORWARDRENDERER_H_

#include <vector>
#include <functional>
#include "DBGL/Renderer/IRenderer.h"
#include "DBGL/Platform/Shader/IShaderProgram.h"
#include "DBGL/Platform/Platform.h"

namespace dbgl
{
	/**
	 * @brief Implements a forward renderer
	 */
	class ForwardRenderer: public IRenderer
	{
	public:
		/**
		 * @brief Constructor
		 * @param useZPrePass Specifies if the renderer should use a depth pre-pass
		 */
		ForwardRenderer(bool useZPrePass = false);
		/**
		 * @brief Destructor
		 */
		virtual ~ForwardRenderer();
		virtual bool addEntity(IRenderEntity* entity);
		virtual bool removeEntity(IRenderEntity* entity);
		virtual void setCameraEntity(ICameraEntity* camera);
		virtual void render(IRenderContext* rc);
		virtual double getDeltaTime() const;
		virtual unsigned int getFPS() const;
		void setUseZPrePass(bool use);
		bool getUseZPrePass() const;
	private:
		void renderWithZPrePass(IRenderContext* rc);
		void renderWithoutZPrePass(IRenderContext* rc);

		std::vector<IRenderEntity*> m_translucentEntities; // TODO: Use more appropriate data structure
		std::vector<IRenderEntity*> m_entities;
		ICameraEntity* m_pCamera = nullptr;
		IShaderProgram* m_pZPrePassShader;
		IShaderProgram::UniformHandle m_prePassMVPHandle;
		bool m_useZPrePass = false;
		std::function<void(IRenderContext*)> m_renderFunction;
		double m_delta = 1;
		unsigned int m_fps = 0;
		double m_curElapsed = 0;
		unsigned int m_curFrames = 0;
		ITimer* m_pTime = nullptr;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_FORWARDRENDERER_FORWARDRENDERER_H_ */
