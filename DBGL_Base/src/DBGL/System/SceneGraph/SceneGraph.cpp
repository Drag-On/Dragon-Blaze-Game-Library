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
    SceneGraph::Node::Node(Entity* entity) : m_pEntity(entity)
    {
    }

    Entity* SceneGraph::Node::getEntity() const
    {
	return m_pEntity;
    }

    auto SceneGraph::Node::getChildren() const -> std::set<Node*> const&
    {
	return m_childNodes;
    }

    void SceneGraph::Node::addChild(Node* child)
    {
	m_childNodes.insert(child);
    }

    void SceneGraph::Node::removeChild(Node* child)
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

    SceneGraph::Node* SceneGraph::getRoot() const
    {
	return m_pRoot;
    }

    void SceneGraph::setRoot(Node* root)
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
