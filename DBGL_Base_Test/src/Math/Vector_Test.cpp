//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR_TEST_CPP
#define VECTOR_TEST_CPP

#include <cstdio>
#include "cute.h"
#include <cmath>
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Vector.h"

using namespace dbgl;

int testVector()
{
    LOG.info("Starting Vector test suite...");
    LOG.info("Constructors... ");
    Vector<float, 5> vec;
    ASSERT(vec[0] == 0);
    ASSERT(vec[1] == 0);
    ASSERT(vec[2] == 0);
    ASSERT(vec[3] == 0);
    ASSERT(vec[4] == 0);
    Vector<float, 5> vec2;
    vec2[0] = -1.5f;
    vec2[1] = 3;
    vec2[2] = 15;
    vec2[3] = -9;
    vec2[4] = 10;
    Vector<float, 5> vec3(vec2);
    ASSERT(vec3[0] == -1.5f);
    ASSERT(vec3[1] == 3);
    ASSERT(vec3[2] == 15);
    ASSERT(vec3[3] == -9);
    ASSERT(vec3[4] == 10);
    LOG.info("OK!");
    LOG.info("Methods... ");
    // getDimension()
    ASSERT(vec.getDimension() == 5);
    // getSquaredLength()
    ASSERT(vec2.getSquaredLength() == vec2[0]*vec2[0] + vec2[1]*vec2[1] + vec2[2]*vec2[2] + vec2[3]*vec2[3] + vec2[4]*vec2[4]);
    // getLength()
    ASSERT(vec2.getLength() == std::sqrt((float)(vec2[0]*vec2[0] + vec2[1]*vec2[1] + vec2[2]*vec2[2] + vec2[3]*vec2[3] + vec2[4]*vec2[4])));
    // getNormalized
    auto temp = vec2.getNormalized();
    ASSERT(temp.getLength() >= 0.99f && temp.getLength() <= 1.01f);
    // normalize
    vec2.normalize();
    ASSERT(vec2.getLength() >= 0.99f && vec2.getLength() <= 1.01f);
    // cross
    vec3[0] = 1;
    vec3[1] = 1;
    vec3[2] = 0;
    vec3[3] = 0;
    vec3[4] = 0;
    vec2[0] = -1;
    vec2[1] = 1;
    vec2[2] = 0;
    vec2[3] = 0;
    vec2[4] = 0;
    temp = vec2.cross(vec3);
    ASSERT(temp[0] == vec2[1]*vec3[2] - vec2[2]*vec3[1]);
    ASSERT(temp[1] == vec2[2]*vec3[3] - vec2[3]*vec3[2]);
    ASSERT(temp[2] == vec2[3]*vec3[4] - vec2[4]*vec3[3]);
    ASSERT(temp[3] == vec2[4]*vec3[0] - vec2[0]*vec3[4]);
    ASSERT(temp[4] == vec2[0]*vec3[1] - vec2[1]*vec3[0]);
    // isZero
    ASSERT(vec.isZero());
    ASSERT(!vec2.isZero());
    // getDataPointer
    for(unsigned int i = 0; i < vec.getDimension(); i++)
	ASSERT(vec.getDataPointer()[i] == vec[i]);
    LOG.info("OK!");
    LOG.info("Operators... ");
    vec2[0] = -1.5;
    vec2[1] = 3;
    // =
    vec = vec2;
    ASSERT(vec[0] == -1.5);
    ASSERT(vec[1] == 3);
    // +
    vec3 = vec + vec2;
    ASSERT(vec3[0] == -3);
    ASSERT(vec3[1] == 6);
    // +=
    vec += vec3;
    ASSERT(vec[0] == -4.5);
    ASSERT(vec[1] == 9);
    // -
    vec3 = vec - vec2;
    ASSERT(vec3[0] == -3);
    ASSERT(vec3[1] == 6);
    // -=
    vec -= vec3;
    ASSERT(vec[0] == -1.5);
    ASSERT(vec[1] == 3);
    // -(unary)
    vec = -vec;
    ASSERT(vec[0] == 1.5);
    ASSERT(vec[1] == -3);
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
    // []
//	ASSERT(vec2[0] == vec2.getX());
//	ASSERT(vec2[1] == vec2.getY());
    // *
    vec3 = vec3 * 2;
    ASSERT(vec3[0] == -6);
    ASSERT(vec3[1] == 12);
    float dotProd = vec3 * vec;
    ASSERT(dotProd == vec3[0]*vec[0] + vec3[1]*vec[1]);
    2.0f * vec3;
    // *=
    vec3 *= 0.5;
    ASSERT(vec3[0] == -3);
    ASSERT(vec3[1] == 6);
    vec3 *= vec2;
    ASSERT(vec3[0] == vec3[1]*vec2[0] - vec3[0]*vec2[1]);
    ASSERT(vec3[1] == vec3[0]*vec2[1] - vec3[1]*vec2[0]);
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
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}

#endif
