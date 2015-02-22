//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_UTILITY_BITUTILITY_H_
#define INCLUDE_DBGL_CORE_UTILITY_BITUTILITY_H_

#include <cstdint>

namespace dbgl
{
	/**
	 * @brief Provides functionality to interpret the bit patterns of char arrays as integers
	 */
	class BitUtility
	{
	public:
		/**
		 * @brief Interprets the bit pattern of a char array of length 2 as unsigned 16 bit integer,
		 * 		  assuming that the array is little endian.
		 * @param array Array to interpret
		 * @warning \p array must have (at least) length 2!
		 * @return The unsigned integer
		 */
		static uint16_t readUInt16_LE(unsigned char* array);
		/**
		 * @brief Interprets the bit pattern of a char array of length 4 as unsigned 32 bit integer,
		 * 		  assuming that the array is little endian.
		 * @param array Array to interpret
		 * @warning \p array must have (at least) length 4!
		 * @return The unsigned integer
		 */
		static uint32_t readUInt32_LE(unsigned char* array);
		/**
		 * @brief Interprets the bit pattern of a char array of length 2 as signed 16 bit integer,
		 * 		  assuming that the array is little endian.
		 * @param array Array to interpret
		 * @warning \p array must have (at least) length 2!
		 * @return The signed integer
		 */
		static int16_t readInt16_LE(unsigned char* array);
		/**
		 * @brief Interprets the bit pattern of a char array of length 4 as signed 32 bit integer,
		 * 		  assuming that the array is little endian.
		 * @param array Array to interpret
		 * @warning \p array must have (at least) length 4!
		 * @return The signed integer
		 */
		static int32_t readInt32_LE(unsigned char* array);
		/**
		 * @brief Interprets the bit pattern of a char array of length 2 as signed 16 bit integer,
		 * 		  assuming that the array is big endian.
		 * @param array Array to interpret
		 * @warning \p array must have (at least) length 2!
		 * @return The unsigned integer
		 */
		static uint16_t readUInt16_BE(unsigned char* array);
		/**
		 * @brief Interprets the bit pattern of a char array of length 4 as unsigned 32 bit integer,
		 * 		  assuming that the array is big endian.
		 * @param array Array to interpret
		 * @warning \p array must have (at least) length 4!
		 * @return The unsigned integer
		 */
		static uint32_t readUInt32_BE(unsigned char* array);
		/**
		 * @brief Interprets the bit pattern of a char array of length 2 as signed 16 bit integer,
		 * 		  assuming that the array is big endian.
		 * @param array Array to interpret
		 * @warning \p array must have (at least) length 2!
		 * @return The signed integer
		 */
		static int16_t readInt16_BE(unsigned char* array);
		/**
		 * @brief Interprets the bit pattern of a char array of length 4 as signed 32 bit integer,
		 * 		  assuming that the array is big endian.
		 * @param array Array to interpret
		 * @warning \p array must have (at least) length 4!
		 * @return The signed integer
		 */
		static int32_t readInt32_BE(unsigned char* array);
	};
}

#endif /* INCLUDE_DBGL_CORE_UTILITY_BITUTILITY_H_ */
