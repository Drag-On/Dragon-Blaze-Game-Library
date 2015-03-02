//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_MATH_PLANE_H_
#define INCLUDE_DBGL_CORE_MATH_PLANE_H_

#include "Vector3.h"

namespace dbgl
{
	/**
	 * @brief Basic three-dimensional plane class
	 */
	template<typename T> class Plane
	{
	public:
		/**
		 * @brief Default constructor
		 */
		Plane() = default;
		/**
		 * @brief Constructor
		 * @param base Base point on the plane
		 * @param normal Plane normal
		 */
		Plane(Vector3<T> base, Vector3<T> normal);
		/**
		 * @brief Provides the plane normal
		 * @return Plane normal
		 */
		Vector3<T>& normal();
		/**
		 * @brief Provides the plane base point
		 * @return Plane base point
		 */
		Vector3<T>& base();
		/**
		 * @brief Checks if two planes intersect
		 * @param other Plane to check
		 * @return True if intersecting, otherwise false
		 */
		bool intersects(Plane const& other) const;
		/**
		 * @brief Computes the distance between a point and this plane
		 * @param point Point to check
		 * @return Unsigned distance
		 */
		T getDistance(Vec3f const& point) const;
		/**
		 * @brief Computes the signed distance between a point and this plane
		 * @param point Point to check
		 * @return Signed distance
		 */
		T getSignedDistance(Vec3f const& point) const;
	private:
		Vector3<T> m_base;
		Vector3<T> m_normal;
	};
}

#include "Plane.imp"

#endif /* INCLUDE_DBGL_CORE_MATH_PLANE_H_ */
