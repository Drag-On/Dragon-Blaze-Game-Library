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
#include "Utility.h"
#include "DBGL/Core/Debug/Log.h"

//////////////////////////////////////////////////////////////////////
// This header involves some pre-processor (black) magic.
// In order to prevent copy & pasting of common parts of all Vector
// specializations, the common part is included from a separate file.
// In this case deriving from a common supertype was not an option
// since operators don't work well with inheritance.
//
// Specialization was necessary since some types get promoted when
// using variadic functions; e.g. float becomes double. Using
// va_arg(args, TYPE) with the wrong type makes the program crash.
// Unfortunately constructors can not be specialized, just methods
// or whole classes.
//////////////////////////////////////////////////////////////////////

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
	     * @brief Constructs a new vector and initializes it
	     * @param n Amount of passed parameters
	     * @param ... n initialization values
	     */
	    explicit Vector(unsigned int n, ...);
	    /**
	     * @brief Constructs a new vector and initializes all values with the same value
	     * @param value Value used to initialize
	     */
	    Vector(T value);
	    /**
	     * @brief Copies a vector
	     */
	    Vector(const Vector<T, N> &other);
	    /**
	     * @brief Constructs a new vector from an initializer list
	     * @param args Arguments
	     */
	    Vector(std::initializer_list<T> args);
	    /**
	     * @brief Destructor
	     */
	    ~Vector();

	    #undef RETURN_QUALIFIER
	    #define RETURN_QUALIFIER const
	    #include "Vector_Common.hpart"
    };

    /**
     * @brief Vector of arbitrary dimension
     */
    template<unsigned int N> class Vector<float, N>
    {
	private:
	    using T = float;
	public:
	    /**
	     * @brief Constructs a new null vector
	     */
	    Vector();
	    /**
	     * @brief Constructs a new vector and initializes it
	     * @param n Amount of passed parameters
	     * @param ... n initialization values
	     */
	    explicit Vector(unsigned int n, ...);
	    /**
	     * @brief Constructs a new vector and initializes all values with the same value
	     * @param value Value used to initialize
	     */
	    Vector(T value);
	    /**
	     * @brief Copies a vector
	     */
	    Vector(const Vector<T, N> &other);
	    /**
	     * @brief Constructs a new vector from an initializer list
	     * @param a_args Arguments
	     */
	    Vector(std::initializer_list<T> a_args);
	    /**
	     * @brief Destructor
	     */
	    ~Vector();

	    #undef RETURN_QUALIFIER
	    #define RETURN_QUALIFIER
	    #include "Vector_Common.hpart"
    };

    /**
     * @brief Vector of arbitrary dimension
     */
    template<unsigned int N> class Vector<char, N>
    {
	private:
	    using T = char;
	public:
	    /**
	     * @brief Constructs a new null vector
	     */
	    Vector();
	    /**
	     * @brief Constructs a new vector and initializes it
	     * @param n Amount of passed parameters
	     * @param ... n initialization values
	     */
	    explicit Vector(unsigned int n, ...);
	    /**
	     * @brief Constructs a new vector and initializes all values with the same value
	     * @param value Value used to initialize
	     */
	    Vector(T value);
	    /**
	     * @brief Copies a vector
	     */
	    Vector(const Vector<T, N> &other);
	    /**
	     * @brief Constructs a new vector from an initializer list
	     * @param a_args Arguments
	     */
	    Vector(std::initializer_list<T> a_args);
	    /**
	     * @brief Destructor
	     */
	    ~Vector();

	    #undef RETURN_QUALIFIER
	    #define RETURN_QUALIFIER
	    #include "Vector_Common.hpart"
    };

    /**
     * @brief Vector of arbitrary dimension
     */
    template<unsigned int N> class Vector<short, N>
    {
	private:
	    using T = short;
	public:
	    /**
	     * @brief Constructs a new null vector
	     */
	    Vector();
	    /**
	     * @brief Constructs a new vector and initializes it
	     * @param n Amount of passed parameters
	     * @param ... n initialization values
	     */
	    explicit Vector(unsigned int n, ...);
	    /**
	     * @brief Constructs a new vector and initializes all values with the same value
	     * @param value Value used to initialize
	     */
	    Vector(T value);
	    /**
	     * @brief Copies a vector
	     */
	    Vector(const Vector<T, N> &other);
	    /**
	     * @brief Constructs a new vector from an initializer list
	     * @param a_args Arguments
	     */
	    Vector(std::initializer_list<T> a_args);
	    /**
	     * @brief Destructor
	     */
	    ~Vector();

	    #undef RETURN_QUALIFIER
	    #define RETURN_QUALIFIER
	    #include "Vector_Common.hpart"
    };

    // Free function operators
    /**
     * @brief Scalar multiplication. Scales the vector by rhs
     * @param lhs Vector to scale
     * @param rhs Scalar
     * @return Result of the operation
     */
    template<typename T, unsigned int N> const Vector<T, N> operator*(Vector<T, N> const& lhs, T const& rhs);
    /**
     * @brief Scalar multiplication. Scales the vector by lhs
     * @param lhs Scalar
     * @param rhs Vector to scale
     * @return Result of the operation
     */
    template<typename T, unsigned int N> const Vector<T, N> operator*(T const& lhs, Vector<T, N> const& rhs);
}

#undef RETURN_QUALIFIER
#include "Vector.imp"

#endif /* VECTOR_H_ */
