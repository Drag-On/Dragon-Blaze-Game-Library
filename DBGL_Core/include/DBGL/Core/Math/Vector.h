//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR_H_
#define VECTOR_H_

#include <assert.h>
#include <cstdarg>
#include <cstddef>
#include <type_traits>
#include <cmath>
#include <cstring>
#include <algorithm>
#include "Utility.h"
#include "DBGL/Core/Debug/Log.h"

namespace dbgl
{
	/**
	 * @brief Vector of arbitrary dimension
	 */
	template<typename T, unsigned int N> class Vector
	{
	public:
		/**
		 * @brief Constructs a new null vector
		 */
		Vector();
		/**
		 * @brief Constructs a new vector and initializes all values with the same value
		 * @param value Value used to initialize
		 */
		explicit Vector(T value);
		/**
		 * @brief Constructs a new vector from a lower-dimensionality vector and sets the remaining elements to zero
		 */
		template<unsigned int N2> Vector(Vector<T, N2> const& other);
		/**
		 * @brief Copy constructor
		 */
		Vector(Vector<T, N> const& other);
		/**
		 * @brief Constructs a new vector from an initializer list
		 * @param args Arguments
		 */
		Vector(std::initializer_list<T> args);
		/**
		 * @brief Destructor
		 */
		~Vector();
		/**
		 * @brief Returns the dimension of this vector
		 */
		static inline constexpr std::size_t getDimension();
		/**
		 * @brief Returns the squared length of this vector
		 */
		inline T getSquaredLength() const;
		/**
		 * @brief Returns the length of this vector
		 */
		inline T getLength() const;
		/**
		 * @brief Normalizes this vector so it has the length 1
		 */
		Vector<T, N>& normalize();
		/**
		 * @brief Returns a normalized copy of this vector of length 1
		 */
		Vector<T, N> getNormalized() const;
		/**
		 * @brief Returns the dot product of this vector and the
		 * 	      passed vector
		 */
		inline T dot(Vector<T, N> const& rhs) const;
		/**
		 * @brief Returns a new vector that is the cross product of
		 *        this vector and the passed vector
		 */
		Vector<T, N> cross(Vector<T, N> const& rhs) const;
		/**
		 * @brief Checks if all components are zero
		 */
		bool isZero() const;
		/**
		 * @brief Checks if other is similar to this vector
		 * @param other Other vector
		 * @param precision How close every component needs to be
		 */
		bool isSimilar(Vector<T, N> const& other, double precision = 0.1) const;
		/**
		 * @brief Grants access to the internal memory
		 * @return A pointer to the first element of this vector
		 */
		inline T const* getDataPointer() const;
		/**
		 * @brief Assignment operator
		 * @param rhs Other vector
		 * @return Reference to this
		 */
		Vector<T, N>& operator=(Vector<T, N> const& rhs);
		/**
		 * @brief Adds another vector to this vector
		 * @param rhs Vector to add
		 * @return The resulting vector
		 */
		Vector<T, N> operator+(Vector<T, N> const& rhs) const;
		/**
		 * @brief Adds another vector to this vector, assigning the resulting vector to this
		 * @param rhs Vector to add
		 * @return Reference to this
		 */
		Vector<T, N>& operator+=(Vector<T, N> const& rhs);
		/**
		 * @brief Subtracts another vector from this vector
		 * @param rhs Vector to subtract
		 * @return The resulting vector
		 */
		Vector<T, N> operator-(Vector<T, N> const& rhs) const;
		/**
		 * @brief Subtracts another vector from this vector, assigning the resulting vector to this
		 * @param rhs Vector to subtract
		 * @return Reference tot his
		 */
		Vector<T, N>& operator-=(Vector<T, N> const& rhs);
		/**
		 * @brief Dot product
		 * @param rhs Vector to calculate the dot product with
		 * @return Resulting scalar
		 */
		T operator*(Vector<T, N> const& rhs) const;
		/**
		 * @brief Scalar multiplication
		 * @param rhs Scalar
		 * @return Resulting vector
		 */
		Vector<T, N> operator*(T const& rhs) const;
		/**
		 * @brief Scalar multiplication, assigning the resulting vector to this
		 * @param rhs Scalar
		 * @return Reference to this
		 */
		Vector<T, N>& operator*=(T const& rhs);
		/**
		 * @brief Cross product, assigning the resulting vector to this
		 * @param rhs Other vector
		 * @return Reference to this
		 */
		Vector<T, N>& operator*=(Vector<T, N> const& rhs);
		/**
		 * @brief Scalar division
		 * @param rhs Scalar
		 * @return Resulting vector
		 */
		Vector<T, N> operator/(T const& rhs) const;
		/**
		 * @brief Scalar division, assigning the resulting vector to this
		 * @param rhs Scalar
		 * @return Reference to this
		 */
		Vector<T, N>& operator/=(T const& rhs);
		/**
		 * @brief Unary minus. Inverts the signs of all components.
		 * @return Resulting vector
		 */
		Vector<T, N> operator-() const;
		/**
		 * @brief Equality operator. Checks for value equality.
		 * @param rhs Other vector
		 * @return True if all values are equal, otherwise false
		 */
		bool operator==(Vector<T, N> const& rhs) const;
		/**
		 * @brief Inequality operator. Checks for value inequality.
		 * @param rhs Other vector
		 * @return True if not equal, otherwise false
		 */
		bool operator!=(Vector<T, N> const& rhs) const;
		/**
		 * @brief Direct access operator
		 * @param index Index of the component to access
		 * @return Reference to the requested dimension
		 */
		inline T& operator[](std::size_t const& index);
		/**
		 * @brief Direct access operator
		 * @param index Index of the component to access
		 * @return Reference to the requested dimension
		 */
		inline T const& operator[](std::size_t const& index) const;

	private:
		/**
		 * @brief Array holding the components of the vector
		 */
		T m_elements[N] { };
	};

	// Free function operators
	/**
	 * @brief Scalar multiplication. Scales the vector by rhs
	 * @param lhs Vector to scale
	 * @param rhs Scalar
	 * @return Result of the operation
	 */
	template<typename T, unsigned int N> inline Vector<T, N> operator*(Vector<T, N> const& lhs, T const& rhs);
	/**
	 * @brief Scalar multiplication. Scales the vector by lhs
	 * @param lhs Scalar
	 * @param rhs Vector to scale
	 * @return Result of the operation
	 */
	template<typename T, unsigned int N> inline Vector<T, N> operator*(T const& lhs, Vector<T, N> const& rhs);

}
#include "Vector.imp"

#endif /* VECTOR_H_ */
