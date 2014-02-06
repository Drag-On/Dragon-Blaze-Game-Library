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
#include <cassert>
#include "Math/Matrix.h"
#include "Math/Vector.h"

using namespace dbgl;

int testMatrix()
{
	printf("Starting Matrix test suite...\n");
	printf("Constructors... ");
	// Default
	Matrix<float,3,2> mat;
	assert(mat[0][0] == 1);
	assert(mat[0][1] == 0);
	assert(mat[1][0] == 0);
	assert(mat[1][1] == 1);
	// Copy
	Matrix<float,3,2> mat2;
	mat2[0][0] = 3;
	mat2[0][1] = 2;
	Matrix<float,3,2> mat3(mat2);
	assert(mat3[0][0] == 3 && mat3[0][1] == 2);
	printf("OK!\n");
	printf("Methods... ");
	// getWidth / height
	assert(mat.getWidth() == 3);
	assert(mat.getHeight() == 2);
	// getTransposed
	auto temp = mat3.getTransposed();
	assert(temp[0][0] == mat3[0][0] && temp[0][1] == mat3[1][0] && temp[1][0] == mat3[0][1] && temp[1][1] == mat3[1][1]);
	// isZero
	assert(!mat.isZero());
	// isIdentity
	assert(mat.isIdentity());
	printf("OK!\n");
	printf("Operators... ");
	// =
	mat = mat2;
	assert(mat == mat2);
	// +
	auto temp2 = mat + mat2;
	assert(temp2[0] == mat[0] + mat2[0] && temp2[1] == mat[1] + mat2[1]);
	// +=
	mat += temp2;
	assert(mat[0] == temp2[0] + mat2[0] && mat[1] == temp2[1] + mat2[1]);
	// -
	temp2 = mat - mat2;
	assert(temp2[0] == mat[0] - mat2[0] && temp2[1] == mat[1] - mat2[1]);
	// -=
	mat = mat2;
	mat -= temp2;
	assert(mat[0] == mat2[0] - temp2[0] && mat[1] == mat2[1] - temp2[1]);
	// *
	auto temp3 = mat * mat2.getTransposed();
	assert(temp3[0][0] == mat[0][0]*mat2.getTransposed()[0][0] + mat[1][0]*mat2.getTransposed()[0][1] + mat[2][0]*mat2.getTransposed()[0][2]);
	assert(temp3[1][0] == mat[0][0]*mat2.getTransposed()[1][0] + mat[1][0]*mat2.getTransposed()[1][1] + mat[2][0]*mat2.getTransposed()[1][2]);
	assert(temp3[0][1] == mat[0][1]*mat2.getTransposed()[0][0] + mat[1][1]*mat2.getTransposed()[0][1] + mat[2][1]*mat2.getTransposed()[0][2]);
	assert(temp3[1][1] == mat[0][1]*mat2.getTransposed()[1][0] + mat[1][1]*mat2.getTransposed()[1][1] + mat[2][1]*mat2.getTransposed()[1][2]);
	Vector<float,3> vec;
	vec[0] = 1;
	vec[1] = -2.5;
	vec[2] = 0;
	mat3 = Matrix<float,3,2>();
	assert((mat3 * vec)[0] == 1 && (mat3 * vec)[1] == -2.5);
	mat3[0][0] = 2;
	assert((mat3 * vec)[0] == mat3.getTransposed()[0] * vec);
	assert((mat3 * 2.0f)[0][0] == 4);
	// *=
	auto temp4 = mat;
	temp4 *= 3;
	assert(temp4[0] == mat[0] * 3.0f);
	// /
	assert((mat3 / 2.0f)[0][0] == 1);
	// /=
	mat3 /= 2;
	assert(mat3[0][0] == 1);
	// -(unary)
	assert((-mat3)[0] == -(mat3[0]));
	// ==
	temp2 = mat3;
	assert(temp2 == mat3);
	// !=
	assert(mat3 != mat);
	// []
	mat3 = Matrix<float,3,2>();
	assert(mat3[0][0] == 1 && mat3[1][0] == 0);
	printf("OK!\n");
	printf("Done!\n");
	return 0;
}

#endif
