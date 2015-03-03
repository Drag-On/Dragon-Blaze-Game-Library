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
#include "DBGL/Core/Math/Vector2.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Collection/Tree/VolumetricKdTree.h"
#include "DBGL/Core/Shape/Hyperrectangle.h"
#include "DBGL/Core/Shape/HyperSphere.h"

using namespace dbgl;
using namespace std;

TEST(VolumetricKdTree,construct)
{
	VolumetricKdTree<Sphere<float>, unsigned int> tree;
}

TEST(VolumetricKdTree,insert)
{
	VolumetricKdTree<Circle<float>, unsigned int> tree;
	Circle<float> v0 { Vec2f { }, 1 };
	Circle<float> v1 { Vec2f { 1, 0 }, 1 };
	Circle<float> v2 { Vec2f { 1, 1 }, 1 };
	Circle<float> v3 { Vec2f { 5, 1 }, 1 };
	Circle<float> v4 { Vec2f { -1, 0 }, 1 };
	Circle<float> v5 { Vec2f { 3, 3 }, 1 };
	Circle<float> v6 { Vec2f { 3, 4 }, 1 };
	tree.insert(v0, 0);
	tree.insert(v1, 1);
	tree.insert(v2, 2);
	tree.insert(v3, 3);
	tree.insert(v4, 4);
	tree.insert(v5, 5);
	tree.insert(v6, 6);
}

TEST(VolumetricKdTree,remove)
{
	VolumetricKdTree<Circle<float>, unsigned int> tree;
	Circle<float> v0 { Vec2f { }, 1 };
	Circle<float> v1 { Vec2f { 1, 0 }, 1 };
	Circle<float> v2 { Vec2f { 1, 1 }, 1 };
	Circle<float> v3 { Vec2f { 5, 1 }, 1 };
	Circle<float> v4 { Vec2f { -1, 0 }, 1 };
	Circle<float> v5 { Vec2f { 3, 3 }, 1 };
	Circle<float> v6 { Vec2f { 3, 4 }, 1 };
	tree.insert(v0, 0);
	tree.insert(v1, 1);
	tree.insert(v2, 2);
	tree.insert(v3, 3);
	tree.insert(v4, 4);
	tree.insert(v5, 5);
	tree.insert(v6, 6);
	tree.insert(v6, 6);
	auto removed = tree.remove(v5, 5);
	ASSERT_EQ(removed, 1);
	removed = tree.remove(v2, 2);
	ASSERT_EQ(removed, 1);
	removed = tree.remove(v3, 42);
	ASSERT_EQ(removed, 0);
	removed = tree.remove(v6, 6);
	ASSERT_EQ(removed, 2);
}

TEST(VolumetricKdTree,get)
{
	VolumetricKdTree<Circle<float>, unsigned int> tree;
	Circle<float> v0 { Vec2f { }, 1 };
	Circle<float> v1 { Vec2f { 1, 0 }, 1 };
	Circle<float> v2 { Vec2f { 1, 1 }, 1 };
	Circle<float> v3 { Vec2f { 5, 1 }, 1 };
	Circle<float> v4 { Vec2f { -1, 0 }, 1 };
	Circle<float> v5 { Vec2f { 3, 3 }, 1 };
	Circle<float> v6 { Vec2f { 3, 4 }, 1 };
	Circle<float> v7 { Vec2f { 3, 4 }, 1 };
	tree.insert(v0, 0);
	tree.insert(v1, 1);
	tree.insert(v2, 2);
	tree.insert(v3, 3);
	tree.insert(v4, 4);
	tree.insert(v5, 5);
	tree.insert(v6, 6);
	tree.insert(v7, 7);
	std::vector<unsigned int*> data;
	tree.get(v0, data);
	ASSERT_EQ(data.size(), 1);
	ASSERT_EQ(*data[0], 0);
	data.clear();
	tree.get(v6, data);
	ASSERT_EQ(data.size(), 2);
	ASSERT_EQ(*data[0], 6);
	ASSERT_EQ(*data[1], 7);
	data.clear();
	tree.get({ Vec2f { 10, 10 }, 42 }, data);
	ASSERT_EQ(data.size(), 0);
}
