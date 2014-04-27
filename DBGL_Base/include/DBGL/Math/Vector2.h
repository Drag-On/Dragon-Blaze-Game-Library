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

#include <cstdlib>
#include <cstddef>
#include <cmath>
#include "Utility.h"
#include "Vector.h"
#include "DBGL/System/Log/Log.h"

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
    template<typename T> class Vector2 : public Vector<T, 2>
    {
	private:
	    /**
	     * @brief Type this class is derived from
	     */
	    using BaseVectorType = Vector<T, 2>;

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
	    Vector2(const BaseVectorType &other);
	    // Destructors
	    ~Vector2();
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
	    /// @brief Translates this vector by the specified amount
	    /// </summary>
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
