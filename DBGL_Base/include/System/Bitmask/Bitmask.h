//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef BITMASK_H_
#define BITMASK_H_

#include <stdexcept>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <cmath>

namespace dbgl
{
    /**
     * @brief Bitmask of arbitrary size, designed to store flags
     */
    class Bitmask
    {
	public:
	    /**
	     * @brief Constructs a bitmask of the size of an int
	     * @param bits Interprets the int as flags
	     */
	    Bitmask(int bits = 0);
	    /**
	     * @brief Constructs a bitmask from a string
	     * @param bits String to interpret as bits
	     */
	    Bitmask(std::string bits);
	    /**
	     * @brief Constructs a bitmask from the bits set in bits
	     * @param bits Char array that is interpreted as bitmask
	     * @param length Length of the array
	     */
	    Bitmask(char* bits, unsigned int length);
	    /**
	     * @brief Copies another bitmask
	     * @param other Bitmask to copy
	     */
	    Bitmask(Bitmask const& other);
	    /**
	     * @brief Destructor
	     */
	    ~Bitmask();
	    /**
	     * @return Amount of usable bits
	     */
	    unsigned int getSize() const;
	    /**
	     * @brief Sets a certain bit
	     * @param index Index of the bit to set
	     */
	    void set(unsigned int index);
	    /**
	     * @brief Clears a certain bit
	     * @param index Index of the bit to clear
	     */
	    void clear(unsigned int index);
	    /**
	     * @brief Toggles a certain bit
	     * @param index Index of the bit to toggle
	     */
	    void toggle(unsigned int index);
	    /**
	     * @brief Gets the state of a certain bit
	     * @param index Index of the bit to get
	     * @return True in case the bit is set, otherwise false
	     */
	    bool get(unsigned int index) const;
	    /**
	     * @brief Checks if the passed bitmask is set
	     * @param bit bitmask
	     * @return True in case all bits set in the mask are set
	     */
	    bool isSet(int mask) const;
	    /**
	     * @brief Replaces all bits with content from the string
	     * @param bits String to parse
	     */
	    void fromString(std::string bits);
	    /**
	     * @brief Converts this bitmask to a readable string
	     * @return The bitmask formatted as a string
	     */
	    std::string toString() const;
	    /**
	     * @brief Copies some other bitmask
	     * @param rhs
	     * @return Reference to this bitmask
	     */
	    Bitmask& operator=(Bitmask const& rhs);
	    /**
	     * @brief Interprets the char as a bitmask of size sizeof(char)
	     * @param rhs Bitmask to copy
	     * @return Reference to this bitmask
	     */
	    Bitmask& operator=(char const& rhs);
	    /**
	     * @brief Interprets the int as a bitmask of size sizeof(int)
	     * @param rhs Bitmask to copy
	     * @return Reference to this bitmask
	     */
	    Bitmask& operator=(int const& rhs);
	private:
	    char* m_pData;
	    unsigned int m_length;
    };
}

#endif /* BITMASK_H_ */
