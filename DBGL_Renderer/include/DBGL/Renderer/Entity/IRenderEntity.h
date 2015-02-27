//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_IRENDERENTITY_H_
#define INCLUDE_DBGL_RENDERER_IRENDERENTITY_H_

#include "DBGL/Core/Math/Matrix4x4.h"
#include "DBGL/Platform/Mesh/IMesh.h"

namespace dbgl
{
	/**
	 * @brief Interface class for renderable entities
	 */
	class IRenderEntity
	{
	public:
		/**
		 * @brief Destructor
		 */
		virtual ~IRenderEntity() = default;
		/**
		 * @brief Checks if the entity must be considered as having translucent parts
		 * @return True if the entity is translucent, otherwise false
		 */
		virtual bool isTranslucent() = 0;
		/**
		 * @brief Sets all necessary render states that are needed to render this entity
		 */
		virtual void setupMaterial() = 0;
		/**
		 * @brief Returns an ID that uniquely identifies the material used by this entity
		 * @return The material ID
		 * @note If two entities return the same material ID they guarantee that their setupMaterial() methods are
		 * 		 identical as well. Therefore, the renderer is free to optimize out subsequent calls to setupMaterial()
		 * 		 of identical materials.
		 */
		virtual int getMaterialId() = 0;
		/**
		 * @brief Retrieves the entitie's model matrix
		 * @return Model matrix
		 */
		virtual Mat4f const& getModelMatrix() = 0;
		/**
		 * @brief Retrieves the mesh of this entity
		 * @return Pointer to the mesh
		 */
		virtual IMesh* getMesh() = 0;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_IRENDERENTITY_H_ */
