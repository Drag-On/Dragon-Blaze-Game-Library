//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include<cstdlib>
#include<cstddef>
#include<cmath>
#include"Log/Log.h"

namespace dbgl
{
    /// <summary>
    /// @brief Vector of dimension 2
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
    template<typename T> class Vector2
    {
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a new null vector
	    /// </summary>
	    Vector2();
	    /// <summary>
	    /// @brief Constructs a new vector from the given coordinates
	    /// </summary>
	    Vector2(T x, T y);
	    /// <summary>
	    /// @brief Copies a vector
	    /// </summary>
	    Vector2(const Vector2<T> &other);
	    // Destructors
	    ~Vector2();
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
	    Vector2<T>& normalize();
	    /// <summary>
	    /// @brief Returns a normalized copy of this vector of length 1
	    /// </summary>
	    Vector2<T> getNormalized() const;
	    /// <summary>
	    /// @brief Returns a new vector that is the cross product of
	    ///	       this vector and the passed vector
	    /// </summary>
	    Vector2<T> getCrossProduct(Vector2<T> const& rhs) const;
	    /// <summary>
	    /// @brief Checks if all components are zero
	    /// </summary>
	    bool isZero() const;
	    /// <summary>
	    /// @brief Translates this vector by the specified amount
	    /// </summary>
	    Vector2<T>& translate(T x, T y);
	    // Operators
	    Vector2<T>& operator=(Vector2<T> const& rhs);
	    const Vector2<T> operator+(Vector2<T> const& rhs) const;
	    Vector2<T>& operator+=(Vector2<T> const& rhs);
	    const Vector2<T> operator-(Vector2<T> const& rhs) const;
	    Vector2<T>& operator-=(Vector2<T> const& rhs);
	    const T operator*(Vector2<T> const& rhs) const;
	    const Vector2<T> operator*(T const& rhs) const;
	    Vector2<T>& operator*=(T const& rhs);
	    Vector2<T>& operator*=(Vector2<T> const& rhs);
	    const Vector2<T> operator/(T const& rhs) const;
	    Vector2<T>& operator/=(T const& rhs);
	    Vector2<T> operator-() const;
	    bool operator==(Vector2<T> const& rhs) const;
	    bool operator!=(Vector2<T> const& rhs) const;
	    bool operator<(Vector2<T> const& rhs) const;
	    bool operator>(Vector2<T> const& rhs) const;
	    bool operator<=(Vector2<T> const& rhs) const;
	    bool operator>=(Vector2<T> const& rhs) const;
	    T& operator[](std::size_t const& index);
	    const T& operator[](std::size_t const& index) const;

	private:
	    T _x, _y;
    };

    // Some default types
    using Vec2i = Vector2<int>;
    using Vec2f = Vector2<float>;
    using Vec2d = Vector2<double>;
}

#include "Vector2.imp"

#endif /* VECTOR2_H_ */
