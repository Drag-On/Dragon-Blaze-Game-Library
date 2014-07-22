//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/SceneGraph/SceneGraph.h"

namespace dbgl
{
    SceneGraph::SceneNode::SceneNode(Entity* entity) : m_pEntity(entity)
    {
    }

    Entity* SceneGraph::SceneNode::getEntity() const
    {
	return m_pEntity;
    }

    auto SceneGraph::SceneNode::getChildren() const -> std::set<SceneNode*> const&
    {
	return m_childNodes;
    }

    void SceneGraph::SceneNode::addChild(SceneNode* child)
    {
	m_childNodes.insert(child);
    }

    void SceneGraph::SceneNode::removeChild(SceneNode* child)
    {
	m_childNodes.erase(child);
    }

    SceneGraph::~SceneGraph()
    {
    }

    void SceneGraph::accept(AbstractTreeVisitor& visitor)
    {
	AbstractTree::accept(visitor);
	if (m_pRoot != nullptr)
	    m_pRoot->accept(visitor);
    }

    SceneGraph::SceneNode* SceneGraph::getRoot() const
    {
	return m_pRoot;
    }

    void SceneGraph::setRoot(SceneNode* root)
    {
	m_pRoot = root;
    }

    Entity* SceneGraph::getRootEntity() const
    {
	if (m_pRoot != nullptr)
	    return m_pRoot->getEntity();
	else
	    return nullptr;
    }

}
