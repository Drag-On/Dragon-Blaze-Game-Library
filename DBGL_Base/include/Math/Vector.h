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

#include<assert.h>
#include<cstdarg>
#include<cstddef>
#include<type_traits>
#include<cmath>
#include"Utility.h"
#include"System/Log/Log.h"

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
	    /// @brief Constructs a new vector and initializes it
	    /// @param n Amount of passed parameters
	    /// @param ... n initialization values
	    /// </summary>
	    Vector(int n, ...);
	    /// <summary>
	    /// @brief Copies a vector
	    /// </summary>
	    Vector(const Vector<T, N> &other);
	    // Destructors
	    ~Vector();

	    #undef RETURN_QUALIFIER
	    #define RETURN_QUALIFIER const
	    #include "Vector_Common.hpart"
    };

    /*
     * Vector<float,N>
     * Specialized for floats
     */
    template<unsigned int N> class Vector<float, N>
    {
	private:
	    using T = float;
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a new null vector
	    /// </summary>
	    Vector();
	    /// <summary>
	    /// @brief Constructs a new vector and initializes it
	    /// @param n Amount of passed parameters
	    /// @param ... n initialization values
	    /// </summary>
	    Vector(int n, ...);
	    /// <summary>
	    /// @brief Copies a vector
	    /// </summary>
	    Vector(const Vector<T, N> &other);
	    // Destructors
	    ~Vector();

	    #undef RETURN_QUALIFIER
	    #define RETURN_QUALIFIER
	    #include "Vector_Common.hpart"
    };

    /*
     * Vector<char,N>
     * Specialized for chars
     */
    template<unsigned int N> class Vector<char, N>
    {
	private:
	    using T = char;
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a new null vector
	    /// </summary>
	    Vector();
	    /// <summary>
	    /// @brief Constructs a new vector and initializes it
	    /// @param n Amount of passed parameters
	    /// @param ... n initialization values
	    /// </summary>
	    Vector(int n, ...);
	    /// <summary>
	    /// @brief Copies a vector
	    /// </summary>
	    Vector(const Vector<T, N> &other);
	    // Destructors
	    ~Vector();

	    #undef RETURN_QUALIFIER
	    #define RETURN_QUALIFIER
	    #include "Vector_Common.hpart"
    };

    /*
     * Vector<short,N>
     * Specialized for shorts
     */
    template<unsigned int N> class Vector<short, N>
    {
	private:
	    using T = short;
	public:
	    // Constructors
	    /// <summary>
	    /// @brief Constructs a new null vector
	    /// </summary>
	    Vector();
	    /// <summary>
	    /// @brief Constructs a new vector and initializes it
	    /// @param n Amount of passed parameters
	    /// @param ... n initialization values
	    /// </summary>
	    Vector(int n, ...);
	    /// <summary>
	    /// @brief Copies a vector
	    /// </summary>
	    Vector(const Vector<T, N> &other);
	    // Destructors
	    ~Vector();

	    #undef RETURN_QUALIFIER
	    #define RETURN_QUALIFIER
	    #include "Vector_Common.hpart"
    };
}

#undef RETURN_QUALIFIER
#include "Vector.imp"

#endif /* VECTOR_H_ */
