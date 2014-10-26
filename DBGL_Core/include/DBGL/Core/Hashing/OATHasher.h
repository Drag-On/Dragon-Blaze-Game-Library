//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef OATHASHER_H_
#define OATHASHER_H_

#include <cstdint>
#include <string>

namespace dbgl
{
    /**
     * @brief Implementation of the One-At-A-Time hashing algorithm.
     * @details The OAT algorithm is fast and performs very well
     */
    class OATHasher
    {
	public:
	    /**
	     * @brief Generates a 32-bit hash for some arbitrary data
	     * @param data Pointer to the data, laid out continuously in memory
	     * @param length Length of the data array
	     * @return The 32 bit hash
	     */
	    static uint32_t hash32(void const* data, size_t length);
	    /**
	     * @brief Generates a 32-bit hash for a string
	     * @param string Pointer to the first character of the string
	     * @param length Length of the string
	     * @return The 32 bit hash
	     */
	    static uint32_t hash32(char const* string, size_t length);
	    /**
	     * @brief Generates a 32-bit hash for a string
	     * @param string String to generate hash for
	     * @return The 32 bit hash
	     */
	    static uint32_t hash32(std::string const& string);
    };
}

#endif /* OATHASHER_H_ */
