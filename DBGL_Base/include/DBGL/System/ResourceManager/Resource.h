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

#include <string>
#include <limits>
#include "ResourceManager.h"

namespace dbgl
{
    /**
     * @brief Interface class for all resource types that can be handled by a ResourceManager
     */
    class Resource
    {
	public:
	    /**
	     * @brief Base structure, can be used to pass additional information to ResourceManager
	     */
	    struct ResourceInfo
	    {
		std::string m_filename;
	    };

	    /**
	     * @brief Constructor
	     * @param filename Filename of the resource
	     */
	    Resource(std::string const& filename);
	    /**
	     * @brief Constructor
	     * @param info Object holding all the data needed to properly initialize the resource
	     */
	    Resource(ResourceInfo const& info);
	    /**
	     * @brief Destructor
	     */
	    virtual ~Resource() = default;
	    /**
	     * @brief Retrieves the resource filename
	     * @return The filename of this resource
	     */
	    std::string const& getFilename() const;
	    /**
	     * @brief Retrieves the handle of the resource
	     * @return The handle of the resource or InvalidHandle if not valid
	     */
	    ResourceHandle getHandle() const;
	    /**
	     * @brief Checks if this resource is currently loaded
	     * @return True in case the resource is loaded, otherwise false
	     */
	    bool isLoaded() const;
	    /**
	     * @brief Loads the resource
	     */
	    virtual void load() = 0;
	    /**
	     * @brief Unloads the resource
	     */
	    virtual void unload() = 0;

	protected:
	    /**
	     * @brief Resource filename
	     */
	    std::string m_filename = "";
	    /**
	     * @brief Handle of the resource, assigned by ResourceManager
	     */
	    ResourceHandle m_handle = InvalidHandle;
	    /**
	     * @brief Amount of references the ResourceManager has passed of this resource
	     * @note If this reaches zero, it might be unloaded by the resource manager
	     */
	    unsigned int m_refCount = 0;
	    /**
	     * @brief Indicates if the resource is currently loaded
	     */
	    bool m_loaded = false;

	    friend class ResourceManager<Resource>;
    };
}



#endif /* IRESOURCE_H_ */
