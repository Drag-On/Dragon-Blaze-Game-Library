//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Scenegraph/SceneNode.h"

namespace dbgl
{
    SceneNode::SceneNode()
    {
	m_pObj = NULL;
    }

    SceneNode::~SceneNode()
    {
	// Remove connection from parent node and release children
	if(m_pParent != NULL)
	    m_pParent->remove(this);
	else // If no parent just release all children
	    clear();
    }

    void SceneNode::add(SceneNode* child)
    {
	m_children.push_back(child);
	child->m_pParent = this;
    }

    bool SceneNode::remove(SceneNode* child)
    {
	std::list<SceneNode*>::iterator it = std::find(m_children.begin(),
		m_children.end(), child);
	// Remove and deallocate child if found
	if (it != m_children.end())
	{
	    (*it)->clear();
	    m_children.erase(it);
	    return true;
	}
	else
	    return false;
    }

    void SceneNode::clear()
    {
	std::list<SceneNode*>::iterator it = m_children.begin();
	for (; it != m_children.end(); ++it)
	{
	    (*it)->clear();
	    delete (*it);
	}
	m_children.clear();
    }

    void SceneNode::traverse(Mat4f transform)
    {
	std::list<SceneNode*>::iterator it = m_children.begin();
	for (; it != m_children.end(); ++it)
	{
	    // Apply new transform
	    Mat4f childTransform = (*it)->m_pObj->getTransform() * transform;
	    (*it)->m_pObj->update(childTransform);
	    (*it)->traverse(childTransform);
	}
    }
}
