//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MODULE_H_
#define MODULE_H_

#include <string>
#include <cstring>

namespace dbgl
{
    namespace internal_os
    {
#ifdef __linux__
	#include <dlfcn.h>
	using ModHandle = void*;
#elif __WIN32
        #undef _MSC_EXTENSIONS
	#include <windows.h>
	using ModHandle = HINSTANCE;
#endif
    }

    class Module
    {
	public:
	    using Func = void(*)(void);
	    Module(std::string path);
	    ~Module();
	    bool load();
	    Func getFunction(std::string name);
	private:
	    // Prevent copies
	    Module(Module& other);
	    Module& operator=(Module& other);

	    std::string m_path;
            internal_os::ModHandle m_handle{};
    };
}

#endif /* MODULE_H_ */
