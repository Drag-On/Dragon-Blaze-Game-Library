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

namespace dbgl
{
	template<typename VOLUME, typename PRECISION = float> class VolumetricKdTree: public AbstractTree
	{
	public:
		class Node: public AbstractTree::Node
		{
		public:
			Node* m_pParent = nullptr;
			Node* m_pLeftChild = nullptr;
			Node* m_pRightChild = nullptr;
			VOLUME m_data;
			std::vector<VOLUME> m_undecidable;
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
		 */
		void insert(VOLUME const& volume);

	private:
		/**
		 * @brief Frees the passed node and all nodes further down in the hierarchy
		 * @param node Node to free
		 * @note Also disconnects the freed node from it's parent
		 */
		void free(Node* node);
		/**
		 * @brief Inserts new volume data below \p node
		 * @param data Data to construct node from
		 * @param node Node to insert below
		 * @param curDepth Depth of \p node
		 * @return
		 */
		Node* insert(VOLUME const& data, Node* node, unsigned int curDepth);

		Node* m_pRoot;
	};
}

#include "VolumetricKdTree.imp"

#endif /* INCLUDE_DBGL_CORE_COLLECTION_TREE_VOLUMETRICKDTREE_H_ */
