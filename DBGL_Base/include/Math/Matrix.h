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

#include "System/Log/Log.h"
#include "Vector.h"

namespace dbgl
{
    /// <summary>
    /// @brief Matrix of arbitrary size
    /// @author Jan Moeller
    /// </summary>
    template<typename T, unsigned int N, unsigned int M> class Matrix
    {
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Creates an identity matrix of the desired size
	    /// </summary>
	    Matrix();
	    /// <summary>
	    /// @brief Copies the passed matrix
	    /// </summary>
	    Matrix(const Matrix<T, N, M> &other);
	    // Destructors
	    ~Matrix();
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
	    Matrix<T, N, M>& operator=(Matrix<T, N, M> const& rhs);
	    const Matrix<T, N, M> operator+(Matrix<T, N, M> const& rhs) const;
	    Matrix<T, N, M>& operator+=(Matrix<T, N, M> const& rhs);
	    const Matrix<T, N, M> operator-(Matrix<T, N, M> const& rhs) const;
	    Matrix<T, N, M>& operator-=(Matrix<T, N, M> const& rhs);
	    template<unsigned int O> const Matrix<T, M, O> operator*(
		    Matrix<T, O, N> const& rhs) const;
	    const Vector<T, M> operator*(Vector<T, N> const& rhs) const;
	    const Matrix<T, N, M> operator*(T const& rhs) const;
	    Matrix<T, N, M>& operator*=(T const& rhs);
	    const Matrix<T, N, M> operator/(T const& rhs) const;
	    Matrix<T, N, M>& operator/=(T const& rhs);
	    Matrix<T, N, M> operator-() const;
	    bool operator==(Matrix<T, N, M> const& rhs) const;
	    bool operator!=(Matrix<T, N, M> const& rhs) const;
	    Vector<T, M>& operator[](std::size_t const& index);
	    const Vector<T, M>& operator[](std::size_t const& index) const;

	private:
	    Vector<T, M> m_columns[N];
    };
}

#include "Matrix.imp"

#endif /* MATRIX_H_ */
