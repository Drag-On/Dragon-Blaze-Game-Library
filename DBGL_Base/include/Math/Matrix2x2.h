//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATRIX2X2_H_
#define MATRIX2X2_H_

#include "Log/Log.h"
#include "Vector2.h"

namespace dbgl
{
    /// <summary>
    /// @brief Matrix of size 2 by 2
    /// @author Jan Moeller
    /// </summary>
    template<typename T> class Matrix2x2
    {
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a 2x2 identity matrix
	    /// </summary>
	    Matrix2x2();
	    /// <summary>
	    /// @brief Copies another 2x2 matrix
	    /// </summary>
	    Matrix2x2(const Matrix2x2<T> &other);
	    // Destructors
	    ~Matrix2x2();
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
	    Matrix2x2<T> getTransposed() const;
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
	    Matrix2x2<T> getInverted() const;
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
	    /// @brief Constructs a rotation matrix from the given angle
	    /// @param angle Angle to rotate around
	    /// </summary>
	    static Matrix2x2<T> makeRotation(T angle);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factor
	    /// @param factor Factor to scale by
	    /// </summary>
	    static Matrix2x2<T> makeScale(T factor);
	    /// <summary>
	    /// @brief Constructs a scale matrix from the given factors
	    /// @param x Factor to scale by in x direction
	    /// @param y Factor to scale by in y direction
	    /// </summary>
	    static Matrix2x2<T> makeScale(T x, T y);
	    // Operators
	    Matrix2x2<T>& operator=(Matrix2x2<T> const& rhs);
	    const Matrix2x2<T> operator+(Matrix2x2<T> const& rhs) const;
	    Matrix2x2<T>& operator+=(Matrix2x2<T> const& rhs);
	    const Matrix2x2<T> operator-(Matrix2x2<T> const& rhs) const;
	    Matrix2x2<T>& operator-=(Matrix2x2<T> const& rhs);
	    const Matrix2x2<T> operator*(Matrix2x2<T> const& rhs) const;
	    const Vector2<T> operator*(Vector2<T> const& rhs) const;
	    const Matrix2x2<T> operator*(T const& rhs) const;
	    Matrix2x2<T>& operator*=(Matrix2x2<T> const& rhs);
	    Matrix2x2<T>& operator*=(T const& rhs);
	    const Matrix2x2<T> operator/(T const& rhs) const;
	    Matrix2x2<T>& operator/=(T const& rhs);
	    Matrix2x2<T> operator-() const;
	    bool operator==(Matrix2x2<T> const& rhs) const;
	    bool operator!=(Matrix2x2<T> const& rhs) const;
	    Vector2<T>& operator[](std::size_t const& index);
	    const Vector2<T>& operator[](std::size_t const& index) const;

	private:
	    Vector2<T> _columns[2];
    };

    // Some default types
    using Mat2i = Matrix2x2<int>;
    using Mat2f = Matrix2x2<float>;
    using Mat2d = Matrix2x2<double>;
}

#include "Matrix2x2.imp"

#endif /* MATRIX2X2_H_ */
