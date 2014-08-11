//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <vector>
#include <stack>
#include <unordered_map>
#include <set>
#include <string>
#include <algorithm>
#include "ResourceException.h"

namespace dbgl
{
    /**
     * @brief Unique handle the ResourceManager assigns to every resource
     */
    using ResourceHandle = unsigned int;
    /**
     * @brief Value of an invalid handle
     */
    static const ResourceHandle InvalidHandle = std::numeric_limits<ResourceHandle>::max();

    /**
     * @brief Manages a certain type of resource which is assumed to inherit from IResource.
     */
    template <typename T> class ResourceManager
    {
	public:
	    /**
	     * @brief Constructor
	     */
	    ResourceManager();
	    /**
	     * @brief Destructor
	     */
	    ~ResourceManager();
	    /**
	     * @brief Adds a new resource to the manager
	     * @param filename Filename to load resource from
	     * @return Handle assigned to the resource
	     */
	    ResourceHandle add(std::string const& filename);
	    /**
	     * @brief Adds a new resource to the manager
	     * @param filename Filename to load resource from
	     * @return Handle assigned to the resource
	     */
	    template <size_t N> ResourceHandle add(const char(&filename)[N]);
	    /**
	     * @brief Adds a new resource to the manager
	     * @param filename Filename to load resource from
	     * @param info All info the resource needs to be loaded
	     * @return Handle assigned to the resource
	     */
	    template <typename ResInfo> ResourceHandle add(ResInfo const& info);
	    /**
	     * @brief Adds a range of new resources to the manager
	     * @param begin Iterator representing the beginning of a list of filenames
	     * @param end Iterator representing the end of a list of filenames
	     */
	    template <typename Iterator> void add(Iterator begin, Iterator end);
	    /**
	     * @brief Checks if the resource with a certain filename exists
	     * @param filename Filename of the resource to search for
	     * @return True in case the resource is known, otherwise false
	     */
	    bool checkExist(std::string const& filename) const;
	    /**
	     * @brief Checks if the resource with a certain handle exists
	     * @param handle Handle of the resource to search for
	     * @return True in case the resource is known, otherwise false
	     */
	    bool checkExist(ResourceHandle handle) const;
	    /**
	     * @brief Retrieves the handle associated with a filename
	     * @param filename Filename to get the handle for
	     * @return The handle associated with the passed filename or an invalid handle, if not found
	     */
	    ResourceHandle getHandle(std::string const& filename) const;
	    /**
	     * @brief Retrieves a resource by filename
	     * @param filename Filename of the resource to retrieve
	     * @param forceLoad Forces the returned resource to be loaded
	     * @return Pointer to the resource or nullptr if not found
	     * @details The requested resource needs to be released after it is not needed
	     * 		by the caller anymore.
	     */
	    T* request(std::string const& filename, bool forceLoad = false);
	    /**
	     * @brief Retrieves a resource by handle
	     * @param handle Handle of the resource to retrieve
	     * @param forceLoad Forces the returned resource to be loaded
	     * @return Pointer to the resource or nullptr if not found
	     * @details The requested resource needs to be released after it is not needed
	     * 		by the caller anymore.
	     */
	    T* request(ResourceHandle handle, bool forceLoad = false);
	    /**
	     * @brief Indicates that the caller has no interest in a resource anymore
	     * @param filename Name of the resource to release
	     * @return True in case the resource was found, otherwise false
	     * @details If there are no more instances that requested the resource, it may
	     * 		be unloaded by the manager at any time.
	     */
	    bool release(std::string const& filename);
	    /**
	     * @brief Indicates that the caller has no interest in a resource anymore
	     * @param handle Handle of the resource to release
	     * @return True in case the resource was found, otherwise false
	     * @details If there are no more instances that requested the resource, it may
	     * 		be unloaded by the manager at any time.
	     */
	    bool release(ResourceHandle handle);
	    /**
	     * @brief Removes the resource with the passed filename from the manager
	     * @param filename Name of the resource to remove
	     * @return True in case the resource has been removed, otherwise false
	     * @warning This will remove the resource from the resource manager and deallocate it.
	     * 		The handle of the resource will be invalidated.
	     */
	    bool remove(std::string const& filename);
	    /**
	     * @brief Removes the resource with the passed filename from the manager
	     * @param handle Handle of the resource to remove
	     * @return True in case the resource has been removed, otherwise false
	     * @warning This will remove the resource from the resource manager and deallocate it.
	     * 		The handle of the resource will be invalidated.
	     */
	    bool remove(ResourceHandle handle);
	    /**
	     * @brief Checks if there are resources that need to be loaded
	     * @return True in case there are resources to load, otherwise false
	     */
	    bool needLoad() const;
	    /**
	     * @brief Provides the amount of resources that need loading
	     * @return Amount of resources that need loading
	     */
	    unsigned int getLoadQueueSize() const;
	    /**
	     * @brief Loads the next resource which needs to be loaded
	     */
	    void loadNext();
	    /**
	     * @brief Computes the amount of held resources
	     * @return The amount of held resources
	     */
	    unsigned int size() const;

	private:
	    /**
	     * @brief Acquires the next valid handle
	     * @return
	     */
	    ResourceHandle newHandle();
	    /**
	     * @brief Adds a new resource to the manager using the next valid handle
	     * @param res
	     * @return
	     */
	    ResourceHandle addNew(T* res);
	    /**
	     * @brief Checks if the passed handle is valid
	     * @param handle Handle to check
	     * @return True in case the handle is valid, otherwise false
	     */
	    bool isValid(ResourceHandle handle) const;

	    /**
	     * @brief Collects handles that have been invalidated
	     */
	    std::stack<ResourceHandle> m_openHandles;
	    /**
	     * @brief List of all currently known resources
	     */
	    std::vector<T*> m_resources;
	    /**
	     * @brief Maps file names to resource handles to accelerate lookup
	     */
	    std::unordered_map<std::string, ResourceHandle> m_fileNameMap;
	    /**
	     * @brief Handles of resources that need processing, i.e. loading or unloading
	     */
	    std::set<ResourceHandle> m_needProcHandles;
    };
}

#include "ResourceManager.imp"

#endif /* RESOURCEMANAGER_H_ */
