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
		 * @brief Constructs a new vector and initializes all values with the same value
		 * @param value Value used to initialize
		 */
		explicit Vector3(T value);
		/**
		 * @brief Constructs a new vector from a lower-dimensionality vector and sets the remaining elements to zero
		 */
		template<unsigned int N2> Vector3(Vector<T, N2> const& other);
	    /**
	     * @brief Copies a vector
	     */
	    Vector3(const BaseVectorType &other);
		/**
		 * @brief Constructs a new vector from an initializer list
		 * @param args Arguments
		 */
	    Vector3(std::initializer_list<T> args);
	    // Destructors
	    ~Vector3();
	    // Methods
	    /**
	     * @brief Returns the vector's first element
	     */
	    inline T const& x() const;
	    /**
	     * @brief Returns the vector's first element
	     */
	    inline T& x();
	    /**
	     * @brief Returns the vector's second element
	     */
	    inline T const& y() const;
	    /**
	     * @brief Returns the vector's second element
	     */
	    inline T& y();
	    /**
	     * @brief Returns the vector's third element
	     */
	    inline T const& z() const;
	    /**
	     * @brief Returns the vector's third element
	     */
	    inline T& z();
	    /**
	     * @brief Translates this vector by the specified amount
	     */
	    Vector3<T>& translate(T x, T y, T z);
		/**
		 * @brief Normalizes this vector so it has the length 1
		 */
	    inline Vector3<T>& normalize();
		/**
		 * @brief Returns a normalized copy of this vector of length 1
		 */
		inline Vector3<T> getNormalized() const;
		/**
		 * @brief Returns a new vector that is the cross product of
		 *        this vector and the passed vector
		 */
		inline Vector3<T> cross(BaseVectorType const& rhs) const;
		// Operators
		/**
		 * @brief Assignment operator
		 * @param rhs Other vector
		 * @return Reference to this
		 */
		inline Vector3<T>& operator=(BaseVectorType const& rhs);
		/**
		 * @brief Adds another vector to this vector
		 * @param rhs Vector to add
		 * @return The resulting vector
		 */
		inline Vector3<T> operator+(BaseVectorType const& rhs) const;
		/**
		 * @brief Adds another vector to this vector, assigning the resulting vector to this
		 * @param rhs Vector to add
		 * @return Reference to this
		 */
		inline Vector3<T>& operator+=(BaseVectorType const& rhs);
		/**
		 * @brief Subtracts another vector from this vector
		 * @param rhs Vector to subtract
		 * @return The resulting vector
		 */
		inline Vector3<T> operator-(BaseVectorType const& rhs) const;
		/**
		 * @brief Subtracts another vector from this vector, assigning the resulting vector to this
		 * @param rhs Vector to subtract
		 * @return Reference tot his
		 */
		inline Vector3<T>& operator-=(BaseVectorType const& rhs);
		/**
		 * @brief Dot product
		 * @param rhs Vector to calculate the dot product with
		 * @return Resulting scalar
		 */
		inline T operator*(BaseVectorType const& rhs) const;
		/**
		 * @brief Scalar multiplication
		 * @param rhs Scalar
		 * @return Resulting vector
		 */
		inline Vector3<T> operator*(T const& rhs) const;
		/**
		 * @brief Scalar multiplication, assigning the resulting vector to this
		 * @param rhs Scalar
		 * @return Reference to this
		 */
		inline Vector3<T>& operator*=(T const& rhs);
		/**
		 * @brief Cross product, assigning the resulting vector to this
		 * @param rhs Other vector
		 * @return Reference to this
		 */
		inline Vector3<T>& operator*=(BaseVectorType const& rhs);
		/**
		 * @brief Scalar division
		 * @param rhs Scalar
		 * @return Resulting vector
		 */
		inline Vector3<T> operator/(T const& rhs) const;
		/**
		 * @brief Scalar division, assigning the resulting vector to this
		 * @param rhs Scalar
		 * @return Reference to this
		 */
		inline Vector3<T>& operator/=(T const& rhs);
		/**
		 * @brief Unary minus. Inverts the signs of all components.
		 * @return Resulting vector
		 */
		inline Vector3<T> operator-() const;

	private:
    };

	// Free function operators
	/**
	 * @brief Scalar multiplication. Scales the vector by rhs
	 * @param lhs Vector to scale
	 * @param rhs Scalar
	 * @return Result of the operation
	 */
	template<typename T> inline Vector3<T> operator*(Vector<T, 3> const& lhs, T const& rhs);
	/**
	 * @brief Scalar multiplication. Scales the vector by lhs
	 * @param lhs Scalar
	 * @param rhs Vector to scale
	 * @return Result of the operation
	 */
	template<typename T> inline Vector3<T> operator*(T const& lhs, Vector<T, 3> const& rhs);

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
