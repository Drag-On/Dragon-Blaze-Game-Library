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
    /**
     * @brief Vector of dimension 4
     * @author Jan Moeller
     *
     * @details Since it's not possible to implement dot product and
     * 		 cross product as operator, * does the dot product. For
     * 		 convenience there is a method getCrossProduct() which
     * 		 returns a new vector containing the cross product of
     * 		 this vector and another one. For the *= operator there
     * 		 is an overload for the cross product, but not for the
     * 		 dot product.
     */
    template<typename T> class Vector4 : public Vector<T, 4>
    {
	private:
	    /**
	     * @brief Type this class is derived from
	     */
	    using BaseVectorType = Vector<T, 4>;

	public:
	    // Constructors
	    /**
	     * @brief Constructs a new null vector
	     */
	    Vector4();
	    /**
	     * @brief Constructs a new vector from the given coordinates
	     */
	    Vector4(T x, T y, T z, T w);
	    /**
	     * @brief Copies a vector
	     */
	    Vector4(const BaseVectorType &other);
	    // Destructors
	    ~Vector4();
	    // Methods
	    /**
	     * @brief Returns the vector's first element
	     */
	    const T& x() const;
	    /**
	     * @brief Returns the vector's first element
	     */
	    T& x();
	    /**
	     * @brief Returns the vector's second element
	     */
	    const T& y() const;
	    /**
	     * @brief Returns the vector's second element
	     */
	    T& y();
	    /**
	     * @brief Returns the vector's third element
	     */
	    const T& z() const;
	    /**
	     * @brief Returns the vector's third element
	     */
	    T& z();
	    /**
	     * @brief Returns the vector's fourth element
	     */
	    const T& w() const;
	    /**
	     * @brief Returns the vector's fourth element
	     */
	    T& w();
	    /**
	     * @brief Translates this vector by the specified amount
	     */
	    Vector4<T>& translate(T x, T y, T z, T w);
	    // Operators
	    using BaseVectorType::operator=;
	private:
    };

    // Some default types
    /**
     * @brief 4D vector of integers
     */
    using Vec4i = Vector4<int>;
    /**
     * @brief 4D vector of floats
     */
    using Vec4f = Vector4<float>;
    /**
     * @brief 4D vector of doubles
     */
    using Vec4d = Vector4<double>;
}

#include "Vector4.imp"

#endif /* VECTOR4_H_ */
