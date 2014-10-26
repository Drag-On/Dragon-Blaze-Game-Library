//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Memory/StackAllocator.h"

namespace dbgl
{
    StackAllocator::StackAllocator(unsigned long long size)
    {
	// Allocate raw memory
	m_pMemory = operator new(size);
	m_pCur = m_pMemory;
	m_pEnd = reinterpret_cast<char*>(m_pMemory) + size; // cast to char to make sure increments are by 1 byte
    }

    StackAllocator::~StackAllocator()
    {
	operator delete(m_pMemory);
    }

    void* StackAllocator::allocate(unsigned long long size)
    {
	if ((reinterpret_cast<char*>(m_pCur) + size) <= m_pEnd)
	{
	    void* addr = m_pCur;
	    m_pCur = reinterpret_cast<char*>(m_pCur) + size;
	    return addr;
	}
	else
	    return nullptr;
    }

    auto StackAllocator::top() -> Marker
    {
	return m_pCur;
    }

    void StackAllocator::rollBack(Marker marker)
    {
	if(marker < m_pCur)
	    m_pCur = marker;
    }

    void StackAllocator::clear()
    {
	rollBack(m_pMemory);
    }
}
