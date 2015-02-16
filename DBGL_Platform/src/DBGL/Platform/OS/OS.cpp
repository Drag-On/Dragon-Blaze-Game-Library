//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/OS/OS.h"

namespace dbgl
{
    // Include platform-dependent source files
    #ifdef _WIN32
	#include "OS_Win32.spart"
    #endif
    #ifdef __linux__
	#include "OS_Linux.spart"
    #endif
    #ifdef __APPLE__
	#include "OS_Apple.spart"
    #endif

    std::string OS::getDescripion(OS::Type const& os)
    {
	std::stringstream osDesc {};
	osDesc << os.name;
	if(os.derivative.length() > 0)
	    osDesc<< " " << os.derivative;
	osDesc << " " << os.major << "." << os.minor;
	if(os.descr.length() > 0)
	    osDesc << " (" << os.descr << ")";
	return osDesc.str();
    }

    std::string OS::getDescripion()
    {
	return getDescripion(getType());
    }
}
