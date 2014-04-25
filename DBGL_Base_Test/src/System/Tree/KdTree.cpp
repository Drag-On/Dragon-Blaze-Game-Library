//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <vector>
#include "DBGL/System/Tree/KdTree.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Vector2.h"

using namespace dbgl;

int testKdTree()
{
    LOG->info("Starting KdTree test suite...");
    LOG->info("Constructors... ");
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
    LOG->info("OK!");
    LOG->info("Methods... ");
    // get
    assert(tree.get(Vec2f()) == nullptr);
    assert(*tree2.get(Vec2f()) == 0);
    assert(*tree2.get(Vec2f(1, 0)) == 1);
    assert(*tree2.get(Vec2f(-1, 1)) == 2);
    assert(*tree2.get(Vec2f(0.5f, -0.5f)) == 3);
    assert(*tree2.get(Vec2f(0.75f, 0.5f)) == 4);
    assert(*tree2.get(Vec2f(-0.5f, -0.5f)) == 5);
    assert(tree2.get(Vec2f(300, 0)) == nullptr);
    // insert
    tree.insert(Vec2f(), 300);
    tree.insert(Vec2f(-1, 0), 42);
    tree.insert(Vec2f(-0.5f, 0), 23);
    assert(*tree.get(Vec2f()) == 300);
    assert(*tree.get(Vec2f(-1, 0)) == 42);
    assert(*tree.get(Vec2f(-0.5f, 0)) == 23);
    assert(tree.get(Vec2f(42, 42)) == nullptr);
    // remove
    assert(tree.remove(Vec2f(42, 42)) == false);
    assert(tree.remove(Vec2f()) == true);
    assert(*tree.get(Vec2f(-1, 0)) == 42);
    assert(*tree.get(Vec2f(-0.5f, 0)) == 23);
    assert(tree.get(Vec2f()) == nullptr);
    // balance
    tree.balance();
    assert(*tree.get(Vec2f(-1, 0)) == 42);
    assert(*tree.get(Vec2f(-0.5f, 0)) == 23);
    // findNearestNeighbor
    Vec2f neighbor;
    int neighborData;
    tree2.findNearestNeighbor(Vec2f(0.25f, 0.25f), neighbor, neighborData);
    assert(neighborData == 0);
    tree2.findNearestNeighbor(Vec2f(), neighbor, neighborData);
    assert(neighborData == 0);
    tree2.findNearestNeighbor(Vec2f(0.5f, 0.5f), neighbor, neighborData);
    assert(neighborData == 4);
    tree2.findNearestNeighbor(Vec2f(-1, 0), neighbor, neighborData);
    assert(neighborData == 5);
    tree2.findNearestNeighbor(Vec2f(-2, 100), neighbor, neighborData);
    assert(neighborData == 2);
    tree2.findNearestNeighbor(Vec2f(1.5f, 0.5f), neighbor, neighborData);
    assert(neighborData == 1);
    tree2.findNearestNeighbor(Vec2f(0.5f, -0.5f), neighbor, neighborData);
    assert(neighborData == 3);
    tree2.findNearestNeighbor(Vec2f(0.5f, 0), neighbor, neighborData);
    assert(neighborData == 0 || neighborData == 3 || neighborData == 1);
    // getAll
    auto allNodes = tree2.getAll();
    assert(allNodes.size() == 6);
    allNodes = tree.getAll();
    assert(allNodes.size() == 2);
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}
