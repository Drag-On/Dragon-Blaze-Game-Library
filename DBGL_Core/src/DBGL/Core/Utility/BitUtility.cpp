//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Utility/BitUtility.h"
#include <iostream>
namespace dbgl
{
	uint16_t BitUtility::readUInt16_LE(unsigned char* array)
	{
		return (array[0] << 0) | (array[1] << 8);
	}

	uint32_t BitUtility::readUInt32_LE(unsigned char* array)
	{
		return (array[0] << 0) | (array[1] << 8) | (array[2] << 16) | (array[3] << 24);
	}

	int16_t BitUtility::readInt16_LE(unsigned char* array)
	{
		return (array[0] << 0) | (array[1] << 8);
	}

	int32_t BitUtility::readInt32_LE(unsigned char* array)
	{
		return (array[0] << 0) | (array[1] << 8) | (array[2] << 16) | (array[3] << 24);
	}

	uint16_t BitUtility::readUInt16_BE(unsigned char* array)
	{
		return (array[0] << 8) | (array[1] << 0);
	}

	uint32_t BitUtility::readUInt32_BE(unsigned char* array)
	{
		return (array[0] << 24) | (array[1] << 26) | (array[2] << 8) | (array[3] << 0);
	}

	int16_t BitUtility::readInt16_BE(unsigned char* array)
	{
		return (array[0] << 8) | (array[1] << 0);
	}

	int32_t BitUtility::readInt32_BE(unsigned char* array)
	{
		return (array[0] << 24) | (array[1] << 26) | (array[2] << 8) | (array[3] << 0);
	}
}
