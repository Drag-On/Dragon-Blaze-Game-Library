//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Hashing/FNVHasher.h"

namespace dbgl
{
    uint32_t FNVHasher::hash32(void const* data, size_t length)
    {
	unsigned char const* start = reinterpret_cast<unsigned char const*>(data);
	unsigned char const* end = start + length;
	uint32_t hash = 0x811c9dc5;
	while (start < end)
	{
	    hash ^= *start++;
	    hash *= s_FNV32_Prime;
	}
	return hash;
    }

    uint32_t FNVHasher::hash32(char const* string, size_t length)
    {
	return hash32(static_cast<void const*>(string), length);
    }

    uint32_t FNVHasher::hash32(std::string const& string)
    {
	return hash32(string.c_str(), string.length());
    }

    uint64_t FNVHasher::hash64(void const* data, size_t length)
    {
	unsigned char const* start = reinterpret_cast<unsigned char const*>(data);
	unsigned char const* end = start + length;
	uint64_t hash = 0xcbf29ce484222325ULL;
	while (start < end)
	{
	    hash ^= *start++;
	    hash *= s_FNV64_Prime;
	}
	return hash;
    }

    uint64_t FNVHasher::hash64(char const* string, size_t length)
    {
	return hash64(static_cast<void const*>(string), length);
    }

    uint64_t FNVHasher::hash64(std::string const& string)
    {
	return hash64(string.c_str(), string.length());
    }
}


