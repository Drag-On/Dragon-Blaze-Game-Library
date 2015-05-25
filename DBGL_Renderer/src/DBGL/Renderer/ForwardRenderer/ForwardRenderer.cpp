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
#include "DBGL/Renderer/Component/CameraComponent.h"
#include "DBGL/Renderer/Component/RenderComponent.h"
#include "DBGL/Renderer/Component/TransformComponent.h"
#include <algorithm>

namespace dbgl
{
    ForwardRenderer::ForwardRenderer()
    {
        // Timer
        m_pTime = Platform::get()->createTimer();
    }

    ForwardRenderer::~ForwardRenderer()
    {
        delete m_pTime;
    }

    bool ForwardRenderer::addEntity(GameEntity const* entity)
    {
        if (entity->renderComponent()->getMaterial()->isTranslucent())
        {
            if (m_translucentEntityMap.count(entity) <= 0)
            {
                m_translucentEntities.push_back(entity);
                m_translucentEntityMap[entity] = m_translucentEntities.size() - 1;
            }
            else
                return false;
        }
        else
        {
            if (m_entityMap.count(entity) <= 0)
            {
                m_entities.push_back(entity);
                m_entityMap[entity] = m_entities.size() - 1;
            }
            else
                return false;
        }
        return true;
    }

    bool ForwardRenderer::removeEntity(GameEntity const* entity)
    {
        if (entity->renderComponent()->getMaterial()->isTranslucent())
        {
            auto it = std::find(m_translucentEntities.begin(), m_translucentEntities.end(), entity);
            if (it != m_translucentEntities.end())
            {
                m_translucentEntities.erase(it);
                m_translucentEntityMap.erase(entity);
                return true;
            }
        }
        else
        {
            auto it = std::find(m_entities.begin(), m_entities.end(), entity);
            if (it != m_entities.end())
            {
                m_entities.erase(it);
                m_entityMap.erase(entity);
                return true;
            }
        }
        return false;
    }

    void ForwardRenderer::clear()
    {
        m_translucentEntities.clear();
        m_entities.clear();
    }

    void ForwardRenderer::tryOptimize()
    {
        sortNormalEntities();
        sortTranslucentEntities();
    }

    void ForwardRenderer::setCameraEntity(ICamera const* camera)
    {
        m_pCamera = camera;
    }

    void ForwardRenderer::render(IRenderContext* rc)
    {
        // Don't render if there is no camera attached
        if (!m_pCamera)
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
        if (m_curElapsed >= 1.0)
        {
            m_curElapsed -= 1.0;
            m_fps = m_curFrames;
            m_curFrames = 0;
        }

        // Render!
        renderWithoutZPrePass(rc);
    }

    double ForwardRenderer::getDeltaTime() const
    {
        return m_delta;
    }

    unsigned int ForwardRenderer::getFPS() const
    {
        return m_fps;
    }

    void ForwardRenderer::renderWithoutZPrePass(IRenderContext* rc)
    {
        // TODO: Only sort every nth time step
        // Sort the normal entities in front-to-back order, and the translucent entities in back-to-front order
        sortNormalEntities();
        sortTranslucentEntities();

        // Do color pass
        rc->enableColorBuffer(true, true, true, true);
        rc->enableDepthBuffer(true);
        rc->clear(IRenderContext::COLOR | IRenderContext::DEPTH);
        rc->setDepthTest(IRenderContext::DepthTestValue::LessEqual);
        rc->setDrawMode(IRenderContext::DrawMode::Fill);
        for (auto& e : m_entities)
        {
            e->renderComponent()->getMaterial()->setupUnique(*e);
            e->renderComponent()->getMaterial()->setupMaterial();
            rc->drawMesh(e->renderComponent()->getMesh());
        }

        // Render translucent objects in back-to-front order
        for (auto& e : m_translucentEntities)
        {
            e->renderComponent()->getMaterial()->setupUnique(*e);
            e->renderComponent()->getMaterial()->setupMaterial();
            rc->drawMesh(e->renderComponent()->getMesh());
        }
    }

    void ForwardRenderer::sortNormalEntities()
    {
        auto sortFrontBack = [this](GameEntity const* e1, GameEntity const* e2)
        {
            return !this->compareBackFront(e1, e2);
        };
        std::sort(m_entities.begin(), m_entities.end(), sortFrontBack);
        m_entityMap.clear();
        for (unsigned int i = 0; i < m_entities.size(); i++)
            m_entityMap[m_entities[i]] = i;
    }

    void ForwardRenderer::sortTranslucentEntities()
    {
        auto sortBackFront = [this](GameEntity const* e1, GameEntity const* e2)
        {
            return this->compareBackFront(e1, e2);
        };
        std::sort(m_translucentEntities.begin(), m_translucentEntities.end(), sortBackFront);
        m_translucentEntityMap.clear();
        for (unsigned int i = 0; i < m_translucentEntities.size(); i++)
            m_translucentEntityMap[m_translucentEntities[i]] = i;
    }
}

