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
#include "DBGL/Math/Vector4.h"

using namespace dbgl;

namespace Vector4Test
{
    void testConstructors()
    {
	Vector4<float> vec;
	ASSERT(vec[0] == 0);
	ASSERT(vec[1] == 0);
	ASSERT(vec[2] == 0);
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	ASSERT(vec2[0] == -1.5f);
	ASSERT(vec2[1] == 3);
	ASSERT(vec2[2] == 15);
	Vector4<float> vec3(vec2);
	ASSERT(vec3[0] == -1.5f);
	ASSERT(vec3[1] == 3);
	ASSERT(vec3[2] == 15);
    }

    void testDimensions()
    {
	Vector4<float> vec;
	// getDimension()
	ASSERT(vec.getDimension() == 4);
    }

    void testCoordinates()
    {
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	// x()
	ASSERT(vec2.x() == -1.5);
	// y()
	ASSERT(vec2.y() == 3);
	// z()
	ASSERT(vec2.z() == 15);
    }

    void testLength()
    {
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	// getSquaredLength()
	ASSERT(vec2.getSquaredLength() == vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2]);
	// getLength()
	ASSERT(
		vec2.getLength()
			== std::sqrt((float )(vec2[0] * vec2[0] + vec2[1] * vec2[1] + vec2[2] * vec2[2])));
    }

    void testNormalize()
    {
	Vector4<float> vec2(-1.5f, 3, 15, 0);

	// getNormalized
	auto temp = vec2.getNormalized();
	ASSERT(temp.getLength() >= 0.99f && temp.getLength() <= 1.01f);
	// normalize
	vec2.normalize();
	ASSERT(vec2.getLength() >= 0.99f && vec2.getLength() <= 1.01f);
    }

    void testCross()
    {
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	Vector4<float> vec3(vec2);

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
	Vector4<float> vec;
	Vector4<float> vec2(-1.5f, 3, 15, 0);

	// isZero
	ASSERT(vec.isZero());
	ASSERT(!vec2.isZero());
    }

    void testTranslate()
    {
	// translate
	auto test = Vector4<float>(1, 0, -4.11, 0);
	test.translate(-4, 2, 42, 0);
	ASSERT(test == Vector4<float>(-3, 2, 37.89, 0));
    }

    void testGetDataPointer()
    {
	auto test = Vector4<float>(-3, 2, 37.89, 0);
	// getDataPointer
	for (unsigned int i = 0; i < test.getDimension(); i++)
	    ASSERT(test.getDataPointer()[i] == test[i]);
    }

    void testOperatorAssign()
    {
	Vector4<float> vec;
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	Vector4<float> vec3(vec2);

	// =
	vec = vec2;
	for (unsigned int i = 0; i < vec.getDimension(); i++)
	    ASSERT(vec[i] == vec2[i]);
    }

    void testOperatorAdd()
    {
	Vector4<float> vec;
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	Vector4<float> vec3(vec2);
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
	Vector4<float> vec;
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	Vector4<float> vec3(vec2);

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
	Vector4<float> vec;
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	Vector4<float> vec3(vec2);

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
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	// []
	ASSERT(vec2[0] == vec2.x());
	ASSERT(vec2[1] == vec2.y());
    }

    void testOperatorMultiply()
    {
	Vector4<float> vec;
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	Vector4<float> vec3(vec2);
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
	Vector4<float> vec2(-1.5f, 3, 15, 0);
	Vector4<float> vec3(vec2);
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

using namespace Vector4Test;

cute::suite testVector4()
{
    cute::suite s {};
    s.push_back(CUTE(testConstructors));
    s.push_back(CUTE(testDimensions));
    s.push_back(CUTE(testCoordinates));
    s.push_back(CUTE(testLength));
    s.push_back(CUTE(testNormalize));
    s.push_back(CUTE(testCross));
    s.push_back(CUTE(testIsZero));
    s.push_back(CUTE(testTranslate));
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
