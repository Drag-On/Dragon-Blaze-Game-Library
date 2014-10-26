//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef STACKALLOCATOR_H_
#define STACKALLOCATOR_H_

namespace dbgl
{
    /**
     * @brief Allocator that works stack-based
     * @details The allocator pre-allocates a certain amount of memory on creation and
     * 		serves requests from this preallocated patch of memory. Thus, no context
     * 		switch is needed on allocation.
     */
    class StackAllocator
    {
	public:
	    /**
	     * @brief Marker on the stack
	     */
	    using Marker = void*;

	    /**
	     * @brief Constructs the allocator with a certain maximum size
	     * @param size Maximum amount of memory that can be allocated
	     */
	    StackAllocator(unsigned long long size);
	    /**
	     * @brief Destructor
	     */
	    ~StackAllocator();
	    /**
	     * @brief Allocates raw memory on the stack
	     * @param size Amount of memory to allocate
	     * @return Pointer to the allocated memory or nullptr if no memory left
	     */
	    void* allocate(unsigned long long size);
	    /**
	     * @brief Allocates and initializes an object on the stack
	     * @warning The stack doesn't keep track of actual objects, therefore the
	     * 		constructor will not be called automatically on rollBack().
	     * 		It's the caller's responsibility to call the destructor.
	     * @return Pointer to the allocated object or nullptr if no memory left
	     */
	    template<typename T> T* allocate();
	    /**
	     * @brief Retrieves a marker of the current top address on the stack
	     * @return Marker for the top address on the stack
	     */
	    Marker top();
	    /**
	     * @brief Rolls back the stack to a previously obtained marker
	     * @warning Does not call any destructors on objects that have been created after
	     * 		the marker has been obtained.
	     * @param marker Marker to roll back to
	     */
	    void rollBack(Marker marker);
	    /**
	     * @brief Clears the whole stack
	     * @see rollBack()
	     */
	    void clear();
	private:
	    void* m_pMemory = nullptr;
	    void* m_pCur = nullptr;
	    void* m_pEnd = nullptr;
    };
}

#include "StackAllocator.imp"

#endif /* STACKALLOCATOR_H_ */
