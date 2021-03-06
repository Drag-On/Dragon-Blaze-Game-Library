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
#include "DBGL/Core/Collection/Tree/BoundingVolumeHierarchy.h"
#include "DBGL/Core/Shape/Shapes.h"
#include "DBGL/Core/Math/Vector3.h"

using namespace dbgl;
using namespace std;

void checkResult(std::vector<BoundingVolumeHierarchy<int, Sphere<float>>::Aggregate*> const& result,
		std::vector<int> needed)
{
	for (auto item : result)
	{
		auto it = std::find(needed.begin(), needed.end(), item->m_data);
		ASSERT(it != needed.end());
	}
	ASSERT_EQ(result.size(), needed.size());
}

TEST(BoundingVolumeHierarchy,construct)
{
	BoundingVolumeHierarchy<int, Sphere<float>> bvh { };
}

TEST(BoundingVolumeHierarchy,insert)
{
	BoundingVolumeHierarchy<int, Sphere<float>> bvh { };

	Sphere<float> s0 { };
	Sphere<float> s1 { Vec3f { 10, 0, 0 }, 3 };
	Sphere<float> s2 { Vec3f { 1, 2, 0 }, 2 };
	Sphere<float> s3 { Vec3f { 2, 4, 0 }, 1 };
	Sphere<float> s4 { Vec3f { 0, 1, 0 }, 10 };
	Sphere<float> s5 { Vec3f { 42, 0, 0 }, 1 };
	Sphere<float> s6 { Vec3f { 1, 5, 0 }, 4 };
	bvh.insert(s0, 0);
	bvh.insert(s1, 1);
	bvh.insert(s2, 2);
	bvh.insert(s3, 3);
	bvh.insert(s4, 4);
	bvh.insert(s5, 5);
	bvh.insert(s6, 6);
}

TEST(BoundingVolumeHierarchy,remove)
{
	BoundingVolumeHierarchy<int, Sphere<float>> bvh { };

	Sphere<float> s0 { };
	Sphere<float> s1 { Vec3f { 10, 0, 0 }, 3 };
	Sphere<float> s2 { Vec3f { 1, 2, 0 }, 2 };
	Sphere<float> s3 { Vec3f { 2, 4, 0 }, 1 };
	Sphere<float> s4 { Vec3f { 0, 1, 0 }, 10 };
	Sphere<float> s5 { Vec3f { 42, 0, 0 }, 1 };
	Sphere<float> s6 { Vec3f { 1, 5, 0 }, 4 };
	bvh.insert(s0, 0);
	bvh.insert(s1, 1);
	bvh.insert(s2, 2);
	bvh.insert(s3, 3);
	bvh.insert(s4, 4);
	bvh.insert(s5, 5);
	bvh.insert(s6, 6);

	ASSERT_EQ(bvh.remove(s1, 1), 1);
	ASSERT_EQ(bvh.remove(s2, 2), 1);
	ASSERT_EQ(bvh.remove(s5, 5), 1);
}

TEST(BoundingVolumeHierarchy,get)
{
	BoundingVolumeHierarchy<int, Sphere<float>> bvh { };

	Sphere<float> s0 { };
	Sphere<float> s1 { Vec3f { 10, 0, 0 }, 3 };
	Sphere<float> s2 { Vec3f { 1, 2, 0 }, 2 };
	Sphere<float> s3 { Vec3f { 2, 4, 0 }, 1 };
	Sphere<float> s4 { Vec3f { 0, 1, 0 }, 10 };
	Sphere<float> s5 { Vec3f { 42, 0, 0 }, 1 };
	Sphere<float> s6 { Vec3f { 1, 5, 0 }, 4 };
	bvh.insert(s0, 0);
	bvh.insert(s1, 1);
	bvh.insert(s2, 2);
	bvh.insert(s3, 3);
	bvh.insert(s4, 4);
	bvh.insert(s5, 5);
	bvh.insert(s6, 6);

	std::vector<BoundingVolumeHierarchy<int, Sphere<float>>::Aggregate*> results;
	bvh.get(AABB<float> { }, results);
	checkResult(results, { 0, 2, 4, 6 });
	results.clear();

	bvh.get(AABB<float> { Vec3f { 0, 0, 0 }, Vec3f { 8, 2, 0 } }, results);
	checkResult(results, { 0, 1, 2, 4, 6 });
	results.clear();

	bvh.get(AABB<float> { Vec3f { 1.5f, 3.5f, 0 }, Vec3f { 1, 1, 1 } }, results);
	checkResult(results, { 2, 3, 4, 6 });
	results.clear();

	bvh.get(AABB<float> { Vec3f { -100, -9, 0 }, Vec3f { 1, 1, 1 } }, results);
	checkResult(results, { });
	results.clear();

	bvh.get(AABB<float> { Vec3f { 20, -9, 0 }, Vec3f { 40, 100, 10 } }, results);
	checkResult(results, { 5 });
	results.clear();
}
