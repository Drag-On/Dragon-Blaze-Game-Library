//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR_H_
#define VECTOR_H_

#include<assert.h>
#include<cstdarg>
#include<cstddef>
#include<type_traits>
#include<cmath>
#include"Utility.h"
#include"System/Log/Log.h"

namespace dbgl
{
    /// <summary>
    /// @brief Vector of arbitrary dimension
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
    template<typename T, unsigned int N> class Vector
    {
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a new null vector
	    /// </summary>
	    Vector();
	    /// <summary>
	    /// @brief Constructs a new vector and initializes it
	    /// @param n Amount of passed parameters
	    /// @param ... n initialization values
	    /// </summary>
	    Vector(int n, ...);
	    /// <summary>
	    /// @brief Copies a vector
	    /// </summary>
	    Vector(const Vector<T, N> &other);
	    // Destructors
	    ~Vector();
	    // Methods
	    /// <summary>
	    /// @brief Returns the dimension of this vector
	    /// </summary>
	    std::size_t getDimension() const;
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
	    Vector<T, N> getNormalized() const;
	    /// <summary>
	    /// @brief Returns the dot product of this vector and the
	    ///	       passed vector
	    /// </summary>
	    T dot(Vector<T, N> const& rhs) const;
	    /// <summary>
	    /// @brief Returns a new vector that is the cross product of
	    ///	       this vector and the passed vector
	    /// </summary>
	    Vector<T, N> cross(Vector<T, N> const& rhs) const;
	    /// <summary>
	    /// @brief Checks if all components are zero
	    /// </summary>
	    bool isZero() const;
	    /// <summary>
	    /// @brief Checks if other is similar to this vector
	    /// @param other Other vector
	    /// @param precision How close every component needs to be
	    /// </summary>
	    bool isSimilar(Vector<T, N> const& other,
		    double precision = 0.1) const;
	    /// <summary>
	    /// @brief Grants access to the internal memory
	    /// @return A pointer to the first element of this vector
	    /// </summary>
	    const T* getDataPointer() const;
	    // Operators
	    Vector<T, N>& operator=(Vector<T, N> const& rhs);
	    const Vector<T, N> operator+(Vector<T, N> const& rhs) const;
	    Vector<T, N>& operator+=(Vector<T, N> const& rhs);
	    const Vector<T, N> operator-(Vector<T, N> const& rhs) const;
	    Vector<T, N>& operator-=(Vector<T, N> const& rhs);
	    const T operator*(Vector<T, N> const& rhs) const;
	    const Vector<T, N> operator*(T const& rhs) const;
	    Vector<T, N>& operator*=(T const& rhs);
	    Vector<T, N>& operator*=(Vector<T, N> const& rhs);
	    const Vector<T, N> operator/(T const& rhs) const;
	    Vector<T, N>& operator/=(T const& rhs);
	    Vector<T, N> operator-() const;
	    bool operator==(Vector<T, N> const& rhs) const;
	    bool operator!=(Vector<T, N> const& rhs) const;
	    bool operator<(Vector<T, N> const& rhs) const;
	    bool operator>(Vector<T, N> const& rhs) const;
	    bool operator<=(Vector<T, N> const& rhs) const;
	    bool operator>=(Vector<T, N> const& rhs) const;
	    T& operator[](std::size_t const& index);
	    const T& operator[](std::size_t const& index) const;

	private:
	    T m_elements[N];
    };
}

#include "Vector.imp"

#endif /* VECTOR_H_ */
