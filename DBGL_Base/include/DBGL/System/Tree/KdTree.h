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

namespace dbgl
{
    /**
     * @brief A homogeneous k-d tree implementation for organizing points in k-dimensional space.
     * @details This tree is well suited to store spatial data along with additional information.
     * 		It has an average insertion-, deletion- and search complexity of O(log n). Every
     * 		node (in contrary to every leaf node in a nonhomogeneous k-d tree) holds exactly
     * 		one data object.
     */
    template<typename Data, typename Point> class KdTree
    {
	public:
	    struct Container
	    {
		Point point;
		Data data;
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
	     * @param begin Iterator pointing to the first element to add
	     * @param end iterator pointing to the last element to add
	     * @note Objects in the range begin to end will be modified
	     */
	    template<class RandomAccessIterator> KdTree(RandomAccessIterator begin, RandomAccessIterator end);
	    /**
	     * @brief Frees all previously allocated memory
	     */
	    ~KdTree();
	    /**
	     * @brief Gets the data attached to the passed point
	     * @param point Point to get data for
	     * @return Poiner to the data attached to the passed point or NULL if the point wasn't found
	     */
	    Data* get(Point const& point);
	    /**
	     * @brief Inserts an element into the tree, probably leaving the tree unbalanced
	     * @param point Coordinates of the point to add
	     * @param data Data to store with that point
	     */
	    void insert(Point const& point, Data& data);
	    /**
	     * @brief Removes a point completely from the tree
	     * @param point Point to remove
	     */
	    void remove(Point const& point);
	    /**
	     * @brief Balances the tree, increasing query performance
	     */
	    void balance();
	    /**
	     * @brief Finds the nearest neighbor to point
	     * @param point Point to find the nearest neighbor for
	     * @param nearest Location of the nearest neighbor will be copied here
	     * @param data Data attached to the nearest neighbor will be copied here
	     */
	    void findNearestNeighbor(Point const& point, Point& nearest, Data& data);
	private:
	    /**
	     * @brief Represents a node
	     */
	    class Node
	    {
		public:
		    Point point;			// Stored point
		    Data data;			// Attached data
		    Node* parent = nullptr;		// Parent node
		    Node* leftChild = nullptr;	// Left child node
		    Node* rightChild = nullptr;	// Right child node
		    ~Node()
		    {
			delete leftChild;
			delete rightChild;
		    }
	    };

	    /**
	     * @brief Recursively builds a tree from the passed list
	     * @param begin Iterator pointing to the first element to add
	     * @param end iterator pointing to the last element to add
	     * @param curDepth Current depth of tree building
	     * @param parent Pointer to the parent node of the node to build
	     * @return Pointer to the root of the built tree
	     * @note Objects in the range begin to end will be modified
	     */
	    template<class RandomAccessIterator> Node* buildTree(RandomAccessIterator begin,
		    RandomAccessIterator end, unsigned int curDepth = 0, Node* parent = nullptr);

	    /**
	     * @brief Searches for the node with the passed coordinates
	     * @param point Coordinates of the point to search for
	     * @param node Node to start search
	     * @param curDepth Depth of the node to start from
	     * @return Pointer to the node with the passed coordinates or NULL if not found
	     */
	    Node* searchFor(Point const& point, Node* node, unsigned int curDepth);

	    /**
	     * @brief Compares two containers by their coordinate defined in compareAxis
	     * @param a First container
	     * @param b Second container
	     * @return True if as compareAxis is smaller or equal to bs, otherwise false
	     */
	    static bool compare(Container const& a, Container const& b);

	    /**
	     * Axis used by compare()
	     */
	    static unsigned int compareAxis;

	    /**
	     * @brief Pointer to root node
	     */
	    Node* m_pRoot = nullptr;
    };
}

#include "KdTree.imp"

#endif /* KDTREE_H_ */
