//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/GL/HandleGenerator.h"

namespace dbgl
{
    auto HandleGenerator::generate() -> Handle
    {
	auto handle = m_nextHandle;
	if(m_openStack.empty())
	    m_nextHandle++;
	else
	{
	    handle = m_openStack.top();
	    m_openStack.pop();
	}
	return handle;
    }

    void HandleGenerator::invalidate(Handle& handle)
    {
	if(handle != InvalidHandle)
	{
	    m_openStack.push(handle);
	    handle = InvalidHandle;
	}
    }
}
