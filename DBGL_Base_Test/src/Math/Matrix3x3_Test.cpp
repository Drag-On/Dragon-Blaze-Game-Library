//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX3_TEST_CPP
#define MATRIX3_TEST_CPP

#include <cstdio>
#include "cute.h"
#include <cmath>
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Matrix3x3.h"
#include "DBGL/Math/Vector3.h"

using namespace dbgl;

int testMatrix3x3()
{
    LOG.info("Starting Matrix3x3 test suite...");
    LOG.info("Constructors... ");
    // Default
    Matrix3x3<float> mat;
    ASSERT(mat[0][0] == 1);
    ASSERT(mat[0][1] == 0);
    ASSERT(mat[1][0] == 0);
    ASSERT(mat[1][1] == 1);
    // Copy
    Matrix3x3<float> mat2;
    mat2[0][0] = 3;
    mat2[0][1] = 2;
    Matrix3x3<float> mat3(mat2);
    ASSERT(mat3[0][0] == 3 && mat3[0][1] == 2);
    LOG.info("OK!");
    LOG.info("Methods... ");
    // getWidth / height
    ASSERT(mat.getWidth() == 3);
    ASSERT(mat.getHeight() == 3);
    // transpose
    auto temp = Matrix3x3<float>(mat3);
    temp.transpose();
    ASSERT(temp[0][0] == mat3[0][0] && temp[0][1] == mat3[1][0] && temp[1][0] == mat3[0][1] && temp[1][1] == mat3[1][1]);
    // getTransposed
    ASSERT(temp.getTransposed() == mat3);
    // invert
    temp = mat3;
    mat3.invert();
    temp = temp * mat3;
    ASSERT(temp.isIdentity());
    // getInverted
    temp = mat3.getInverted() * mat3;
    ASSERT(temp.isIdentity());
    // isZero
    ASSERT(!mat.isZero());
    // isIdentity
    ASSERT(mat.isIdentity());
    // getDataPointer
    for(int i = 0; i < mat3.getWidth() * mat3.getHeight(); i++)
    {
	ASSERT(mat3.getDataPointer()[i] == mat3[i / mat3.getWidth()][i % mat3.getWidth()]);
    }
    // makeRotationX
    Vector3<float> testVec(0, 1, 0);
    auto res = (Matrix3x3<float>::makeRotationX(1.57079633f) * testVec);// 90°
    ASSERT(std::abs(res[0] - 0) <= 0.01);
    ASSERT(std::abs(res[1] - 0) <= 0.01);
    ASSERT(std::abs(res[2] - 1) <= 0.01);
    // makeRotationY
    testVec[0] = 1;
    testVec[1] = 0;
    res = (Matrix3x3<float>::makeRotationY(1.57079633f) * testVec);// 90°
    ASSERT(std::abs(res[0] - 0) <= 0.01);
    ASSERT(std::abs(res[1] - 0) <= 0.01);
    ASSERT(std::abs(res[2] + 1) <= 0.01);
    // makeRotationZ
    res = (Matrix3x3<float>::makeRotationZ(1.57079633f) * testVec);// 90°
    ASSERT(std::abs(res[0] - 0) <= 0.01);
    ASSERT(std::abs(res[1] - 1) <= 0.01);
    ASSERT(std::abs(res[2] - 0) <= 0.01);
    // makeRotation
    res = (Matrix3x3<float>::makeRotation(Vector3<float>(0, 1, 0), 1.57079633f) * testVec);// 90°
    ASSERT(std::abs(res[0] - 0) <= 0.01);
    ASSERT(std::abs(res[1] - 0) <= 0.01);
    ASSERT(std::abs(res[2] + 1) <= 0.01);
    ASSERT(Matrix3x3<float>::makeRotation(Vector3<float>(1, 0, 0), 1) == Matrix3x3<float>::makeRotationX(1));
    ASSERT(Matrix3x3<float>::makeRotation(Vector3<float>(0, 1, 0), 1) == Matrix3x3<float>::makeRotationY(1));
    ASSERT(Matrix3x3<float>::makeRotation(Vector3<float>(0, 0, 1), 1) == Matrix3x3<float>::makeRotationZ(1));
    res = (Matrix3x3<float>::makeRotation(Vector3<float>(0, 1, 0), 1.57079633f) * Vector3<float>(1, 1, 0));// 90°
    ASSERT(std::abs(res[0] - 0) <= 0.01);
    ASSERT(std::abs(res[1] - 1) <= 0.01);
    ASSERT(std::abs(res[2] + 1) <= 0.01);
    res = (Matrix3x3<float>::makeRotation(Vector3<float>(1, 1, 0), 1.57079633f) * testVec);// 90°
    ASSERT(std::abs(res[0] - 0.5) <= 0.01);
    ASSERT(std::abs(res[1] - 0.5) <= 0.01);
    ASSERT(std::abs(res[2] + 0.7) <= 0.01);
    // makeScale
    res = (Mat3f::makeScale(2) * Vec3f(1, 0, 0));
    ASSERT(std::abs(res[0] - 2) <= 0.01);
    ASSERT(std::abs(res[1] - 0) <= 0.01);
    ASSERT(std::abs(res[2] - 0) <= 0.01);
    res = (Mat3f::makeScale(2, 0.5, -3) * Vec3f(1, 1, -2));
    ASSERT(std::abs(res[0] - 2) <= 0.01);
    ASSERT(std::abs(res[1] - 0.5) <= 0.01);
    ASSERT(std::abs(res[2] - 6) <= 0.01);
    LOG.info("OK!");
    LOG.info("Operators... ");
    // =
    mat = mat2;
    ASSERT(mat == mat2);
    // +
    temp = mat + mat2;
    ASSERT(temp[0] == mat[0] + mat2[0] && temp[1] == mat[1] + mat2[1]);
    // +=
    mat += temp;
    ASSERT(mat[0] == temp[0] + mat2[0] && mat[1] == temp[1] + mat2[1]);
    // -
    temp = mat - mat2;
    ASSERT(temp[0] == mat[0] - mat2[0] && temp[1] == mat[1] - mat2[1]);
    // -=
    mat = mat2;
    mat -= temp;
    ASSERT(mat[0] == mat2[0] - temp[0] && mat[1] == mat2[1] - temp[1]);
    // *
    temp = mat * mat2;
    ASSERT(temp[0][0] == mat.getTransposed()[0] * mat2[0]);
    ASSERT(temp[1][0] == mat.getTransposed()[0] * mat2[1]);
    ASSERT(temp[0][1] == mat.getTransposed()[1] * mat2[0]);
    ASSERT(temp[1][1] == mat.getTransposed()[1] * mat2[1]);
    Vector3<float> vec(1, -2.5, 0);
    mat3 = Matrix3x3<float>();
    ASSERT((mat3 * vec)[0] == 1 && (mat3 * vec)[1] == -2.5);
    mat3[0][0] = 2;
    ASSERT((mat3 * vec)[0] == mat3.getTransposed()[0] * vec);
    ASSERT((mat3 * 2.0f)[0][0] == 4);
    // *=
    mat *= mat2;
    ASSERT(mat == temp);
    // /
    ASSERT((mat3 / 2.0f)[0][0] == 1);
    // /=
    mat3 /= 2;
    ASSERT(mat3[0][0] == 1);
    // -(unary)
    ASSERT((-mat3)[0] == -(mat3[0]));
    // ==
    temp = mat3;
    ASSERT(temp == mat3);
    // !=
    ASSERT(mat3 != mat);
    // []
    mat3 = Matrix3x3<float>();
    ASSERT(mat3[0][0] == 1 && mat3[1][0] == 0);
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}

#endif
