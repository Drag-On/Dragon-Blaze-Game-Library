//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_COLLECTION_TREE_OBJECTHIERARCHY_H_
#define INCLUDE_DBGL_CORE_COLLECTION_TREE_OBJECTHIERARCHY_H_

#include "AbstractTree.h"
#include <vector>
#include <functional>
#include <algorithm>

namespace dbgl
{
	/**
	 * @brief Implements a tree-structured object hierarchy
	 */
	template<typename T> class ObjectHierarchy: public AbstractTree
	{
	public:
		/**
		 * @brief A node within the hierarchy
		 */
		class Node: public AbstractTree::Node
		{
		public:
			/**
			 * @brief Provides access to the stored data instance
			 * @return Reference to data
			 */
			T& data();
			/**
			 * @brief Provides access to the stored data instance
			 * @return Reference to data
			 */
			T const& data() const;
			/**
			 * @brief Provides access to this node's parent
			 * @return Pointer to parent node
			 */
			Node* parent();
			/**
			 * @brief Provides access to this node's parent
			 * @return Pointer to parent node
			 */
			Node const* parent() const;
			/**
			 * @brief Creates a child node
			 * @param data Data instance to store with the new child
			 * @return Pointer to the newly created child
			 */
			Node* insert(T const& data);
			/**
			 * @brief Removes a child node and deallocates it
			 * @param node Node to remove
			 * @return True in case the node was removed, otherwise false
			 * @warning If the attached data is a pointer, the allocated memory will not be freed!
			 */
			bool remove(Node* node);
			/**
			 * @brief Finds the child node that matches certain criteria
			 * @param criterion Function that returns true if the criteria are matched, otherwise false
			 * @param recursive Specifies if a recursive search should be done
			 * @return Pointer to the found node
			 */
			Node* find(std::function<bool(Node*)> criterion, bool recursive = true) const;
			/**
			 * @brief Finds all child nodes that match certain criteria
			 * @param criterion Function that returns true if the criteria are matched, otherwise false
			 * @param use Function that gets every matching nodes and may due something with them
			 * @param recursive Specifies if a recursive search should be done
			 */
			void findAll(std::function<bool(Node*)> criterion, std::function<void(Node*)> use,
					bool recursive = true) const;
			/**
			 * @brief Retrieves the amount of child nodes
			 * @return Amount of child nodes
			 */
			size_t childCount() const;
		private:
			Node(ObjectHierarchy* base);

			ObjectHierarchy* m_pBase;
			T m_data;
			Node* m_pParent = nullptr;
			std::vector<Node*> m_children;

			friend class ObjectHierarchy;
		};

		/**
		 * @brief Destructor
		 */
		~ObjectHierarchy();
		/**
		 * @brief Creates a new top-level node
		 * @param data Data to attach to that node
		 * @return A pointer to the newly created node
		 */
		Node* insert(T const& data);
		/**
		 * @brief Removes a node from the tree
		 * @param node Node to remove
		 * @return True if the node was removed, otherwise false
		 * @warning If the attached data is a pointer, the allocated memory will not be freed!
		 */
		bool remove(Node* node);
		/**
		 * @brief Finds the first node that matches certain criteria
		 * @param criterion Function that returns true if the criteria are matched, otherwise false
		 * @param recursive Specifies if a recursive search should be done
		 * @return Pointer to the found node
		 */
		Node* find(std::function<bool(Node*)> criterion, bool recursive = true) const;
		/**
		 * @brief Finds all nodes that match certain criteria
		 * @param criterion Function that returns true if the criteria are matched, otherwise false
		 * @param use Function that gets every matching nodes and may due something with them
		 * @param recursive Specifies if a recursive search should be done
		 */
		void findAll(std::function<bool(Node*)> criterion, std::function<void(Node*)> use, bool recursive = true) const;
		/**
		 * @brief Retrieves the amount of root nodes
		 * @return Amount of root nodes
		 */
		size_t rootCount() const;
		/**
		 * @brief Retrieves the total amount of nodes
		 * @return Amount of nodes
		 */
		size_t size() const;
		/**
		 * @brief Removes all nodes from the hierarchy
		 */
		void clear();
	private:
		void free(Node* node);
		Node* find(std::vector<Node*> const& nodes, std::function<bool(Node*)> criterion, bool recursive) const;
		void findAll(std::vector<Node*> const& nodes, std::function<bool(Node*)> criterion,
				std::function<void(Node*)> use, bool recursive) const;

		std::vector<Node*> m_nodes;
		size_t m_size = 0;

		friend class Node;
	};
}

#include "ObjectHierarchy.imp"

#endif /* INCLUDE_DBGL_CORE_COLLECTION_TREE_OBJECTHIERARCHY_H_ */
