//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_MATERIAL_IMATERIAL_H_
#define INCLUDE_DBGL_RENDERER_MATERIAL_IMATERIAL_H_

#include "DBGL/Renderer/Entity/GameEntity.h"

namespace dbgl
{
	/**
	 * @brief Interface class for materials, which may include any combination of textures, shaders, and additional data.
	 */
	class IMaterial
	{
	public:
		/**
		 * @brief Destructor
		 */
		virtual ~IMaterial() = default;
		/**
		 * @brief Checks if the entity must be considered as having translucent parts
		 * @return True if the entity is translucent, otherwise false
		 */
		virtual bool isTranslucent() = 0;
		/**
		 * @brief Sets all render states and shader uniforms, that are unique to this entity.
		 * @note This method is guaranteed to be called before rendering of each entity.
		 * @param entity Entity to set up material for
		 */
		virtual void setupUnique(GameEntity const& entity) = 0;
		/**
		 * @brief Sets additional render states and shader uniforms, that are the same for each entity with this material.
		 * @note This method may be optimized out be the renderer if two subsequently rendered object have the same material.
		 */
		virtual void setupMaterial() = 0;
		/**
		 * @brief Returns an ID that uniquely identifies this material
		 * @return The material ID
		 * @note If two entities return the same material ID they guarantee that their setupMaterial() methods are
		 * 		 identical as well. Therefore, the renderer is free to optimize out subsequent calls to setupMaterial()
		 * 		 of identical materials.
		 */
		virtual int getMaterialId() = 0;
		/**
		 * @brief Loads all the resources required by this material
		 */
		virtual void load() = 0;
		/**
		 * @brief Unloads all the resources required by this material
		 */
		virtual void unload() = 0;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_MATERIAL_IMATERIAL_H_ */
