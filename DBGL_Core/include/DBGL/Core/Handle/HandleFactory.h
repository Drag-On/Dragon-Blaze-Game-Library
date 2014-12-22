//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_HANDLE_HANDLEFACTORY_H_
#define INCLUDE_DBGL_CORE_HANDLE_HANDLEFACTORY_H_

#include <vector>
#include <set>
#include <limits>
#include <exception>
#include <cstdint>
#include <algorithm>
#include <functional>

namespace dbgl
{
    /**
     * @brief Generates unique handles.
     * @details The generated identifiers will be unique within the used factory.
     * 		Handles will be generated sequentially, with lower identifiers being
     * 		favored over higher ones, i.e. if a low qualifier is getting invalidated, a
     * 		newly generated one will take the same ID instead of generating a new one.
     * 		Copying an existing identifier will link the copy to the "original". If one
     * 		is getting invalidated, the other one will be invalid as well. When the last
     * 		instance of an identifier is destroyed, the handle will automatically become
     * 		invalid and will be reused for future identifiers.
     * 		It is possible to create handles from a integers; in that case the
     * 		passed integer must not be already in use. This can be used to store handles
     * 		on harddisk and reload them at a later time.
     * 		If the factory is destroyed, all handles left will be invalidated.
     */
    template<typename T = uint32_t> class HandleFactory
    {
	public:
	    /**
	     * @brief Handle object that can uniquely identify other objects.
	     */
	    class Handle
	    {
		public:
		    /**
		     * @brief Construct an invalid handle
		     */
		    Handle();
		    /**
		     * @brief Copy constructor
		     * @param other Handle to copy
		     */
		    Handle(Handle const& other);
		    /**
		     * @brief Copy-assignment
		     * @param other Handle to copy
		     * @return Reference to the handle that has been assigned to.
		     */
		    Handle& operator=(Handle const& other);
		    /**
		     * @brief Destructor
		     */
		    ~Handle();
		    /**
		     * @brief Checks if this handle is valid
		     * @return True in case the handle is valid, otherwise false
		     */
		    bool isValid() const;
		    /**
		     * @brief Invalidates this handle
		     */
		    void invalidate();
		    /**
		     * @brief Retrieves the raw value of this handle
		     * @return The value of this handle
		     */
		    T getValue() const;
		    /**
		     * @brief Retrieves the reference count of this handle
		     */
		    unsigned long getRefCount() const;
		    /**
		     * @brief Comparison operator
		     * @param other Handle to compare to
		     * @return True if handles are equal, otherwise false
		     */
		    bool operator==(Handle const& other) const;
		    /**
		     * @brief Comparison operator
		     * @param other Handle to compare to
		     * @return True if handles are not equal, otherwise false
		     */
		    bool operator!=(Handle const& other) const;

		    /**
		     * @brief Constant that describes an invalid ID
		     */
		    static const T InvalidHandle = std::numeric_limits<T>::max();

		private:
		    Handle(T id, HandleFactory<T>* factory);
		    void checkDelete();

		    T* m_pId = nullptr;
		    unsigned long* m_pRefCount = nullptr;
		    HandleFactory<T>* m_pFactory = nullptr;

		    friend class HandleFactory<T>;
	    };

	    /**
	     * @brief Destructor
	     * @details Invalidates all handles handed out by this factory
	     */
	    ~HandleFactory();
	    /**
	     * @brief Requests a new handle
	     * @return The new handle
	     * @throws std::overflow_error if no unique identifiers are left
	     */
	    Handle next();
	    /**
	     * @brief Requests a new handle with a certain value.
	     * @param id Value of the handle
	     * @return The new handle
	     * @throws std::overflow_error if the passed value is not in a valid range.
	     * 	       std::runtime_error if the passed value is already taken.
	     */
	    Handle request(T id);
	    /**
	     * @brief Checks if the passed handle is valid
	     * @param handle Handle to check
	     * @return True in case the handle is valid and in use, otherwise false
	     */
	    bool isValid(Handle const& handle);
	    /**
	     * @brief Invalidates a handle
	     * @param handle Handle to invalidate
	     */
	    void invalidate(Handle& handle);
	    /**
	     * @brief Potentially frees some memory
	     */
	    void clean();
	private:
	    /**
	     * @brief Gets the next id to use and marks it as used
	     * @return ID to use
	     * @warning Throws if no new ID available
	     */
	    T getNext();
	    /**
	     * @brief Tries to use the passed number as ID. Throws if already taken.
	     * @param id ID to use
	     * @return ID to use
	     */
	    T tryUse(T id);

	    /**
	     * @brief Next ID that is not used yet
	     */
	    T m_next = 0;
	    /**
	     * @brief List of IDs that are currently not in use, but lower than @see next
	     */
	    std::vector<T> m_open{};
	    /**
	     * @brief Currently valid handles
	     */
	    std::set<T*> m_handles{};
    };
}

#include "HandleFactory.imp"

#endif /* INCLUDE_DBGL_CORE_HANDLE_HANDLEFACTORY_H_ */
