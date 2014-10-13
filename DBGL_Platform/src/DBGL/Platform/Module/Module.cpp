//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Module/Module.h"

namespace dbgl
{
    Module::Module(std::string path) : m_path{path}
    {
    }

    Module::~Module()
    {
#ifdef _WIN32
	OS_Win32::FreeLibrary(m_handle);
#endif
    }

    bool Module::load()
    {
#ifdef _WIN32
	m_handle = OS_Win32::LoadLibrary(m_path.c_str());
	if (!m_handle)
	    return false;
	else
	    return true;
#endif
	// TODO: Linux & Mac implementations
    }
}
