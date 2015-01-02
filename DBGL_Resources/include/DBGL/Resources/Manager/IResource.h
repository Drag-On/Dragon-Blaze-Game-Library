//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IRESOURCE_H_
#define IRESOURCE_H_

#include "DBGL/Core/Handle/HandleFactory.h"

namespace dbgl
{
    /**
     * @brief Interface class for all resource types that can be handled by a ResourceManager
     */
    class IResource
    {
	public:
	    /**
	     * @brief Resource handle
	     */
	    using ResourceHandle = HandleFactory<>::Handle;

	    /**
	     * @brief Destructor
	     */
	    virtual ~IResource() = default;
	    /**
	     * @brief Retrieves the handle associated with this resource
	     * @return Handle of this resource
	     */
	    virtual ResourceHandle getHandle() const = 0;
	    /**
	     * @brief Provides a constant reference to the handle associated with this resource
	     * @return Handle of this resource
	     * @note This will not increase the handle reference count.
	     */
	    virtual ResourceHandle const& peekHandle() const = 0;
	    /**
	     * @brief Checks if this resource is currently loaded
	     * @return True in case the resource is loaded, otherwise false
	     */
	    virtual bool isLoaded() const = 0;
	    /**
	     * @brief Loads the resource
	     */
	    virtual void load() = 0;
	    /**
	     * @brief Unloads the resource
	     */
	    virtual void unload() = 0;
    };
}

#endif /* IRESOURCE_H_ */
