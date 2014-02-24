//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef QUATERNION_TEST_CPP
#define QUATERNION_TEST_CPP

#include <cstdio>
#include <cassert>
#include "Log/Log.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector4.h"
#include "Math/Tools.h"

using namespace dbgl;

int testQuaternion()
{
    LOG->info("Starting Quaternion test suite...");
    LOG->info("Constructors... ");
    QuatF quat1;
    QuatF quat2 = QuatF(1, 3, -2.5, 0);
    QuatF quat3 = QuatF(Vec3f(1, 0, 0), pi());
    QuatF quat4 = QuatF(Vec3f(pi_2(), pi_4(), 0));
    LOG->info("OK!");
    LOG->info("Methods... ");
    // isUnit
    assert(quat1.isUnit());
    // getMatrix
    assert(quat3.getMatrix() == Mat4f::makeRotationX(pi()));
    // getAngles
    assert(isSimilar(quat4.getAngles()[0], pi_2()));
    assert(isSimilar(quat4.getAngles()[1], pi_4()));
    assert(isSimilar(quat4.getAngles()[2], 0));
    // dot
    assert(isSimilar(quat1.dot(quat2), Vec4f(0,0,0,1) * Vec4f(1, 3, -2.5, 0)));
    LOG->info("OK!");
    LOG->info("Operators... ");
    // =
    auto temp = quat3;
    assert(temp.isSimilar(quat3, 0));
    // +
    assert((quat2 + quat1).isSimilar(QuatF(1, 3, -2.5, 1)));
    // +=
    temp = quat2;
    temp += quat1;
    assert(temp.isSimilar(QuatF(1, 3, -2.5, 1)));
    //-
    assert((quat2 - quat1).isSimilar(QuatF(1, 3, -2.5, -1)));
    // -=
    temp = quat2;
    temp -= quat1;
    assert(temp.isSimilar(QuatF(1, 3, -2.5, -1)));
    // *
    temp = quat2 * 3;
    assert(temp.isSimilar(QuatF(Vec4f(1, 3, -2.5, 0)*3)));
    // *=
    temp = quat2;
    temp *= 3;
    assert(temp.isSimilar(QuatF(Vec4f(1, 3, -2.5, 0)*3)));
    // /
    temp = quat2 / 3;
    assert(temp.isSimilar(QuatF(Vec4f(1, 3, -2.5, 0)/3)));
    // /=
    temp = quat2;
    temp /= 3;
    assert(temp.isSimilar(QuatF(Vec4f(1, 3, -2.5, 0)/3)));
    // - (unary)
    temp = -quat2;
    assert(temp.isSimilar(QuatF(-Vec4f(1, 3, -2.5, 0))));
    // ==
    assert(temp == temp);
    temp = quat2;
    assert(temp == quat2);
    // !=
    assert(temp != quat4);
    // []
    assert(quat2[0] == 1);
    assert(quat2[1] == 3);
    assert(quat2[2] == -2.5);
    assert(quat2[3] == 0);
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
