//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_MANAGER_RESOURCEMANAGER_H_
#define INCLUDE_DBGL_RESOURCES_MANAGER_RESOURCEMANAGER_H_

#include <vector>
#include <set>
#include <unordered_map>
#include <utility>
#include <type_traits>
#include "DBGL/Resources/Manager/IResource.h"
#include "DBGL/Core/Hashing/FNVHasher.h"

namespace dbgl
{
    template<class T> class ResourceManager
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
	     * @brief Adds a resource with the passed parameters
	     * @param params Parameters to pass to the resource constructor
	     * @return Handle of the added resource
	     */
	    template<typename ... Types> typename T::ResourceHandle add(Types&&... params);
	    /**
	     * @brief Retrieves a resource handle by other identifying parameters
	     * @details The parameters depend on the resource implementation, but may be something like filename and path.
	     * @param params Parameters that identify the resource
	     * @return Handle of the resource or invalid handle if resource not found
	     * @note This operation generally has near-constant time complexity if the resource has been found using the same
	     * 	     parameters before. On first identification it is linear in the amount of managed resources. This is also
	     * 	     the worst-case.
	     */
	    template<typename ... Types> typename T::ResourceHandle identify(Types&&... params);
	    /**
	     * @brief Retrieve a resource by its handle
	     * @param handle Resource handle
	     * @param forceLoad Forces the resource to be returned loaded
	     * @return Pointer to the resource or nullptr if handle invalid
	     */
	    T* request(typename T::ResourceHandle const& handle, bool forceLoad = false);

	private:
	    uint32_t computeHash();
	    template<typename First, typename ... Last> uint32_t computeHash(First const& first, Last&&... last);

	    HandleFactory<> m_handleFactory;
	    std::vector<T> m_resources;
	    std::set<typename IResource::ResourceHandle> m_needProcHandles;
	    std::unordered_multimap<uint32_t, unsigned int> m_resLookup;
    };
}

#include "ResourceManager.imp"

#endif /* INCLUDE_DBGL_RESOURCES_MANAGER_RESOURCEMANAGER_H_ */
