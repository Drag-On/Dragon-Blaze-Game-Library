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
    /**
     * @brief Matrix of arbitrary size
     */
    template<typename T, unsigned int N, unsigned int M> class Matrix
    {
	public:
	    /**
	     * @brief Creates an identity matrix of the desired size
	     */
	    Matrix();
	    /**
	     * @brief Copies the passed matrix
	     */
	    Matrix(const Matrix<T, N, M> &other);
	    /**
	     * @brief Destructor
	     */
	    ~Matrix();
	    // Methods
	    /**
	     * @brief Gets the amount of columns of this matrix
	     */
	    static constexpr int getWidth();
	    /**
	     * @brief Gets the amount of lines of this matrix
	     */
	    static constexpr int getHeight();
	    /**
	     * @brief Returns a transposed copy of this matrix
	     */
	    Matrix<T, M, N> getTransposed() const;
	    /**
	     * @brief Checks if all elements are zero
	     */
	    bool isZero() const;
	    /**
	     * @brief Checks if this matrix is an identity matrix
	     */
	    bool isIdentity() const;
	    /**
	     * @brief Grants access to the internal memory
	     * @return A pointer to the first element of this matrix
	     */
	    const T* getDataPointer() const;
	    // Operators
	    /**
	     * @brief Assignment operator
	     * @param rhs Other matrix
	     * @return Reference to this
	     */
	    Matrix<T, N, M>& operator=(Matrix<T, N, M> const& rhs);
	    /**
	     * @brief Component-wise addition
	     * @param rhs Other matrix
	     * @return Resulting matrix
	     */
	    const Matrix<T, N, M> operator+(Matrix<T, N, M> const& rhs) const;
	    /**
	     * @brief Component-wise addition, assigning the resulting matrix to this
	     * @param rhs Other matrix
	     * @return Reference to this
	     */
	    Matrix<T, N, M>& operator+=(Matrix<T, N, M> const& rhs);
	    /**
	     * @brief Component-wise subtraction
	     * @param rhs Other matrix
	     * @return Resulting matrix
	     */
	    const Matrix<T, N, M> operator-(Matrix<T, N, M> const& rhs) const;
	    /**
	     * @brief Component-wise subtraction, assigning the resulting matrix to this
	     * @param rhs Other matrix
	     * @return Reference to this
	     */
	    Matrix<T, N, M>& operator-=(Matrix<T, N, M> const& rhs);
	    /**
	     * @brief Matrix multiplication
	     * @param rhs Other matrix
	     * @return Resulting matrix
	     */
	    template<unsigned int O> const Matrix<T, M, O> operator*(Matrix<T, O, N> const& rhs) const;
	    /**
	     * @brief Matrix-vector multiplication
	     * @param rhs Vector
	     * @return Resulting vector
	     */
	    const Vector<T, M> operator*(Vector<T, N> const& rhs) const;
	    /**
	     * @brief Scalar multiplication
	     * @param rhs Scalar
	     * @return Resulting matrix
	     */
	    const Matrix<T, N, M> operator*(T const& rhs) const;
	    /**
	     * @brief Scalar multiplication, assigning the resulting matrix to this
	     * @param rhs Scalar
	     * @return Reference to this
	     */
	    Matrix<T, N, M>& operator*=(T const& rhs);
	    /**
	     * @brief Scalar division
	     * @param rhs Scalar
	     * @return Resulting matrix
	     */
	    const Matrix<T, N, M> operator/(T const& rhs) const;
	    /**
	     * @brief Scalar division, assigning the resulting matrix to this
	     * @param rhs Other matrix
	     * @return Reference to this
	     */
	    Matrix<T, N, M>& operator/=(T const& rhs);
	    /**
	     * @brief Unary minus. Inverts the signs of all components
	     * @return Resulting matrix
	     */
	    Matrix<T, N, M> operator-() const;
	    /**
	     * @brief Equality operator. Checks for value equality.
	     * @param rhs Other matrix
	     * @return True if all values are equal, otherwise false
	     */
	    bool operator==(Matrix<T, N, M> const& rhs) const;
	    /**
	     * @brief Inequality operator. Checks for value inequality.
	     * @param rhs Other matrix
	     * @return True if not all values are equal, otherwise false
	     */
	    bool operator!=(Matrix<T, N, M> const& rhs) const;
	    /**
	     * @brief Access operator. Grants access to a column.
	     * @param index Index of the column to access
	     * @return The requested column vector
	     */
	    Vector<T, M>& operator[](std::size_t const& index);
	    /**
	     * @brief Access operator. Grants access to a column.
	     * @param index Index of the column to access
	     * @return The requested column vector
	     */
	    const Vector<T, M>& operator[](std::size_t const& index) const;

	private:
	    /**
	     * @brief Columns of the matrix
	     */
	    Vector<T, M> m_columns[N];
    };

    // Free function operators
    /**
     * @brief Scalar multiplication
     * @param lhs Matrix
     * @param rhs Scalar
     * @return Resulting matrix
     */
    template<typename T, unsigned int N, unsigned int M> const Matrix<T, N, M> operator*(Matrix<T, N, M> const& lhs, T const& rhs);
    /**
     * @brief Scalar multiplication
     * @param lhs Scalar
     * @param rhs Matrix
     * @return Resulting matrix
     */
    template<typename T, unsigned int N, unsigned int M> const Matrix<T, N, M> operator*(T const& lhs, Matrix<T, N, M> const& rhs);
}

#include "Matrix.imp"

#endif /* MATRIX_H_ */
