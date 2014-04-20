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

#include <cstdlib>
#include <cstddef>
#include <cmath>
#include "Utility.h"
#include "Vector.h"
#include "DBGL/System/Log/Log.h"

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
    template<typename T> class Vector4 : public Vector<T, 4>
    {
	    using BaseVectorType = Vector<T, 4>;

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
	    Vector4(const BaseVectorType &other);
	    // Destructors
	    ~Vector4();
	    // Methods
	    /// <summary>
	    /// @brief Returns the vector's first element
	    /// </summary>
	    const T& x() const;
	    /// <summary>
	    /// @brief Returns the vector's first element
	    /// </summary>
	    T& x();
	    /// <summary>
	    /// @brief Returns the vector's second element
	    /// </summary>
	    const T& y() const;
	    /// <summary>
	    /// @brief Returns the vector's second element
	    /// </summary>
	    T& y();
	    /// <summary>
	    /// @brief Returns the vector's third element
	    /// </summary>
	    const T& z() const;
	    /// <summary>
	    /// @brief Returns the vector's third element
	    /// </summary>
	    T& z();
	    /// <summary>
	    /// @brief Returns the vector's fourth element
	    /// </summary>
	    const T& w() const;
	    /// <summary>
	    /// @brief Returns the vector's fourth element
	    /// </summary>
	    T& w();
	    /// <summary>
	    /// @brief Translates this vector by the specified amount
	    /// </summary>
	    Vector4<T>& translate(T x, T y, T z, T w);
	    // Operators
	    using BaseVectorType::operator=;
	private:
    };

    // Some default types
    using Vec4i = Vector4<int>;
    using Vec4f = Vector4<float>;
    using Vec4d = Vector4<double>;
}

#include "Vector4.imp"

#endif /* VECTOR4_H_ */
