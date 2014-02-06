//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include<cmath>
#include "Vector4.h"

namespace dbgl
{
    /// <summary>
    /// @brief Matrix of size 4 by 4
    /// @author Jan Moeller
    /// </summary>
    template<typename T> class Matrix4x4
    {
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a 3x3 identity matrix
	    /// </summary>
	    Matrix4x4();
	    /// <summary>
	    /// @brief Copies another 3x3 matrix
	    /// </summary>
	    Matrix4x4(const Matrix4x4<T> &other);
	    // Destructors
	    ~Matrix4x4();
	    // Methods
	    /// <summary>
	    /// @brief Gets the amount of columns of this matrix
	    /// </summary>
	    int getWidth() const;
	    /// <summary>
	    /// @brief Gets the amount of lines of this matrix
	    /// </summary>
	    int getHeight() const;
	    /// <summary>
	    /// @brief Transposes this matrix
	    /// </summary>
	    void transpose();
	    /// <summary>
	    /// @brief Returns a transposed version of this matrix
	    /// </summary>
	    Matrix4x4<T> getTransposed() const;
	    /// <summary>
	    /// @brief Inverts this matrix so that a multiplication with
	    ///	   the original results in an identity matrix
	    /// </summary>
	    void invert();
	    /// <summary>
	    /// @brief Returns an inverted version of this matrix so that
	    ///	   a multiplication with the original results in an
	    ///	   identity matrix
	    /// </summary>
	    Matrix4x4<T> getInverted() const;
	    /// <summary>
	    /// @brief Checks if all elements are zero
	    /// </summary>
	    bool isZero();
	    /// <summary>
	    /// @brief Checks if this matrix is an identity matrix
	    /// </summary>
	    bool isIdentity();
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angle
	    /// @param angle Angle to rotate around the x axis
	    /// </summary>
	    static Matrix4x4<T> makeRotationX(T angle);
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angle
	    /// @param angle Angle to rotate around the y axis
	    /// </summary>
	    static Matrix4x4<T> makeRotationY(T angle);
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angle
	    /// @param angle Angle to rotate around the z axis
	    /// </summary>
	    static Matrix4x4<T> makeRotationZ(T angle);
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angles
	    /// @param xAngle Angle to rotate around the x axis
	    /// @param yAngle Angle to rotate around the y axis
	    /// @param zAngle Angle to rotate around the z axis
	    /// </summary>
	    static Matrix4x4<T> makeRotation(T xAngle, T yAngle, T zAngle);
	    /// <summary>
	    /// @brief Constructs a rotation matrix from the given angles and vectors
	    /// @param vec Vector to rotate around
	    /// @param angle Angle to rotate around the x axis
	    /// </summary>
	    static Matrix4x4<T> makeRotation(Vector4<T> vec, T angle);
	    // Operators
	    Matrix4x4<T>& operator=(Matrix4x4<T> const& rhs);
	    const Matrix4x4<T> operator+(Matrix4x4<T> const& rhs);
	    Matrix4x4<T>& operator+=(Matrix4x4<T> const& rhs);
	    const Matrix4x4<T> operator-(Matrix4x4<T> const& rhs);
	    Matrix4x4<T>& operator-=(Matrix4x4<T> const& rhs);
	    const Matrix4x4<T> operator*(Matrix4x4<T> const& rhs);
	    const Vector4<T> operator*(Vector4<T> const& rhs);
	    const Matrix4x4<T> operator*(T const& rhs);
	    Matrix4x4<T>& operator*=(Matrix4x4<T> const& rhs);
	    Matrix4x4<T>& operator*=(T const& rhs);
	    const Matrix4x4<T> operator/(T const& rhs);
	    Matrix4x4<T>& operator/=(T const& rhs);
	    Matrix4x4<T> operator-() const;
	    bool operator==(Matrix4x4<T> const& rhs);
	    bool operator!=(Matrix4x4<T> const& rhs);
	    Vector4<T>& operator[](std::size_t const& index);
	    const Vector4<T>& operator[](std::size_t const& index) const;

	private:
	    Vector4<T> _columns[4];
    };
}

#include "Matrix4x4.imp"

#endif /* MATRIX4X4_H_ */