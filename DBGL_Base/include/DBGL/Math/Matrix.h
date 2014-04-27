//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX_H_
#define MATRIX_H_

#include "DBGL/System/Log/Log.h"
#include "Vector.h"

namespace dbgl
{
    /// <summary>
    /// @brief Matrix of arbitrary size
    /// </summary>
    template<typename T, unsigned int N, unsigned int M> class Matrix
    {
	public:
	    /// <summary>
	    /// @brief Creates an identity matrix of the desired size
	    /// </summary>
	    Matrix();
	    /// <summary>
	    /// @brief Copies the passed matrix
	    /// </summary>
	    Matrix(const Matrix<T, N, M> &other);
	    /// <summary>
	    /// @brief Destructor
	    /// </summary>
	    ~Matrix();
	    // Methods
	    /// <summary>
	    /// @brief Gets the amount of columns of this matrix
	    /// </summary>
	    static int getWidth();
	    /// <summary>
	    /// @brief Gets the amount of lines of this matrix
	    /// </summary>
	    static int getHeight();
	    /// <summary>
	    /// @brief Returns a transposed copy of this matrix
	    /// </summary>
	    Matrix<T, M, N> getTransposed() const;
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
	    // Operators
	    /// <summary>
	    /// @brief Assignment operator
	    /// @param rhs Other matrix
	    /// @return Reference to this
	    /// </summary>
	    Matrix<T, N, M>& operator=(Matrix<T, N, M> const& rhs);
	    /// <summary>
	    /// @brief Component-wise addition
	    /// @param rhs Other matrix
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix<T, N, M> operator+(Matrix<T, N, M> const& rhs) const;
	    /// <summary>
	    /// @brief Component-wise addition, assigning the resulting matrix to this
	    /// @param rhs Other matrix
	    /// @return Reference to this
	    /// </summary>
	    Matrix<T, N, M>& operator+=(Matrix<T, N, M> const& rhs);
	    /// <summary>
	    /// @brief Component-wise subtraction
	    /// @param rhs Other matrix
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix<T, N, M> operator-(Matrix<T, N, M> const& rhs) const;
	    /// <summary>
	    /// @brief Component-wise subtraction, assigning the resulting matrix to this
	    /// @param rhs Other matrix
	    /// @return Reference to this
	    /// </summary>
	    Matrix<T, N, M>& operator-=(Matrix<T, N, M> const& rhs);
	    /// <summary>
	    /// @brief Matrix multiplication
	    /// @param rhs Other matrix
	    /// @return Resulting matrix
	    /// </summary>
	    template<unsigned int O> const Matrix<T, M, O> operator*(Matrix<T, O, N> const& rhs) const;
	    /// <summary>
	    /// @brief Matrix-vector multiplication
	    /// @param rhs Vector
	    /// @return Resulting vector
	    /// </summary>
	    const Vector<T, M> operator*(Vector<T, N> const& rhs) const;
	    /// <summary>
	    /// @brief Scalar multiplication
	    /// @param rhs Scalar
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix<T, N, M> operator*(T const& rhs) const;
	    /// <summary>
	    /// @brief Scalar multiplication, assigning the resulting matrix to this
	    /// @param rhs Scalar
	    /// @return Reference to this
	    /// </summary>
	    Matrix<T, N, M>& operator*=(T const& rhs);
	    /// <summary>
	    /// @brief Scalar division
	    /// @param rhs Scalar
	    /// @return Resulting matrix
	    /// </summary>
	    const Matrix<T, N, M> operator/(T const& rhs) const;
	    /// <summary>
	    /// @brief Scalar division, assigning the resulting matrix to this
	    /// @param rhs Other matrix
	    /// @return Reference to this
	    /// </summary>
	    Matrix<T, N, M>& operator/=(T const& rhs);
	    /// <summary>
	    /// @brief Unary minus. Inverts the signs of all components
	    /// @return Resulting matrix
	    /// </summary>
	    Matrix<T, N, M> operator-() const;
	    /// <summary>
	    /// @brief Equality operator. Checks for value equality.
	    /// @param rhs Other matrix
	    /// @return True if all values are equal, otherwise false
	    /// </summary>
	    bool operator==(Matrix<T, N, M> const& rhs) const;
	    /// <summary>
	    /// @brief Inequality operator. Checks for value inequality.
	    /// @param rhs Other matrix
	    /// @return True if not all values are equal, otherwise false
	    /// </summary>
	    bool operator!=(Matrix<T, N, M> const& rhs) const;
	    /// <summary>
	    /// @brief Access operator. Grants access to a column.
	    /// @param index Index of the column to access
	    /// @return The requested column vector
	    /// </summary>
	    Vector<T, M>& operator[](std::size_t const& index);
	    /// <summary>
	    /// @brief Access operator. Grants access to a column.
	    /// @param index Index of the column to access
	    /// @return The requested column vector
	    /// </summary>
	    const Vector<T, M>& operator[](std::size_t const& index) const;

	private:
	    /**
	     * @brief Columns of the matrix
	     */
	    Vector<T, M> m_columns[N];
    };

    // Free function operators
    /// <summary>
    /// @brief Scalar multiplication
    /// @param lhs Matrix
    /// @param rhs Scalar
    /// @return Resulting matrix
    /// </summary>
    template<typename T, unsigned int N, unsigned int M> const Matrix<T, N, M> operator*(Matrix<T, N, M> const& lhs, T const& rhs);
    /// <summary>
    /// @brief Scalar multiplication
    /// @param lhs Scalar
    /// @param rhs Matrix
    /// @return Resulting matrix
    /// </summary>
    template<typename T, unsigned int N, unsigned int M> const Matrix<T, N, M> operator*(T const& lhs, Matrix<T, N, M> const& rhs);
}

#include "Matrix.imp"

#endif /* MATRIX_H_ */
