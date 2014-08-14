//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////


#include <cstdio>
#include "cute.h"
#include <cmath>
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Vector.h"

using namespace dbgl;

namespace VectorTest
{
    void testConstructors()
    {
	Vector<float, 3> vec;
	ASSERT(vec[0] == 0);
	ASSERT(vec[1] == 0);
	ASSERT(vec[2] == 0);
	Vector<float, 4> vec2 = {-1.5f, 3.0f, 15.0f, 0.0f};
	ASSERT(vec2[0] == -1.5f);
	ASSERT(vec2[1] == 3);
	ASSERT(vec2[2] == 15);
	ASSERT(vec2[3] == 0);
	Vector<float, 4> vec3(vec2);
	ASSERT(vec3[0] == -1.5f);
	ASSERT(vec3[1] == 3);
	ASSERT(vec3[2] == 15);
	ASSERT(vec2[3] == 0);
    }

    void testDimensions()
    {
	Vector<float, 5> vec;
	// getDimension()
	ASSERT(vec.getDimension() == 5);
    }

    void testCoordinates()
    {
	Vector<float, 4> vec2(4, -1.5f, 3.0f, 15.0f, 0.0f);
	// x()
	ASSERT(vec2[0] == -1.5);
	// y()
	ASSERT(vec2[1] == 3);
	// z()
	ASSERT(vec2[2] == 15);
    }

    void testLength()
    {
	Vector<float, 4> vec2(4, -1.5f, 3, 15, 0);
	// getSquaredLength()
	ASSERT(vec2.getSquaredLength() == vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2]);
	// getLength()
	ASSERT(
		vec2.getLength()
			== std::sqrt((float )(vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2])));
    }

    void testNormalize()
    {
	Vector<float, 4> vec2(4, -1.5f, 3, 15, 0);

	// getNormalized
	auto temp = vec2.getNormalized();
	ASSERT(temp.getLength() >= 0.99f && temp.getLength() <= 1.01f);
	// normalize
	vec2.normalize();
	ASSERT(vec2.getLength() >= 0.99f && vec2.getLength() <= 1.01f);
    }

    void testCross()
    {
	Vector<float, 4> vec2(4, -1.5f, 3, 15, 0);
	Vector<float, 4> vec3(vec2);

	// cross
	vec3[0] = 1;
	vec3[1] = 1;
	vec3[2] = 0;
	vec2[0] = -1;
	vec2[1] = 1;
	vec2[2] = 0;
	auto temp = vec2.cross(vec3);
	ASSERT(temp[0] == vec2[1] * vec3[2] - vec2[2] * vec3[1]);
	ASSERT(temp[1] == vec2[2] * vec3[3] - vec2[3] * vec3[2]);
	ASSERT(temp[2] == vec2[3] * vec3[0] - vec2[0] * vec3[3]);
	ASSERT(temp[3] == vec2[0] * vec3[1] - vec2[1] * vec3[0]);
    }

    void testIsZero()
    {
	Vector<float, 4> vec;
	Vector<float, 4> vec2(4, -1.5f, 3, 15, 0);

	// isZero
	ASSERT(vec.isZero());
	ASSERT(!vec2.isZero());
    }

    void testGetDataPointer()
    {
	auto test = Vector<float, 4>(4, -3, 2, 37.89, 0);
	// getDataPointer
	for (unsigned int i = 0; i < test.getDimension(); i++)
	    ASSERT(test.getDataPointer()[i] == test[i]);
    }

    void testOperatorAssign()
    {
	Vector<float, 4> vec;
	Vector<float, 4> vec2(4, -1.5f, 3, 15, 0);
	Vector<float, 4> vec3(vec2);

	// =
	vec = vec2;
	for (unsigned int i = 0; i < vec.getDimension(); i++)
	    ASSERT(vec[i] == vec2[i]);
    }

    void testOperatorAdd()
    {
	Vector<float, 4> vec;
	Vector<float, 4> vec2(4, -1.5f, 3.0f, 15.0f, 0.0f);
	Vector<float, 4> vec3(vec2);
	// +
	vec3 = vec + vec2;
	ASSERT(vec3[0] == -1.5);
	ASSERT(vec3[1] == 3);
	ASSERT(vec3[2] == 15);
	// +=
	vec += vec3;
	ASSERT(vec[0] == -1.5);
	ASSERT(vec[1] == 3);
	ASSERT(vec[2] == 15);
    }

    void testOperatorSubtract()
    {
	Vector<float, 4> vec;
	Vector<float, 4> vec2(4, -1.5f, 3.0f, 15.0f, 0.0f);
	Vector<float, 4> vec3(vec2);

	// -
	vec3 = vec - vec2;
	ASSERT(vec3[0] == 1.5);
	ASSERT(vec3[1] == -3);
	ASSERT(vec3[2] == -15);
	// -=
	vec -= vec3;
	ASSERT(vec[0] == -1.5);
	ASSERT(vec[1] == 3);
	ASSERT(vec[2] == 15);
	// -(unary)
	vec = -vec;
	ASSERT(vec[0] == 1.5);
	ASSERT(vec[1] == -3);
	ASSERT(vec[2] == -15);
    }

    void testOperatorEquals()
    {
	Vector<float, 4> vec;
	Vector<float, 4> vec2(4, -1.5f, 3.0f, 15.0f, 0.0f);
	Vector<float, 4> vec3(vec2);

	// ==
	vec2 = vec3;
	ASSERT(vec2 == vec3);
	// !=
	ASSERT(vec != vec2);
	// <
	ASSERT(vec < vec2);
	// >
	ASSERT(vec2 > vec);
	// <=
	ASSERT(vec <= vec2);
	// >=
	ASSERT(vec2 >= vec);
    }

    void testOperatorIndex()
    {
	Vector<float, 4> vec2(4, -1.5f, 3.0f, 15.0f, 0.0f);
	// []
	ASSERT(vec2[0] == vec2[0]);
	ASSERT(vec2[1] == vec2[1]);
    }

    void testOperatorMultiply()
    {
	Vector<float, 4> vec;
	Vector<float, 4> vec2(4, -1.5f, 3.0f, 15.0f, 0.0f);
	Vector<float, 4> vec3(vec2);
	// *
	vec3 = vec3 * 2;
	ASSERT(vec3[0] == -3);
	ASSERT(vec3[1] == 6);
	ASSERT(vec3[2] == 30);
	float dotProd = vec3 * vec;
	ASSERT(dotProd == vec3[0] * vec[0] + vec3[1] * vec[1] + vec3[2] * vec[2]);
	// *=
	vec3 *= 0.5;
	ASSERT(vec3 == vec2);
	vec3 *= vec2;
	ASSERT(vec3[0] == vec3[1] * vec2[0] - vec3[0] * vec2[1]);
	ASSERT(vec3[1] == vec3[2] * vec2[1] - vec3[1] * vec2[2]);
	ASSERT(vec3[2] == vec3[0] * vec2[2] - vec3[2] * vec2[0]);
    }

    void testOperatorDivide()
    {
	Vector<float, 4> vec2(4, -1.5f, 3.0f, 15.0f, 0.0f);
	Vector<float, 4> vec3(vec2);
	// /
	vec3[0] = -3;
	vec3[1] = 6;
	vec3 = vec3 / 2;
	ASSERT(vec3[0] == -1.5);
	ASSERT(vec3[1] == 3);
	// /=
	vec3 /= 0.5;
	ASSERT(vec3[0] == -3);
	ASSERT(vec3[1] == 6);
    }
}

using namespace VectorTest;

cute::suite testVector()
{
    cute::suite s {};
    s.push_back(CUTE(testConstructors));
    s.push_back(CUTE(testDimensions));
    s.push_back(CUTE(testCoordinates));
    s.push_back(CUTE(testLength));
    s.push_back(CUTE(testNormalize));
    s.push_back(CUTE(testCross));
    s.push_back(CUTE(testIsZero));
    s.push_back(CUTE(testGetDataPointer));
    s.push_back(CUTE(testOperatorAssign));
    s.push_back(CUTE(testOperatorAdd));
    s.push_back(CUTE(testOperatorSubtract));
    s.push_back(CUTE(testOperatorEquals));
    s.push_back(CUTE(testOperatorIndex));
    s.push_back(CUTE(testOperatorMultiply));
    s.push_back(CUTE(testOperatorDivide));

    return s;
}
