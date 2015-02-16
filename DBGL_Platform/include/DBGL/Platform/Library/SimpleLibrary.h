//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SIMPLELIBRARY_H_
#define SIMPLELIBRARY_H_

#include<string>

#include "Library.h"
#include"DBGL/Platform/File/Filename.h"

namespace dbgl
{
    /**
     * @brief Advanced library class that can load classes
     * @details A simple library must have at least two c-style functions:
     * 		    - Base* create()
     * 		    - void destroy(Base*)
     * 		create() is used to create a new instance of the interface class Base,
     * 		destroy() is used to delete any previously created instance.
     * 		The SimpleLibrary allows only one instance of the library class to be created,
     * 		however it manages this instance and makes sure it will get freed eventually.
     */
    template<class Base> class SimpleLibrary
    {
	public:
	    /**
	     * @brief Creates a new library
	     * @param path Path of the library to load
	     */
	    SimpleLibrary(std::string const& path);
	    /**
	     * @brief Creates a new library
	     * @param path Path of the library to load
	     */
	    SimpleLibrary(Filename const& path);
	    /**
	     * @brief Move constructor
	     * @param other Library to move
	     */
	    SimpleLibrary(SimpleLibrary&& other);
	    /**
	     * @brief Move assignment
	     * @param other Library to move
	     * @return Reference to this library
	     */
	    SimpleLibrary& operator=(SimpleLibrary&& other);
	    /**
	     * @brief Destructor
	     */
	    ~SimpleLibrary();
	    /**
	     * @brief Loads the library
	     * @return True in case the library could be loaded, otherwise false
	     */
	    bool load();
	    /**
	     * @brief Retrieves a pointer to the created class if loading was successful.
	     * @return A pointer to the created class or nullptr, if the library could not be loaded.
	     */
	    Base* get();

	private:
	    SimpleLibrary(SimpleLibrary&) = delete;
	    SimpleLibrary& operator=(SimpleLibrary&) = delete;

	    using CreateFunc = Base*(*)(void);
	    using DestroyFunc = void(*)(Base*);

	    Library m_lib;
	    CreateFunc m_pCreate = nullptr;
	    DestroyFunc m_pDestroy = nullptr;
	    Base* m_pClass = nullptr;
    };
}

#include "../Library/SimpleLibrary.imp"

#endif /* SIMPLELIBRARY_H_ */
