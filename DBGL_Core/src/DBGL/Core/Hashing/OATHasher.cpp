//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Hashing/OATHasher.h"

namespace dbgl
{
    uint32_t OATHasher::hash32(void const* data, size_t length)
    {
	unsigned char const* start = reinterpret_cast<unsigned char const*>(data);
	uint32_t hash = 0;
	for (unsigned int i = 0; i < length; i++)
	{
	    hash += start[i];
	    hash += (hash << 10);
	    hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
    }

    uint32_t OATHasher::hash32(char const* string, size_t length)
    {
	return hash32(static_cast<void const*>(string), length);
    }

    uint32_t OATHasher::hash32(std::string const& string)
    {
	return hash32(string.c_str(), string.length());
    }
}

