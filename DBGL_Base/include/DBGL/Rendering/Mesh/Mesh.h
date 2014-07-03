//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MESH_H_
#define MESH_H_

#include <stdexcept>
#include <sstream>
#include "MeshLoader.h"
#include "OBJMeshLoader.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Bitmask/Bitmask.h"
#include "DBGL/Math/Vector3.h"
#include "DBGL/Math/Vector2.h"
#include "DBGL/Rendering/Renderer/Renderer.h"

namespace dbgl
{
    /**
     * @brief Represents a 3D model which can be rendered to the screen
     */
    class Mesh
    {
	private:
	    std::vector<unsigned short> m_indices;
	    Renderer::IndexBufferId m_indexBuffer = Renderer::INVALID_INDEX_BUFFER;
	    std::vector<Vector3<float>> m_vertices;
	    Renderer::VertexBufferId m_vertexBuffer = Renderer::INVALID_VERTEX_BUFFER;
	    std::vector<Vector3<float>> m_normals;
	    Renderer::VertexBufferId m_normalBuffer = Renderer::INVALID_VERTEX_BUFFER;
	    std::vector<Vector2<float>> m_uv;
	    Renderer::VertexBufferId m_uvBuffer = Renderer::INVALID_VERTEX_BUFFER;
	    std::vector<Vector3<float>> m_tangents;
	    Renderer::VertexBufferId m_tangentBuffer = Renderer::INVALID_VERTEX_BUFFER;
	    std::vector<Vector3<float>> m_bitangents;
	    Renderer::VertexBufferId m_bitangentBuffer = Renderer::INVALID_VERTEX_BUFFER;
	public:
	    /**
	     * @brief File types that can be loaded
	     */
	    enum Type
	    {
		OBJ, //!< OBJ
	    };
	    /**
	     * @brief Flag indicating if tangents and bitangents should be generated
	     */
	    static const int GenerateTangentBase = 1 << 0;
	    /**
	     * @brief Automatically sends the loaded mesh to gpu
	     */
	    static const int SendToGPU = 1 << 1;
	    /**
	     * @brief Indicates if the mesh should be optimized (i.e. vertices that are
	     * 	      close to each other and have normals within 80° are merged)
	     */
	    static const int Optimize = 1 << 2;

	    /**
	     * @brief Bare constructor. You probably want to use the factory methods.
	     */
	    Mesh();
	    /**
	     * @brief Clean up memory
	     */
	    ~Mesh();
	    /**
	     * @return A const reference to the indices list
	     */
	    auto getIndices() const -> decltype(m_indices) const&;
	    /**
	     * @return A const reference to the vertices list
	     */
	    auto getVertices() const -> decltype(m_vertices) const&;
	    /**
	     * @return A const reference to the normals list
	     */
	    auto getNormals() const -> decltype(m_normals) const&;
	    /**
	     * @return A const reference to the UVs list
	     */
	    auto getUVs() const -> decltype(m_uv) const&;
	    /**
	     * @return A const reference to the tangents list
	     */
	    auto getTangents() const -> decltype(m_tangents) const&;
	    /**
	     * @return A const reference to the bitangents list
	     */
	    auto getBitangents() const -> decltype(m_bitangents) const&;
	    /**
	     * @return A reference to the indices list
	     */
	    auto indices() -> decltype(m_indices)&;
	    /**
	     * @return A reference to the vertices list
	     */
	    auto vertices() -> decltype(m_vertices)&;
	    /**
	     * @return A reference to the normals list
	     */
	    auto normals() -> decltype(m_normals)&;
	    /**
	     * @return A reference to the UVs list
	     */
	    auto uvs() -> decltype(m_uv)&;
	    /**
	     * @return A reference to the tangents list
	     */
	    auto tangents() -> decltype(m_tangents)&;
	    /**
	     * @return A reference to the bitangents list
	     */
	    auto bitangents() -> decltype(m_bitangents)&;
	    /**
	     * @brief Loads a mesh from hard disk
	     * @warning The allocated memory needs to be freed manually!
	     * @param type File type to load
	     * @param path Path of the file
	     * @param flags Parameters to pass to the loader
	     * @return The loaded mesh or NULL if something went wrong
	     */
	    static Mesh* load(const Type type, const std::string path,
		    Bitmask<> flags = SendToGPU | Optimize);
	    /**
	     * @brief Loads a mesh from hard disk
	     * @warning The allocated memory needs to be freed manually!
	     * @param path Path of the file
	     * @param flags Parameters to pass to the loader
	     * @return The loaded mesh or NULL if something went wrong
	     */
	    template<class Loader> static Mesh* load(const std::string path,
		    Bitmask<> flags = SendToGPU | Optimize);
	    /**
	     * @brief Loads a mesh from hard disk
	     * @warning The allocated memory needs to be freed manually!
	     * @param loader Loader to use
	     * @param path Path of the file
	     * @param flags Parameters to pass to the loader
	     * @return The loaded mesh or NULL if something went wrong
	     */
	    static Mesh* load(MeshLoader& loader, const std::string path,
		    Bitmask<> flags = SendToGPU | Optimize);
	    /**
	     * @brief Creates a mesh that represents a simple triangle
	     * @warning The allocated memory needs to be freed manually!
	     * @param flags Parameters to pass to the loader
	     * @return The triangle mesh
	     */
	    static Mesh* makeTriangle(Bitmask<> flags = SendToGPU | Optimize);
	    /**
	     * @brief Creates a mesh that represents a simple plane
	     * @warning The allocated memory needs to be freed manually!
	     * @param flags Parameters to pass to the loader
	     * @return The plane mesh
	     */
	    static Mesh* makePlane(Bitmask<> flags = SendToGPU | Optimize);
	    /**
	     * @brief Creates a mesh that represents a cube
	     * @warning The allocated memory needs to be freed manually!
	     * @param flags Parameters to pass to the loader
	     * @return The cube mesh
	     */
	    static Mesh* makeCube(Bitmask<> flags = SendToGPU | Optimize);
	    /**
	     * @brief Creates a mesh that represents a four-sided pyramid
	     * @warning The allocated memory needs to be freed manually!
	     * @param flags Parameters to pass to the loader
	     * @return The pyramid mesh
	     */
	    static Mesh* makePyramid(Bitmask<> flags = SendToGPU | Optimize);
	    /**
	     * @brief Updates GL buffers, resends vertices, uvs and normals
	     */
	    void updateBuffers();
	    /**
	     * @brief Checks if the mesh has a vertex with the passed coordinates
	     * 	      (or at least very, very similar)
	     * @param coords Coordinates to search for
	     * @return Index of the vertex or size if not found
	     */
	    unsigned int getVertexIndex(Vec3f const& coords);
	    /**
	     * @brief Generates tangents and bitangents from this mesh's normals and UVs
	     */
	    void generateTangentBasis();
	    /**
	     * @brief Removes a vertex and all faces using that vertex from the mesh
	     * @param i Index of the vertex to remove
	     * @note This method does not update the buffers automatically, so you
	     * 	     probably want to do that on your own.
	     * @warning The internal data representation isn't very well suited for
	     * 		removal of vertices, thus this method might take quite a long
	     * 		time to finish.
	     */
	    void removeVertex(unsigned short i);

	    friend class RenderContext;
	    // So the render context can render
    };
}

#endif /* MESH_H_ */
