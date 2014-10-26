//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/File/Filename.h"

namespace dbgl
{
    namespace internal_os
    {
#ifdef __linux__
	#include <stdlib.h>
#elif __WIN32
        #undef _MSC_EXTENSIONS
	#include <windows.h>
	#include <Shlwapi.h>
#endif
    }

    Filename::Filename(std::string const& path) : m_completeFile{path}
    {
	analyze(path);
    }

    bool Filename::isRelative() const
    {
	return m_isRelative;
    }

    std::string Filename::getExtension() const
    {
	return m_extension;
    }

    std::string Filename::getAbsolute() const
    {
	std::string fullPath{};
	if(isRelative())
	{
#ifdef __linux__
	    char absPath[512];
	    realpath(m_completeFile.c_str(), absPath);
	    fullPath.append(absPath);
#elif __WIN32
	    int reqSize = internal_os::GetFullPathName(m_completeFile.c_str(), 0, nullptr, nullptr);
	    char* absPath = new char[reqSize];
	    internal_os::GetFullPathName(m_completeFile.c_str(), reqSize, absPath, nullptr);
	    fullPath.append(absPath);
	    delete [] absPath;
#endif
	    return fullPath;
	}
	else
	    return m_completeFile;
    }

//    std::string Filename::getRelative() const
//    {
//	std::string relPath{};
//	if(!isRelative())
//	{
//#ifdef __linux__
//#elif __WIN32
////	    char* relative = new char[MAX_PATH]{};
////	    internal_os::PathRelativePathTo(relative, Filesystem::getCurWorkingDir().c_str(), 0, m_completeFile.c_str(), 0);
////	    relPath.append(relative);
////	    delete [] relative;
//	    return relPath;
//#endif
//	}
//	else
//	    return m_completeFile;
//    }

    std::string const& Filename::get() const
    {
	return m_completeFile;
    }

    void Filename::analyze(std::string const& path)
    {
	// Check if the path is relative or absolute
	analyzeRelative(path);
	analyzeExtension(path);
    }

    void Filename::analyzeRelative(std::string const& path)
    {
#ifdef __linux__
	m_isRelative = !std::regex_match(path, std::regex("\\/[A-Za-z0-9\\/\\\\ \\.\\-_]*"));
#elif __WIN32
	m_isRelative = !std::regex_match(path, std::regex("[A-Z]:[A-Za-z0-9\\/\\\\ \\.\\-_]*"));
#endif
    }

    void Filename::analyzeExtension(std::string const& path)
    {
	std::smatch m;
	std::regex_search(path, m, std::regex("\\.[A-Za-z0-9]*$"));
	m_extension = m.str();
    }
}
