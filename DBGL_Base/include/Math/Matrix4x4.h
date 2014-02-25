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
#include"Log/Log.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Utility.h"

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
	    Matrix4x4<T>& transpose();
	    /// <summary>
	    /// @brief Returns a transposed version of this matrix
	    /// </summary>
	    Matrix4x4<T> getTransposed() const;
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
	    /// @brief Checks if all elements are zero
	    /// </summary>
	    bool isZero() const;
	    /// <summary>
	    /// @brief Checks if this matrix is an identity matrix
	    /// </summary>
	    bool isIdentity() const;
	    /// <summary>
	    /// @brief Grants access to the internal memory
	    /// @return A pointer to the first element of this matrix
	    /// </summary>
	    const T* getDataPointer() const;
	    /// <summary>
	    /// @brief Constructs a translation matrix from the given translation values
	    /// @param x Amount to translate on the x axis
	    /// @param y Amount to translate on the y axis
	    /// @param z Amount to translate on the z axis
	    /// </summary>
	    static Matrix4x4<T> makeTranslation(T x, T y, T z);
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
	    /// @param w Factor to scale by in w direction
	    /// </summary>
	    static Matrix4x4<T> makeScale(T x, T y, T z, T w);
	    /// <summary>
	    /// @brief Constructs a camera matrix from the given data
	    /// @param pos Position of the camera in 3D space
	    /// @param target Position the camera aims at
	    /// @param up Vector that defines the camera up direction
	    /// </summary>
	    static Matrix4x4<T> makeView(Vector3<T> const& pos,
		    Vector3<T> const& target, Vector3<T> const& up);
	    /// <summary>
	    /// @brief Makes this matrix a camera matrix from the given data
	    /// @param pos Position of the camera in 3D space
	    /// @param target Position the camera aims at
	    /// @param up Vector that defines the camera up direction
	    /// </summary>
	    void view(Vector3<T> const& pos, Vector3<T> const& target,
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
	    Matrix4x4<T>& operator=(Matrix4x4<T> const& rhs);
	    const Matrix4x4<T> operator+(Matrix4x4<T> const& rhs) const;
	    Matrix4x4<T>& operator+=(Matrix4x4<T> const& rhs);
	    const Matrix4x4<T> operator-(Matrix4x4<T> const& rhs) const;
	    Matrix4x4<T>& operator-=(Matrix4x4<T> const& rhs);
	    const Matrix4x4<T> operator*(Matrix4x4<T> const& rhs) const;
	    const Vector4<T> operator*(Vector4<T> const& rhs) const;
	    const Matrix4x4<T> operator*(T const& rhs) const;
	    Matrix4x4<T>& operator*=(Matrix4x4<T> const& rhs);
	    Matrix4x4<T>& operator*=(T const& rhs);
	    const Matrix4x4<T> operator/(T const& rhs) const;
	    Matrix4x4<T>& operator/=(T const& rhs);
	    Matrix4x4<T> operator-() const;
	    bool operator==(Matrix4x4<T> const& rhs) const;
	    bool operator!=(Matrix4x4<T> const& rhs) const;
	    Vector4<T>& operator[](std::size_t const& index);
	    const Vector4<T>& operator[](std::size_t const& index) const;

	private:
	    Vector4<T> _columns[4];
    };

    // Some default types
    using Mat4i = Matrix4x4<int>;
    using Mat4f = Matrix4x4<float>;
    using Mat4d = Matrix4x4<double>;
}

#include "Matrix4x4.imp"

#endif /* MATRIX4X4_H_ */
