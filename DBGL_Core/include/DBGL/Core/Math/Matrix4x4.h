//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX4X4_H_
#define MATRIX4X4_H_

#include <cmath>
#include "DBGL/Core/Debug/Log.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include "Utility.h"

namespace dbgl
{
	/**
	 * @brief Matrix of size 4 by 4
	 * @author Jan Moeller
	 */
	template<typename T> class Matrix4x4: public Matrix<T, 4, 4>
	{
		using BaseMatrixType = Matrix<T, 4, 4>;
	public:
		// Constructors
		/**
		 * @brief Constructs a 3x3 identity matrix
		 */
		Matrix4x4();
		/**
		 * @brief Creates a matrix and fills it with the passed value
		 */
		explicit Matrix4x4(T value);
		/**
		 * @brief Constructs a new matrix from a lower-dimensionality matrix and sets the remaining elements to unit
		 */
		template<unsigned int N2, unsigned int M2> Matrix4x4(Matrix<T, N2, M2> const& other);
		/**
		 * @brief Constructs a new matrix from an initializer list
		 * @param args Columns
		 */
		Matrix4x4(std::initializer_list<Vector<T, 4>> args);
		/**
		 * @brief Copies another 3x3 matrix
		 */
		Matrix4x4(const BaseMatrixType &other);
		// Destructors
		~Matrix4x4();
		// Methods
		/**
		 * @brief Transposes this matrix
		 */
		Matrix4x4<T>& transpose();
		/**
		 * @brief Inverts this matrix so that a multiplication with
		 * 	   the original results in an identity matrix
		 */
		Matrix4x4<T>& invert();
		/**
		 * @brief Returns an inverted version of this matrix so that
		 * 	   a multiplication with the original results in an
		 * 	   identity matrix
		 */
		Matrix4x4<T> getInverted() const;
		/**
		 * @brief Constructs a translation matrix from the given translation values
		 * @param x Amount to translate on the x axis
		 * @param y Amount to translate on the y axis
		 * @param z Amount to translate on the z axis
		 */
		static Matrix4x4<T> makeTranslation(T x, T y, T z);
		/**
		 * @brief Constructs a translation matrix from the given translation values
		 * @param translation Translation values
		 */
		static Matrix4x4<T> makeTranslation(Vector3<T> translation);
		/**
		 * @brief Constructs a rotation matrix from the given angle
		 * @param angle Angle to rotate around the x axis
		 */
		static Matrix4x4<T> makeRotationX(T angle);
		/**
		 * @brief Constructs a rotation matrix from the given angle
		 * @param angle Angle to rotate around the y axis
		 */
		static Matrix4x4<T> makeRotationY(T angle);
		/**
		 * @brief Constructs a rotation matrix from the given angle
		 * @param angle Angle to rotate around the z axis
		 */
		static Matrix4x4<T> makeRotationZ(T angle);
		/**
		 * @brief Constructs a rotation matrix from the given angles
		 * @param xAngle Angle to rotate around the x axis
		 * @param yAngle Angle to rotate around the y axis
		 * @param zAngle Angle to rotate around the z axis
		 */
		static Matrix4x4<T> makeRotation(T xAngle, T yAngle, T zAngle);
		/**
		 * @brief Constructs a rotation matrix from the given angles and vectors
		 * @param vec Vector to rotate around
		 * @param angle Angle to rotate around the x axis
		 */
		static Matrix4x4<T> makeRotation(Vector3<T> vec, T angle);
		/**
		 * @brief Constructs a scale matrix from the given factor
		 * @param factor Factor to scale by
		 */
		static Matrix4x4<T> makeScale(T factor);
		/**
		 * @brief Constructs a scale matrix from the given factors
		 * @param x Factor to scale by in x direction
		 * @param y Factor to scale by in y direction
		 * @param z Factor to scale by in z direction
		 */
		static Matrix4x4<T> makeScale(T x, T y, T z);
		/**
		 * @brief Constructs a scale matrix from the given factors
		 * @param scale Factors to scale by
		 */
		static Matrix4x4<T> makeScale(Vector3<T> scale);
		/**
		 * @brief Constructs a camera matrix from the given data
		 * @param pos Position of the camera in 3D space
		 * @param direction Direction the camera aims at
		 * @param up Vector that defines the camera up direction
		 */
		static Matrix4x4<T> makeView(Vector3<T> const& pos, Vector3<T> const& direction, Vector3<T> const& up);
		/**
		 * @brief Makes this matrix a camera matrix from the given data
		 * @param pos Position of the camera in 3D space
		 * @param direction Direction the camera aims at
		 * @param up Vector that defines the camera up direction
		 */
		void view(Vector3<T> const& pos, Vector3<T> const& direction, Vector3<T> const& up);
		/**
		 * @brief Constructs a projection matrix from the given data
		 * @param fieldOfView Angle of aperture
		 * @param aspectRatio Aspect ratio of the display
		 * @param near Near clipping plane
		 * @param far Far clipping plane
		 */
		static Matrix4x4<T> makeProjection(T fieldOfView, T aspectRatio, T near, T far);
		/**
		 * @brief Makes this matrix a projection matrix from the given data
		 * @param fieldOfView Angle of aperture
		 * @param aspectRatio Aspect ratio of the display
		 * @param near Near clipping plane
		 * @param far Far clipping plane
		 */
		void projection(T fieldOfView, T aspectRatio, T near, T far);
		/**
		 * @brief Returns a transposed copy of this matrix
		 */
		inline Matrix4x4<T> getTransposed() const;
		// Operators
		/**
		 * @brief Assignment operator
		 * @param rhs Other matrix
		 * @return Reference to this
		 */
		inline Matrix4x4<T>& operator=(BaseMatrixType const& rhs);
		/**
		 * @brief Component-wise addition
		 * @param rhs Other matrix
		 * @return Resulting matrix
		 */
		inline const Matrix4x4<T> operator+(BaseMatrixType const& rhs) const;
		/**
		 * @brief Component-wise addition, assigning the resulting matrix to this
		 * @param rhs Other matrix
		 * @return Reference to this
		 */
		inline Matrix4x4<T>& operator+=(BaseMatrixType const& rhs);
		/**
		 * @brief Component-wise subtraction
		 * @param rhs Other matrix
		 * @return Resulting matrix
		 */
		inline const Matrix4x4<T> operator-(BaseMatrixType const& rhs) const;
		/**
		 * @brief Component-wise subtraction, assigning the resulting matrix to this
		 * @param rhs Other matrix
		 * @return Reference to this
		 */
		inline Matrix4x4<T>& operator-=(BaseMatrixType const& rhs);
		/**
		 * @brief Matrix multiplication
		 * @param rhs Other matrix
		 * @return Resulting matrix
		 */
		template<unsigned int O> inline const Matrix<T, 4, O> operator*(Matrix<T, O, 4> const& rhs) const;
		/**
		 * @brief Matrix multiplication
		 * @param rhs Other matrix
		 * @return Resulting matrix
		 */
		inline const Matrix4x4<T> operator*(Matrix<T, 4, 4> const& rhs) const;
		/**
		 * @brief Matrix-vector multiplication
		 * @param rhs Vector
		 * @return Resulting vector
		 */
		inline const Vector4<T> operator*(Vector<T, 4> const& rhs) const;
		/**
		 * @brief Scalar multiplication
		 * @param rhs Scalar
		 * @return Resulting matrix
		 */
		inline const Matrix4x4<T> operator*(T const& rhs) const;
		/**
		 * @brief Scalar multiplication, assigning the resulting matrix to this
		 * @param rhs Scalar
		 * @return Reference to this
		 */
		inline Matrix4x4<T>& operator*=(T const& rhs);
		/**
		 * @brief Scalar division
		 * @param rhs Scalar
		 * @return Resulting matrix
		 */
		inline const Matrix4x4<T> operator/(T const& rhs) const;
		/**
		 * @brief Scalar division, assigning the resulting matrix to this
		 * @param rhs Other matrix
		 * @return Reference to this
		 */
		inline Matrix4x4<T>& operator/=(T const& rhs);
		/**
		 * @brief Unary minus. Inverts the signs of all components
		 * @return Resulting matrix
		 */
		inline Matrix4x4<T> operator-() const;
	private:
	};

	// Free function operators
	/**
	 * @brief Scalar multiplication
	 * @param lhs Matrix
	 * @param rhs Scalar
	 * @return Resulting matrix
	 */
	template<typename T> inline Matrix4x4<T> operator*(Matrix<T, 4, 4> const& lhs, T const& rhs);
	/**
	 * @brief Scalar multiplication
	 * @param lhs Scalar
	 * @param rhs Matrix
	 * @return Resulting matrix
	 */
	template<typename T> inline Matrix4x4<T> operator*(T const& lhs, Matrix<T, 4, 4> const& rhs);

	// Some default types
	/**
	 * @brief 4x4 matrix of integers
	 */
	using Mat4i = Matrix4x4<int>;
	/**
	 * @brief 4x4 matrix of floats
	 */
	using Mat4f = Matrix4x4<float>;
	/**
	 * @brief 4x4 matrix of doubles
	 */
	using Mat4d = Matrix4x4<double>;
}

#include "Matrix4x4.imp"

#endif /* MATRIX4X4_H_ */
