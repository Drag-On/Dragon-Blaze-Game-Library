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
		/**
		 * @brief Retrieves the camera position in world space
		 * @return Cam position
		 */
		virtual Vec3f const& getPosition() = 0;
		/**
		 * @brief Retrieves the camera's direction vector in world space
		 * @return Cam direction
		 */
		virtual Vec3f const& getDirection() = 0;
		/**
		 * @brief Retrieves the camera's up vector in world space
		 * @return Cam up direction
		 */
		virtual Vec3f const& getUp() = 0;
		/**
		 * @brief Retrieves the camera's distance to the near plane
		 * @return Near plane
		 */
		virtual float getNear() = 0;
		/**
		 * @brief Retrieves the camera's distance to the far plane
		 * @return Far plane
		 */
		virtual float getFar() = 0;
		/**
		 * @brief Retrieves the camera's field of view
		 * @return Field of view
		 */
		virtual float getFieldOfView() = 0;
		/**
		 * @brief Retrieves the camera's ratio
		 * @return Ratio
		 */
		virtual float getRatio() = 0;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_ENTITY_ICAMERAENTITY_H_ */
