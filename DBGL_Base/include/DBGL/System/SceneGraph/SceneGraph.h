//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SCENEGRAPH_H_
#define SCENEGRAPH_H_

#include <set>
#include "DBGL/System/Entity/Entity.h"
#include "DBGL/System/Tree/AbstractTree.h"

namespace dbgl
{
    class SceneGraph : public AbstractTree
    {
	public:
	    /**
	     * @brief A node within a scene graph.
	     */
	    class SceneNode: public AbstractTree::Node
	    {
		public:
		    /**
		     * @brief Constructor
		     * @param entity Entity to hold
		     */
		    SceneNode(Entity* entity);
		    /**
		     * @brief Provides read access to the entity
		     * @return The entity of this node
		     */
		    Entity* getEntity() const;
		    /**
		     * @brief Provides access to this node's children
		     * @return The node's children
		     */
		    std::set<SceneNode*> const& getChildren() const;
		    /**
		     * @brief Adds a new child node
		     * @param child New child
		     */
		    void addChild(SceneNode* child);
		    /**
		     * @brief Removes a child node
		     * @param child Node to remove
		     */
		    void removeChild(SceneNode* child);
		    /**
		     * @brief Accepts a visitor
		     * @param visitor Visitor to accept
		     */
		    template<class Visitor> void accept(Visitor& visitor)
		    {
			AbstractTree::Node::accept<Visitor, SceneNode*>(visitor);
		    }
		private:
		    Entity* m_pEntity;
		    std::set<SceneNode*> m_childNodes;
	    };

	    /**
	     * @brief Destructor
	     */
	    ~SceneGraph();
	    /**
	     * @brief Accept a visitor
	     * @param visitor Visitor to accept
	     */
	    virtual void accept(AbstractTreeVisitor& visitor);
	    /**
	     * @brief Accept a visitor
	     * @param visitor Visitor to accept
	     */
	    template<class Visitor> void accept(Visitor& visitor);
	    /**
	     * @brief Provides access to the root node
	     * @return The root node or nullptr if scene graph is empty
	     */
	    SceneNode* getRoot() const;
	    /**
	     * @brief Provides access to the root entity
	     * @return The entity held by the root node or nullptr if scene graph is empty
	     */
	    Entity* getRootEntity() const;
	private:
	    SceneNode* m_pRoot = nullptr;
    };
}

#include "SceneGraph.imp"

#endif /* SCENEGRAPH_H_ */
