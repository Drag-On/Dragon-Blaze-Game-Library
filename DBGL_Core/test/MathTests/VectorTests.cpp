//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Math/Vector.h"
#include "DBGL/Core/Math/Vector2.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Math/Vector4.h"
#include "DBGL/Core/Math/Utility.h"

using namespace dbgl;
using namespace std;

const float numbers[] = {-1.5f, 1.0f, 0.256f, 25.0f, -100.38585f, 0.00001f, 42.1337f, 571, 43.495f};

template <class Vec> void testConstructor()
{
    Vec vec;
    for(unsigned int i = 0; i < vec.getDimension(); i++)
	ASSERT_EQ(vec[i], 0);
}

TEST(Vector,construct)
{
    testConstructor<Vec2f>();
    testConstructor<Vec3f>();
    testConstructor<Vec4f>();
}

template<class Vec> void testCoordinates()
{
    Vec vec;
    for(unsigned int i = 0; i< vec.getDimension(); i++)
	vec[i] = numbers[i];
    for(unsigned int i = 0; i< vec.getDimension(); i++)
	ASSERT_EQ(vec[i], numbers[i]);
}

TEST(Vector,directaccess)
{
    testCoordinates<Vec2f>();
    testCoordinates<Vec3f>();
    testCoordinates<Vec4f>();
}

template<class Vec> void testLength()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];
    // getSquaredLength()
    auto sqLen = 0.0;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	sqLen += vec[i] * vec[i];
    ASSERT(dbgl::isSimilar(vec.getSquaredLength(), (float)sqLen));
    // getLength()
    ASSERT(dbgl::isSimilar(vec.getLength(), (float)std::sqrt(sqLen)));
}

TEST(Vector,length)
{
    testLength<Vec2f>();
    testLength<Vec3f>();
    testLength<Vec4f>();
}

template<class Vec> void testNormalize()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];

    // getNormalized
    auto temp = vec.getNormalized();
    ASSERT(dbgl::isSimilar(temp.getLength(), 1.0f));
    // normalize
    vec.normalize();
    ASSERT(dbgl::isSimilar(vec.getLength(), 1.0f));
}

TEST(Vector,normalize)
{
    testNormalize<Vec2f>();
    testNormalize<Vec3f>();
    testNormalize<Vec4f>();
}

template<class Vec> void testCross()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];
    Vec vec2;
    for (unsigned int i = vec.getDimension(); i < vec2.getDimension(); i++)
	vec2[i] = numbers[i];

    auto temp = vec.cross(vec2);
    ASSERT_EQ(temp.getDimension(), vec.getDimension());
    for(unsigned int i = 0; i < temp.getDimension(); i++)
    {
	unsigned int i1 = i+1;
	unsigned int i2 = i+2;
	if(i2 >= temp.getDimension())
	    i2 -= temp.getDimension();
	if(i1 >= temp.getDimension())
	    i1 -= temp.getDimension();
	ASSERT(dbgl::isSimilar(temp[i], vec[i1] * vec2[i2] - vec[i2] * vec2[i1]));
    }
}

TEST(Vector,cross)
{
    testCross<Vec2f>();
    testCross<Vec3f>();
    testCross<Vec4f>();
}

template<class Vec> void testIsZero()
{
    Vec vec;
    Vec vec2;
    for (unsigned int i = 0; i < vec2.getDimension(); i++)
	vec2[i] = numbers[i];

    // isZero
    ASSERT(vec.isZero());
    ASSERT(!vec2.isZero());
}

TEST(Vector,isZero)
{
    testIsZero<Vec2f>();
    testIsZero<Vec3f>();
    testIsZero<Vec4f>();
}

template<class Vec> void testGetDataPointer()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	ASSERT(vec.getDataPointer()[i] == vec[i]);
}

TEST(Vector,getDataPointer)
{
    testGetDataPointer<Vec2f>();
    testGetDataPointer<Vec3f>();
    testGetDataPointer<Vec4f>();
}

template<class Vec> void testOperatorAssign()
{
    Vec vec;
    Vec vec2;
    for (unsigned int i = 0; i < vec2.getDimension(); i++)
	vec2[i] = numbers[i];

    vec = vec2;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	ASSERT_EQ(vec[i], vec2[i]);
}

TEST(Vector,operatorAssign)
{
    testOperatorAssign<Vec2f>();
    testOperatorAssign<Vec3f>();
    testOperatorAssign<Vec4f>();
}

template<class Vec> void testOperatorAdd()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];
    Vec vec2;
    for (unsigned int i = vec.getDimension(); i < vec2.getDimension(); i++)
	vec2[i] = numbers[i];
    // +
    auto vec3 = vec + vec2;
    for (unsigned int i = 0; i < vec3.getDimension(); i++)
	ASSERT(vec3[i] == vec[i] + vec2[i]);
    // +=
    Vec copy{vec};
    vec += vec3;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	ASSERT(vec[i] == copy[i] + vec3[i]);
}

TEST(Vector,operatorAdd)
{
    testOperatorAdd<Vec2f>();
    testOperatorAdd<Vec3f>();
    testOperatorAdd<Vec4f>();
}

template<class Vec> void testOperatorSubtract()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];
    Vec vec2;
    for (unsigned int i = vec.getDimension(); i < vec2.getDimension(); i++)
	vec2[i] = numbers[i];

    // -
    auto vec3 = vec - vec2;
    for (unsigned int i = 0; i < vec3.getDimension(); i++)
	ASSERT(vec3[i] == vec[i] - vec2[i]);
    // -=
    Vec copy{vec};
    vec -= vec3;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	ASSERT(vec[i] == copy[i] - vec3[i]);
    // -(unary)
    copy = vec;
    vec = -vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	ASSERT(vec[i] == -copy[i]);
}

TEST(Vector,operatorSubtract)
{
    testOperatorSubtract<Vec2f>();
    testOperatorSubtract<Vec3f>();
    testOperatorSubtract<Vec4f>();
}

template<class Vec> void testOperatorComparison()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];
    Vec vec2;
    for (unsigned int i = vec.getDimension(); i < vec2.getDimension(); i++)
	vec2[i] = numbers[i];

    // ==
    auto vec3 = vec2;
    ASSERT(vec2 == vec3);
    // !=
    ASSERT(vec != vec2);
    // < <= > >=
    ASSERT(vec < vec2 || vec >= vec2);
    ASSERT(vec > vec2 || vec <= vec2);
}

TEST(Vector,operatorComparison)
{
    testOperatorComparison<Vec2f>();
    testOperatorComparison<Vec3f>();
    testOperatorComparison<Vec4f>();
}

template<class Vec> void testOperatorMultiply()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];
    Vec vec2;
    for (unsigned int i = vec.getDimension(); i < vec2.getDimension(); i++)
	vec2[i] = numbers[i];

    // *
    auto vec3 = vec2 * 2;
    for (unsigned int i = 0; i < vec3.getDimension(); i++)
	ASSERT(vec3[i] == vec2[i] * 2);
    float dotProd = 0;
    for (unsigned int i = 0; i < vec3.getDimension(); i++)
	dotProd += vec2[i] * vec[i];
    ASSERT(vec2 * vec == dotProd);
    // *=
    Vec copy{vec2};
    vec2 *= 0.5;
    for (unsigned int i = 0; i < vec2.getDimension(); i++)
	ASSERT(vec2[i] == copy[i] * 0.5);
    copy = vec;
    vec *= vec2;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	ASSERT(vec[i] == copy[i] * vec2[i]);
}

TEST(Vector,operatorMultiply)
{
    testOperatorMultiply<Vec2f>();
    testOperatorMultiply<Vec3f>();
    testOperatorMultiply<Vec4f>();
}

template<class Vec> void testOperatorDivide()
{
    Vec vec;
    for (unsigned int i = 0; i < vec.getDimension(); i++)
	vec[i] = numbers[i];
    Vec vec2;
    for (unsigned int i = vec.getDimension(); i < vec2.getDimension(); i++)
	vec2[i] = numbers[i];

    // /
    auto vec3 = vec2 / 2;
    for (unsigned int i = 0; i < vec3.getDimension(); i++)
	ASSERT(vec3[i] == vec2[i] / 2);
    // /=
    Vec copy{vec2};
    vec2 /= 0.5;
    for (unsigned int i = 0; i < vec2.getDimension(); i++)
	ASSERT(vec2[i] == copy[i] / 0.5);
}

TEST(Vector,operatorDivide)
{
    testOperatorDivide<Vec2f>();
    testOperatorDivide<Vec3f>();
    testOperatorDivide<Vec4f>();
}
