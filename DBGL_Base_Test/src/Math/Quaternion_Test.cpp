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
    LOG->info("OK!");
    LOG->info("Operators... ");

    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
