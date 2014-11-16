//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ADVANCEDMODULE_H_
#define ADVANCEDMODULE_H_

#include<string>
#include"Module.h"
#include"DBGL/Platform/File/Filename.h"

namespace dbgl
{
    /**
     * @brief Advanced module class that can load classes
     * @details An advanced module must have at least two c-style functions:
     * 		    - Base* create()
     * 		    - void destroy(Base*)
     * 		create() is used to create a new instance of the interface class Base,
     * 		destroy() is used to delete any previously created instance.
     * 		The AdvancedModule allows only one instance of the module class to be created,
     * 		however it manages this instance and makes sure it will get freed eventually.
     */
    template<class Base> class AdvancedModule
    {
	public:
	    /**
	     * @brief Creates a new advanced module
	     * @param path Path of the library to load
	     */
	    AdvancedModule(std::string const& path);
	    /**
	     * @brief Creates a new advanced module
	     * @param path Path of the library to load
	     */
	    AdvancedModule(Filename const& path);
	    /**
	     * @brief Move constructor
	     * @param other AdvancedModule to move
	     */
	    AdvancedModule(AdvancedModule&& other);
	    /**
	     * @brief Move assignment
	     * @param other AdvancedModule to move
	     * @return Reference to this module
	     */
	    AdvancedModule& operator=(AdvancedModule&& other);
	    /**
	     * @brief Destructor
	     */
	    ~AdvancedModule();
	    /**
	     * @brief Loads the library
	     * @return True in case the library could be loaded, otherwise false
	     */
	    bool load();
	    /**
	     * @brief Retrieves a pointer to the created class if loading was successful.
	     * @return A pointer to the created class or nullptr, if the module could not be loaded.
	     */
	    Base* get();

	private:
	    AdvancedModule(AdvancedModule&) = delete;
	    AdvancedModule& operator=(AdvancedModule&) = delete;

	    using CreateFunc = Base*(*)(void);
	    using DestroyFunc = void(*)(Base*);

	    Module m_module;
	    CreateFunc m_pCreate = nullptr;
	    DestroyFunc m_pDestroy = nullptr;
	    Base* m_pClass = nullptr;
    };
}

#include "AdvancedModule.imp"

#endif /* ADVANCEDMODULE_H_ */
