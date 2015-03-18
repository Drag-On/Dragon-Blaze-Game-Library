//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Mesh/MeshResource.h"
#include "DBGL/Resources/Mesh/MeshUtility.h"

namespace dbgl
{
	MeshIO MeshResource::s_meshIO { };

	MeshResource::MeshResource(ResourceHandle h, std::string const& filename, bool genNormals, bool genTangents)
			: AbstractResource(h), m_filename { filename }, m_genNormals { genNormals }, m_genTangents { genTangents }
	{
	}

	void MeshResource::load()
	{
		m_pMesh = s_meshIO.load(m_filename);
		if (m_pMesh)
		{
			if (m_genNormals)
				MeshUtility::generateNormals(m_pMesh);
			if (m_genTangents)
				MeshUtility::generateTangentBase(m_pMesh);
			m_pMesh->updateBuffers();
		}
		else
		{
			Log::getDefault().error("Couldn't load mesh \"%\". Using a cube instead.", m_filename);
			m_pMesh = MeshUtility::createCube(true);
		}
		AbstractResource::load();
	}

	void MeshResource::unload()
	{
		delete m_pMesh;
		m_pMesh = nullptr;
		AbstractResource::unload();
	}

	bool MeshResource::identify(std::string const& filename) const
	{
		return m_filename == filename;
	}

	IMesh* MeshResource::getMesh()
	{
		return m_pMesh;
	}

	MeshIO& MeshResource::loader()
	{
		return MeshResource::s_meshIO;
	}
}

