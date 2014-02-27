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
#include "Math/Utility.h"

using namespace dbgl;

int testQuaternion()
{
    LOG->info("Starting Quaternion test suite...");
    LOG->info("Constructors... ");
    QuatF quat1;
    QuatF quat2 = QuatF(1, 3, -2.5, 0);
    QuatF quat3 = QuatF(Vec3f(1, 0, 0), pi());
    QuatF quat4 = QuatF(Vec3f(pi_2(), pi_4(), 0));
    QuatF quat5 = QuatF(Vec3f(1, 0, 0), Vec3f(0, 1, 0));
    assert(quat5.getAngles().x() == 0);
    assert(quat5.getAngles().y() == 0);
    assert(isSimilar(quat5.getAngles().z(), pi_2()));
    LOG->info("OK!");
    LOG->info("Methods... ");
    // x, y, z, w
    auto temp = quat1;
    temp.x() = 1;
    assert(temp.x() == 1);
    // isUnit
    assert(quat1.isUnit());
    // getMatrix
    assert(quat3.getMatrix() == Mat4f::makeRotationX(pi()));
    // getAngles
    assert(isSimilar(quat4.getAngles()[0], pi_2()));
    assert(isSimilar(quat4.getAngles()[1], pi_4()));
    assert(isSimilar(quat4.getAngles()[2], 0));
    // getSquaredLength
    assert(quat1.getSquaredLength() == 1);
    // getLength
    assert(quat1.getLength() == 1);
    assert(isSimilar(quat2.getLength(), std::sqrt(1*1 + 3*3 +2.5*2.5)));
    assert(isSimilar(quat3.getLength(), std::sqrt(quat3.x()*quat3.x() + quat3.y()*quat3.y() + quat3.z()*quat3.z() + quat3.w()*quat3.w())));
    assert(isSimilar(quat4.getLength(), std::sqrt(quat4.x()*quat4.x() + quat4.y()*quat4.y() + quat4.z()*quat4.z() + quat4.w()*quat4.w())));
    // getNormalized
    assert(isSimilar(quat4.getNormalized().getLength(), 1));
    // normalize
    temp = quat4;
    assert(isSimilar(temp.normalize().getLength(), 1));
    // getConjugated
    assert(isSimilar(quat2.getConjugated().x(), -quat2.x()));
    assert(isSimilar(quat2.getConjugated().y(), -quat2.y()));
    assert(isSimilar(quat2.getConjugated().z(), -quat2.z()));
    assert(isSimilar(quat2.getConjugated().w(), quat2.w()));
    // conjugate
    temp = quat2;
    temp.conjugate();
    assert(isSimilar(temp.x(), -quat2.x()));
    assert(isSimilar(temp.y(), -quat2.y()));
    assert(isSimilar(temp.z(), -quat2.z()));
    assert(isSimilar(temp.w(), quat2.w()));
    // getInverted
    assert((quat2.getInverted() * quat2).isSimilar(QuatF(1,0,0,0)));
    // invert
    temp = quat2;
    temp.invert();
    assert((quat2 * temp).isSimilar(QuatF(1,0,0,0)));
    // dot
    assert(isSimilar(quat1.dot(quat2), Vec4f(0,0,0,1) * Vec4f(1, 3, -2.5, 0)));
    // lerp
    assert(quat1.lerp(quat2, 0) == quat1);
    assert(quat1.lerp(quat2, 1) == quat2);
    assert(quat1.lerp(quat2, 2) == quat2);
    temp = QuatF(Vec3f(1, 0, 0), 0);
    auto temp2 = QuatF(Vec3f(1, 0, 0), pi_2());
    assert(temp.lerp(temp2, 0.5).isSimilar(QuatF(Vec3f(1, 0, 0), pi_4())));
    // slerp
    assert(quat1.slerp(quat2, 0) == quat1);
    assert(quat1.slerp(quat2, 1) == quat2);
    assert(temp.slerp(temp2, 0.5).isSimilar(QuatF(Vec3f(1, 0, 0), pi_4())));
    // rotateTowards
    temp = QuatF(Vec3f(pi_2(), 0, 0));
    temp2 = QuatF(Vec3f(0, 0, 0));
    assert(temp.rotateTowards(temp2, pi_2()).isSimilar(temp2));
    assert(temp2.rotateTowards(temp, pi_4()).isSimilarRot(QuatF(pi_4(), 0, 0)));
    LOG->info("OK!");
    LOG->info("Operators... ");
    // =
    temp = quat3;
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
    // Cast to Matrix4x4<T>
    Mat4f mat = quat1;
    assert(mat.isIdentity());
    // That's it!
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
