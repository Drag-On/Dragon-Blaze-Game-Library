//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef POOLALLOCATOR_H_
#define POOLALLOCATOR_H_

#include <iostream>
#include <stdexcept>

namespace dbgl
{
    /**
     * @brief Pool-based allocator.
     * @details Pre-allocates a certain amount of memory on creation and serves requests from
     * 		this preallocated memory. Thus no context switch is needed on creation.
     * 		A pool allocator can only be used to allocate multiple objects of the same type.
     */
    template <typename T> class PoolAllocator
    {
	public:
	    /**
	     * @brief Constructor
	     * @param size Amount of objects that can be allocated with this allocator
	     */
	    PoolAllocator(unsigned long long size);
	    /**
	     * @brief Destructor
	     */
	    ~PoolAllocator();
	    /**
	     * @brief Allocates and constructs a new object
	     * @return Pointer to the allocated object
	     */
	    T* allocate();
	    /**
	     * @brief Destructs and deallocates a previously allocated object
	     * @param obj Pointer to the object to deallocate
	     */
	    void deallocate(T*& obj);
	private:
	    void* m_pMemory = nullptr;
	    T** m_pFreeListStart = nullptr;
	    T** m_pFreeListEnd = nullptr;
	    unsigned long long m_size;

	    bool canAllocate();
    };
}

#include "PoolAllocator.imp"

#endif /* POOLALLOCATOR_H_ */
