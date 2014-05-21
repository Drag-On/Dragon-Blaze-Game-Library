//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef KDTREE_H_
#define KDTREE_H_

#include <iterator>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <type_traits>
#include "AbstractTree.h"
#include "DBGL/Math/Hyperrectangle.h"

namespace dbgl
{
    /**
     * @brief A homogeneous k-d tree implementation for organizing points in k-dimensional space.
     * @details This tree is well suited to store spatial data along with additional information.
     * 		It has an average insertion-, deletion- and search complexity of O(log n). Every
     * 		node (in contrary to every leaf node in a nonhomogeneous k-d tree) holds exactly
     * 		one data object.
     * 		It is possible to add multiple points with the same coordinates, however methods
     * 		like get() and remove() only expect one, i.e. it's undefined which one they use.
     * @note This implementation is meant to be used with dbgl::Vector as Point.
     */
    template<typename Data, typename Point> class KdTree : public AbstractTree
    {
	private:
	    using PrecisionType = typename std::remove_reference<decltype((*((Point*)(0)))[0])>::type;
	public:
	    /**
	     * @brief Container struct used to create a k-d tree from a list
	     */
	    struct Container
	    {
		/**
		 * @brief Spatial data
		 */
		Point point;
		/**
		 * @brief Data stored with the point
		 */
		Data data;
	    };
	    /**
	     * @brief Represents a node
	     */
	    class Node : public AbstractTree::Node
	    {
		public:
		    /**
		     * @brief Stored point
		     */
		    Point point;
		    /**
		     * @brief Attached data
		     */
		    Data data;
		    /**
		     * @brief Parent node
		     */
		    Node* parent = nullptr;
		    /**
		     * @brief Left child node
		     */
		    Node* leftChild = nullptr;
		    /**
		     * @brief Right child node
		     */
		    Node* rightChild = nullptr;
		    /**
		     * @brief Accepts a visitor
		     * @param visitor Visitor to accept
		     */
		    template<class Visitor> void accept(Visitor& visitor)
		    {
			AbstractTree::Node::accept<Visitor, KdTree<Data, Point>::Node*>(visitor);
		    }
	    };

	    /**
	     * @brief Constructs an empty k-d tree.
	     * @note If you know what's going to be inserted into the tree it's better to use
	     * 	     the other constructor as it will produce a well-balanced tree. Inserting
	     * 	     elements into an already created tree on the other hand will probably
	     * 	     leave the tree unbalanced.
	     */
	    KdTree();
	    /**
	     * @brief Constructs an k-d tree from the passed elements
	     * @details The iterators have to be random-access iterators to a list of KdTree::Container
	     * @param begin Iterator pointing to the first element to add
	     * @param end iterator pointing to the last element to add
	     * @note Objects in the range begin to end will be modified
	     */
	    template<class RandomAccessIterator> KdTree(RandomAccessIterator begin, RandomAccessIterator end);
	    /**
	     * @brief Copies a k-d tree
	     * @param other Tree to copy
	     */
	    KdTree(KdTree const& other);
	    /**
	     * @brief Move operator
	     * @param other Tree to move
	     */
	    KdTree(KdTree&& other);
	    /**
	     * @brief Copy assignment operator
	     * @param other Tree to copy
	     * @return Reference to this tree
	     */
	    KdTree& operator=(KdTree const& other);
	    /**
	     * @brief Move assignment operator
	     * @param other Tree to move
	     * @return Reference to this tree
	     */
	    KdTree& operator=(KdTree&& other);
	    /**
	     * @brief Frees all previously allocated memory
	     */
	    ~KdTree();
	    /**
	     * @brief Gets the data attached to the passed point
	     * @param point Point to get data for
	     * @return Pointer to the data attached to the passed point or NULL if the point wasn't found
	     */
	    Data* get(Point const& point) const;
	    /**
	     * @brief Gets the data attached to the first found point similar to the passed one
	     * @param point Point to get data for
	     * @param precision Defines how close every coordinate has to be to be treated as similar
	     * @return Pointer to the data attached to the passed point or NULL if the point wasn't found
	     */
	    Data* getSimilar(Point const& point, double precision = 0.001) const;
	    /**
	     * @brief Inserts an element into the tree, probably leaving the tree unbalanced
	     * @param point Coordinates of the point to add
	     * @param data Data to store with that point
	     */
	    void insert(Point const& point, Data const& data);
	    /**
	     * @brief Removes a point completely from the tree
	     * @param point Point to remove
	     * @return True in case something was removed, otherwise false
	     */
	    bool remove(Point const& point);
	    /**
	     * @brief Balances the tree, increasing query performance
	     */
	    void balance();
	    /**
	     * @brief Finds the nearest neighbor to point
	     * @param point Point to find the nearest neighbor for
	     * @param[out] nearest Location of the nearest neighbor will be copied here
	     * @param[out] data Data attached to the nearest neighbor will be copied here
	     */
	    void findNearestNeighbor(Point const& point, Point& nearest, Data& data) const;
	    /**
	     * @brief Finds the k nearest neighbors to point
	     * @param point Point to find the nearest neighbors for
	     * @param k Amount of nearest neighbors to find
	     * @param[out] nearest This list will be filled with the found nearest neighbors
	     */
	    void findKNearestNeighbors(Point const& point, unsigned int k, std::vector<Container>& nearest) const;
	    /**
	     * @brief Finds all points within \p range
	     * @param range Range to find all points in
	     * @param[out] result This list will be filled with the found points
	     */
	    void findRange(Hyperrectangle<PrecisionType, Point::getDimension()> const& range, std::vector<Container>& result) const;
	    /**
	     * @brief Collects all nodes stored in the tree
	     * @return The list of all nodes
	     */
	    std::vector<Container> getAll() const;
	    /**
	     * @return Amount of elements held by the tree
	     */
	    unsigned int size() const;
	    /**
	     * @brief Clears the tree.
	     */
	    void clear();
	    /**
	     * @brief Accept a visitor
	     * @param visitor Visitor to accept
	     */
	    virtual void accept(AbstractTreeVisitor& visitor);
	    /**
	     * @brief Aceept a visitor
	     * @param visitor Visitor to accept
	     */
	    template<class Visitor> void accept(Visitor& visitor);
	private:
	    /**
	     * @brief Container used to temporarily store found nearest neighbors
	     */
	    struct NearestNeighbor
	    {
		Node const* pNode = nullptr;
		float sqDist = std::numeric_limits<float>::max();
	    };

	    /**
	     * @brief Copies a node and all of its children
	     * @param node Node to copy
	     * @return Pointer to the copied root node
	     */
	    Node* copyNode(Node& node) const;

	    /**
	     * @brief Recursively builds a tree from the passed list
	     * @details The iterators have to be random-access iterators to a list of KdTree::Container
	     * @param begin Iterator pointing to the first element to add
	     * @param end iterator pointing to the last element to add
	     * @param curDepth Current depth of tree building
	     * @param parent Pointer to the parent node of the node to build
	     * @return Pointer to the root of the built tree
	     * @note Objects in the range begin to end will be modified
	     * @warning Due to a bug in some versions of gcc (4.7.x / 4.8.x / 4.9.x) this method may
	     * 		segfault on std::nth_element. It's recommended to use an up-to-date version of gcc.
	     *		See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=58800 for more details.
	     */
	    template<class RandomAccessIterator> Node* buildTree(RandomAccessIterator begin,
		    RandomAccessIterator end, unsigned int curDepth = 0, Node* parent = nullptr) const;

	    /**
	     * @brief Searches for the node with the passed coordinates
	     * @param point Coordinates of the point to search for
	     * @param node Node to start search
	     * @param curDepth Depth of the node to start from
	     * @param level If level is not NULL the level of the found node is copied here.
	     * 		    If the searched node has not been found this variable is left unchanged
	     * @return Pointer to the node with the passed coordinates or NULL if not found
	     */
	    Node* searchFor(Point const& point, Node* node, unsigned int curDepth, unsigned int *level = nullptr) const;

	    /**
	     * @brief Searches for the first node with similar coordinates to the passed coordinates
	     * @param point Coordinates of the point to search for
	     * @param node Node to start search
	     * @param curDepth Depth of the node to start from
	     * @param level If level is not NULL the level of the found node is copied here.
	     * 		    If the searched node has not been found this variable is left unchanged
	     * @param precision Defines how precisely a point has to match
	     * @return Pointer to the node with the passed coordinates or NULL if not found
	     */
	    Node* searchForSimilar(Point const& point, Node* node, unsigned int curDepth,
		    unsigned int *level = nullptr, double precision = 0.001) const;

	    /**
	     * @brief Collects all child nodes of the passed node
	     * @param node Node to get all children from
	     * @return The list of all child nodes of node
	     */
	    std::vector<Container> getAllChildren(Node const& node) const;

	    /**
	     * @brief Collects all child nodes of the passed node and the passed node and inserts them into list
	     * @param node Node to get all children from
	     * @param list List to insert all child nodes into
	     */
	    void getAllNodes(Node const& node, std::vector<Container>& list) const;

	    /**
	     * @brief Searches for the node with the passed coordinates, returning the last checked node,
	     * 	      even if the point was not found
	     * @param point Coordinates of the point to search for
	     * @param data Data to store with that point
	     * @param node Node to start search
	     * @param curDepth Depth of the node to start from
	     * @return Reference to the last node the algorithm checked. This might be the searched node
	     * 	       but if no such node could be found it's the "closest" node in the tree
	     */
	    Node& insert(Point const& point, Data const& data, Node& node, unsigned int curDepth);

	    /**
	     * @brief Recursively frees all child nodes of node and node itself
	     * @param node Node to free recursively
	     */
	    void free(Node* node);

	    /**
	     * @brief Recursively finds the nearest neighbor to point
	     * @param point Point to find nearest neighbor for
	     * @param node Node to start search at
	     * @param currentBest Current best match
	     * @param goDown Tells the algorithm to check for closer nodes down of the current node
	     * @param curDepth Current depth
	     */
	    void findNearestNeighbor(Point const& point, Node const& node, NearestNeighbor& currentBest,
		    bool goDown, unsigned int curDepth) const;

	    /**
	     * @brief Recursively finds the k nearest neighbors to point
	     * @param point Point to find nearest neighbors for
	     * @param k Amount of nearest neighbors to find
	     * @param node Node to start search at
	     * @param currentBest List of current best matches. Needs to have space for exactly k elements.
	     * @param goDown Tells the algorithm to check for closer nodes down of the current node
	     * @param curDepth Current depth
	     */
	    void findKNearestNeighbors(Point const& point, unsigned int k, Node const& node,
		    std::vector<NearestNeighbor>& currentBest, bool goDown, unsigned int curDepth) const;
	    /**
	     * @brief Recursively finds all points within \p range
	     * @param range Range to find points in
	     * @param node Node to start search
	     * @param curDepth Current depth
	     * @param result[out] Matching nodes will be appended here
	     */
	    void findRange(Hyperrectangle<PrecisionType, Point::getDimension()> const& range, Node const& node,
		    unsigned int curDepth, std::vector<Container>& result) const;

	    /**
	     * @brief Pointer to root node
	     */
	    Node* m_pRoot = nullptr;

	    /**
	     * @brief Amount of elements held by the tree
	     */
	    unsigned int m_size = 0;
    };
}

#include "KdTree.imp"

#endif /* KDTREE_H_ */
