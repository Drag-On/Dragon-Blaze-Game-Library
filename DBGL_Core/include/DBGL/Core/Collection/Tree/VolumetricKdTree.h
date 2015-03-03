//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_COLLECTION_TREE_VOLUMETRICKDTREE_H_
#define INCLUDE_DBGL_CORE_COLLECTION_TREE_VOLUMETRICKDTREE_H_

#include "AbstractTree.h"
#include "DBGL/Core/Math/HyperPlane.h"
#include <vector>
#include <functional>

namespace dbgl
{
	template<typename VOLUME, typename DATA, typename PRECISION = float> class VolumetricKdTree: public AbstractTree
	{
	public:
		/**
		 * @brief Internal structure to keep data and volume together
		 */
		struct Aggregate
		{
			VOLUME m_volume;
			DATA m_data;
		};

		/**
		 * @brief Constructs an empty tree
		 */
		VolumetricKdTree();
		/**
		 * @brief Destructor
		 */
		~VolumetricKdTree();
		/**
		 * @brief Inserts a new volume into the tree
		 * @param volume New volume to add
		 * @param data Data belonging to that volume
		 */
		void insert(VOLUME const& volume, DATA const& data);
		/**
		 * @brief Retrieves pointers to all data objects that have a volume attached that is reasonably similar to \p volume
		 * @param volume Volume to search for
		 * @param[out] out Pointers to all found data objects will be pushed to this container
		 * @note The pointers retrieved this way can be used to modify the data within the tree. However, they are not guaranteed
		 * 		 to stay valid after further calls to tree functionality.
		 */
		void get(VOLUME const& volume, std::vector<DATA*>& out) const;
		/**
		 * @brief Removes a volume completely from the tree
		 * @param volume Volume to remove
		 * @param data Data that belongs to that volume
		 * @return Amount of removed nodes
		 */
		unsigned int remove(VOLUME const& volume, DATA const& data);
		/**
		 * @brief Finds all volumes that intersect with \p range
		 * @param range Range to find all volumes in
		 * @param[out] out This list will be filled with the found entities
		 */
		void findRange(Hyperrectangle<PRECISION, VOLUME::getDimension()> const& range,
				std::vector<Aggregate>& out) const;

	private:
		const unsigned int D = VOLUME::getDimension();
		/**
		 * @brief One node within the tree
		 */
		class Node: public AbstractTree::Node
		{
		public:
			Node* m_pParent = nullptr;
			Node* m_pLeftChild = nullptr;
			Node* m_pRightChild = nullptr;
			Aggregate m_data;
			VOLUME m_bounds;
		};

		/**
		 * @brief Frees the passed node and all nodes further down in the hierarchy
		 * @param node Node to free
		 * @note Also disconnects the freed node from it's parent
		 */
		void free(Node* node);
		/**
		 * @brief Inserts new volume data below \p node
		 * @param volume Volume information
		 * @param data Data to construct node from
		 * @param node Node to insert below
		 * @param curDepth Depth of \p node
		 * @return
		 */
		Node* insert(VOLUME const& volume, DATA const& data, Node* node, unsigned int curDepth);
		/**
		 * @brief Retrieves pointers to all data objects that have a volume attached that is reasonably similar to \p volume
		 * @param volume Volume to search for
		 * @param[out] out Pointers to all found data objects will be pushed to this container
		 * @param node Node to start searching for
		 * @param curDepth Depth of \p node
		 */
		void get(VOLUME const& volume, std::vector<DATA*>& out, Node* node, unsigned int curDepth) const;
		/**
		 * @brief Removes a volume completely from the tree
		 * @param volume Volume to remove
		 * @param data Data that belongs to that volume
		 * @param node Node to start searching
		 * @param curDepth Depth of \p node
		 * @return Amount of removed nodes
		 */
		unsigned int remove(VOLUME const& volume, DATA const& data, Node* node, unsigned int curDepth);
		/**
		 * @brief Finds the node with the least \p dimension coordinate
		 * @param start Node to start searching from
		 * @param dimension Dimension to minimize
		 * @param curMin Current minimum
		 * @return The found node
		 */
		Node* findMinNode(Node* start, unsigned int dimension, unsigned int& depth, unsigned int curDepth,
				Node* curMin = nullptr) const;
		/**
		 * @brief Finds the node with the largest \p dimension coordinate
		 * @param start Node to start searching from
		 * @param dimension Dimension to maximize
		 * @param curMax Current maximum
		 * @return The found node
		 */
		Node* findMaxNode(Node* start, unsigned int dimension, unsigned int& depth, unsigned int curDepth,
				Node* curMax = nullptr) const;
		/**
		 * @brief Removes the passed node
		 * @param node Node to remove
		 * @param depth Depth of the node
		 * @returns The node that has been put into the place of the removed one
		 */
		Node* removeNode(Node* node, unsigned int depth);
		/**
		 * @brief Finds all volumes that intersect with \p range
		 * @param range Range to find all volumes in
		 * @param[out] out This list will be filled with the found entities
		 */
		void findRange(Hyperrectangle<PRECISION, VOLUME::getDimension()> const& range, std::vector<Aggregate>& out,
				Node* node, unsigned int curDepth) const;

		/**
		 * @brief Root node
		 */
		Node* m_pRoot;
	};
}

#include "VolumetricKdTree.imp"

#endif /* INCLUDE_DBGL_CORE_COLLECTION_TREE_VOLUMETRICKDTREE_H_ */
