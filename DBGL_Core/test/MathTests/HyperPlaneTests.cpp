//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Math/Hyperplane.h"

using namespace dbgl;
using namespace std;

template<class T, unsigned int D> void testConstructor()
{
	HyperPlane<T, D> plane { };
	ASSERT_EQ(plane.normal().getSquaredLength(), 0);
	ASSERT_EQ(plane.base().getSquaredLength(), 0);
	Vector<T, D> normal;
	normal[0] = 1;
	HyperPlane<T, D> plane2 { Vector<T, D> { }, normal };
	ASSERT_EQ(plane2.normal().getSquaredLength(), 1);
	ASSERT_EQ(plane2.base().getSquaredLength(), 0);
	ASSERT_NOTHROW(plane.getDistance(plane2.base()));
}

TEST(Hyperplane,construct)
{
	testConstructor<float, 2>();
	testConstructor<float, 3>();
}

template<class T, unsigned int D> void testIntersectsDistance()
{
	Vector<T, D> base;
	Vector<T, D> normal;
	normal[0] = 1;
	HyperPlane<T, D> plane { base, normal };
	base[0] = 1;
	HyperPlane<T, D> plane2 { base, normal };
	ASSERT_EQ(plane.intersects(plane2), false);
	ASSERT_EQ(plane.getDistance(plane2.base()), 1);

	plane2.base()[0] = 0;
	plane2.base()[1] = 1;
	ASSERT_EQ(plane.intersects(plane2), true);
	ASSERT_EQ(plane.getDistance(plane2.base()), 0);

	plane2.base()[0] = 1;
	plane2.base()[1] = 1;
	plane2.normal()[0] = 1;
	plane2.normal()[1] = 1;
	plane2.normal().normalize();
	ASSERT_EQ(plane.intersects(plane2), true);
	ASSERT_APPROX(plane2.getDistance(Vector<T, D>()), static_cast<T>(std::sqrt(2.0f)), static_cast<T>(0.001f));
}

TEST(Hyperplane,intersects)
{
	testIntersectsDistance<float, 2>();
	testIntersectsDistance<float, 3>();
}
