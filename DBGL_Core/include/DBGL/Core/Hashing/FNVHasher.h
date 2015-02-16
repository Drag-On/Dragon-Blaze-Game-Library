//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef FNVHASHER_H_
#define FNVHASHER_H_

#include <cstdint>
#include <string>

namespace dbgl
{
    /**
     * @brief Implementation of the FNV-1a hashing algorithm.
     * @details The FNV-1a algorithm is fast and simple and generates fairly evenly distributed outputs.
     * 		http://isthe.com/chongo/tech/comp/fnv/
     */
    class FNVHasher
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
	    /**
	     * @brief Generates a 64-bit hash for some arbitrary data
	     * @param data Pointer to the data, laid out continuously in memory
	     * @param length Length of the data array
	     * @return The 64 bit hash
	     */
	    static uint64_t hash64(void const* data, size_t length);
	    /**
	     * @brief Generates a 64-bit hash for a string
	     * @param string Pointer to the first character of the string
	     * @param length Length of the string
	     * @return The 64 bit hash
	     */
	    static uint64_t hash64(char const* string, size_t length);
	    /**
	     * @brief Generates a 64-bit hash for a string
	     * @param string String to generate hash for
	     * @return The 64 bit hash
	     */
	    static uint64_t hash64(std::string const& string);

	private:
	    /**
	     * 32 bit magic FNV-1a prime
	     */
	    static constexpr uint32_t s_FNV32_Prime = 0x01000193;
	    /**
	     * 64 bit magic FNV-1a prime
	     */
	    static constexpr uint64_t s_FNV64_Prime = 0x100000001b3ULL;
    };
}

#endif /* FNVHASHER_H_ */
