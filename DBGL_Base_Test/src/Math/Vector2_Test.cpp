//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR2_TEST_CPP
#define VECTOR2_TEST_CPP

#include <cstdio>
#include <cmath>
#include "cute.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Vector2.h"

using namespace dbgl;

void testConstructor()
{
    Vector2<float> vec;
    ASSERT(vec[0] == 0);
    ASSERT(vec[1] == 0);
    Vector2<float> vec2(-1.5f, 3);
    ASSERT(vec2[0] == -1.5f);
    ASSERT(vec2[1] == 3);
    Vector2<float> vec3(vec2);
    ASSERT(vec3[0] == -1.5f);
    ASSERT(vec3[1] == 3);
    Vector2<char> vec4(42, 100);
    ASSERT(vec4[0] == 42);
    ASSERT(vec4[1] == 100);
    Vector2<short> vec5(1, -5);
    ASSERT(vec5[0] == 1);
    ASSERT(vec5[1] == -5);
    Vector2<double> vec6(23.444, 3.141);
    ASSERT(vec6[0] == 23.444);
    ASSERT(vec6[1] == 3.141);
}

void testGetDimension()
{
    Vector2<float> vec;
    // getDimension()
    ASSERT(vec.getDimension() == 2);
}

void testCoords()
{
    Vector2<float> vec2(-1.5f, 3);
    // x()
    ASSERT(vec2.x() == -1.5);
    // y()
    ASSERT(vec2.y() == 3);
}

void testLength()
{
    Vector2<float> vec2(-1.5f, 3);
    // getSquaredLength()
    ASSERT(vec2.getSquaredLength() == vec2[0] * vec2[0] + vec2[1] * vec2[1]);
    // getLength()
    ASSERT(vec2.getLength() == std::sqrt((float )(vec2[0] * vec2[0] + vec2[1] * vec2[1])));
}

void testNormalize()
{
    Vector2<float> vec2(-1.5f, 3);
    // getNormalized
    auto temp = vec2.getNormalized();
    ASSERT(temp.getLength() >= 0.99f && temp.getLength() <= 1.01f);
    // normalize
    vec2.normalize();
    ASSERT(vec2.getLength() >= 0.99f && vec2.getLength() <= 1.01f);
}

void testCross()
{
    Vector2<float> vec2(-1.5f, 3);
    Vector2<float> vec3(vec2);
    // cross
    vec3[0] = -1;
    auto temp = vec2.cross(vec3);
    ASSERT(temp[0] == vec2[1] * vec3[0] - vec2[0] * vec3[1]);
    ASSERT(temp[1] == vec2[0] * vec3[1] - vec2[1] * vec3[0]);
}

void testIsZero()
{
    Vector2<float> vec;
    Vector2<float> vec2(-1.5f, 3);
    // isZero
    ASSERT(vec.isZero());
    ASSERT(!vec2.isZero());
}

void testTranslate()
{
    // translate
    auto test = Vector2<float>(1, 0);
    test.translate(-4, 2);
    ASSERT(test == Vector2<float>(-3, 2));
}

void testDataPointer()
{
    auto test = Vector2<float>(1, 0);
    // getDataPointer
    for (unsigned int i = 0; i < test.getDimension(); i++)
	ASSERT(test.getDataPointer()[i] == test[i]);
}

void testOperatorAssign()
{
    Vector2<float> vec2(-1.5f, 3);
    Vector2<float> vec3(vec2);
    // =
    auto vec = vec2;
    ASSERT(vec[0] == -1.5);
    ASSERT(vec[1] == 3);
}

void testOperatorPlus()
{
    Vector2<float> vec2(-1.5f, 3);
    Vector2<float> vec3(vec2);
    auto vec = vec2;
    // +
    vec3 = vec + vec2;
    ASSERT(vec3[0] == -3);
    ASSERT(vec3[1] == 6);
    // +=
    vec += vec3;
    ASSERT(vec[0] == -4.5);
    ASSERT(vec[1] == 9);
}

void testOperatorMinus()
{
    Vector2<float> vec2(-1.5f, 3);
    Vector2<float> vec3(vec2);
    auto vec = vec2;
    // -
    vec3 = vec - vec2;
    ASSERT(vec3[0] == 0);
    ASSERT(vec3[1] == 0);
    // -=
    vec -= vec3;
    ASSERT(vec[0] == -1.5);
    ASSERT(vec[1] == 3);
    // -(unary)
    vec = -vec;
    ASSERT(vec[0] == 1.5);
    ASSERT(vec[1] == -3);
}

void testOperatorEqual()
{
    Vector2<float> vec(3, 1);
    Vector2<float> vec2(-1.5f, 3);
    Vector2<float> vec3(vec2);
    // ==
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
    Vector2<float> vec2(-1.5f, 3);
    Vector2<float> vec3(vec2);
    auto vec = vec2;
    // []
    ASSERT(vec2[0] == vec2.x());
    ASSERT(vec2[1] == vec2.y());
}

void testOperatorMultiply()
{
    Vector2<float> vec2(-1.5f, 3);
    Vector2<float> vec3(vec2);
    auto vec = vec2;
    // *
    vec3 = vec3 * 2;
    ASSERT(vec3[0] == -3);
    ASSERT(vec3[1] == 6);
    float dotProd = vec3 * vec;
    ASSERT(dotProd == vec3[0] * vec[0] + vec3[1] * vec[1]);
    // *=
    vec3 *= 0.5;
    ASSERT(vec3 == vec2);
    vec3 *= vec2;
    ASSERT(vec3[0] == vec3[1] * vec2[0] - vec3[0] * vec2[1]);
    ASSERT(vec3[1] == vec3[0] * vec2[1] - vec3[1] * vec2[0]);
}

void testOperatorDivide()
{
    Vector2<float> vec2(-1.5f, 3);
    Vector2<float> vec3(vec2);
    auto vec = vec2;
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

cute::suite testVector2()
{
    cute::suite s {};
    s.push_back(CUTE(testConstructor));
    s.push_back(CUTE(testGetDimension));
    s.push_back(CUTE(testCoords));
    s.push_back(CUTE(testLength));
    s.push_back(CUTE(testNormalize));
    s.push_back(CUTE(testCross));
    s.push_back(CUTE(testIsZero));
    s.push_back(CUTE(testTranslate));
    s.push_back(CUTE(testDataPointer));
    s.push_back(CUTE(testOperatorAssign));
    s.push_back(CUTE(testOperatorPlus));
    s.push_back(CUTE(testOperatorMinus));
    s.push_back(CUTE(testOperatorEqual));
    s.push_back(CUTE(testOperatorIndex));
    s.push_back(CUTE(testOperatorMultiply));
    s.push_back(CUTE(testOperatorDivide));

    return s;
}

#endif
