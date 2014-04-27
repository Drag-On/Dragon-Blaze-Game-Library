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

#include <string>
#include <cmath>

namespace dbgl
{
    /**
     * @brief Bitmask of arbitrary size, designed to store flags
     * @details Per default the bitmask uses unsigned integers to store flags. Integers
     * 		usually have 4 bytes and thus can store 4 * 8 = 32 flags. If more or less
     * 		flags are needed, one can create a bitmask with a different underlying
     * 		datatype, e.g. char or long int
     */
    template <typename T = unsigned int> class Bitmask
    {
	public:
	    /**
	     * @brief Constructs a bitmask of the size of an int
	     * @param mask Interprets the int as flags
	     */
	    Bitmask(T const& mask = 0);
	    /**
	     * @brief Copies another bitmask
	     * @param other Bitmask to copy
	     */
	    Bitmask(Bitmask<T> const& other);
	    /**
	     * @return Amount of usable bits
	     */
	    unsigned int getSize() const;
	    /**
	     * @brief Sets all bits set in mask, leaving the others unchanged
	     * @param mask Indicates which bits to set
	     */
	    void set(Bitmask<T> mask);
	    /**
	     * @brief Clears all bits set in mask, leaving others unchanged
	     * @param mask Indicates which bits to clear
	     */
	    void clear(Bitmask<T> mask);
	    /**
	     * @brief Toggles all bits set in mask, leaving others unchanged
	     * @param mask Indicates which bits to toggle
	     */
	    void toggle(Bitmask<T> mask);
	    /**
	     * @brief Checks if the passed bitmask is set
	     * @param mask Bitmask
	     * @return True in case all bits set in the mask are set
	     */
	    bool isSet(Bitmask<T> mask) const;
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
	    Bitmask<T>& operator=(Bitmask<T> const& rhs);
	    /**
	     * @brief Interprets rhs as a bitmask
	     * @param rhs Bitmask to copy
	     * @return Reference to this bitmask
	     */
	    Bitmask<T>& operator=(T const& rhs);
	    /**
	     * @brief Allows for implicit conversion to T
	     * @return The base representation of this bitfield
	     */
	    operator T();
	private:
	    T m_data;
    };
}

#include "Bitmask.imp"

#endif /* BITMASK_H_ */
