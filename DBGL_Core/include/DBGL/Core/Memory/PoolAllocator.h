//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
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
    template <typename T> class PoolAllocator
    {
	public:
	    PoolAllocator(unsigned long long size);
	    ~PoolAllocator();
	    T* allocate();
	    void deallocate(T*& obj);
	private:
	    void* m_pMemory = nullptr;
	    T** m_pFreeListStart = nullptr;
	    T** m_pFreeListEnd = nullptr;
	    unsigned long long m_size;

	    void debugOut();
    };
}

#include "PoolAllocator.imp"

#endif /* POOLALLOCATOR_H_ */
