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
#include <vector>

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
		Vector<T, D> const& p1 { };
		Vector<T, D> const& p2 { 1, 0 };
		Vector<T, D> const& p3 { 0, 1 };
		Vector<T, D> p4Vec { 0.5, 0.5 };
		if (D > 2)
			p4Vec[2] = std::sqrt(0.5 * 0.5 + 0.5 * 0.5);
		Vector<T, D> const& p4 = p4Vec;
		HyperSphere<T, D> sphere3(p1);
		ASSERT_EQ(sphere3.center(), p1);
		ASSERT_EQ(sphere3.radius(), 0);
		HyperSphere<T, D> sphere4(p1, p2);
		Vector<T, D> temp = { 0.5, 0 };
		ASSERT_EQ(sphere4.center(), temp);
		ASSERT_EQ(sphere4.radius(), 0.5);
		HyperSphere<T, D> sphere5(p1, p2, p3);
		temp[1] = 0.5;
		ASSERT_EQ(sphere5.center(), temp);
		ASSERT_APPROX(sphere5.radius(), (T )std::sqrt(0.5 * 0.5 + 0.5 * 0.5), (T )0.01);
		HyperSphere<T, D> sphere6(p1, p2, p3, p4);
		ASSERT_EQ(sphere6.center(), temp);
		ASSERT_APPROX(sphere5.radius(), (T )std::sqrt(0.5 * 0.5 + 0.5 * 0.5), (T )0.01);
	}

	template<class T, unsigned int D> void testIntersectsDistance()
	{
		HyperSphere<T, D> sphere { };
		HyperSphere<T, D> sphere2 { };
		HyperPlane<T, D> plane { };
		plane.normal()[0] = 1;
		HyperRectangle<T, D> rect { };
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

	std::vector<Vector<float, 2>> points { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0.5, 0.5 } };
	HyperSphere<float, 2> circle(points);
	ASSERT_APPROX(circle.center()[0], 0.5f, 0.01f);
	ASSERT_APPROX(circle.center()[1], 0.5f, 0.01f);
	ASSERT_APPROX(circle.radius(), std::sqrt(2.0f) / 2.0f, 0.01f);

	std::vector<Vector<float, 3>> points2 { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0.5, 0.5, 0 }, { 0, 0, 1 }, { 1, 1,
			1 } };
	HyperSphere<float, 3> sphere(points2);
	ASSERT_APPROX(sphere.center()[0], 0.5f, 0.01f);
	ASSERT_APPROX(sphere.center()[1], 0.5f, 0.01f);
	ASSERT_APPROX(sphere.center()[2], 0.5f, 0.01f);
	ASSERT_APPROX(sphere.radius(), std::sqrt(3.0f) / 2.0f, 0.01f);
}

TEST(HyperSphere,intersects)
{
	dbgl_test_hypersphere::testIntersectsDistance<float, 2>();
	dbgl_test_hypersphere::testIntersectsDistance<float, 3>();
}
