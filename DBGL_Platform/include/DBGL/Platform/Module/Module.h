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
#include "DBGL/Platform/File/Filename.h"

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

    /**
     * @brief Represents a dynamic library that can be loaded on runtime
     */
    class Module
    {
	public:
	    /**
	     * @brief Void function pointer
	     */
	    using Func = void(*)(void);
	    /**
	     * @brief Constructs a new module from a file
	     * @param path Path of the file
	     */
	    Module(std::string const& path);
	    /**
	     * @brief Constructs a new module from a file
	     * @param path Path of the file
	     */
	    Module(Filename const& path);
	    /**
	     * @brief Move constructor
	     * @param other Module to move
	     */
	    Module(Module&& other);
	    /**
	     * @brief Move assignment
	     * @param other Module to move
	     * @return Reference to this module
	     */
	    Module& operator=(Module&& other);
	    /**
	     * @brief Destructor
	     */
	    ~Module();
	    /**
	     * @brief Loads the module into memory
	     * @return True in case the module was loaded, otherwise false
	     */
	    bool load();
	    /**
	     * @brief Retrieves a pointer to a function within this module
	     * @details The function has to be a c-style function. It may have any signature, however
	     * 		this signature needs to be known to the caller, since the returned function
	     * 		pointer needs to be cast into the right format.
	     * @param name Name of the function to get
	     * @return Function pointer to the requested function or nullptr if something went wrong
	     */
	    Func getFunction(std::string const& name);
	private:
	    // Prevent copies
	    Module(Module& other) = delete;
	    Module& operator=(Module& other) = delete;

	    Filename m_path;
            internal_os::ModHandle m_handle{};
    };
}

#endif /* MODULE_H_ */
