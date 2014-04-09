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
#include <cassert>
#include <cmath>
#include "System/Log/Log.h"
#include "Math/Vector.h"

using namespace dbgl;

int testVector()
{
    LOG->info("Starting Vector test suite...");
    LOG->info("Constructors... ");
    Vector<float, 5> vec;
    assert(vec[0] == 0);
    assert(vec[1] == 0);
    assert(vec[2] == 0);
    assert(vec[3] == 0);
    assert(vec[4] == 0);
    Vector<float, 5> vec2;
    vec2[0] = -1.5f;
    vec2[1] = 3;
    vec2[2] = 15;
    vec2[3] = -9;
    vec2[4] = 10;
    Vector<float, 5> vec3(vec2);
    assert(vec3[0] == -1.5f);
    assert(vec3[1] == 3);
    assert(vec3[2] == 15);
    assert(vec3[3] == -9);
    assert(vec3[4] == 10);
    LOG->info("OK!");
    LOG->info("Methods... ");
    // getDimension()
    assert(vec.getDimension() == 5);
    // getSquaredLength()
    assert(vec2.getSquaredLength() == vec2[0]*vec2[0] + vec2[1]*vec2[1] + vec2[2]*vec2[2] + vec2[3]*vec2[3] + vec2[4]*vec2[4]);
    // getLength()
    assert(vec2.getLength() == std::sqrt((float)(vec2[0]*vec2[0] + vec2[1]*vec2[1] + vec2[2]*vec2[2] + vec2[3]*vec2[3] + vec2[4]*vec2[4])));
    // getNormalized
    auto temp = vec2.getNormalized();
    assert(temp.getLength() >= 0.99f && temp.getLength() <= 1.01f);
    // normalize
    vec2.normalize();
    assert(vec2.getLength() >= 0.99f && vec2.getLength() <= 1.01f);
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
    assert(temp[0] == vec2[1]*vec3[2] - vec2[2]*vec3[1]);
    assert(temp[1] == vec2[2]*vec3[3] - vec2[3]*vec3[2]);
    assert(temp[2] == vec2[3]*vec3[4] - vec2[4]*vec3[3]);
    assert(temp[3] == vec2[4]*vec3[0] - vec2[0]*vec3[4]);
    assert(temp[4] == vec2[0]*vec3[1] - vec2[1]*vec3[0]);
    // isZero
    assert(vec.isZero());
    assert(!vec2.isZero());
    // getDataPointer
    for(unsigned int i = 0; i < vec.getDimension(); i++)
	assert(vec.getDataPointer()[i] == vec[i]);
    LOG->info("OK!");
    LOG->info("Operators... ");
    vec2[0] = -1.5;
    vec2[1] = 3;
    // =
    vec = vec2;
    assert(vec[0] == -1.5);
    assert(vec[1] == 3);
    // +
    vec3 = vec + vec2;
    assert(vec3[0] == -3);
    assert(vec3[1] == 6);
    // +=
    vec += vec3;
    assert(vec[0] == -4.5);
    assert(vec[1] == 9);
    // -
    vec3 = vec - vec2;
    assert(vec3[0] == -3);
    assert(vec3[1] == 6);
    // -=
    vec -= vec3;
    assert(vec[0] == -1.5);
    assert(vec[1] == 3);
    // -(unary)
    vec = -vec;
    assert(vec[0] == 1.5);
    assert(vec[1] == -3);
    // ==
    vec2 = vec3;
    assert(vec2 == vec3);
    // !=
    assert(vec != vec2);
    // <
    assert(vec < vec2);
    // >
    assert(vec2 > vec);
    // <=
    assert(vec <= vec2);
    // >=
    assert(vec2 >= vec);
    // []
//	assert(vec2[0] == vec2.getX());
//	assert(vec2[1] == vec2.getY());
    // *
    vec3 = vec3 * 2;
    assert(vec3[0] == -6);
    assert(vec3[1] == 12);
    float dotProd = vec3 * vec;
    assert(dotProd == vec3[0]*vec[0] + vec3[1]*vec[1]);
    2.0f * vec3;
    // *=
    vec3 *= 0.5;
    assert(vec3[0] == -3);
    assert(vec3[1] == 6);
    vec3 *= vec2;
    assert(vec3[0] == vec3[1]*vec2[0] - vec3[0]*vec2[1]);
    assert(vec3[1] == vec3[0]*vec2[1] - vec3[1]*vec2[0]);
    // /
    vec3[0] = -3;
    vec3[1] = 6;
    vec3 = vec3 / 2;
    assert(vec3[0] == -1.5);
    assert(vec3[1] == 3);
    // /=
    vec3 /= 0.5;
    assert(vec3[0] == -3);
    assert(vec3[1] == 6);
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
