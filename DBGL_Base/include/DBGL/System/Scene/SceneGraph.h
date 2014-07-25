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
#include "DBGL/System/Tree/AbstractTree.h"

namespace dbgl
{
    /**
     * @brief A scene graph which can be used to structure entities.
     * @note The scene graph will hold pointers to the passed entities, yet it does not manage their memory.
     * 	     All entities will be wrapped in a node object which contains information about the tree structure,
     * 	     and which can be used to modify the tree. Those wrapper objects will be freed by the scene graph on
     * 	     destruction or when an entity gets removed from the tree. The held entities will be left untouched.
     */
    template<typename T> class SceneGraph : public AbstractTree
    {
	public:
	    /**
	     * @brief A node within a scene graph.
	     */
	    class Node: public AbstractTree::Node
	    {
		public:
		    /**
		     * @brief Constructor
		     * @param entity Entity to hold
		     */
		    Node(T* entity);
		    /**
		     * @brief Destructor
		     */
		    ~Node();
		    /**
		     * @brief Provides read access to the entity
		     * @return The entity of this node
		     */
		    T* getEntity() const;
		    /**
		     * @brief Provides access to this node's children
		     * @return The node's children
		     */
		    std::set<Node*> const& getChildren() const;
		    /**
		     * @brief Adds a new child node
		     * @param child New child
		     * @returns The node wrapping the new child
		     */
		    Node* addChild(T* child);
		    /**
		     * @brief Removes a child node
		     * @param child Node to remove
		     */
		    void removeChild(T* child);
		    /**
		     * @brief Provides access to this node's parent
		     * @return The parent node of this node or nullptr if none
		     */
		    Node* getParent() const;
		    /**
		     * @brief Replaces the current parent node with a new one
		     * @param parent Node to attach this node to
		     */
		    void setParent(Node* parent);
		    /**
		     * @brief Accepts a visitor
		     * @param visitor Visitor to accept
		     */
		    template<class Visitor> void accept(Visitor& visitor);
		private:
		    T* m_pEntity;
		    Node* m_pParent = nullptr;
		    std::set<Node*> m_childNodes;
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
	     * @brief Provides access to the top-level nodes
	     * @return List of all top-level nodes
	     */
	    std::set<Node*> const& getNodes() const;
	    /**
	     * @brief Adds a new top-level node
	     * @param node Entity to add. It will automatically be wrapped in a node
	     * @returns The node wrapping the passed entity
	     */
	    Node* addNode(T* entity);
	    /**
	     * @brief Remove top-level node
	     * @param node Entity to remove.
	     */
	    void removeNode(T* entity);
	private:
	    std::set<Node*> m_nodes;
    };
}

#include "SceneGraph.imp"

#endif /* SCENEGRAPH_H_ */
