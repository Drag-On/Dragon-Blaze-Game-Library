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
#include "DBGL/Core/Math/Hyperrectangle.h"
#include "DBGL/Core/Math/Vector2.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Collection/Tree/KdTree.h"

using namespace dbgl;
using namespace std;

void checkResult(std::vector<typename KdTree<int, Vec2f>::Container> result, std::vector<int> needed)
{
    for(auto item : result)
    {
	auto it = std::find(needed.begin(), needed.end(), item.data);
	if(it == needed.end())
	    FAIL();
    }
    ASSERT_EQ(result.size(), needed.size());
}

TEST(KdTree,construct)
{
    std::vector<Vec3f> vectors = { {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
    std::vector<int> data = { 0, 1, 2, 3 };
    std::vector<KdTree<int,Vec3f>::Container> containers = { {{0, 0, 0},0}, {{0, 0, 1},1} };

    KdTree<int, Vec3f> kdTree1;
    ASSERT_EQ(kdTree1.size(), 0u);

    KdTree<int, Vec3f> kdTree2(containers.begin(), containers.end());
    ASSERT_EQ(kdTree2.size(), 2u);

    KdTree<int, Vec3f> kdTree3(vectors.begin(), vectors.end(), data.begin(), data.end());
    ASSERT_EQ(kdTree3.size(), 4u);
}

TEST(KdTree,copy)
{
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
    ASSERT_EQ(*copy.get(Vec2f(0,0)), *tree2.get(Vec2f(0,0)));
    ASSERT_NEQ(copy.get(Vec2f(0,0)), tree2.get(Vec2f(0,0)));
}

TEST(KdTree,move)
{
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
    auto move = std::move(copy);
    ASSERT_EQ(*move.get(Vec2f(0,0)), *tree2.get(Vec2f(0,0)));
    ASSERT_NEQ(move.get(Vec2f(0,0)), tree2.get(Vec2f(0,0)));
    ASSERT_EQ(copy.get(Vec2f(0,0)), nullptr);
    ASSERT_EQ(copy.size(), 0);
}

TEST(KdTree,size)
{
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
    ASSERT_EQ(tree.size(), 0);
    ASSERT_EQ(tree2.size(), data.size());
}

TEST(KdTree,get)
{
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
    ASSERT_EQ(tree.get(Vec2f()), nullptr);
    ASSERT_EQ(*tree2.get(Vec2f()), 0);
    ASSERT_EQ(*tree2.get(Vec2f(1, 0)), 1);
    ASSERT_EQ(*tree2.get(Vec2f(-1, 1)), 2);
    ASSERT_EQ(*tree2.get(Vec2f(0.5f, -0.5f)), 3);
    ASSERT_EQ(*tree2.get(Vec2f(0.75f, 0.5f)), 4);
    ASSERT_EQ(*tree2.get(Vec2f(-0.5f, -0.5f)), 5);
    ASSERT_EQ(tree2.get(Vec2f(300, 0)), nullptr);
}

TEST(KdTree,getSimilar)
{
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
    ASSERT_EQ(tree.getSimilar(Vec2f()), nullptr);
    ASSERT_EQ(*tree2.getSimilar(Vec2f()), 0);
    ASSERT_EQ(*tree2.getSimilar(Vec2f(1.00001, 0)), 1);
    ASSERT_EQ(*tree2.getSimilar(Vec2f(-1, 1.000134)), 2);
    ASSERT_EQ(*tree2.getSimilar(Vec2f(0.5f, -0.5f)), 3);
    ASSERT_EQ(*tree2.getSimilar(Vec2f(0.75023f, 0.5f)), 4);
    ASSERT_EQ(*tree2.getSimilar(Vec2f(-0.5f, -0.5f)), 5);
    ASSERT_EQ(tree2.getSimilar(Vec2f(300, 0)), nullptr);
    ASSERT_EQ(*tree2.getSimilar(Vec2f(300, 0), 299.1), 1);
}

TEST(KdTree,insert)
{
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
    tree.insert(Vec2f(), 300);
    tree.insert(Vec2f(-1, 0), 42);
    tree.insert(Vec2f(-0.5f, 0), 23);
    ASSERT_EQ(tree.size(), 3);
    ASSERT_EQ(*tree.get(Vec2f()), 300);
    ASSERT_EQ(*tree.get(Vec2f(-1, 0)), 42);
    ASSERT_EQ(*tree.get(Vec2f(-0.5f, 0)), 23);
    ASSERT_EQ(tree.get(Vec2f(42, 42)), nullptr);
}

TEST(KdTree,remove)
{
    std::vector<typename KdTree<int, Vec2f>::Container> data = {
	    {Vec2f(0, 0), 300},
	    {Vec2f(-1, 0), 42},
	    {Vec2f(-0.5f, 0), 23},
    };
    KdTree<int, Vec2f> tree(data.begin(), data.end());
    ASSERT_EQ(tree.remove(Vec2f(42, 42)), false);
    ASSERT_EQ(tree.size(), 3);
    ASSERT_EQ(tree.remove(Vec2f()), true);
    ASSERT_EQ(tree.size(), 2);
    ASSERT_EQ(*tree.get(Vec2f(-1, 0)), 42);
    ASSERT_EQ(*tree.get(Vec2f(-0.5f, 0)), 23);
    ASSERT_EQ(tree.get(Vec2f()), nullptr);
}

TEST(KdTree,balance)
{
    std::vector<typename KdTree<int, Vec2f>::Container> data = {
	    {Vec2f(-1, 0), 42},
	    {Vec2f(-0.5f, 0), 23},
    };
    KdTree<int, Vec2f> tree(data.begin(), data.end());
    tree.balance();
    ASSERT_EQ(tree.size(), 2);
    ASSERT_EQ(*tree.get(Vec2f(-1, 0)), 42);
    ASSERT_EQ(*tree.get(Vec2f(-0.5f, 0)), 23);
}

TEST(KdTree,findNearestNeighbor)
{
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
    Vec2f neighbor;
    int neighborData;
    tree2.findNearestNeighbor(Vec2f(0.25f, 0.25f), neighbor, neighborData);
    ASSERT_EQ(neighborData, 0);
    tree2.findNearestNeighbor(Vec2f(), neighbor, neighborData);
    ASSERT_EQ(neighborData, 0);
    tree2.findNearestNeighbor(Vec2f(0.5f, 0.5f), neighbor, neighborData);
    ASSERT_EQ(neighborData, 4);
    tree2.findNearestNeighbor(Vec2f(-1, 0), neighbor, neighborData);
    ASSERT_EQ(neighborData, 5);
    tree2.findNearestNeighbor(Vec2f(-2, 100), neighbor, neighborData);
    ASSERT_EQ(neighborData, 2);
    tree2.findNearestNeighbor(Vec2f(1.5f, 0.5f), neighbor, neighborData);
    ASSERT_EQ(neighborData, 1);
    tree2.findNearestNeighbor(Vec2f(0.5f, -0.5f), neighbor, neighborData);
    ASSERT_EQ(neighborData, 3);
    tree2.findNearestNeighbor(Vec2f(0.5f, 0), neighbor, neighborData);
    ASSERT(neighborData == 0 || neighborData == 3 || neighborData == 1);
}

TEST(KdTree,findKNearestNeighbors)
{
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
}

TEST(KdTree,findRange)
{
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
    std::vector<typename KdTree<int, Vec2f>::Container> list;
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
}

TEST(KdTree,getAll)
{
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
    std::vector<KdTree<int, Vec2f>::Container> allNodes;
    tree2.getAll(allNodes);
    ASSERT_EQ(allNodes.size(), tree2.size());
    allNodes.clear();
    tree.getAll(allNodes);
    ASSERT_EQ(allNodes.size(), tree.size());
}

TEST(KdTree,clear)
{
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
    tree.clear();
    tree2.clear();
    ASSERT_EQ(tree.size(), 0);
    ASSERT_EQ(tree2.size(), 0);
    ASSERT_EQ(tree.get(Vec2f(-1, 0)), nullptr);
    ASSERT_EQ(tree.get(Vec2f(-0.5f, 0)), nullptr);
}
