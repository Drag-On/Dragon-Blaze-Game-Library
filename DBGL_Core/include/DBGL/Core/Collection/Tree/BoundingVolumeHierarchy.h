//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_COLLECTION_TREE_BOUNDINGVOLUMEHIERARCHY_H_
#define INCLUDE_DBGL_CORE_COLLECTION_TREE_BOUNDINGVOLUMEHIERARCHY_H_

#include "AbstractTree.h"
#include "DBGL/Core/Shape/IShape.h"
#include <vector>

namespace dbgl
{
	template<typename Data, typename Volume> class BoundingVolumeHierarchy: public AbstractTree
	{
	public:
		/**
		 * @brief Aggregates data and volume
		 */
		class Aggregate
		{
		public:
			/**
			 * @brief Volume
			 */
			Volume m_volume;
			/**
			 * @brief Data
			 */
			Data m_data;
		};
		/**
		 * @brief Destructor
		 */
		~BoundingVolumeHierarchy();
		/**
		 * @brief Inserts an element into the tree, probably leaving the tree unbalanced
		 * @param volume Volumetric data of the element to add
		 * @param data Data to store with the volume
		 */
		void insert(Volume const& volume, Data const& data);
		/**
		 * @brief Completely removes an element from the tree
		 * @param volume Volumetric data of the element to remove
		 * @param data Data stored with the volume
		 * @return Amount of removed elements
		 */
		unsigned int remove(Volume const& volume, Data const& data);
		/**
		 * @brief Finds all points within \p range
		 * @param range Range to find all points in
		 * @param[out] result This list will be filled with the found points
		 */
		void get(IShape<typename Volume::PrecisionType, Volume::getDimension()> const& range,
				std::vector<Aggregate*>& result) const;
		/**
		 * @brief Clears the tree.
		 */
		void clear();

	private:
		class Node: public AbstractTree::Node
		{
		public:
			Aggregate m_info;
			Volume m_bounds;
			Node* m_pParent = nullptr;
			Node* m_pLeftChild = nullptr;
			Node* m_pRightChild = nullptr;
			unsigned int m_children = 0;
		};

		void free(Node* node);
		void insert(Volume const& volume, Data const& data, Node* node);
		float rateNode(Node* node, Node* parent, Volume const& volume) const;
		unsigned int remove(Volume const& volume, Data const& data, Node* node);
		Node* findReplacement(Node* node);
		void get(IShape<typename Volume::PrecisionType, Volume::getDimension()> const& range, std::vector<Aggregate*>& result,
				Node* node) const;

		Node* m_pRoot = nullptr;
	};
}

#include "BoundingVolumeHierarchy.imp"

#endif /* INCLUDE_DBGL_CORE_COLLECTION_TREE_BOUNDINGVOLUMEHIERARCHY_H_ */
