//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <string>
#include <cstring>
#include "DBGL/Platform/File/Filename.h"

namespace dbgl
{
    namespace internal_os
    {
#ifdef __linux__
	#include <dlfcn.h>
	using LibHandle = void*;
#elif __WIN32
        #undef _MSC_EXTENSIONS
	#include <windows.h>
	using LibHandle = HINSTANCE;
#endif
    }

    /**
     * @brief Represents a dynamic library that can be loaded on runtime
     */
    class Library
    {
	public:
	    /**
	     * @brief Void function pointer
	     */
	    using Func = void(*)(void);
	    /**
	     * @brief Constructs a new library from a file
	     * @param path Path of the file
	     */
	    Library(std::string const& path);
	    /**
	     * @brief Constructs a new library from a file
	     * @param path Path of the file
	     */
	    Library(Filename const& path);
	    /**
	     * @brief Move constructor
	     * @param other Library to move
	     */
	    Library(Library&& other);
	    /**
	     * @brief Move assignment
	     * @param other Library to move
	     * @return Reference to this library
	     */
	    Library& operator=(Library&& other);
	    /**
	     * @brief Destructor
	     */
	    ~Library();
	    /**
	     * @brief Loads the library into memory
	     * @return True in case the library was loaded, otherwise false
	     */
	    bool load();
	    /**
	     * @brief Retrieves a pointer to a function within this library
	     * @details The function has to be a c-style function. It may have any signature, however
	     * 		this signature needs to be known to the caller, since the returned function
	     * 		pointer needs to be cast into the right format.
	     * @param name Name of the function to get
	     * @return Function pointer to the requested function or nullptr if something went wrong
	     */
	    Func getFunction(std::string const& name);

	    /**
	     * @brief Gets the default library file extension for the current operating system.
	     * @return "ddl" on windows, "so" on linux, "dylib" on mac
	     */
	    static std::string getFileExtension();
	private:
	    // Prevent copies
	    Library(Library& other) = delete;
	    Library& operator=(Library& other) = delete;

	    Filename m_path;
            internal_os::LibHandle m_handle{};
    };
}

#endif /* LIBRARY_H_ */
