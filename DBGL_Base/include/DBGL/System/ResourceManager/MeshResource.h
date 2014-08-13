//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MESHRESOURCE_H_
#define MESHRESOURCE_H_

#include <string>
#include "Resource.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Rendering/Mesh/MeshLoader.h"
#include "DBGL/Rendering/Mesh/OBJMeshLoader.h"
#include "DBGL/System/Bitmask/Bitmask.h"
#include "DBGL/System/Log/Log.h"

namespace dbgl
{
    /**
     * @brief A mesh resource which can be used with a ResourceManager
     * @details It wraps a mesh inside and makes sure it gets loaded at an appropriate time
     */
    class MeshResource : public Resource
    {
	public:
	    /**
	     * @brief Base structure, can be used to pass additional information to ResourceManager
	     */
	    template <class T> struct MeshResourceInfo : public Resource::ResourceInfo
	    {
		/**
		 * @brief Type of the loader to use
		 */
		using LoaderType = T;

		/**
		 * @brief Constructor
		 * @param filename Filename
		 * @param flags Flags to pass to the mesh loader
		 * @param usage Expected usage
		 */
		MeshResourceInfo(std::string filename, Bitmask<> flags = 0, Mesh::Usage usage = Mesh::Usage::StaticDraw)  :
		    ResourceInfo(filename), m_flags(flags), m_usage(usage)
		{
		}

		/**
		 * Flags to pass to the loader, defined in Mesh class
		 */
		Bitmask<> m_flags = 0;
		/**
		 * @brief Expected mesh usage
		 */
		Mesh::Usage m_usage = Mesh::Usage::StaticDraw;
	    };

	    /**
	     * @brief Constructor
	     * @param filename Filename of the mesh
	     */
	    MeshResource(std::string const& filename);
	    /**
	     * @brief Constructor
	     * @param info Object holding all the data needed to properly initialize the resource
	     */
	    template<class T> MeshResource(MeshResourceInfo<T> const& info) :
		    Resource(info), m_pMeshLoader(new T {}), m_flags(info.m_flags), m_usage(info.m_usage)
	    {
	    }
	    /**
	     * @brief Destructor
	     */
	    virtual ~MeshResource();
	    /**
	     * @brief Loads the resource
	     */
	    virtual void load();
	    /**
	     * @brief Unloads the resource
	     */
	    virtual void unload();
	    /**
	     * @brief Provides the held mesh
	     * @return Pointer to the held mesh or nullptr if not loaded yet
	     */
	    Mesh* getMesh() const;

	private:
	    Mesh* m_pMesh = nullptr;
	    MeshLoader* m_pMeshLoader = nullptr;
	    Bitmask<> m_flags = 0;
	    Mesh::Usage m_usage = Mesh::Usage::StaticDraw;

	    friend class ResourceManager<MeshResource>;
    };
}



#endif /* MESHRESOURCE_H_ */
