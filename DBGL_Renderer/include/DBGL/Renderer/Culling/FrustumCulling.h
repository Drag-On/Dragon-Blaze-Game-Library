//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_CULLING_FRUSTUMCULLING_H_
#define INCLUDE_DBGL_RENDERER_CULLING_FRUSTUMCULLING_H_

#include "DBGL/Core/Shape/HyperPlane.h"
#include "DBGL/Core/Math/Matrix4x4.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Renderer/Entity/ICameraEntity.h"

namespace dbgl
{
	/**
	 * @brief Functionality to filter out objects outside of the visible view frustum
	 */
	class FrustumCulling
	{
	public:
		/**
		 * @brief Constructor
		 */
		FrustumCulling();
		/**
		 * @brief Updates the frustum planes internally
		 */
		void update();
		/**
		 * @brief Checks if a point is within the frustum
		 * @param point Point in world space
		 * @return True if the point lies within the frustum, otherwise false
		 */
		bool checkPoint(Vec3f const& point);
		/**
		 * @brief Checks if a sphere intersects the frustum
		 * @param center Center of the sphere in world space
		 * @param radius Sphere radius
		 * @return True in case the sphere intersects the frustum, otherwise false
		 */
		bool checkSphere(Vec3f const& center, float radius);
		/**
		 * @brief Set new camera
		 * @param pCam New camera
		 */
		void setCamera(ICameraEntity* pCam);
		/**
		 * @brief Retrieves the currently set camera entity
		 * @return
		 */
		ICameraEntity* getCamera() const;
	private:
		ICameraEntity* m_pCam = nullptr;
		Plane<float> m_planes[6]; //near, far, left, right, top, bottom;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_CULLING_FRUSTUMCULLING_H_ */
