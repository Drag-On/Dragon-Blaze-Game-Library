//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX2X2_H_
#define MATRIX2X2_H_

#include "DBGL/Core/Debug/Log.h"
#include "Matrix.h"
#include "Vector2.h"

namespace dbgl
{
	/**
	 * @brief Matrix of size 2 by 2
	 * @author Jan Moeller
	 */
	template<typename T> class Matrix2x2: public Matrix<T, 2, 2>
	{
		using BaseMatrixType = Matrix<T, 2, 2>;
	public:
		// Constructors
		/**
		 * @brief Constructs a 2x2 identity matrix
		 */
		Matrix2x2();
		/**
		 * @brief Creates a matrix and fills it with the passed value
		 */
		explicit Matrix2x2(T value);
		/**
		 * @brief Constructs a new matrix from a lower-dimensionality matrix and sets the remaining elements to unit
		 */
		template<unsigned int N2, unsigned int M2> Matrix2x2(Matrix<T, N2, M2> const& other);
		/**
		 * @brief Constructs a new matrix from an initializer list
		 * @param args Columns
		 */
		Matrix2x2(std::initializer_list<Vector<T, 2>> args);
		/**
		 * @brief Copies another 2x2 matrix
		 */
		Matrix2x2(const BaseMatrixType &other);
		// Destructors
		~Matrix2x2();
		// Methods
		/**
		 * @brief Transposes this matrix
		 */
		Matrix2x2<T>& transpose();
		/**
		 * @brief Inverts this matrix so that a multiplication with
		 * 	   the original results in an identity matrix
		 */
		Matrix2x2<T>& invert();
		/**
		 * @brief Returns an inverted version of this matrix so that
		 * 	   a multiplication with the original results in an
		 * 	   identity matrix
		 */
		Matrix2x2<T> getInverted() const;
		/**
		 * @brief Constructs a rotation matrix from the given angle
		 * @param angle Angle to rotate around
		 */
		static Matrix2x2<T> makeRotation(T angle);
		/**
		 * @brief Constructs a scale matrix from the given factor
		 * @param factor Factor to scale by
		 */
		static Matrix2x2<T> makeScale(T factor);
		/**
		 * @brief Constructs a scale matrix from the given factors
		 * @param x Factor to scale by in x direction
		 * @param y Factor to scale by in y direction
		 */
		static Matrix2x2<T> makeScale(T x, T y);
		/**
		 * @brief Returns a transposed copy of this matrix
		 */
		inline Matrix2x2<T> getTransposed() const;
		// Operators
		/**
		 * @brief Assignment operator
		 * @param rhs Other matrix
		 * @return Reference to this
		 */
		inline Matrix2x2<T>& operator=(BaseMatrixType const& rhs);
		/**
		 * @brief Component-wise addition
		 * @param rhs Other matrix
		 * @return Resulting matrix
		 */
		inline const Matrix2x2<T> operator+(BaseMatrixType const& rhs) const;
		/**
		 * @brief Component-wise addition, assigning the resulting matrix to this
		 * @param rhs Other matrix
		 * @return Reference to this
		 */
		inline Matrix2x2<T>& operator+=(BaseMatrixType const& rhs);
		/**
		 * @brief Component-wise subtraction
		 * @param rhs Other matrix
		 * @return Resulting matrix
		 */
		inline const Matrix2x2<T> operator-(BaseMatrixType const& rhs) const;
		/**
		 * @brief Component-wise subtraction, assigning the resulting matrix to this
		 * @param rhs Other matrix
		 * @return Reference to this
		 */
		inline Matrix2x2<T>& operator-=(BaseMatrixType const& rhs);
		/**
		 * @brief Matrix multiplication
		 * @param rhs Other matrix
		 * @return Resulting matrix
		 */
		template<unsigned int O> inline const Matrix<T, 2, O> operator*(Matrix<T, O, 2> const& rhs) const;
		/**
		 * @brief Matrix multiplication
		 * @param rhs Other matrix
		 * @return Resulting matrix
		 */
		inline const Matrix2x2<T> operator*(Matrix<T, 2, 2> const& rhs) const;
		/**
		 * @brief Matrix-vector multiplication
		 * @param rhs Vector
		 * @return Resulting vector
		 */
		inline const Vector2<T> operator*(Vector<T, 2> const& rhs) const;
		/**
		 * @brief Scalar multiplication
		 * @param rhs Scalar
		 * @return Resulting matrix
		 */
		inline const Matrix2x2<T> operator*(T const& rhs) const;
		/**
		 * @brief Scalar multiplication, assigning the resulting matrix to this
		 * @param rhs Scalar
		 * @return Reference to this
		 */
		inline Matrix2x2<T>& operator*=(T const& rhs);
		/**
		 * @brief Scalar division
		 * @param rhs Scalar
		 * @return Resulting matrix
		 */
		inline const Matrix2x2<T> operator/(T const& rhs) const;
		/**
		 * @brief Scalar division, assigning the resulting matrix to this
		 * @param rhs Other matrix
		 * @return Reference to this
		 */
		inline Matrix2x2<T>& operator/=(T const& rhs);
		/**
		 * @brief Unary minus. Inverts the signs of all components
		 * @return Resulting matrix
		 */
		inline Matrix2x2<T> operator-() const;
	private:
	};

	// Free function operators
	/**
	 * @brief Scalar multiplication
	 * @param lhs Matrix
	 * @param rhs Scalar
	 * @return Resulting matrix
	 */
	template<typename T> inline Matrix2x2<T> operator*(Matrix<T, 2, 2> const& lhs, T const& rhs);
	/**
	 * @brief Scalar multiplication
	 * @param lhs Scalar
	 * @param rhs Matrix
	 * @return Resulting matrix
	 */
	template<typename T> inline Matrix2x2<T> operator*(T const& lhs, Matrix<T, 2, 2> const& rhs);

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
