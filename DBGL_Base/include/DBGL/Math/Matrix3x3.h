//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX3X3_H_
#define MATRIX3X3_H_

#include "DBGL/System/Log/Log.h"
#include "Matrix.h"
#include "Vector3.h"

namespace dbgl
{
    /**
     * @brief Matrix of size 3 by 3
     * @author Jan Moeller
     */
    template<typename T> class Matrix3x3 : public Matrix<T, 3, 3>
    {
	    using BaseMatrixType = Matrix<T, 3, 3>;
	public:
	    // Constructors
	    /**
	     * @brief Constructs a 3x3 identity matrix
	     */
	    Matrix3x3();
	    /**
	     * @brief Copies another 3x3 matrix
	     */
	    Matrix3x3(const BaseMatrixType &other);
	    // Destructors
	    ~Matrix3x3();
	    // Methods
	    /**
	     * @brief Transposes this matrix
	     */
	    Matrix3x3<T>& transpose();
	    /**
	     * @brief Inverts this matrix so that a multiplication with
	     * 	   the original results in an identity matrix
	     */
	    Matrix3x3<T>& invert();
	    /**
	     * @brief Returns an inverted version of this matrix so that
	     * 	   a multiplication with the original results in an
	     * 	   identity matrix
	     */
	    Matrix3x3<T> getInverted() const;
	    /**
	     * @brief Constructs a translation matrix from the given translation values
	     * @param x Amount to translate on the x axis
	     * @param y Amount to translate on the y axis
	     */
	    static Matrix3x3<T> make2DTranslation(T x, T y);
	    /**
	     * @brief Constructs a rotation matrix from the given angle
	     * @param angle Angle to rotate around the z axis
	     */
	    static Matrix3x3<T> make2DRotation(T angle);
	    /**
	     * @brief Constructs a scale matrix from the given factor
	     * @param factor Factor to scale by
	     */
	    static Matrix3x3<T> make2DScale(T factor);
	    /**
	     * @brief Constructs a scale matrix from the given factors
	     * @param x Factor to scale by in x direction
	     * @param y Factor to scale by in y direction
	     */
	    static Matrix3x3<T> make2DScale(T x, T y);
	    /**
	     * @brief Constructs a rotation matrix from the given angle
	     * @param angle Angle to rotate around the x axis
	     */
	    static Matrix3x3<T> makeRotationX(T angle);
	    /**
	     * @brief Constructs a rotation matrix from the given angle
	     * @param angle Angle to rotate around the y axis
	     */
	    static Matrix3x3<T> makeRotationY(T angle);
	    /**
	     * @brief Constructs a rotation matrix from the given angle
	     * @param angle Angle to rotate around the z axis
	     */
	    static Matrix3x3<T> makeRotationZ(T angle);
	    /**
	     * @brief Constructs a rotation matrix from the given angles
	     * @param xAngle Angle to rotate around the x axis
	     * @param yAngle Angle to rotate around the y axis
	     * @param zAngle Angle to rotate around the z axis
	     */
	    static Matrix3x3<T> makeRotation(T xAngle, T yAngle, T zAngle);
	    /**
	     * @brief Constructs a rotation matrix from the given angles and vectors
	     * @param vec Vector to rotate around
	     * @param angle Angle to rotate around the x axis
	     */
	    static Matrix3x3<T> makeRotation(Vector3<T> vec, T angle);
	    /**
	     * @brief Constructs a scale matrix from the given factor
	     * @param factor Factor to scale by
	     */
	    static Matrix3x3<T> makeScale(T factor);
	    /**
	     * @brief Constructs a scale matrix from the given factors
	     * @param x Factor to scale by in x direction
	     * @param y Factor to scale by in y direction
	     * @param z Factor to scale by in z direction
	     */
	    static Matrix3x3<T> makeScale(T x, T y, T z);
	    // Operators
	    using BaseMatrixType::operator=;
	    using BaseMatrixType::operator+=;
	    using BaseMatrixType::operator-=;
	    using BaseMatrixType::operator*=;
	    using BaseMatrixType::operator/=;
	    /**
	     * @brief Adds a matrix to this matrix
	     * @param rhs Other matrix
	     * @return Resulting matrix
	     */
	    const Matrix3x3<T> operator+(BaseMatrixType const& rhs) const;
	    /**
	     * @brief Subtracts a matrix from this matrix
	     * @param rhs Other matrix
	     * @return Resulting matrix
	     */
	    const Matrix3x3<T> operator-(BaseMatrixType const& rhs) const;
	    /**
	     * @brief Matrix multiplication
	     * @param rhs Other matrix
	     * @return Resulting matrix
	     */
	    const Matrix3x3<T> operator*(BaseMatrixType const& rhs) const;
	    /**
	     * @brief Matrix-vector multiplication
	     * @param rhs 2D Vector
	     * @return Resulting vector
	     */
	    const Vector3<T> operator*(Vector<T,3> const& rhs) const;
	    /**
	     * @brief Scalar multiplication
	     * @param rhs Scalar
	     * @return Resulting matrix
	     */
	    const Matrix3x3<T> operator*(T const& rhs) const;
	    /**
	     * @brief Matrix multiplication, assigning the resulting matrix to this
	     * @param rhs Other matrix
	     * @return Reference to this
	     */
	    Matrix3x3<T>& operator*=(BaseMatrixType const& rhs);
	    /**
	     * @brief Scalar division
	     * @param rhs Scalar
	     * @return Resulting matrix
	     */
	    const Matrix3x3<T> operator/(T const& rhs) const;
	    /**
	     * @brief Unary minus
	     * @return Resulting matrix
	     */
	    Matrix3x3<T> operator-() const;

	private:
    };

    // Some default types
    /**
     * @brief 3x3 matrix of integers
     */
    using Mat3i = Matrix3x3<int>;
    /**
     * @brief 3x3 matrix of floats
     */
    using Mat3f = Matrix3x3<float>;
    /**
     * @brief 3x3 matrix of doubles
     */
    using Mat3d = Matrix3x3<double>;
}

#include "Matrix3x3.imp"

#endif /* MATRIX3X3_H_ */
