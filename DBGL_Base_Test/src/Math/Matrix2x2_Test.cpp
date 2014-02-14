//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX2_TEST_CPP
#define MATRIX2_TEST_CPP

#include <cmath>
#include <cstdio>
#include <cassert>
#include "Log/Log.h"
#include "Math/Matrix2x2.h"
#include "Math/Vector2.h"

using namespace dbgl;

int testMatrix2x2()
{
    LOG->info("Starting Matrix2x2 test suite...");
    LOG->info("Constructors... ");
    // Default
    Mat2f mat;
    assert(mat[0][0] == 1);
    assert(mat[0][1] == 0);
    assert(mat[1][0] == 0);
    assert(mat[1][1] == 1);
    // Copy
    Matrix2x2<float> mat2;
    mat2[0][0] = 3;
    mat2[0][1] = 2;
    Matrix2x2<float> mat3(mat2);
    assert(mat3[0][0] == 3 && mat3[0][1] == 2);
    LOG->info("OK!");
    LOG->info("Methods... ");
    // getWidth / height
    assert(mat.getWidth() == 2);
    assert(mat.getHeight() == 2);
    // transpose
    auto temp = Matrix2x2<float>(mat3);
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
    // getDataPointer
    for(int i = 0; i < mat3.getWidth() * mat3.getHeight(); i++)
    {
	assert(mat3.getDataPointer()[i] == mat3[i / mat3.getWidth()][i % mat3.getWidth()]);
    }
    // makeRotation
    auto res = (Matrix2x2<float>::makeRotation(1.57079633f) * Vector2<float>(1, 0));// 90°
    assert(std::abs(res[0] - 0) <= 0.01);
    assert(std::abs(res[1] - 1) <= 0.01);
    // makeScale
    res = (Mat2f::makeScale(2) * Vector2<float>(1, 0));
    assert(std::abs(res[0] - 2) <= 0.01);
    assert(std::abs(res[1] - 0) <= 0.01);
    res = (Mat2f::makeScale(2, 0.5) * Vector2<float>(1, 1));
    assert(std::abs(res[0] - 2) <= 0.01);
    assert(std::abs(res[1] - 0.5) <= 0.01);
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
    Vector2<float> vec(1, -2.5);
    mat3 = Matrix2x2<float>();
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
    mat3 = Matrix2x2<float>();
    assert(mat3[0][0] == 1 && mat3[1][0] == 0);
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
