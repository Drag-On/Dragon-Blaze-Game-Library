//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_MATH_HYPERPLANE_H_
#define INCLUDE_DBGL_CORE_MATH_HYPERPLANE_H_

#include "Vector.h"

namespace dbgl
{
	/**
	 * @brief Basic three-dimensional plane class
	 */
	template<typename T, unsigned int D = 3> class HyperPlane
	{
	public:
		/**
		 * @brief Default constructor
		 */
		HyperPlane() = default;
		/**
		 * @brief Constructor
		 * @param base Base point on the plane
		 * @param normal Plane normal
		 */
		HyperPlane(Vector<T, D> base, Vector<T, D> normal);
		/**
		 * @brief Provides the plane normal
		 * @return Plane normal
		 */
		Vector<T, D>& normal();
		/**
		 * @brief Provides the plane base point
		 * @return Plane base point
		 */
		Vector<T, D>& base();
		/**
		 * @brief Checks if two planes intersect
		 * @param other Plane to check
		 * @return True if intersecting, otherwise false
		 */
		bool intersects(HyperPlane<T, D> const& other) const;
		/**
		 * @brief Computes the distance between a point and this plane
		 * @param point Point to check
		 * @return Unsigned distance
		 */
		T getDistance(Vector<T, D> const& point) const;
		/**
		 * @brief Computes the signed distance between a point and this plane
		 * @param point Point to check
		 * @return Signed distance
		 */
		T getSignedDistance(Vector<T, D> const& point) const;
	private:
		Vector<T, D> m_base;
		Vector<T, D> m_normal;
	};

	/**
	 * @brief Two-dimensional plane, i.e. a line
	 */
	template<typename T> using Line = HyperPlane<T, 2>;
	/**
	 * @brief Three-dimensional plane
	 */
	template<typename T> using Plane = HyperPlane<T, 3>;
}

#include "HyperPlane.imp"

#endif /* INCLUDE_DBGL_CORE_MATH_HYPERPLANE_H_ */
