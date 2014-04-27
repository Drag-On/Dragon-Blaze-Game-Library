//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX2X2_H_
#define MATRIX2X2_H_

#include "DBGL/System/Log/Log.h"
#include "Matrix.h"
#include "Vector2.h"

namespace dbgl
{
    /// <summary>
    /// @brief Matrix of size 2 by 2
    /// @author Jan Moeller
    /// </summary>
    template<typename T> class Matrix2x2 : public Matrix<T, 2, 2>
    {
	    using BaseMatrixType = Matrix<T, 2, 2>;
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a 2x2 identity matrix
	    /// </summary>
	    Matrix2x2();
	    /// <summary>
	    /// @brief Copies another 2x2 matrix
	    /// </summary>
	    Matrix2x2(const BaseMatrixType &other);
	    // Destructors
	    ~Matrix2x2();
	    // Methods
	    /// <summary>
	    /// @brief Transposes this matrix
	    /// </summary>
	    Matrix2x2<T>& transpose();
	    /// <summary>
	    /// @brief Inverts this matrix so that a multiplication with
	    ///	   the original results in an identity matrix
	    /// </summary>
	    Matrix2x2<T>& invert();
	    /// <summary>
	    /// @brief Returns an inverted version of this matrix so that
	    ///	   a multiplication with the original results in an
	    ///	   identity matrix
	    /// </summary>
	    Matrix2x2<T> getInverted() const;
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angle
	    /// @param angle Angle to rotate around
	    /// </summary>
	    static Matrix2x2<T> makeRotation(T angle);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factor
	    /// @param factor Factor to scale by
	    /// </summary>
	    static Matrix2x2<T> makeScale(T factor);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factors
	    /// @param x Factor to scale by in x direction
	    /// @param y Factor to scale by in y direction
	    /// </summary>
	    static Matrix2x2<T> makeScale(T x, T y);
	    // Operators
	    using BaseMatrixType::operator=;
	    using BaseMatrixType::operator+=;
	    using BaseMatrixType::operator-=;
	    using BaseMatrixType::operator*=;
	    using BaseMatrixType::operator/=;
	    /// <summary>
	    /// @brief Adds a matrix to this matrix
	    /// @param rhs Other matrix
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix2x2<T> operator+(BaseMatrixType const& rhs) const;
	    /// <summary>
	    /// @brief Subtracts a matrix from this matrix
	    /// @param rhs Other matrix
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix2x2<T> operator-(BaseMatrixType const& rhs) const;
	    /// <summary>
	    /// @brief Matrix multiplication
	    /// @param rhs Other matrix
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix2x2<T> operator*(BaseMatrixType const& rhs) const;
	    /// <summary>
	    /// @brief Matrix-vector multiplication
	    /// @param rhs 2D Vector
	    /// @return Resulting vector
	    /// </summary>
	    const Vector2<T> operator*(Vector<T,2> const& rhs) const;
	    /// <summary>
	    /// @brief Scalar multiplication
	    /// @param rhs Scalar
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix2x2<T> operator*(T const& rhs) const;
	    /// <summary>
	    /// @brief Matrix multiplication, assigning the resulting matrix to this
	    /// @param rhs Other matrix
	    /// @return Reference to this
	    /// </summary>
	    Matrix2x2<T>& operator*=(BaseMatrixType const& rhs);
	    /// <summary>
	    /// @brief Scalar division
	    /// @param rhs Scalar
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix2x2<T> operator/(T const& rhs) const;
	    /// <summary>
	    /// @brief Unary minus
	    /// @return Resulting matrix
	    /// </summary>
	    Matrix2x2<T> operator-() const;
	private:
    };

    // Some default types
    /**
     * @brief 2x2 matrix of integers
     */
    using Mat2i = Matrix2x2<int>;
    /**
     * @brief 2x2 matrix of floats
     */
    using Mat2f = Matrix2x2<float>;
    /**
     * @brief 2x2 matrix of doubles
     */
    using Mat2d = Matrix2x2<double>;
}

#include "Matrix2x2.imp"

#endif /* MATRIX2X2_H_ */
