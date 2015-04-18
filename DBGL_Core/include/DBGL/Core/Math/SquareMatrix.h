//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_MATH_SQUAREMATRIX_H_
#define INCLUDE_DBGL_CORE_MATH_SQUAREMATRIX_H_

#include "Matrix.h"

namespace dbgl
{
	/**
	 * @brief Intermediate class for square matrix types
	 */
	template<typename T, unsigned int D> class SquareMatrix: public Matrix<T, D, D>
	{
	public:
		/**
		 * @brief Creates an identity matrix of the desired size
		 */
		SquareMatrix();
		/**
		 * @brief Creates a matrix and fills it with the passed value
		 */
		explicit SquareMatrix(T value);
		/**
		 * @brief Copies the passed matrix
		 */
		SquareMatrix(const Matrix<T, D, D> &other);
		/**
		 * @brief Constructs a new matrix from a lower-dimensionality matrix and sets the remaining elements to unit
		 */
		template<unsigned int N2, unsigned int M2> SquareMatrix(Matrix<T, N2, M2> const& other);
		/**
		 * @brief Constructs a new matrix from an initializer list
		 * @param args Columns
		 */
		SquareMatrix(std::initializer_list<Vector<T, D>> args);
		/**
		 * @brief Computes a minor matrix by deleting a row and a column
		 * @param column Column to delete
		 * @param row Row to delete
		 * @return The minor matrix
		 */
		SquareMatrix<T, D - 1> minor(unsigned int column, unsigned int row) const;
		/**
		 * @brief Computes the determinant of the matrix
		 * @return The determinant
		 */
		T determinant() const;
	};

	/**
	 * @brief Template specialization for matrices of size one. Note: This is only to stop compile-time recursion for
	 * 		  the minor() method. It doesn't actually have any implementation.
	 */
	template<typename T> class SquareMatrix<T, 1> : public Matrix<T, 1, 1>
	{
	public:
	/**
	 * @copydoc SquareMatrix::minor()
	 */
	SquareMatrix<T, 1> minor(unsigned int row, unsigned int column) const;
	/**
	 * @copydoc SquareMatrix::determinant()
	 */
	T determinant() const;
	};
}

#include "SquareMatrix.imp"

#endif /* INCLUDE_DBGL_CORE_MATH_SQUAREMATRIX_H_ */
