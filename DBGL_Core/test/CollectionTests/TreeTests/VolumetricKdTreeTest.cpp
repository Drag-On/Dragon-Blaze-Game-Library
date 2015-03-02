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
#include "DBGL/Core/Math/Hyperrectangle.h"
#include "DBGL/Core/Math/HyperSphere.h"
#include "DBGL/Core/Math/Vector2.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Collection/Tree/VolumetricKdTree.h"

using namespace dbgl;
using namespace std;

namespace dbgl_volumetrickdtree_test
{
	class Volume: public Sphere<float>
	{
	public:
		Volume() = default;
		Volume(unsigned int i, Vec3f center, float radius)
				: Sphere<float> ( center, radius ), id { i }
		{
		}
		unsigned int id = 0;
	};
}

using Volume = dbgl_volumetrickdtree_test::Volume;

TEST(VolumetricKdTree,construct)
{
	VolumetricKdTree<Volume> tree;
}

TEST(VolumetricKdTree,insert)
{
	VolumetricKdTree<Volume> tree;
	Volume v0 { 0, Vec3f{}, 1 };
	Volume v1 { 1, Vec3f{1, 0, 0}, 1 };
	Volume v2 { 2, Vec3f{1, 1, 0}, 1 };
	Volume v3 { 3, Vec3f{5, 1, 0}, 1 };
	Volume v4 { 4, Vec3f{-1, 0, 0}, 1 };
	Volume v5 { 5, Vec3f{3, 3, 0}, 1 };
	Volume v6 { 6, Vec3f{3, 4, 0}, 1 };
	tree.insert(v0);
	tree.insert(v1);
	tree.insert(v2);
	tree.insert(v3);
	tree.insert(v4);
	tree.insert(v5);
	tree.insert(v6);
}
