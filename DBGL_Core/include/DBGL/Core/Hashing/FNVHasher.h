//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
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
    class FNVHasher
    {
	public:
	    static uint32_t hash32(void const* data, size_t length);
	    static uint32_t hash32(char const* string, size_t length);
	    static uint32_t hash32(std::string const& string);
	    static uint64_t hash64(void const* data, size_t length);
	    static uint64_t hash64(char const* string, size_t length);
	    static uint64_t hash64(std::string const& string);

	private:
	    /*
	     * 32 bit magic FNV-1a prime
	     */
	    static constexpr uint32_t s_FNV32_Prime = 0x01000193;
	    static constexpr uint64_t s_FNV64_Prime = 0x100000001b3ULL;
    };
}



#endif /* FNVHASHER_H_ */
