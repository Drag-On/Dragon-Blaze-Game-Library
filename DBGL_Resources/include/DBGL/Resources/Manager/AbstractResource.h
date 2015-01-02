//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_MANAGER_ABSTRACTRESOURCE_H_
#define INCLUDE_DBGL_RESOURCES_MANAGER_ABSTRACTRESOURCE_H_

#include "IResource.h"

namespace dbgl
{
    /**
     * @brief Abstract base class for resources
     */
    class AbstractResource: public IResource
    {
	public:
	    /**
	     * @brief Constructor
	     * @param handle Handle to assign to this resource
	     */
	    AbstractResource(ResourceHandle handle);
	    virtual ResourceHandle getHandle() const;
	    virtual ResourceHandle const& peekHandle() const;
	    virtual bool isLoaded() const;
	    virtual void load();
	    virtual void unload();

	protected:
	    /**
	     * @brief Handle of this resource
	     */
	    ResourceHandle m_handle;
	    /**
	     * @brief Indicates if the resource is loaded
	     */
	    bool m_loaded = false;
    };
}

#endif /* INCLUDE_DBGL_RESOURCES_MANAGER_ABSTRACTRESOURCE_H_ */
