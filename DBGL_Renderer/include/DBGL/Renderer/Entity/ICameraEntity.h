//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_ENTITY_ICAMERAENTITY_H_
#define INCLUDE_DBGL_RENDERER_ENTITY_ICAMERAENTITY_H_

#include "DBGL/Core/Math/Matrix4x4.h"

namespace dbgl
{
	/**
	 * @brief Interface class for camera entities as used by the renderer
	 */
	class ICameraEntity
	{
	public:
		/**
		 * @brief Destructor
		 */
		virtual ~ICameraEntity() = default;
		/**
		 * @brief Retrieves the camera's view matrix
		 * @return Camera view matrix
		 */
		virtual Mat4f const& getViewMatrix() = 0;
		/**
		 * @brief Retrieves the camera's projection matrix
		 * @return Camera projection matrix
		 */
		virtual Mat4f const& getProjectionMatrix() = 0;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_ENTITY_ICAMERAENTITY_H_ */
