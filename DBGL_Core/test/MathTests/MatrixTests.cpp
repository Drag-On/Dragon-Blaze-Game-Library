//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Math/Vector.h"
#include "DBGL/Core/Math/Matrix.h"
#include "DBGL/Core/Math/Matrix2x2.h"
#include "DBGL/Core/Math/Matrix3x3.h"
#include "DBGL/Core/Math/Matrix4x4.h"
#include "DBGL/Core/Math/Utility.h"

using namespace dbgl;
using namespace std;

const float numbers[] = {-1.5f, 1.0f, 0.256f, 25.0f, -100.38585f, 0.00001f, 42.1337f, 571, 43.495f};

template<class Mat>
void testConstructor()
{
    Mat mat;
    ASSERT(mat.isIdentity());
    mat[0][0] = numbers[0];
    Mat copy{mat};
    ASSERT_EQ(mat, copy);
    Mat2f smallMat(42);
    Mat mat2{smallMat};
    for (unsigned int x = 0; x < 2; x++)
        for (unsigned int y = 0; y < 2; y++)
            ASSERT_EQ(mat2[x][y], smallMat[x][y]);
    Vector<float, Mat::getHeight()> vector1{numbers[0], numbers[1]};
    Vector<float, Mat::getHeight()> vector2{numbers[2], numbers[3]};
    Mat mat3{vector1, vector2};
    ASSERT_EQ(mat3[0], vector1);
    ASSERT_EQ(mat3[1], vector2);
}

TEST(Matrix, constructor)
{
    testConstructor<Mat2f>();
    testConstructor<Mat3f>();
    testConstructor<Mat4f>();
}

template<class Mat>
void testTranspose()
{
    Mat mat;
    ASSERT_EQ(mat.getTransposed(), mat);
    mat[1][0] = numbers[0];
    ASSERT_NEQ(mat.getTransposed(), mat);
    ASSERT_EQ(mat.getTransposed()[0][1], mat[1][0]);
}

TEST(Matrix, transpose)
{
    testTranspose<Mat2f>();
    testTranspose<Mat3f>();
    testTranspose<Mat4f>();
}

template<class Mat>
void testInvert()
{
    Mat mat;
    ASSERT_EQ(mat.getInverted(), mat);
    Mat mat2 = mat * 42;
    ASSERT_EQ(mat2 * mat2.getInverted(), mat);
}

TEST(Matrix, invert)
{
    testInvert<Mat2f>();
    testInvert<Mat3f>();
    testInvert<Mat4f>();
}

template<class Mat>
void testIsZero()
{
    Mat mat;
    ASSERT(!mat.isZero());
    Mat mat2(0.0);
    ASSERT(mat2.isZero());
}

TEST(Matrix, isZero)
{
    testIsZero<Mat2f>();
    testIsZero<Mat3f>();
    testIsZero<Mat4f>();
}

template<class Mat>
void testIsIdentity()
{
    Mat mat;
    ASSERT(mat.isIdentity());
    Mat mat2(0.0);
    ASSERT(!mat2.isIdentity());
}

TEST(Matrix, isIdentity)
{
    testIsIdentity<Mat2f>();
    testIsIdentity<Mat3f>();
    testIsIdentity<Mat4f>();
}

template<class Mat>
void testGetDataPointer()
{
    Mat mat;
    for (unsigned int i = 0; i < Mat::getHeight() * Mat::getWidth(); i++)
        ASSERT(mat.getDataPointer()[i] == mat[i / Mat::getHeight()][i % Mat::getWidth()]);
}

TEST(Matrix, getDataPointer)
{
    testGetDataPointer<Mat2f>();
    testGetDataPointer<Mat3f>();
    testGetDataPointer<Mat4f>();
}

template<class Mat>
void testOperatorAssign()
{
    Mat mat;
    Mat mat2(42.0);
    mat = mat2;
    ASSERT_EQ(mat, mat2);
}

TEST(Matrix, operatorAssign)
{
    testOperatorAssign<Mat2f>();
    testOperatorAssign<Mat3f>();
    testOperatorAssign<Mat4f>();
}

template<class Mat>
void testOperatorPlusMinus()
{
    Mat mat;
    Mat mat2(42.0);
    Mat mat3 = mat + mat2;
    for (unsigned int x = 0; x < Mat::getWidth(); x++)
        for (unsigned int y = 0; y < Mat::getHeight(); y++)
            ASSERT_EQ(mat3[x][y], mat[x][y] + mat2[x][y]);
    Mat mat4 = mat - mat2;
    for (unsigned int x = 0; x < Mat::getWidth(); x++)
        for (unsigned int y = 0; y < Mat::getHeight(); y++)
            ASSERT_EQ(mat4[x][y], mat[x][y] - mat2[x][y]);
}

TEST(Matrix, operatorPlusMinus)
{
    testOperatorPlusMinus<Mat2f>();
    testOperatorPlusMinus<Mat3f>();
    testOperatorPlusMinus<Mat4f>();
}

template<class Mat>
void testOperatorMultiplyDivide()
{
    Mat mat;
    Mat mat2(42.0);
    Mat mat3 = mat * mat2;
    ASSERT_EQ(mat3, mat2);
    typename std::remove_reference<decltype(mat[0])>::type vec(0.0);
    auto vec2 = mat2 * vec;
    ASSERT(vec2.isZero());
    decltype(vec2) vec3(1.0);
    auto vec4 = mat2 * vec3;
    for (unsigned int i = 0; i < vec3.getDimension(); i++)
        ASSERT(vec4[i] = mat2.getTransposed()[i] * vec3);
    auto mat4 = mat2 * 42;
    for (unsigned int x = 0; x < mat4.getWidth(); x++)
        for (unsigned int y = 0; y < mat4.getHeight(); y++)
            ASSERT(mat4[x][y] = mat2[x][y] * 42);
    auto mat5 = mat4 / 42;
    for (unsigned int x = 0; x < mat5.getWidth(); x++)
        for (unsigned int y = 0; y < mat5.getHeight(); y++)
            ASSERT(mat5[x][y] = mat4[x][y] / 42);
}

TEST(Matrix, operatorMultiplyDivide)
{
    testOperatorMultiplyDivide<Mat2f>();
    testOperatorMultiplyDivide<Mat3f>();
    testOperatorMultiplyDivide<Mat4f>();
}

template<class Mat>
void testOperatorUnaryMinus()
{
    Mat mat(42.0);
    Mat mat2 = -mat;
    for (unsigned int x = 0; x < mat2.getWidth(); x++)
        for (unsigned int y = 0; y < mat2.getHeight(); y++)
            ASSERT(mat2[x][y] = -mat[x][y]);
}

TEST(Matrix, operatorUnaryMinus)
{
    testOperatorUnaryMinus<Mat2f>();
    testOperatorUnaryMinus<Mat3f>();
    testOperatorUnaryMinus<Mat4f>();
}

template<class Mat>
void testOperatorEquality()
{
    Mat mat(42.0);
    Mat mat2(42.0);
    ASSERT(mat == mat2);
    Mat mat3(0.0);
    ASSERT(mat != mat3);
}

TEST(Matrix, operatorEquality)
{
    testOperatorEquality<Mat2f>();
    testOperatorEquality<Mat3f>();
    testOperatorEquality<Mat4f>();
}

TEST(Matrix, determinant)
{
    Mat2f mat2{{1, 2},
               {3, 4}};
    ASSERT_EQ(mat2.determinant(), -2);
    Mat3f mat3{{1, 2, 3},
               {4, 5, 6},
               {7, 8, 9}};
    ASSERT_EQ(mat3.determinant(), 0);
    Mat4f mat4{{1,  2,  3,  4},
               {5,  6,  7,  8},
               {9,  10, 11, 12},
               {13, 14, 15, 16}};
    ASSERT_EQ(mat4.determinant(), 0);
}

TEST(Matrix, getSubMatrix)
{
    Mat4f mat4{{1,  2,  3,  4},
               {5,  6,  7,  8},
               {9,  10, 11, 12},
               {13, 14, 15, 16}};
    auto mat2_1 = mat4.getSubMatrix<2, 2>();
    ASSERT_EQ(mat2_1.getHeight(), 2);
    ASSERT_EQ(mat2_1.getWidth(), 2);
    for (unsigned int i = 0; i < 2; i++)
        for (unsigned int j = 0; j < 2; j++)
            ASSERT_EQ(mat2_1[i][j], mat4[i][j]);

    auto mat2_2 = mat4.getSubMatrix<1, 1, 2, 3>();
    ASSERT_EQ(mat2_2.getHeight(), 3);
    ASSERT_EQ(mat2_2.getWidth(), 2);
    for (unsigned int i = 1; i < 2; i++)
        for (unsigned int j = 1; j < 3; j++)
            ASSERT_EQ(mat2_2[i - 1][j - 1], mat4[i][j]);
}
