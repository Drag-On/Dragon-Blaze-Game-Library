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
#include"System/Log/Log.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix.h"
#include"Utility.h"

namespace dbgl
{
    /// <summary>
    /// @brief Matrix of size 4 by 4
    /// @author Jan Moeller
    /// </summary>
    template<typename T> class Matrix4x4 : public Matrix<T, 4, 4>
    {
	    using BaseMatrixType = Matrix<T, 4, 4>;
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a 3x3 identity matrix
	    /// </summary>
	    Matrix4x4();
	    /// <summary>
	    /// @brief Copies another 3x3 matrix
	    /// </summary>
	    Matrix4x4(const BaseMatrixType &other);
	    // Destructors
	    ~Matrix4x4();
	    // Methods
	    /// <summary>
	    /// @brief Transposes this matrix
	    /// </summary>
	    Matrix4x4<T>& transpose();
	    /// <summary>
	    /// @brief Inverts this matrix so that a multiplication with
	    ///	   the original results in an identity matrix
	    /// </summary>
	    Matrix4x4<T>& invert();
	    /// <summary>
	    /// @brief Returns an inverted version of this matrix so that
	    ///	   a multiplication with the original results in an
	    ///	   identity matrix
	    /// </summary>
	    Matrix4x4<T> getInverted() const;
	    /// <summary>
	    /// @brief Constructs a translation matrix from the given translation values
	    /// @param x Amount to translate on the x axis
	    /// @param y Amount to translate on the y axis
	    /// @param z Amount to translate on the z axis
	    /// </summary>
	    static Matrix4x4<T> makeTranslation(T x, T y, T z);
	    /// <summary>
	    /// @brief Constructs a translation matrix from the given translation values
	    /// @param translation Translation values
	    /// </summary>
	    static Matrix4x4<T> makeTranslation(Vector3<T> translation);
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
	    static Matrix4x4<T> makeRotation(Vector3<T> vec, T angle);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factor
	    /// @param factor Factor to scale by
	    /// </summary>
	    static Matrix4x4<T> makeScale(T factor);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factors
	    /// @param x Factor to scale by in x direction
	    /// @param y Factor to scale by in y direction
	    /// @param z Factor to scale by in z direction
	    /// </summary>
	    static Matrix4x4<T> makeScale(T x, T y, T z);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factors
	    /// @param scale Factors to scale by
	    /// </summary>
	    static Matrix4x4<T> makeScale(Vector3<T> scale);
	    /// <summary>
	    /// @brief Constructs a camera matrix from the given data
	    /// @param pos Position of the camera in 3D space
	    /// @param direction Direction the camera aims at
	    /// @param up Vector that defines the camera up direction
	    /// </summary>
	    static Matrix4x4<T> makeView(Vector3<T> const& pos,
		    Vector3<T> const& direction, Vector3<T> const& up);
	    /// <summary>
	    /// @brief Makes this matrix a camera matrix from the given data
	    /// @param pos Position of the camera in 3D space
	    /// @param direction Direction the camera aims at
	    /// @param up Vector that defines the camera up direction
	    /// </summary>
	    void view(Vector3<T> const& pos, Vector3<T> const& direction,
		    Vector3<T> const& up);
	    /// <summary>
	    /// @brief Constructs a projection matrix from the given data
	    /// @param fieldOfView Angle of aperture
	    /// @param aspectRatio Aspect ratio of the display
	    /// @param near Near clipping plane
	    /// @param far Far clipping plane
	    /// </summary>
	    static Matrix4x4<T> makeProjection(T fieldOfView, T aspectRatio,
		    T near, T far);
	    /// <summary>
	    /// @brief Makes this matrix a projection matrix from the given data
	    /// @param fieldOfView Angle of aperture
	    /// @param aspectRatio Aspect ratio of the display
	    /// @param near Near clipping plane
	    /// @param far Far clipping plane
	    /// </summary>
	    void projection(T fieldOfView, T aspectRatio, T near, T far);
	    // Operators
	    using BaseMatrixType::operator=;
	    using BaseMatrixType::operator+=;
	    using BaseMatrixType::operator-=;
	    using BaseMatrixType::operator*=;
	    using BaseMatrixType::operator/=;
	    const Matrix4x4<T> operator+(BaseMatrixType const& rhs) const;
	    const Matrix4x4<T> operator-(BaseMatrixType const& rhs) const;
	    const Matrix4x4<T> operator*(BaseMatrixType const& rhs) const;
	    const Vector4<T> operator*(Vector<T,4> const& rhs) const;
	    const Matrix4x4<T> operator*(T const& rhs) const;
	    Matrix4x4<T>& operator*=(BaseMatrixType const& rhs);
	    const Matrix4x4<T> operator/(T const& rhs) const;
	    Matrix4x4<T> operator-() const;


	private:
    };

    // Some default types
    using Mat4i = Matrix4x4<int>;
    using Mat4f = Matrix4x4<float>;
    using Mat4d = Matrix4x4<double>;
}

#include "Matrix4x4.imp"

#endif /* MATRIX4X4_H_ */
