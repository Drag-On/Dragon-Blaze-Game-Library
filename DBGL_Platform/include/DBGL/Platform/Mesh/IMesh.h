//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IMESH_H_
#define IMESH_H_

#include <vector>
#include "DBGL/Core/Math/Vector2.h"
#include "DBGL/Core/Math/Vector3.h"

namespace dbgl
{
	/**
	 * @brief Interface class for mesh implementations.
	 */
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
		virtual std::vector<Vec3f>& vertices() = 0;
		/**
		 * @return A reference to the normals list
		 */
		virtual std::vector<Vec3f>& normals() = 0;
		/**
		 * @return A reference to the UVs list
		 */
		virtual std::vector<Vec2f>& uvs() = 0;
		/**
		 * @return A reference to the tangents list
		 */
		virtual std::vector<Vec3f>& tangents() = 0;
		/**
		 * @return A reference to the bitangents list
		 */
		virtual std::vector<Vec3f>& bitangents() = 0;
		/**
		 * @return Amount of indices inside the hardware buffer
		 */
		virtual unsigned int getIndexCount() const = 0;
		/**
		 * @return Amount of vertices inside the hardware buffer
		 */
		virtual unsigned int getVertexCount() const = 0;
		/**
		 * @return Amount of UVs inside the hardware buffer
		 */
		virtual unsigned int getUVCount() const = 0;
		/**
		 * @return Amount of normals inside the hardware buffer
		 */
		virtual unsigned int getNormalCount() const = 0;
		/**
		 * @return Amount of tangents inside the hardware buffer
		 */
		virtual unsigned int getTangentCount() const = 0;
		/**
		 * @return Amount of bitangents inside the hardware buffer
		 */
		virtual unsigned int getBitangentCount() const = 0;
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
	    /**
	     * @brief Generates a deep copy of this mesh
	     * @return The clone
	     */
	    virtual IMesh* clone() const = 0;
	};
}

#endif /* IMESH_H_ */
