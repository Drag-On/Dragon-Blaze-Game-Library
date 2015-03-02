//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Platform.h"
#include "DBGL/Renderer/ForwardRenderer/ForwardRenderer.h"
#include <algorithm>

namespace dbgl
{
	ForwardRenderer::ForwardRenderer(bool useZPrePass)
	{
		// Initialize shader for z-pre-pass
		m_pZPrePassShader = Platform::get()->createShaderProgram();
		std::string codeVertex = R"code(#version 330 core
			layout(location = 0) in vec3 i_v3_Pos_m; // Vertex position in model space
			uniform mat4 MVP;						 // Model-view-projection matrix
			void main()
			{
				gl_Position = MVP * vec4(i_v3_Pos_m, 1); // Vertex position in clip space
			})code";
		auto vertex = Platform::get()->createShader(IShader::Type::VERTEX, codeVertex);
		vertex->compile();
		std::string codeFragment = R"code(#version 330 core
//            out vec3 color;
			void main()
			{
//                color = vec3(1, 0, 0);
			})code";
		auto fragment = Platform::get()->createShader(IShader::Type::FRAGMENT, codeFragment);
		fragment->compile();
		m_pZPrePassShader->attach(vertex);
		m_pZPrePassShader->attach(fragment);
		m_pZPrePassShader->link();
		delete vertex;
		delete fragment;
		m_prePassMVPHandle = m_pZPrePassShader->getUniformHandle("MVP");

		// Timer
		m_pTime = Platform::get()->createTimer();

		// Default render function
		if (useZPrePass)
			m_renderFunction = std::bind(&ForwardRenderer::renderWithZPrePass, this, std::placeholders::_1);
		else
			m_renderFunction = std::bind(&ForwardRenderer::renderWithoutZPrePass, this, std::placeholders::_1);
	}

	ForwardRenderer::~ForwardRenderer()
	{
		delete m_pZPrePassShader;
		delete m_pTime;
	}

	bool ForwardRenderer::addEntity(IRenderEntity* entity)
	{
		if (entity->isTranslucent())
			m_translucentEntities.push_back(entity);
		else
			m_entities.push_back(entity);
		return true;
	}

	bool ForwardRenderer::removeEntity(IRenderEntity* entity)
	{
		if (entity->isTranslucent())
		{
			auto it = std::find(m_translucentEntities.begin(), m_translucentEntities.end(), entity);
			if (it != m_translucentEntities.end())
			{
				m_translucentEntities.erase(it);
				return true;
			}
		}
		else
		{
			auto it = std::find(m_entities.begin(), m_entities.end(), entity);
			if (it != m_entities.end())
			{
				m_entities.erase(it);
				return true;
			}
		}
		return false;
	}

	void ForwardRenderer::setCameraEntity(ICameraEntity* camera)
	{
		m_pCamera = camera;
		if (m_pCamera)
			m_frustumCulling.setCamera(m_pCamera);
	}

	void ForwardRenderer::render(IRenderContext* rc)
	{
		// Don't render if there is no camera attached
		if(!m_pCamera)
		{
			m_curFrames = 0;
			m_curElapsed = 0;
			m_delta = 0;
			m_fps = 0;
			return;
		}

		// Timing
		m_delta = m_pTime->getDelta();
		m_curElapsed += m_delta;
		m_curFrames++;
		if(m_curElapsed >= 1.0)
		{
			m_curElapsed -= 1.0;
			m_fps = m_curFrames;
			m_curFrames = 0;
		}

		// Render!
		m_renderFunction(rc);
	}

	double ForwardRenderer::getDeltaTime() const
	{
		return m_delta;
	}

	unsigned int ForwardRenderer::getFPS() const
	{
		return m_fps;
	}

	void ForwardRenderer::setUseZPrePass(bool use)
	{
		m_useZPrePass = use;
		if(use)
			m_renderFunction = std::bind(&ForwardRenderer::renderWithZPrePass, this, std::placeholders::_1);
		else
			m_renderFunction = std::bind(&ForwardRenderer::renderWithoutZPrePass, this, std::placeholders::_1);
	}

	bool ForwardRenderer::getUseZPrePass() const
	{
		return m_useZPrePass;
	}

	void ForwardRenderer::renderWithZPrePass(IRenderContext* rc)
	{
		cullAll();
		Mat4f VP = m_pCamera->getProjectionMatrix() * m_pCamera->getViewMatrix();

		// Do Z Pre-Pass
		rc->enableColorBuffer(false, false, false, false);
		rc->enableDepthBuffer(true);
		rc->clear(IRenderContext::DEPTH);
		rc->setDepthTest(IRenderContext::DepthTestValue::Less);
		rc->setDrawMode(IRenderContext::DrawMode::Fill);
		m_pZPrePassShader->use();
		for(auto& e : m_entitiesCulled) // TODO: front-to-back order
		{
			Mat4f MVP = VP * e->getModelMatrix();
			Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(m_prePassMVPHandle, 1, false,
					MVP.getDataPointer());
			rc->drawMesh(e->getMesh());
		}

		// Do color pass
		rc->enableColorBuffer(true, true, true, true);
		rc->enableDepthBuffer(false);
		rc->clear(IRenderContext::COLOR);
		rc->setDepthTest(IRenderContext::DepthTestValue::LessEqual);
		rc->setDrawMode(IRenderContext::DrawMode::Fill);
		for(auto& e : m_entitiesCulled) // TODO: ordered by material
		{
			e->setupUnique();
			e->setupMaterial();
			rc->drawMesh(e->getMesh());
		}

		// Render translucent objects in back-to-front order
		rc->enableDepthBuffer(true);
		for(auto& e : m_translucentEntitiesCulled) // TODO: order
		{
			e->setupUnique();
			e->setupMaterial();
			rc->drawMesh(e->getMesh());
		}
	}

	void ForwardRenderer::renderWithoutZPrePass(IRenderContext* rc)
	{
		cullAll();
		// Do color pass
		rc->enableColorBuffer(true, true, true, true);
		rc->enableDepthBuffer(true);
		rc->clear(IRenderContext::COLOR | IRenderContext::DEPTH);
		rc->setDepthTest(IRenderContext::DepthTestValue::LessEqual);
		rc->setDrawMode(IRenderContext::DrawMode::Fill);
		for(auto& e : m_entitiesCulled) // TODO: ordered front-to-back
		{
			e->setupUnique();
			e->setupMaterial();
			rc->drawMesh(e->getMesh());
		}

		// Render translucent objects in back-to-front order
		for(auto& e : m_translucentEntitiesCulled) // TODO: order
		{
			e->setupUnique();
			e->setupMaterial();
			rc->drawMesh(e->getMesh());
		}
	}

	void ForwardRenderer::cullAll()
	{
		// Clear old culling
		m_entitiesCulled.clear();
		m_translucentEntitiesCulled.clear();
		m_frustumCulling.update();

		// Iterate over all entities to determine the potentially visible ones
		// TODO: Object hierarchy for early pruning
		for(auto& e : m_entities)
		{
			// Frustum culling
			Vec4f const& center = e->getModelMatrix()[3];
			Vec3f c{center[0], center[1], center[2]};
			float radius = e->getBoundingSphere();
			if(m_frustumCulling.checkSphere(c, radius))
				m_entitiesCulled.push_back(&*e);
		}
		for(auto& e : m_translucentEntities)
		{
			// Frustum culling
			Vec4f const& center = e->getModelMatrix()[3];
			Vec3f c{center[0], center[1], center[2]};
			float radius = e->getBoundingSphere();
			if(m_frustumCulling.checkSphere(c, radius))
				m_translucentEntitiesCulled.push_back(&*e);
		}
	}
}

