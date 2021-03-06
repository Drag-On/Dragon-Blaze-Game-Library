//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Shape/Shapes.h"
#include "DBGL/Core/Test/Test.h"

using namespace dbgl;
using namespace std;

namespace dbgl_test_hypersphere
{
	template<class T, unsigned int D> void testConstructor()
	{
		HyperSphere<T, D> sphere { };
		Vector<T, D> center = Vector<T, D> { };
		ASSERT_EQ(sphere.center(), center);
		ASSERT_EQ(sphere.radius(), 1);
		center[0] = 1;
		HyperSphere<T, D> sphere2 { center, 2 };
		ASSERT_EQ(sphere2.center(), center);
		ASSERT_EQ(sphere2.radius(), 2);
	}

	template<class T, unsigned int D> void testIntersectsDistance()
	{
		HyperSphere<T, D> sphere { };
		HyperSphere<T, D> sphere2 { };
		HyperPlane<T, D> plane {};
		plane.normal()[0] = 1;
		HyperRectangle<T, D> rect {};
		ASSERT_EQ(sphere.intersects(sphere2), true);
		ASSERT_EQ(sphere.intersects(plane), true);
		ASSERT_EQ(sphere.intersects(rect), true);
		ASSERT_EQ(sphere.getSignedDistance(sphere2), -2);
		ASSERT_EQ(sphere.getSignedDistance(sphere2.center()), -1);
		sphere.center()[0] = 1;
		plane.base()[0] = 10;
		ASSERT_EQ(sphere.intersects(sphere2), true);
		ASSERT_EQ(sphere.intersects(plane), false);
		ASSERT_EQ(sphere.intersects(rect), true);
		ASSERT_EQ(sphere.getSignedDistance(sphere2), -1);
		ASSERT_EQ(sphere.getSignedDistance(sphere2.center()), 0);
		sphere.center()[0] = 2;
		plane.base()[0] = 0;
		ASSERT_EQ(sphere.intersects(sphere2), true);
		ASSERT_EQ(sphere.intersects(plane), false);
		ASSERT_EQ(sphere.intersects(rect), true);
		ASSERT_EQ(sphere.getSignedDistance(sphere2), 0);
		ASSERT_EQ(sphere.getSignedDistance(sphere2.center()), 1);
		sphere.center()[0] = 2.1f;
		plane.base()[0] = 1;
		plane.base()[1] = 1;
		plane.normal()[0] = 1;
		plane.normal()[1] = 1;
		plane.normal().normalize();
		rect.pos()[0] = 1;
		rect.pos()[1] = 1;
		ASSERT_EQ(sphere.intersects(sphere2), false);
		ASSERT_EQ(sphere.intersects(plane), true);
		ASSERT_EQ(sphere.intersects(rect), false);
		ASSERT_APPROX(sphere.getSignedDistance(sphere2), 0.1f, 0.01f);
		ASSERT_APPROX(sphere.getSignedDistance(sphere2.center()), 1.1f, 0.01f);
	}
}

TEST(HyperSphere,construct)
{
	dbgl_test_hypersphere::testConstructor<float, 2>();
	dbgl_test_hypersphere::testConstructor<float, 3>();
}

TEST(HyperSphere,intersects)
{
	dbgl_test_hypersphere::testIntersectsDistance<float, 2>();
	dbgl_test_hypersphere::testIntersectsDistance<float, 3>();
}
