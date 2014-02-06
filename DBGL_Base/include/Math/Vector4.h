//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR4_H_
#define VECTOR4_H_

#include<cstddef>
#include<cmath>

namespace dbgl
{
    /// <summary>
    /// @brief Vector of dimension 4
    /// @author Jan Moeller
    ///
    /// @details Since it's not possible to implement dot product and
    ///		 cross product as operator, * does the dot product. For
    ///		 convenience there is a method getCrossProduct() which
    ///		 returns a new vector containing the cross product of
    ///		 this vector and another one. For the *= operator there
    ///		 is an overload for the cross product, but not for the
    ///		 dot product.
    /// </summary>
    template<typename T> class Vector4
    {
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a new null vector
	    /// </summary>
	    Vector4();
	    /// <summary>
	    /// @brief Constructs a new vector from the given coordinates
	    /// </summary>
	    Vector4(T x, T y, T z, T w);
	    /// <summary>
	    /// @brief Copies a vector
	    /// </summary>
	    Vector4(const Vector4<T> &other);
	    // Destructors
	    ~Vector4();
	    // Methods
	    /// <summary>
	    /// @brief Returns the dimension of this vector
	    /// </summary>
	    std::size_t getDimension() const;
	    /// <summary>
	    /// @brief Returns the vector's first element
	    /// </summary>
	    T getX() const;
	    /// <summary>
	    /// @brief Returns the vector's second element
	    /// </summary>
	    T getY() const;
	    /// <summary>
	    /// @brief Returns the vector's third element
	    /// </summary>
	    T getZ() const;
	    /// <summary>
	    /// @brief Returns the vector's fourth element
	    /// </summary>
	    T getW() const;
	    /// <summary>
	    /// @brief Returns the squared length of this vector
	    /// </summary>
	    T getSquaredLength() const;
	    /// <summary>
	    /// @brief Returns the length of this vector
	    /// </summary>
	    T getLength() const;
	    /// <summary>
	    /// @brief Normalizes this vector so it has the length 1
	    /// </summary>
	    void normalize();
	    /// <summary>
	    /// @brief Returns a normalized copy of this vector of length 1
	    /// </summary>
	    Vector4<T> getNormalized() const;
	    /// <summary>
	    /// @brief Returns a new vector that is the cross product of
	    ///	       this vector and the passed vector
	    /// </summary>
	    Vector4<T> getCrossProduct(Vector4<T> rhs);
	    /// <summary>
	    /// @brief Checks if all components are zero
	    /// </summary>
	    bool isZero();
	    // Operators
	    Vector4<T>& operator=(Vector4<T> const& rhs);
	    const Vector4<T> operator+(Vector4<T> const& rhs);
	    Vector4<T>& operator+=(Vector4<T> const& rhs);
	    const Vector4<T> operator-(Vector4<T> const& rhs);
	    Vector4<T>& operator-=(Vector4<T> const& rhs);
	    const T operator*(Vector4<T> const& rhs);
	    const Vector4<T> operator*(T const& rhs);
	    Vector4<T>& operator*=(T const& rhs);
	    Vector4<T>& operator*=(Vector4<T> const& rhs);
	    const Vector4<T> operator/(T const& rhs);
	    Vector4<T>& operator/=(T const& rhs);
	    Vector4<T> operator-() const;
	    bool operator==(Vector4<T> const& rhs);
	    bool operator!=(Vector4<T> const& rhs);
	    bool operator<(Vector4<T> const& rhs);
	    bool operator>(Vector4<T> const& rhs);
	    bool operator<=(Vector4<T> const& rhs);
	    bool operator>=(Vector4<T> const& rhs);
	    T& operator[](std::size_t const& index);
	    const T& operator[](std::size_t const& index) const;

	private:
	    T _x, _y, _z, _w;
    };
}

#include "Vector4.imp"

#endif /* VECTOR4_H_ */
