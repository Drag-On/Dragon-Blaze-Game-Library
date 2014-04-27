//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cstdlib>
#include <cstddef>
#include <cmath>
#include "Utility.h"
#include "Vector.h"
#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    /// <summary>
    /// @brief Vector of dimension 3
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
    template<typename T> class Vector3 : public Vector<T, 3>
    {
	private:
	    /**
	     * @brief Type this class is derived from
	     */
	    using BaseVectorType = Vector<T, 3>;

	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a new null vector
	    /// </summary>
	    Vector3();
	    /// <summary>
	    /// @brief Constructs a new vector from the given coordinates
	    /// </summary>
	    Vector3(T x, T y, T z);
	    /// <summary>
	    /// @brief Copies a vector
	    /// </summary>
	    Vector3(const BaseVectorType &other);
	    // Destructors
	    ~Vector3();
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
	    /// @brief Translates this vector by the specified amount
	    /// </summary>
	    Vector3<T>& translate(T x, T y, T z);
	    // Operators
	    using BaseVectorType::operator=;

	private:
    };

    // Some default types
    /**
     * @brief 3D vector of integers
     */
    using Vec3i = Vector3<int>;
    /**
     * @brief 3D vector of floats
     */
    using Vec3f = Vector3<float>;
    /**
     * @brief 3D vector of doubles
     */
    using Vec3d = Vector3<double>;
}

#include "Vector3.imp"

#endif /* VECTOR3_H_ */
