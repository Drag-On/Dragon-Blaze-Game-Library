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

#include "System/Log/Log.h"
#include "Matrix.h"
#include "Vector3.h"

namespace dbgl
{
    /// <summary>
    /// @brief Matrix of size 3 by 3
    /// @author Jan Moeller
    /// </summary>
    template<typename T> class Matrix3x3 : public Matrix<T, 3, 3>
    {
	    using BaseMatrixType = Matrix<T, 3, 3>;
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a 3x3 identity matrix
	    /// </summary>
	    Matrix3x3();
	    /// <summary>
	    /// @brief Copies another 3x3 matrix
	    /// </summary>
	    Matrix3x3(const BaseMatrixType &other);
	    // Destructors
	    ~Matrix3x3();
	    // Methods
	    /// <summary>
	    /// @brief Transposes this matrix
	    /// </summary>
	    Matrix3x3<T>& transpose();
	    /// <summary>
	    /// @brief Inverts this matrix so that a multiplication with
	    ///	   the original results in an identity matrix
	    /// </summary>
	    Matrix3x3<T>& invert();
	    /// <summary>
	    /// @brief Returns an inverted version of this matrix so that
	    ///	   a multiplication with the original results in an
	    ///	   identity matrix
	    /// </summary>
	    Matrix3x3<T> getInverted() const;
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angle
	    /// @param angle Angle to rotate around the x axis
	    /// </summary>
	    static Matrix3x3<T> makeRotationX(T angle);
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angle
	    /// @param angle Angle to rotate around the y axis
	    /// </summary>
	    static Matrix3x3<T> makeRotationY(T angle);
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angle
	    /// @param angle Angle to rotate around the z axis
	    /// </summary>
	    static Matrix3x3<T> makeRotationZ(T angle);
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angles
	    /// @param xAngle Angle to rotate around the x axis
	    /// @param yAngle Angle to rotate around the y axis
	    /// @param zAngle Angle to rotate around the z axis
	    /// </summary>
	    static Matrix3x3<T> makeRotation(T xAngle, T yAngle, T zAngle);
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angles and vectors
	    /// @param vec Vector to rotate around
	    /// @param angle Angle to rotate around the x axis
	    /// </summary>
	    static Matrix3x3<T> makeRotation(Vector3<T> vec, T angle);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factor
	    /// @param factor Factor to scale by
	    /// </summary>
	    static Matrix3x3<T> makeScale(T factor);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factors
	    /// @param x Factor to scale by in x direction
	    /// @param y Factor to scale by in y direction
	    /// @param z Factor to scale by in z direction
	    /// </summary>
	    static Matrix3x3<T> makeScale(T x, T y, T z);
	    // Operators
	    using BaseMatrixType::operator=;
	    using BaseMatrixType::operator+=;
	    using BaseMatrixType::operator-=;
	    using BaseMatrixType::operator*=;
	    using BaseMatrixType::operator/=;
	    const Matrix3x3<T> operator+(BaseMatrixType const& rhs) const;
	    const Matrix3x3<T> operator-(BaseMatrixType const& rhs) const;
	    const Matrix3x3<T> operator*(BaseMatrixType const& rhs) const;
	    const Vector3<T> operator*(Vector<T,3> const& rhs) const;
	    const Matrix3x3<T> operator*(T const& rhs) const;
	    Matrix3x3<T>& operator*=(BaseMatrixType const& rhs);
	    const Matrix3x3<T> operator/(T const& rhs) const;
	    Matrix3x3<T> operator-() const;

	private:
    };

    // Some default types
    using Mat3i = Matrix3x3<int>;
    using Mat3f = Matrix3x3<float>;
    using Mat3d = Matrix3x3<double>;
}

#include "Matrix3x3.imp"

#endif /* MATRIX3X3_H_ */
