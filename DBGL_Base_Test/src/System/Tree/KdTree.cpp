//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "cute.h"
#include <vector>
#include "DBGL/System/Tree/KdTree.h"
#include "DBGL/System/Tree/AbstractTreeVisitor.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Vector2.h"

using namespace dbgl;

class KdTreePrintVisitor1 : public AbstractTreeVisitor
{
    public:
	void visit(KdTree<int, Vec2f>& tree)
	{
	    LOG.info("Visiting tree with % elements.", tree.size());
	}
	void visit(KdTree<int, Vec2f>::Node& node)
	{
	    LOG.info("Visiting node at point (%, %).", node.point.x(), node.point.y());
	    if(node.leftChild != nullptr)
		node.leftChild->accept(*this);
	    if(node.rightChild != nullptr)
		node.rightChild->accept(*this);
	}
	void visit(AbstractTreeVisitable& visitable)
	{
	    if(typeid(visitable) == typeid(KdTree<int, Vec2f>&))
		visit((KdTree<int, Vec2f>&)visitable);
	    else if(typeid(visitable) == typeid(KdTree<int, Vec2f>::Node&))
		visit((KdTree<int, Vec2f>::Node&) visitable);
	    else
		LOG.info("I've got no clue what I'm visiting.");
	}
};

class KdTreePrintVisitor2
{
    public:
	void visit(KdTree<int, Vec2f>& tree)
	{
	    LOG.info("Visiting tree with % elements.", tree.size());
	}
	void visit(KdTree<int, Vec2f>::Node& node)
	{
	    LOG.info("Visiting node at point (%, %).", node.point.x(), node.point.y());
	    if(node.leftChild != nullptr)
		node.leftChild->accept(*this);
	    if(node.rightChild != nullptr)
		node.rightChild->accept(*this);
	}
};

void checkResult(std::vector<typename KdTree<int, Vec2f>::Container> result, std::vector<int> needed)
{
    for(auto item : result)
    {
	auto it = std::find(needed.begin(), needed.end(), item.data);
	if(it == needed.end())
	{
	    LOG.error("Item % was returned wrongly.", item.data);
	    ASSERT(false);
	}
    }
    ASSERT(result.size() == needed.size());
}

int testKdTree()
{
    LOG.info("Starting KdTree test suite...");
    LOG.info("Constructors... ");
    KdTree<int, Vec2f> tree;
    std::vector<typename KdTree<int, Vec2f>::Container> data = {
	    {Vec2f(0, 0), 0},
	    {Vec2f(1, 0), 1},
	    {Vec2f(-1, 1), 2},
	    {Vec2f(0.5f, -0.5f), 3},
	    {Vec2f(0.75f, 0.5f), 4},
	    {Vec2f(-0.5f, -0.5f), 5},
    };
    KdTree<int, Vec2f> tree2(data.begin(), data.end());
    auto copy(tree2);
    ASSERT(*copy.get(Vec2f(0,0)) == *tree2.get(Vec2f(0,0)));
    ASSERT(copy.get(Vec2f(0,0)) != tree2.get(Vec2f(0,0)));
    auto move = std::move(copy);
    ASSERT(*move.get(Vec2f(0,0)) == *tree2.get(Vec2f(0,0)));
    ASSERT(move.get(Vec2f(0,0)) != tree2.get(Vec2f(0,0)));
    ASSERT(copy.get(Vec2f(0,0)) == nullptr);
    ASSERT(copy.size() == 0);
    std::vector<typename KdTree<int, Rectangle<float>>::Container> volumdata = {
	    {Rectangle<float>(Vec2f(0, 0), Vec2f(0.5f, 0.5f)), 0},
	    {Rectangle<float>(Vec2f(-0.5f, 1), Vec2f(0.5f, 1)), 1},
	    {Rectangle<float>(Vec2f(-0.5f, -0.5f), Vec2f(1.5f, 1.5f)), 2},
	    {Rectangle<float>(Vec2f(-0.5f, -1), Vec2f(-0.5f, 1)), 3},
    };
    KdTree<int, Rectangle<float>> volumTree(volumdata.begin(), volumdata.end());
    LOG.info("OK!");
    LOG.info("Methods... ");
    // size
    ASSERT(tree.size() == 0);
    ASSERT(tree2.size() == data.size());
    // get
    ASSERT(tree.get(Vec2f()) == nullptr);
    ASSERT(*tree2.get(Vec2f()) == 0);
    ASSERT(*tree2.get(Vec2f(1, 0)) == 1);
    ASSERT(*tree2.get(Vec2f(-1, 1)) == 2);
    ASSERT(*tree2.get(Vec2f(0.5f, -0.5f)) == 3);
    ASSERT(*tree2.get(Vec2f(0.75f, 0.5f)) == 4);
    ASSERT(*tree2.get(Vec2f(-0.5f, -0.5f)) == 5);
    ASSERT(tree2.get(Vec2f(300, 0)) == nullptr);
    // getSimilar
    ASSERT(tree.getSimilar(Vec2f()) == nullptr);
    ASSERT(*tree2.getSimilar(Vec2f()) == 0);
    ASSERT(*tree2.getSimilar(Vec2f(1.00001, 0)) == 1);
    ASSERT(*tree2.getSimilar(Vec2f(-1, 1.000134)) == 2);
    ASSERT(*tree2.getSimilar(Vec2f(0.5f, -0.5f)) == 3);
    ASSERT(*tree2.getSimilar(Vec2f(0.75023f, 0.5f)) == 4);
    ASSERT(*tree2.getSimilar(Vec2f(-0.5f, -0.5f)) == 5);
    ASSERT(tree2.getSimilar(Vec2f(300, 0)) == nullptr);
    ASSERT(*tree2.getSimilar(Vec2f(300, 0), 299.1) == 1);
    // insert
    tree.insert(Vec2f(), 300);
    tree.insert(Vec2f(-1, 0), 42);
    tree.insert(Vec2f(-0.5f, 0), 23);
    ASSERT(tree.size() == 3);
    ASSERT(*tree.get(Vec2f()) == 300);
    ASSERT(*tree.get(Vec2f(-1, 0)) == 42);
    ASSERT(*tree.get(Vec2f(-0.5f, 0)) == 23);
    ASSERT(tree.get(Vec2f(42, 42)) == nullptr);
    // remove
    ASSERT(tree.remove(Vec2f(42, 42)) == false);
    ASSERT(tree.size() == 3);
    ASSERT(tree.remove(Vec2f()) == true);
    ASSERT(tree.size() == 2);
    ASSERT(*tree.get(Vec2f(-1, 0)) == 42);
    ASSERT(*tree.get(Vec2f(-0.5f, 0)) == 23);
    ASSERT(tree.get(Vec2f()) == nullptr);
    // balance
    tree.balance();
    ASSERT(tree.size() == 2);
    ASSERT(*tree.get(Vec2f(-1, 0)) == 42);
    ASSERT(*tree.get(Vec2f(-0.5f, 0)) == 23);
    // findNearestNeighbor
    Vec2f neighbor;
    int neighborData;
    tree2.findNearestNeighbor(Vec2f(0.25f, 0.25f), neighbor, neighborData);
    ASSERT(neighborData == 0);
    tree2.findNearestNeighbor(Vec2f(), neighbor, neighborData);
    ASSERT(neighborData == 0);
    tree2.findNearestNeighbor(Vec2f(0.5f, 0.5f), neighbor, neighborData);
    ASSERT(neighborData == 4);
    tree2.findNearestNeighbor(Vec2f(-1, 0), neighbor, neighborData);
    ASSERT(neighborData == 5);
    tree2.findNearestNeighbor(Vec2f(-2, 100), neighbor, neighborData);
    ASSERT(neighborData == 2);
    tree2.findNearestNeighbor(Vec2f(1.5f, 0.5f), neighbor, neighborData);
    ASSERT(neighborData == 1);
    tree2.findNearestNeighbor(Vec2f(0.5f, -0.5f), neighbor, neighborData);
    ASSERT(neighborData == 3);
    tree2.findNearestNeighbor(Vec2f(0.5f, 0), neighbor, neighborData);
    ASSERT(neighborData == 0 || neighborData == 3 || neighborData == 1);
    // findKNearestNeighbors
    std::vector<typename KdTree<int, Vec2f>::Container> list;
    tree2.findKNearestNeighbors(Vec2f(0.5f, 0), 3, list);
    checkResult(list, {0, 3, 1});
    list.clear();
    tree2.findKNearestNeighbors(Vec2f(0.5f, 0), 4, list);
    checkResult(list, {0, 3, 1, 4});
    list.clear();
    tree2.findKNearestNeighbors(Vec2f(0.2f, -0.25f), 1, list);
    checkResult(list, {0});
    list.clear();
    tree2.findKNearestNeighbors(Vec2f(0.2f, -0.25f), 2, list);
    checkResult(list, {0, 3});
    list.clear();
    tree2.findKNearestNeighbors(Vec2f(0.2f, -0.25f), 3, list);
    checkResult(list, {0, 3, 5});
    list.clear();
    tree2.findKNearestNeighbors(Vec2f(0.2f, -0.25f), 4, list);
    checkResult(list, {0, 3, 5, 1});
    list.clear();
    tree2.findKNearestNeighbors(Vec2f(0.2f, -0.25f), 5, list);
    checkResult(list, {0, 3, 5, 1, 4});
    list.clear();
    tree2.findKNearestNeighbors(Vec2f(0.2f, -0.25f), 6, list);
    checkResult(list, {0, 3, 5, 1, 4, 2});
    list.clear();
    tree2.findKNearestNeighbors(Vec2f(0.2f, -0.25f), 7, list);
    checkResult(list, {0, 3, 5, 1, 4, 2});
    // findRange
    list.clear();
    tree2.findRange(Rectangle<float>(Vec2f(0, 0), Vec2f(1, 1)), list);
    checkResult(list, {0, 1, 4});
    list.clear();
    tree2.findRange(Rectangle<float>(Vec2f(0, -0.5f), Vec2f(1, 1)), list);
    checkResult(list, {0, 1, 4, 3});
    list.clear();
    tree2.findRange(Rectangle<float>(Vec2f(-1, 1), Vec2f(2, -1.4f)), list);
    checkResult(list, {0, 1, 4, 2});
    list.clear();
    tree2.findRange(Rectangle<float>(Vec2f(-1, -1), Vec2f(2, 2)), list);
    checkResult(list, {0, 1, 4, 3, 2, 5});
    list.clear();
    tree2.findRange(Rectangle<float>(Vec2f(0, 0), Vec2f(0, 0)), list);
    checkResult(list, {0});
    list.clear();
    tree2.findRange(Rectangle<float>(Vec2f(1, 1), Vec2f(0, 0)), list);
    checkResult(list, {});
    // getAll
    auto allNodes = tree2.getAll();
    ASSERT(allNodes.size() == tree2.size());
    allNodes = tree.getAll();
    ASSERT(allNodes.size() == tree.size());
    // clear
    tree.clear();
    tree2.clear();
    ASSERT(tree.size() == 0);
    ASSERT(tree2.size() == 0);
    ASSERT(tree.get(Vec2f(-1, 0)) == nullptr);
    ASSERT(tree.get(Vec2f(-0.5f, 0)) == nullptr);
    // Visitor pattern
    KdTreePrintVisitor1 visitor;
    LOG.info("Tree1:");
    tree.accept(visitor);
    KdTreePrintVisitor2 visitor2;
    LOG.info("(Former) Tree2:");
    move.accept<KdTreePrintVisitor2>(visitor2);
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}
