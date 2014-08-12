//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/ResourceManager/MeshResource.h"

namespace dbgl
{
    MeshResource::MeshResource(std::string const& filename) : Resource(filename), m_pMeshLoader(new OBJMeshLoader{})
    {
    }

    template <class T> MeshResource::MeshResource(MeshResourceInfo<T> const& info) : Resource(info), m_pMeshLoader(new T{})
    {
    }

    MeshResource::~MeshResource()
    {
	unload();
	delete m_pMeshLoader;
    }

    void MeshResource::load()
    {
	if(m_pMesh != nullptr)
	    LOG.warning("Tried to load a mesh resource multiple times in a row. Keeping previous state.");
	m_pMesh = m_pMeshLoader->load(m_filename);
	m_pMesh->updateBuffers();
	Resource::load();
    }

    void MeshResource::unload()
    {
	delete m_pMesh;
	m_pMesh = nullptr;
	Resource::unload();
    }

    Mesh* MeshResource::getMesh() const
    {
	return m_pMesh;
    }
}
