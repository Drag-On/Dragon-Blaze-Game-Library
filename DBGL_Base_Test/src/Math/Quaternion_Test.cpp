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
#include "cute.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Quaternion.h"
#include "DBGL/Math/Matrix4x4.h"
#include "DBGL/Math/Vector4.h"
#include "DBGL/Math/Utility.h"

using namespace dbgl;

int testQuaternion()
{
    LOG.info("Starting Quaternion test suite...");
    LOG.info("Constructors... ");
    QuatF quat1;
    QuatF quat2 = QuatF(1, 3, -2.5, 0);
    QuatF quat3 = QuatF(Vec3f(1, 0, 0), pi_2());
    QuatF quat4 = QuatF(Vec3f(pi_2(), pi_4(), 0));
    QuatF quat5 = QuatF(Vec3f(1, 0, 0), Vec3f(0, 1, 0));
    QuatF quat6 = QuatF(Vec3f(1, 0, 0), Vec3f(1, 1, 0), Vec3f(1, 1, 0).cross(Vec3f(1, 0, 0)));
    ASSERT(quat5.getAngles().x() == 0);
    ASSERT(quat5.getAngles().y() == 0);
    ASSERT(isSimilar(quat5.getAngles().z(), (float)pi_2()));
    ASSERT((quat5 * Vec3f(1, 0, 0)).isSimilar(Vec3f(0, 1, 0)));
    ASSERT((quat5 * Vec3f(0, 1, 0)).isSimilar(Vec3f(-1, 0, 0)));
    ASSERT((quat5 * Vec3f(1, 1, 0)).isSimilar(Vec3f(-1, 1, 0)));
    ASSERT((quat6 * Vec3f(1, 0, 0)).isSimilar(Vec3f(1, 1, 0).normalize()));
    ASSERT((quat6 * Vec3f(0, 1, 0)).isSimilar(Vec3f(1, 1, 0).cross(Vec3f(1, 0, 0).normalize())));
    LOG.info("OK!");
    LOG.info("Methods... ");
    // x, y, z, w
    auto temp = quat1;
    temp.x() = 1;
    ASSERT(temp.x() == 1);
    // fromVectors
    temp.fromVectors(Vec3f(0.3, -1.1, 0.5), Vec3f(-0.1, 1, 0.7));
    ASSERT((temp * Vec3f(0.3, -1.1, 0.5).normalize()).isSimilar(Vec3f(-0.1, 1, 0.7).normalize()));
    temp.fromVectors(Vec3f(1, 0, 0), Vec3f(1, 0, 1), Vec3f(0, 1, 0));
    ASSERT((temp * Vec3f(1, 0, 0).normalize()).isSimilar(Vec3f(1, 0, 1).normalize()));
    ASSERT((temp * Vec3f(0, 1, 0).normalize()).isSimilar(Vec3f(0, 1, 0).normalize()));
    temp.fromVectors(Vec3f(1, 0, 0), Vec3f(-1, 0, 0));
    ASSERT((temp * Vec3f(1, 0, 0)).isSimilar(Vec3f(-1, 0, 0)));
    // isUnit
    ASSERT(quat1.isUnit());
    ASSERT(!quat2.isUnit());
    // getMatrix
    ASSERT((Mat4f::makeRotationX(pi_2()) * Vec4f(0, 1, 0, 0)).isSimilar(quat3.getMatrix() * Vec4f(0, 1, 0, 0)));
    ASSERT((Mat4f::makeRotation(pi_2(), pi_4(), 0) * Vec4f(0, 0, 1, 0)).isSimilar(quat4.getMatrix() * Vec4f(0, 0, 1, 0)));
    ASSERT((Mat4f::makeRotationZ(pi_2()) * Vec4f(0, 1, 0, 0)).isSimilar(quat5.getMatrix() * Vec4f(0, 1, 0, 0)));
    // getAngles
    ASSERT(isSimilar(quat4.getAngles()[0], (float) pi_2()));
    ASSERT(isSimilar(quat4.getAngles()[1], (float)pi_4()));
    ASSERT(isSimilar(quat4.getAngles()[2], 0.0f));
    // getSquaredLength
    ASSERT(quat1.getSquaredLength() == 1);
    // getLength
    ASSERT(quat1.getLength() == 1);
    ASSERT(isSimilar(quat2.getLength(), (float) std::sqrt(1*1 + 3*3 +2.5*2.5)));
    ASSERT(isSimilar(quat3.getLength(), std::sqrt(quat3.x()*quat3.x() + quat3.y()*quat3.y() + quat3.z()*quat3.z() + quat3.w()*quat3.w())));
    ASSERT(isSimilar(quat4.getLength(), std::sqrt(quat4.x()*quat4.x() + quat4.y()*quat4.y() + quat4.z()*quat4.z() + quat4.w()*quat4.w())));
    // getNormalized
    ASSERT(isSimilar(quat4.getNormalized().getLength(), 1.0f));
    // normalize
    temp = quat4;
    ASSERT(isSimilar(temp.normalize().getLength(), 1.0f));
    // getConjugated
    ASSERT(isSimilar(quat2.getConjugated().x(), -quat2.x()));
    ASSERT(isSimilar(quat2.getConjugated().y(), -quat2.y()));
    ASSERT(isSimilar(quat2.getConjugated().z(), -quat2.z()));
    ASSERT(isSimilar(quat2.getConjugated().w(), quat2.w()));
    // conjugate
    temp = quat2;
    temp.conjugate();
    ASSERT(isSimilar(temp.x(), -quat2.x()));
    ASSERT(isSimilar(temp.y(), -quat2.y()));
    ASSERT(isSimilar(temp.z(), -quat2.z()));
    ASSERT(isSimilar(temp.w(), quat2.w()));
    // getInverted
    ASSERT((quat2.getInverted() * quat2).isSimilar(QuatF(0,0,0,1)));
    // invert
    temp = quat2;
    temp.invert();
    ASSERT((quat2 * temp).isSimilar(QuatF(0,0,0,1)));
    // dot
    ASSERT(isSimilar(quat1.dot(quat2), Vec4f(0,0,0,1) * Vec4f(1, 3, -2.5, 0)));
    // lerp
    ASSERT(quat1.lerp(quat2, 0) == quat1);
    ASSERT(quat1.lerp(quat2, 1) == quat2);
    ASSERT(quat1.lerp(quat2, 2) == quat2);
    temp = QuatF(Vec3f(1, 0, 0), 0);
    auto temp2 = QuatF(Vec3f(1, 0, 0), pi_2());
    ASSERT(temp.lerp(temp2, 0.5).isSimilar(QuatF(Vec3f(1, 0, 0), pi_4())));
    // slerp
    ASSERT(quat1.slerp(quat2, 0) == quat1);
    ASSERT(quat1.slerp(quat2, 1) == quat2);
    ASSERT(temp.slerp(temp2, 0.5).isSimilar(QuatF(Vec3f(1, 0, 0), pi_4())));
    // rotateTowards
    temp = QuatF(Vec3f(pi_2(), 0, 0));
    temp2 = QuatF(Vec3f(0, 0, 0));
    ASSERT(temp.rotateTowards(temp2, pi_2()).isSimilar(temp2));
    ASSERT(temp2.rotateTowards(temp, pi_4()).isSimilarRot(QuatF(pi_4(), 0, 0)));
    LOG.info("OK!");
    LOG.info("Operators... ");
    // =
    temp = quat3;
    ASSERT(temp.isSimilar(quat3, 0));
    // +
    ASSERT((quat2 + quat1).isSimilar(QuatF(1, 3, -2.5, 1)));
    // +=
    temp = quat2;
    temp += quat1;
    ASSERT(temp.isSimilar(QuatF(1, 3, -2.5, 1)));
    //-
    ASSERT((quat2 - quat1).isSimilar(QuatF(1, 3, -2.5, -1)));
    // -=
    temp = quat2;
    temp -= quat1;
    ASSERT(temp.isSimilar(QuatF(1, 3, -2.5, -1)));
    // *
    temp = quat2 * 3;
    ASSERT(temp.isSimilar(QuatF(Vec4f(1, 3, -2.5, 0)*3)));
    // *=
    temp = quat2;
    temp *= 3;
    ASSERT(temp.isSimilar(QuatF(Vec4f(1, 3, -2.5, 0)*3)));
    // /
    temp = quat2 / 3;
    ASSERT(temp.isSimilar(QuatF(Vec4f(1, 3, -2.5, 0)/3)));
    // /=
    temp = quat2;
    temp /= 3;
    ASSERT(temp.isSimilar(QuatF(Vec4f(1, 3, -2.5, 0)/3)));
    // - (unary)
    temp = -quat2;
    ASSERT(temp.isSimilar(QuatF(-Vec4f(1, 3, -2.5, 0))));
    // ==
    ASSERT(temp == temp);
    temp = quat2;
    ASSERT(temp == quat2);
    // !=
    ASSERT(temp != quat4);
    // Cast to Matrix4x4<T>
    Mat4f mat = quat1;
    ASSERT(mat.isIdentity());
    // That's it!
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}

#endif
