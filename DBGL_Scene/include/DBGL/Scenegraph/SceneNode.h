//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SCENENODE_H_
#define SCENENODE_H_

#include <stddef.h>
#include <list>
#include <algorithm>
#include "SceneNodeObject.h"
#include "DBGL/Math/Matrix4x4.h"

namespace dbgl
{
    /**
     * @brief Basic element of the scene graph.
     */
    class SceneNode
    {
	public:
	    /**
	     * @brief Constructor
	     */
	    SceneNode();
	    /**
	     * @brief Destructor
	     * @detail Deallocates this node and all of its children and removes them
	     * 	       from the graph hierarchy
	     */
	    virtual ~SceneNode();
	    /**
	     * @brief Adds a new child to this node
	     * @param child Node to add
	     */
	    void add(SceneNode* child);
	    /**
	     * @brief Removes a child from this node
	     * @param child Node to remove
	     * @return True in case the requested child was removed, otherwise false
	     * @detail Removes the requested child from this node and deallocates it
	     * 	       (and its children)
	     */
	    bool remove(SceneNode* child);
	    /**
	     * @brief Removes all children from this node
	     * @detail Removes all children and deallocates them (and their children)
	     */
	    void clear();
	    /**
	     * @brief Traverses the scene graph and updates all children
	     * @param transform Accumulated transform of parents. Defaults to unit matrix
	     */
	    void traverse(Mat4f transform = Mat4f());
	private:
	    SceneNode* m_pParent = NULL;
	    std::list<SceneNode*> m_children;
	    SceneNodeObject* m_pObj;
    };
}

#endif /* SCENENODE_H_ */
