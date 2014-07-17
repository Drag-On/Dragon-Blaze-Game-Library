//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX_TEST_CPP
#define MATRIX_TEST_CPP

#include <cstdio>
#include "cute.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Matrix.h"
#include "DBGL/Math/Vector.h"

using namespace dbgl;

int testMatrix()
{
    LOG.info("Starting Matrix test suite...");
    LOG.info("Constructors... ");
    // Default
    Matrix<float,3,2> mat;
    ASSERT(mat[0][0] == 1);
    ASSERT(mat[0][1] == 0);
    ASSERT(mat[1][0] == 0);
    ASSERT(mat[1][1] == 1);
    // Copy
    Matrix<float,3,2> mat2;
    mat2[0][0] = 3;
    mat2[0][1] = 2;
    Matrix<float,3,2> mat3(mat2);
    ASSERT(mat3[0][0] == 3 && mat3[0][1] == 2);
    LOG.info("OK!");
    LOG.info("Methods... ");
    // getWidth / height
    ASSERT(mat.getWidth() == 3);
    ASSERT(mat.getHeight() == 2);
    // getTransposed
    auto temp = mat3.getTransposed();
    ASSERT(temp[0][0] == mat3[0][0] && temp[0][1] == mat3[1][0] && temp[1][0] == mat3[0][1] && temp[1][1] == mat3[1][1]);
    // isZero
    ASSERT(!mat.isZero());
    // isIdentity
    ASSERT(mat.isIdentity());
    // getDataPointer
    for(int i = 0; i < mat3.getWidth() * mat3.getHeight(); i++)
    {
	ASSERT(mat3.getDataPointer()[i] == mat3[i / mat3.getHeight()][i % mat3.getHeight()]);
    }
    LOG.info("OK!");
    LOG.info("Operators... ");
    // =
    mat = mat2;
    ASSERT(mat == mat2);
    // +
    auto temp2 = mat + mat2;
    ASSERT(temp2[0] == mat[0] + mat2[0] && temp2[1] == mat[1] + mat2[1]);
    // +=
    mat += temp2;
    ASSERT(mat[0] == temp2[0] + mat2[0] && mat[1] == temp2[1] + mat2[1]);
    // -
    temp2 = mat - mat2;
    ASSERT(temp2[0] == mat[0] - mat2[0] && temp2[1] == mat[1] - mat2[1]);
    // -=
    mat = mat2;
    mat -= temp2;
    ASSERT(mat[0] == mat2[0] - temp2[0] && mat[1] == mat2[1] - temp2[1]);
    // *
    auto temp3 = mat * mat2.getTransposed();
    ASSERT(temp3[0][0] == mat[0][0]*mat2.getTransposed()[0][0] + mat[1][0]*mat2.getTransposed()[0][1] + mat[2][0]*mat2.getTransposed()[0][2]);
    ASSERT(temp3[1][0] == mat[0][0]*mat2.getTransposed()[1][0] + mat[1][0]*mat2.getTransposed()[1][1] + mat[2][0]*mat2.getTransposed()[1][2]);
    ASSERT(temp3[0][1] == mat[0][1]*mat2.getTransposed()[0][0] + mat[1][1]*mat2.getTransposed()[0][1] + mat[2][1]*mat2.getTransposed()[0][2]);
    ASSERT(temp3[1][1] == mat[0][1]*mat2.getTransposed()[1][0] + mat[1][1]*mat2.getTransposed()[1][1] + mat[2][1]*mat2.getTransposed()[1][2]);
    Vector<float,3> vec;
    vec[0] = 1;
    vec[1] = -2.5;
    vec[2] = 0;
    mat3 = Matrix<float,3,2>();
    ASSERT((mat3 * vec)[0] == 1 && (mat3 * vec)[1] == -2.5);
    mat3[0][0] = 2;
    ASSERT((mat3 * vec)[0] == mat3.getTransposed()[0] * vec);
    ASSERT((mat3 * 2.0f)[0][0] == 4);
    // *=
    auto temp4 = mat;
    temp4 *= 3;
    ASSERT(temp4[0] == mat[0] * 3.0f);
    // /
    ASSERT((mat3 / 2.0f)[0][0] == 1);
    // /=
    mat3 /= 2;
    ASSERT(mat3[0][0] == 1);
    // -(unary)
    ASSERT((-mat3)[0] == -(mat3[0]));
    // ==
    temp2 = mat3;
    ASSERT(temp2 == mat3);
    // !=
    ASSERT(mat3 != mat);
    // []
    mat3 = Matrix<float,3,2>();
    ASSERT(mat3[0][0] == 1 && mat3[1][0] == 0);
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}

#endif
