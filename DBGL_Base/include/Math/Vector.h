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

#include<cstddef>
#include<cmath>

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
	    /// @brief Returns a new vector that is the cross product of
	    ///	       this vector and the passed vector
	    /// </summary>
	    Vector<T, N> getCrossProduct(Vector<T, N> rhs);
	    /// <summary>
	    /// @brief Checks if all components are zero
	    /// </summary>
	    bool isZero();
	    // Operators
	    Vector<T, N>& operator=(Vector<T, N> const& rhs);
	    const Vector<T, N> operator+(Vector<T, N> const& rhs);
	    Vector<T, N>& operator+=(Vector<T, N> const& rhs);
	    const Vector<T, N> operator-(Vector<T, N> const& rhs);
	    Vector<T, N>& operator-=(Vector<T, N> const& rhs);
	    const T operator*(Vector<T, N> const& rhs);
	    const Vector<T, N> operator*(T const& rhs);
	    Vector<T, N>& operator*=(T const& rhs);
	    Vector<T, N>& operator*=(Vector<T, N> const& rhs);
	    const Vector<T, N> operator/(T const& rhs);
	    Vector<T, N>& operator/=(T const& rhs);
	    Vector<T, N> operator-() const;
	    bool operator==(Vector<T, N> const& rhs);
	    bool operator!=(Vector<T, N> const& rhs);
	    bool operator<(Vector<T, N> const& rhs);
	    bool operator>(Vector<T, N> const& rhs);
	    bool operator<=(Vector<T, N> const& rhs);
	    bool operator>=(Vector<T, N> const& rhs);
	    T& operator[](std::size_t const& index);
	    const T& operator[](std::size_t const& index) const;

	private:
	    T _elements[N];
    };
}

#include "Vector.imp"

#endif /* VECTOR_H_ */
