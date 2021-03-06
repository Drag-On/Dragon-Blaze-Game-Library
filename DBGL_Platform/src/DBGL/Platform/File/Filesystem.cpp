//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/File/Filesystem.h"

namespace dbgl
{
    namespace internal_os
    {
#ifdef __linux__
	#include <unistd.h>
#elif __WIN32
        #undef _MSC_EXTENSIONS
	#include <windows.h>
#endif
    }

    std::string Filesystem::getCurWorkingDir()
    {
	std::string cwd{};
#ifdef __linux__
	char buffer[512];
	if (internal_os::getcwd(buffer, sizeof(buffer)))
	    cwd.append(buffer);
#elif __WIN32
	int reqSize = internal_os::GetCurrentDirectory(0, nullptr);
	char* buffer = new char[reqSize]{};
	internal_os::GetCurrentDirectory(reqSize, buffer);
	cwd.append(buffer);
	delete [] buffer;
#endif
	return cwd;
    }

    bool Filesystem::setCurWorkingDir(std::string const& path)
    {
	bool success { false };
#ifdef __linux__
	success = !internal_os::chdir(path.c_str());
#elif __WIN32
	success = internal_os::SetCurrentDirectory(path.c_str());
#endif
	return success;
    }
}
