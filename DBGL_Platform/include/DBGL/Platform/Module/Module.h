//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MODULELOADER_H_
#define MODULELOADER_H_

#include <string>
#include <cstring>

namespace dbgl
{
#ifdef _WIN32
    namespace OS_Win32
    {
	#undef _MSC_EXTENSIONS
	#include<windows.h>
    }
#endif

    class Module
    {
	public:
	    Module(std::string path);
	    ~Module();
	    bool load();
	    template <typename Func> Func getFunction(std::string name);
	private:
	    // Prevent copies
	    Module(Module& other);
	    Module& operator=(Module& other);

	    std::string m_path;
#ifdef _WIN32
	    OS_Win32::HINSTANCE m_handle;
#endif
    };
}

#include "Module.imp"

#endif /* MODULELOADER_H_ */
