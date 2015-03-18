//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RESOURCES_MESH_MESHRESOURCE_H_
#define INCLUDE_DBGL_RESOURCES_MESH_MESHRESOURCE_H_

#include "DBGL/Resources/Manager/AbstractResource.h"
#include "DBGL/Resources/Mesh/MeshIO.h"
#include "DBGL/Core/Debug/Log.h"

namespace dbgl
{
	/**
	 * @brief A mesh resource
	 */
	class MeshResource: public AbstractResource
	{
	public:
		/**
		 * @brief Constructor
		 * @param h Assigned resource handle
		 * @param filename File to load mesh from
		 * @param genNormals Indicates if normals need to be generated for this mesh
		 * @param genTangents Indicates if (bi)tangents need to be generated for this mesh
		 */
		MeshResource(ResourceHandle h, std::string const& filename, bool genNormals = false, bool genTangents = false);
		virtual void load();
		virtual void unload();
		/**
		 * @brief Retrieves the actual mesh
		 * @return Pointer to the loaded mesh or nullptr, if not loaded yet
		 */
		IMesh* getMesh();
		/**
		 * @brief Reference to the mesh loader instance used by all mesh resources
		 * @return Reference to mesh loader
		 * @note This mesh loader needs to be pointed to the right plugins in order to work!
		 */
		static MeshIO& loader();
	private:
		static MeshIO s_meshIO;
		std::string m_filename;
		bool m_genNormals = false;
		bool m_genTangents = false;
		IMesh* m_pMesh = nullptr;
	};
}

#endif /* INCLUDE_DBGL_RESOURCES_MESH_MESHRESOURCE_H_ */
