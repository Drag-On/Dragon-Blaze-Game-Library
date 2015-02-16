//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <cstdlib>
#include <cstddef>
#include <cmath>
#include "Utility.h"
#include "Vector.h"
#include "DBGL/Core/Debug/Log.h"

namespace dbgl
{
    /**
     * @brief Vector of dimension 2
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
    template<typename T> class Vector2 : public Vector<T, 2>
    {
	private:
	    /**
	     * @brief Type this class is derived from
	     */
	    using BaseVectorType = Vector<T, 2>;

	public:
	    // Constructors
	    /**
	     * @brief Constructs a new null vector
	     */
	    Vector2();
	    /**
	     * @brief Constructs a new vector from the given coordinates
	     */
	    Vector2(T x, T y);
	    /**
	     * @brief Copies a vector
	     */
	    Vector2(const BaseVectorType &other);
	    // Destructors
	    ~Vector2();
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
	     * @brief Translates this vector by the specified amount
	     */
	    Vector2<T>& translate(T x, T y);
	    // Operators
	    using BaseVectorType::operator=;

	private:
    };

    // Some default types
    /**
     * @brief 2D vector of integers
     */
    using Vec2i = Vector2<int>;
    /**
     * @brief 2D vector of floats
     */
    using Vec2f = Vector2<float>;
    /**
     * @brief 2D vector of doubles
     */
    using Vec2d = Vector2<double>;
}

#include "Vector2.imp"

#endif /* VECTOR2_H_ */
