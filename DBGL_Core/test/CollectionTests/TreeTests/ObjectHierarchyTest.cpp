//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <vector>
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Collection/Tree/ObjectHierarchy.h"

using namespace dbgl;
using namespace std;

TEST(ObjectHierarchy,construct)
{
	ObjectHierarchy<int> oh;
	ASSERT_EQ(oh.rootCount(), 0);
	ASSERT_EQ(oh.size(), 0);
}

TEST(ObjectHierarchy,insert)
{
	ObjectHierarchy<int> oh;
	// Insert base node
	auto node = oh.insert(0);
	ASSERT_EQ(oh.rootCount(), 1);
	ASSERT_EQ(oh.size(), 1);
	ASSERT_EQ(node->data(), 0);
	ASSERT_EQ(node->parent(), nullptr);
	ASSERT_EQ(node->childCount(), 0);

	// Add a child
	auto node1 = node->insert(1);
	ASSERT_EQ(oh.rootCount(), 1);
	ASSERT_EQ(oh.size(), 2);
	ASSERT_EQ(node->data(), 0);
	ASSERT_EQ(node1->data(), 1);
	ASSERT_EQ(node1->parent(), node);
	ASSERT_EQ(node->childCount(), 1);
	ASSERT_EQ(node1->childCount(), 0);

	// Add a base node with data identical to the first base node
	auto node2 = oh.insert(0);
	ASSERT_EQ(oh.rootCount(), 2);
	ASSERT_EQ(oh.size(), 3);
	ASSERT_EQ(node2->data(), 0);
	ASSERT_EQ(node2->parent(), nullptr);
	ASSERT_EQ(node2->childCount(), 0);
}

TEST(ObjectHierarchy,remove)
{
	ObjectHierarchy<int> oh;
	// Insert some root nodes
	auto node0 = oh.insert(0);
	auto node1 = oh.insert(1);
	auto node2 = oh.insert(2);
	auto node3 = oh.insert(3);
	// Insert some children
	auto node4 = node0->insert(4);
	auto node5 = node0->insert(5);
	/* auto node6 = */node0->insert(6);
	/* auto node7 = */node2->insert(7);
	auto node8 = node5->insert(8);

	ASSERT_EQ(oh.rootCount(), 4);
	ASSERT_EQ(oh.size(), 9);

	ASSERT(!oh.remove(node8));
	ASSERT(!oh.remove(node4));
	ASSERT(oh.remove(node3));
	ASSERT_EQ(oh.rootCount(), 3);
	ASSERT_EQ(oh.size(), 8);

	ASSERT(oh.remove(node0));
	ASSERT_EQ(oh.rootCount(), 2);
	ASSERT_EQ(oh.size(), 3);

	ASSERT_NOTHROW(oh.remove(nullptr));
	ASSERT_EQ(oh.rootCount(), 2);
	ASSERT_EQ(oh.size(), 3);

	ASSERT(oh.remove(node1));
	ASSERT_EQ(oh.rootCount(), 1);
	ASSERT_EQ(oh.size(), 2);

	ASSERT(oh.remove(node2));
	ASSERT_EQ(oh.rootCount(), 0);
	ASSERT_EQ(oh.size(), 0);
}

TEST(ObjectHierarchy,find)
{
	ObjectHierarchy<int> oh;
	// Insert some root nodes
	auto node0 = oh.insert(0);
	auto node1 = oh.insert(1);
	auto node2 = oh.insert(2);
	auto node3 = oh.insert(3);
	// Insert some children
	/* auto node4 = */node0->insert(4);
	auto node5 = node0->insert(5);
	auto node6 = node0->insert(6);
	auto node7 = node2->insert(7);
	auto node8 = node5->insert(8);
	auto node9 = node6->insert(1);
	/* auto node10 = */node7->insert(1);
	/* auto node11 = */node3->insert(1);

	ASSERT_EQ(oh.find([](ObjectHierarchy<int>::Node* n)
	{	return n->data() == 8;}, false), nullptr);
	ASSERT_EQ(oh.find([](ObjectHierarchy<int>::Node* n)
	{	return n->data() == 8;}, true), node8);
	ASSERT_EQ(oh.find([](ObjectHierarchy<int>::Node* n)
	{	return n->data() == 1;}, false), node1);
	ASSERT_EQ(oh.find([](ObjectHierarchy<int>::Node* n)
	{	return n->data() == 1;}, true), node9);
}

TEST(ObjectHierarchy,findAll)
{
	ObjectHierarchy<int> oh;
	// Insert some root nodes
	auto node0 = oh.insert(0);
	auto node1 = oh.insert(1);
	auto node2 = oh.insert(2);
	auto node3 = oh.insert(3);
	// Insert some children
	/* auto node4 = */node0->insert(4);
	auto node5 = node0->insert(5);
	auto node6 = node0->insert(6);
	auto node7 = node2->insert(7);
	auto node8 = node5->insert(8);
	auto node9 = node6->insert(1);
	auto node10 = node7->insert(1);
	auto node11 = node3->insert(1);

	oh.findAll([](ObjectHierarchy<int>::Node* n)
	{	return n->data() == 8;}, [&](ObjectHierarchy<int>::Node* n)
	{	ASSERT(n == node8);}, true);
	oh.findAll([](ObjectHierarchy<int>::Node* n)
	{	return n->data() == 1;}, [&](ObjectHierarchy<int>::Node* n)
	{	ASSERT(n == node1 || n == node9 || n == node10 || n == node11);}, true);
}
