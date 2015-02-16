//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
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
#include "DBGL/Core/Debug/Log.h"

namespace dbgl
{
    /**
     * @brief Vector of dimension 3
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
    template<typename T> class Vector3 : public Vector<T, 3>
    {
	private:
	    /**
	     * @brief Type this class is derived from
	     */
	    using BaseVectorType = Vector<T, 3>;

	public:
	    // Constructors
	    /**
	     * @brief Constructs a new null vector
	     */
	    Vector3();
	    /**
	     * @brief Constructs a new vector from the given coordinates
	     */
	    Vector3(T x, T y, T z);
	    /**
	     * @brief Copies a vector
	     */
	    Vector3(const BaseVectorType &other);
	    // Destructors
	    ~Vector3();
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
	     * @brief Translates this vector by the specified amount
	     */
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
