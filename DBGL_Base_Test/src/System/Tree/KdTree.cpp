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
    assert(*tree2.get(Vec2f(-1, 1)) == 2);
    LOG->info("OK!");
    LOG->info("Operators... ");

    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}
