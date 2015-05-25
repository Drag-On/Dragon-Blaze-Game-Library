//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/Scene/Scene.h"

namespace dbgl
{
    Scene::Scene(IRenderer* pRenderer) : m_pRenderer(pRenderer)
    {
    }

    ObjectHierarchy<GameEntity>::Node* Scene::insert(GameEntity const& data)
    {
//        m_pRenderer->addEntity(&data);
        return ObjectHierarchy::insert(data);
    }

    bool Scene::remove(ObjectHierarchy<GameEntity>::Node* node)
    {
//        m_pRenderer->removeEntity(&node->data());
        return ObjectHierarchy::remove(node);
    }

    void Scene::traverse()
    {
        // TODO: Implement properly (Culling...)
        find([this](Node* n)
             {
                 n->data().update();
                 m_pRenderer->addEntity(&n->data());
                 return false;
             }, true);
    }
}