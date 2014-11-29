//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef UID_H_
#define UID_H_

#include <vector>
#include <limits>
#include <exception>
#include <cstdint>
#include <algorithm>

namespace dbgl
{
    /**
     * @brief Generates unique identifiers.
     * @details The generated identifiers will be unique within the specified group and type.
     * 		Identifiers will be generated sequentially, with lower identifiers being
     * 		favored over higher ones, i.e. if a low qualifier is getting invalidated, a
     * 		newly generated one will take the same ID instead of generating a new one.
     * 		Copying an existing identifier will link the copy to the "original". If one
     * 		is getting invalidated, the other one will be invalid as well. When the last
     * 		instance of an identifier is destroyed, the ID will automatically become
     * 		invalid and will be reused for future identifiers.
     * 		It is possible to create an identifier from an integer; in that case the
     * 		passed integer must not be already in use. This can be used to store IDs
     * 		on harddisk and reload them at a later time.
     */
    template <unsigned int GROUP = 0, typename T = uint32_t> class UID
    {
	public:
	    /**
	     * @brief Constant that describes an invalid ID
	     */
	    static const T InvalidID = std::numeric_limits<T>::max();

	    /**
	     * @brief Constructs a new ID unique to the specified GROUP
	     * @warning If there are no ids left, this constructor will throw.
	     */
	    UID();
	    /**
	     * @brief Constructs a new ID from the passed number
	     * @param uid ID to use
	     * @warning If @p uid is already in use, this constructor will throw.
	     */
	    UID(T uid);
	    /**
	     * @brief Copy constructor
	     */
	    UID(UID<GROUP, T> const& other);
	    /**
	     * @brief Assignment operator
	     * @param other UID to copy
	     * @return Reference to the copied object
	     */
	    UID& operator=(UID<GROUP, T> const& other);
	    /**
	     * @brief Destructor
	     */
	    ~UID();
	    /**
	     * @brief Provides a copy of the underlying number
	     * @return The number used as ID
	     * @warning Don't store this number and assume it will still be unique later on!
	     * 		This should only be used if you know what you're doing.
	     */
	    T getNumber() const;
	    /**
	     * @brief Invalidates this ID
	     */
	    void invalidate();
	    /**
	     * @brief Checks if this ID is still valid
	     * @return True in case the ID is valid and in use, otherwise false
	     */
	    bool isValid() const;

	    /**
	     * @brief Checks if the passed number is a valid ID
	     * @param id ID to check
	     * @return True in case the ID is valid and in use, otherwise false
	     */
	    static bool checkValid(T id);
	    /**
	     * @brief Potentially frees some memory
	     */
	    static void clean();
	private:
	    /**
	     * @brief Checks if all references to this instance are lost and deletes this UID if necessary
	     */
	    void checkDelete();
	    /**
	     * @brief Gets the next id to use and marks it as used
	     * @return ID to use
	     * @warning Throws if no new ID available
	     */
	    static T getNext();
	    /**
	     * @brief Tries to use the passed number as ID. Throws if already taken.
	     * @param id ID to use
	     * @return ID to use
	     */
	    static T tryUse(T id);

	    /**
	     * @brief Unique ID
	     */
	    T* m_pId;
	    /**
	     * @brief Reference count
	     */
	    unsigned long* m_pRefCount;

	    /**
	     * @brief Next ID that is not used yet
	     */
	    static T next;
	    /**
	     * @brief List of IDs that are currently not in use, but lower than @see next
	     */
	    static std::vector<T> open;
    };
}

#include "UID.imp"

#endif /* UID_H_ */
