//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/ForwardRenderer/ForwardRendererZPrePass.h"
#include "DBGL/Renderer/Component/CameraComponent.h"
#include "DBGL/Renderer/Component/RenderComponent.h"
#include "DBGL/Renderer/Component/TransformComponent.h"

namespace dbgl
{
    ForwardRendererZPrePass::ForwardRendererZPrePass()
    {
        // Initialize shader for z-pre-pass
        m_pZPrePassShader = Platform::get()->createShaderProgram();
        std::string codeVertex =
                R"code(#version 330 core
            layout(location = 0) in vec3 i_v3_Pos_m; // Vertex position in model space
            uniform mat4 MVP;						 // Model-view-projection matrix
            void main()
            {
                gl_Position = MVP * vec4(i_v3_Pos_m, 1); // Vertex position in clip space
            })code";
        auto vertex = Platform::get()->createShader(IShader::Type::VERTEX, codeVertex);
        vertex->compile();
        std::string codeFragment =
                R"code(#version 330 core
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
    }

    ForwardRendererZPrePass::~ForwardRendererZPrePass()
    {
        delete m_pZPrePassShader;
    }

    void ForwardRendererZPrePass::render(IRenderContext* rc)
    {
        // TODO: Timer etc.
//        ForwardRenderer::render(rc);
        renderWithZPrePass(rc);
    }

    void ForwardRendererZPrePass::renderWithZPrePass(IRenderContext* rc)
    {
        if (m_entities.size() > 0)
        {
            // Sort the culled entities in front-to-back order, and the translucent entities in back-to-front order
            auto sortFrontBack = [this](GameEntity const* e1, GameEntity const* e2)
            {
                return !this->compareBackFront(e1, e2);
            };
            auto sortBackFront = [this](GameEntity const* e1, GameEntity const* e2)
            {
                return this->compareBackFront(e1, e2);
            };
            std::sort(m_entities.begin(), m_entities.end(), sortFrontBack);
            std::sort(m_translucentEntities.begin(), m_translucentEntities.end(), sortBackFront);

            Mat4f VP = m_pCamera->getProjectionMatrix() * m_pCamera->getViewMatrix();

            // Do Z Pre-Pass
            rc->enableColorBuffer(false, false, false, false);
            rc->enableDepthBuffer(true);
            rc->clear(IRenderContext::DEPTH);
            rc->setDepthTest(IRenderContext::DepthTestValue::Less);
            rc->setDrawMode(IRenderContext::DrawMode::Fill);
            m_pZPrePassShader->use();
            for (auto& e : m_entities)
            {
                Mat4f MVP = VP * e->transformComponent()->modelMat();
                Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(m_prePassMVPHandle, 1, false,
                                                                                 MVP.getDataPointer());
                rc->drawMesh(e->renderComponent()->getMesh());
            }

            // Sort by material
            auto sortMaterial = [this](GameEntity const* e1, GameEntity const* e2)
            {
                return e1->renderComponent()->getMaterial()->getMaterialId() <
                       e2->renderComponent()->getMaterial()->getMaterialId();
            };
            std::sort(m_entities.begin(), m_entities.end(), sortMaterial);

            // Do color pass
            rc->enableColorBuffer(true, true, true, true);
            rc->enableDepthBuffer(false);
            rc->clear(IRenderContext::COLOR);
            rc->setDepthTest(IRenderContext::DepthTestValue::LessEqual);
            rc->setDrawMode(IRenderContext::DrawMode::Fill);
            int curMatId = (*m_entities.begin())->renderComponent()->getMaterial()->getMaterialId();
            (*m_entities.begin())->renderComponent()->getMaterial()->setupMaterial();
            for (auto& e : m_entities)
            {
                if (curMatId != e->renderComponent()->getMaterial()->getMaterialId())
                {
                    e->renderComponent()->getMaterial()->setupMaterial();
                    curMatId = e->renderComponent()->getMaterial()->getMaterialId();
                }
                e->renderComponent()->getMaterial()->setupUnique(*e);
                rc->drawMesh(e->renderComponent()->getMesh());
            }
        }

        if (m_translucentEntities.size() > 0)
        {
            // Render translucent objects in back-to-front order
            rc->enableDepthBuffer(true);
            for (auto& e : m_translucentEntities)
            {
                e->renderComponent()->getMaterial()->setupUnique(*e);
                e->renderComponent()->getMaterial()->setupMaterial();
                rc->drawMesh(e->renderComponent()->getMesh());
            }
        }
    }
}