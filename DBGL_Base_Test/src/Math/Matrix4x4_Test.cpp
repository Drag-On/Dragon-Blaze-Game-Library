//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX4_TEST_CPP
#define MATRIX4_TEST_CPP

#include <cstdio>
#include <cassert>
#include "Log/Log.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector4.h"

using namespace dbgl;

int testMatrix4x4()
{
    LOG->info("Starting Matrix4x4 test suite...");
    LOG->info("Constructors... ");
    // Default
    Matrix4x4<float> mat;
    assert(mat[0][0] == 1);
    assert(mat[0][1] == 0);
    assert(mat[1][0] == 0);
    assert(mat[1][1] == 1);
    // Copy
    Matrix4x4<float> mat2;
    mat2[0][0] = 3;
    mat2[0][1] = 2;
    Matrix4x4<float> mat3(mat2);
    assert(mat3[0][0] == 3 && mat3[0][1] == 2);
    LOG->info("OK!");
    LOG->info("Methods... ");
    // getWidth / height
    assert(mat.getWidth() == 4);
    assert(mat.getHeight() == 4);
    // transpose
    auto temp = Matrix4x4<float>(mat3);
    temp.transpose();
    assert(temp[0][0] == mat3[0][0] && temp[0][1] == mat3[1][0] && temp[1][0] == mat3[0][1] && temp[1][1] == mat3[1][1]);
    // getTransposed
    assert(temp.getTransposed() == mat3);
    // invert
    temp = mat3;
    mat3.invert();
    temp = temp * mat3;
    assert(temp.isIdentity());
    // getInverted
    temp = mat3.getInverted() * mat3;
    assert(temp.isIdentity());
    // isZero
    assert(!mat.isZero());
    // isIdentity
    assert(mat.isIdentity());
    // makeTranslation
    auto res = (Matrix4x4<float>::makeTranslation(1.5, 0.4, -42) * Vector4<float>(1, 0, -1, 1));
    assert(std::abs(res[0] - 2.5) <= 0.01);
    assert(std::abs(res[1] - 0.4) <= 0.01);
    assert(std::abs(res[2] + 43) <= 0.01);
    // makeRotationX
    Vector4<float> testVec(0, 1, 0, 1);
    res = (Matrix4x4<float>::makeRotationX(1.57079633f) * testVec);// 90°
    assert(std::abs(res[0] - 0) <= 0.01);
    assert(std::abs(res[1] - 0) <= 0.01);
    assert(std::abs(res[2] - 1) <= 0.01);
    // makeRotationY
    testVec[0] = 1;
    testVec[1] = 0;
    res = (Matrix4x4<float>::makeRotationY(1.57079633f) * testVec);// 90°
    assert(std::abs(res[0] - 0) <= 0.01);
    assert(std::abs(res[1] - 0) <= 0.01);
    assert(std::abs(res[2] + 1) <= 0.01);
    // makeRotationZ
    res = (Matrix4x4<float>::makeRotationZ(1.57079633f) * testVec);// 90°
    assert(std::abs(res[0] - 0) <= 0.01);
    assert(std::abs(res[1] - 1) <= 0.01);
    assert(std::abs(res[2] - 0) <= 0.01);
    // makeRotation
    res = (Matrix4x4<float>::makeRotation(Vector4<float>(0, 1, 0, 0), 1.57079633f) * testVec);// 90°
    assert(std::abs(res[0] - 0) <= 0.01);
    assert(std::abs(res[1] - 0) <= 0.01);
    assert(std::abs(res[2] + 1) <= 0.01);
    assert(Matrix4x4<float>::makeRotation(Vector4<float>(1, 0, 0, 0), 1) == Matrix4x4<float>::makeRotationX(1));
    assert(Matrix4x4<float>::makeRotation(Vector4<float>(0, 1, 0, 0), 1) == Matrix4x4<float>::makeRotationY(1));
    assert(Matrix4x4<float>::makeRotation(Vector4<float>(0, 0, 1, 0), 1) == Matrix4x4<float>::makeRotationZ(1));
    res = (Matrix4x4<float>::makeRotation(Vector4<float>(0, 1, 0, 0), 1.57079633f) * Vector4<float>(1, 1, 0, 0));// 90°
    assert(std::abs(res[0] - 0) <= 0.01);
    assert(std::abs(res[1] - 1) <= 0.01);
    assert(std::abs(res[2] + 1) <= 0.01);
    res = (Matrix4x4<float>::makeRotation(Vector4<float>(1, 1, 0, 0), 1.57079633f) * testVec);// 90°
    assert(std::abs(res[0] - 0.5) <= 0.01);
    assert(std::abs(res[1] - 0.5) <= 0.01);
    assert(std::abs(res[2] + 0.7) <= 0.01);
    // makeScale
    res = (Mat4f::makeScale(2) * Vec4f(1, 0, 0, 0));
    assert(std::abs(res[0] - 2) <= 0.01);
    assert(std::abs(res[1] - 0) <= 0.01);
    assert(std::abs(res[2] - 0) <= 0.01);
    assert(std::abs(res[3] - 0) <= 0.01);
    res = (Mat4f::makeScale(2, 0.5, -3, 1) * Vec4f(1, 1, -2, 44));
    assert(std::abs(res[0] - 2) <= 0.01);
    assert(std::abs(res[1] - 0.5) <= 0.01);
    assert(std::abs(res[2] - 6) <= 0.01);
    assert(std::abs(res[3] - 44) <= 0.01);
    LOG->info("OK!");
    LOG->info("Operators... ");
    // =
    mat = mat2;
    assert(mat == mat2);
    // +
    temp = mat + mat2;
    assert(temp[0] == mat[0] + mat2[0] && temp[1] == mat[1] + mat2[1]);
    // +=
    mat += temp;
    assert(mat[0] == temp[0] + mat2[0] && mat[1] == temp[1] + mat2[1]);
    // -
    temp = mat - mat2;
    assert(temp[0] == mat[0] - mat2[0] && temp[1] == mat[1] - mat2[1]);
    // -=
    mat = mat2;
    mat -= temp;
    assert(mat[0] == mat2[0] - temp[0] && mat[1] == mat2[1] - temp[1]);
    // *
    temp = mat * mat2;
    assert(temp[0][0] == mat.getTransposed()[0] * mat2[0]);
    assert(temp[1][0] == mat.getTransposed()[0] * mat2[1]);
    assert(temp[0][1] == mat.getTransposed()[1] * mat2[0]);
    assert(temp[1][1] == mat.getTransposed()[1] * mat2[1]);
    Vector4<float> vec(1, -2.5, 0, 0);
    mat3 = Matrix4x4<float>();
    assert((mat3 * vec)[0] == 1 && (mat3 * vec)[1] == -2.5);
    mat3[0][0] = 2;
    assert((mat3 * vec)[0] == mat3.getTransposed()[0] * vec);
    assert((mat3 * 2.0f)[0][0] == 4);
    // *=
    mat *= mat2;
    assert(mat == temp);
    // /
    assert((mat3 / 2.0f)[0][0] == 1);
    // /=
    mat3 /= 2;
    assert(mat3[0][0] == 1);
    // -(unary)
    assert((-mat3)[0] == -(mat3[0]));
    // ==
    temp = mat3;
    assert(temp == mat3);
    // !=
    assert(mat3 != mat);
    // []
    mat3 = Matrix4x4<float>();
    assert(mat3[0][0] == 1 && mat3[1][0] == 0);
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
