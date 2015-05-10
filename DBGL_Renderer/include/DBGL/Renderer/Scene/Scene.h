//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_SCENE_SCENE_H_
#define INCLUDE_DBGL_RENDERER_SCENE_SCENE_H_

#include "DBGL/Core/Collection/Tree/ObjectHierarchy.h"
#include "DBGL/Core/Shape/Shapes.h"
#include "DBGL/Renderer/Culling/FrustumCulling.h"
#include "DBGL/Renderer/Entity/GameEntity.h"
#include "DBGL/Renderer/IRenderer.h"

namespace dbgl
{
    class Scene : public ObjectHierarchy<GameEntity>
    {
    public:
        /**
         * @brief Specify the renderer to use for rendering
         * @param pRenderer Pointer to renderer to use
         */
        Scene(IRenderer* pRenderer);
        /**
         * @brief Destructor
         */
        virtual ~Scene() = default;
        /**
         * @copydoc ObjectHierarchy<GameEntity>::insert()
         */
        virtual Node* insert(GameEntity const& data);
        /**
         * @copydoc ObjectHierarchy<GameEntity>::remove()
         */
        virtual bool remove(Node* node);
        /**
         * @brief Traverses the scene graph, updates entities and renders them
         */
        void traverse();
    private:
        IRenderer* m_pRenderer;
    };
}

#endif /* INCLUDE_DBGL_RENDERER_SCENE_SCENE_H_ */
