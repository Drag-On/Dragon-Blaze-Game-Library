//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Library/Library.h"

namespace dbgl
{
    Library::Library(std::string const& path) : m_path{path}
    {
    }

    Library::Library(Filename const& path) : m_path{path}
    {
    }

    Library::~Library()
    {
        if(m_handle)
        {
#ifdef __linux__
            internal_os::dlclose(m_handle);
#elif __WIN32
            internal_os::FreeLibrary(m_handle);
#endif
        }
    }

    bool Library::load()
    {
#ifdef __linux__
        m_handle = internal_os::dlopen(m_path.get().c_str(), RTLD_LAZY);
#elif __WIN32
        m_handle = internal_os::LoadLibrary(m_path.get().c_str());
#endif
	if (!m_handle)
	    return false;
	else
	    return true;
    }

    auto Library::getFunction(std::string const& name) -> Func
    {
#ifdef __linux__
        return reinterpret_cast<Func>(internal_os::dlsym(m_handle, name.c_str()));
#elif __WIN32
	return reinterpret_cast<Func>(internal_os::GetProcAddress(m_handle, name.c_str()));
#endif
    }

    Library::Library(Library&& other) : m_path{other.m_path}, m_handle{other.m_handle}
    {
	other.m_handle = nullptr;
	other.m_path = "";
    }

    Library& Library::operator=(Library&& other)
    {
	if(this != &other)
	{
	    m_handle = other.m_handle;
	    m_path = other.m_path;
	}
	return *this;
    }

    std::string Library::getFileExtension()
    {
#ifdef __linux__
        return "so";
#elif __WIN32
	return "dll";
#elif __APPLE__
	return "dylib"
#endif
    }
}
