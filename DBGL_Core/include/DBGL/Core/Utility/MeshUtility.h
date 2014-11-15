//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_UTILITY_MESHUTILITY_H_
#define INCLUDE_DBGL_CORE_UTILITY_MESHUTILITY_H_

#include <cstring>
#include <array>
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Mesh/IMesh.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Math/Vector2.h"

namespace dbgl
{
    class MeshUtility
    {
	public:
	    /**
	     * @brief Creates a simple triangle mesh
	     * @param sendToGPU Determines if buffers should be updated after creation
	     * @param usage Initial usage pattern
	     * @return The created mesh
	     */
	    static IMesh* createTriangle(bool sendToGPU = true, IMesh::Usage usage = IMesh::Usage::StaticDraw);
	    /**
	     * @brief Creates a simple rectangle mesh
	     * @param sendToGPU Determines if buffers should be updated after creation
	     * @param usage Initial usage pattern
	     * @return The created mesh
	     */
	    static IMesh* createRectangle(bool sendToGPU = true, IMesh::Usage usage = IMesh::Usage::StaticDraw);
	    /**
	     * @brief Creates a simple cube mesh
	     * @param sendToGPU Determines if buffers should be updated after creation
	     * @param usage Initial usage pattern
	     * @return The created mesh
	     */
	    static IMesh* createCube(bool sendToGPU = true, IMesh::Usage usage = IMesh::Usage::StaticDraw);
	    /**
	     * @brief Creates a simple four-sided pyramid mesh
	     * @param sendToGPU Determines if buffers should be updated after creation
	     * @param usage Initial usage pattern
	     * @return The created mesh
	     */
	    static IMesh* createPyramid(bool sendToGPU = true, IMesh::Usage usage = IMesh::Usage::StaticDraw);
	    /**
	     * @brief Generates the tangent base for a mesh
	     * @param[in,out] mesh Mesh to generate tangent base for
	     * @return Pointer to the same mesh that has been passed in
	     */
	    static IMesh* generateTangentBase(IMesh* mesh);
    };
}

#endif /* INCLUDE_DBGL_CORE_UTILITY_MESHUTILITY_H_ */
