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

namespace dbgl
{
	template<typename Data, typename Volume> class BoundingVolumeHierarchy: public AbstractTree
	{
	public:
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
	private:
		class Aggregate
		{
		public:
			Volume m_volume;
			Data m_data;
		};
		class Node: public AbstractTree::Node
		{
		public:
			Aggregate m_info;
			Volume m_bounds;
			Node* m_pParent = nullptr;
			Node* m_pLeftChild = nullptr;
			Node* m_pRightChild = nullptr;
		};

		void free(Node* node);
		void insert(Volume const& volume, Data const& data, Node* node);
		float rateNode(Node* node, Node* parent, Volume const& volume) const;

		Node* m_pRoot = nullptr;
	};
}

#include "BoundingVolumeHierarchy.imp"

#endif /* INCLUDE_DBGL_CORE_COLLECTION_TREE_BOUNDINGVOLUMEHIERARCHY_H_ */
