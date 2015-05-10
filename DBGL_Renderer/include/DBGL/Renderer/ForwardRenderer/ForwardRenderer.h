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
#include <unordered_map>
#include <functional>
#include "DBGL/Renderer/IRenderer.h"
#include "DBGL/Renderer/Culling/ICamera.h"
#include "DBGL/Platform/Shader/IShaderProgram.h"
#include "DBGL/Platform/Platform.h"

namespace dbgl
{
    /**
     * @brief Implements a forward renderer
     */
    class ForwardRenderer : public IRenderer
    {
    public:
        /**
         * @brief Constructor
         */
        ForwardRenderer();
        /**
         * @brief Destructor
         */
        virtual ~ForwardRenderer();
        virtual bool addEntity(GameEntity const* entity);
        virtual bool removeEntity(GameEntity const* entity);
        virtual void clear();
        virtual void setCameraEntity(ICamera const* camera);
        virtual void render(IRenderContext* rc);
        virtual double getDeltaTime() const;
        virtual unsigned int getFPS() const;
    protected:
        void renderWithoutZPrePass(IRenderContext* rc);
        inline bool compareBackFront(GameEntity const* e1, GameEntity const* e2) const;

        std::vector<GameEntity const*> m_translucentEntities;
        std::vector<GameEntity const*> m_entities;
        std::unordered_map<GameEntity const*, unsigned int> m_translucentEntityMap;
        std::unordered_map<GameEntity const*, unsigned int> m_entityMap;
        ICamera const* m_pCamera = nullptr;
        double m_delta = 1;
        unsigned int m_fps = 0;
        double m_curElapsed = 0;
        unsigned int m_curFrames = 0;
        ITimer* m_pTime = nullptr;
    };
}

#endif /* INCLUDE_DBGL_RENDERER_FORWARDRENDERER_FORWARDRENDERER_H_ */
