//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_UTILITY_MESHUTILITY_H_
#define INCLUDE_DBGL_CORE_UTILITY_MESHUTILITY_H_

#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Mesh/IMesh.h"


namespace dbgl
{
    /**
     * @brief Provides some static functionality to work with meshes.
     */
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
	     * @brief Generates normals for a mesh
	     * @param[in,out] mesh Mesh to generate normals for
	     */
	    static void generateNormals(IMesh* mesh);
	    /**
	     * @brief Generates the tangent base for a mesh
	     * @param[in,out] mesh Mesh to generate tangent base for
	     */
	    static void generateTangentBase(IMesh* mesh);
	    /**
	     * @brief Reverses the direction of all normals
	     * @param[in,out] mesh Mesh to reverse normals for
	     */
	    static void reverseNormals(IMesh* mesh);
	    /**
	     * @brief Joins compatible vertices, i.e. vertices with the same position and uv coordinates and similar normals
	     * @param mesh Mesh to optimize
	     * @param maxCompatibilityAngle Maximum angle in radians for normals to count as compatible
	     */
	    static void optimize(IMesh* mesh, float maxCompatibilityAngle = 0);
    };
}

#endif /* INCLUDE_DBGL_CORE_UTILITY_MESHUTILITY_H_ */
