//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IMESH_H_
#define IMESH_H_

#include <vector>

namespace dbgl
{
    class IMesh
    {
	public:
	    /**
	     * @brief Mesh buffer usage
	     */
	    enum class Usage
	    {
		StreamDraw, //!< StreamDraw
		StreamRead, //!< StreamRead
		StreamCopy, //!< StreamCopy
		StaticDraw, //!< StaticDraw
		StaticRead, //!< StaticRead
		StaticCopy, //!< StaticCopy
		DynamicDraw, //!< DynamicDraw
		DynamicRead, //!< DynamicRead
		DynamicCopy, //!< DynamicCopy
	    };

	    /**
	     * @brief Vertex in 3 dimensions
	     */
	    struct Vertex
	    {
		public:
		    float x, y, z;
	    };
	    /**
	     * @brief UV coordinate in 2 dimensions
	     */
	    struct UV
	    {
		public:
		    float u, v;
	    };

	    /**
	     * @brief Destructor
	     */
	    virtual ~IMesh() = default;
	    /**
	     * @return A reference to the indices list
	     */
	    virtual std::vector<unsigned short>& indices() = 0;
	    /**
	     * @return A reference to the vertices list
	     */
	    virtual std::vector<Vertex>& vertices() = 0;
	    /**
	     * @return A reference to the normals list
	     */
	    virtual std::vector<Vertex>& normals() = 0;
	    /**
	     * @return A reference to the UVs list
	     */
	    virtual std::vector<UV>& uvs() = 0;
	    /**
	     * @return A reference to the tangents list
	     */
	    virtual std::vector<Vertex>& tangents() = 0;
	    /**
	     * @return A reference to the bitangents list
	     */
	    virtual std::vector<Vertex>& bitangents() = 0;
	    /**
	     * @brief Set the buffer usage pattern
	     * @param usage New usage pattern
	     */
	    virtual void setUsage(Usage usage) = 0;
	    /**
	     * @brief Retrieves the current buffer usage pattern
	     * @return Current usage pattern
	     */
	    virtual Usage getUsage() const = 0;
	    /**
	     * @brief Updates the underlying hardware buffers
	     */
	    virtual void updateBuffers() = 0;
    };
}

#endif /* IMESH_H_ */