//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_MATH_HYPERSPHERE_H_
#define INCLUDE_DBGL_CORE_MATH_HYPERSPHERE_H_

#include "Vector.h"

namespace dbgl
{
	template<typename T, unsigned int D = 3> class HyperSphere
	{
	public:
		/**
		 * @brief Default constructor, initializes the sphere at the origin with radius = 1
		 */
		HyperSphere();
		/**
		 * @brief Constructs a sphere from a center point and a radius
		 * @param center Center point of the sphere
		 * @param radius Sphere radius
		 */
		HyperSphere(Vector<T, D> const& center, T radius);
		/**
		 * @brief Provides the sphere center
		 * @return Sphere center
		 */
		Vector<T, D>& center();
		/**
		 * @brief Provides the sphere center
		 * @return Sphere center
		 */
		Vector<T, D> const& getCenter() const;
		/**
		 * @brief Provides the sphere radius
		 * @return Sphere radius
		 */
		T& radius();
	    /**
	     * @brief Provides the lower bound of the sphere along a certain dimension
	     * @param dimension Dimension to get the lower coordinate for
	     * @return The lower bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
	     */
	    T lower(unsigned int dimension) const;
	    /**
	     * @brief Provides the upper bound of the sphere along a certain dimension
	     * @param dimension Dimension to get the upper coordinate for
	     * @return The upper bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
	     */
	    T upper(unsigned int dimension) const;
		/**
		 * @brief Checks if two spheres intersect
		 * @param other Sphere to check
		 * @return True if intersecting, otherwise false
		 */
		bool intersects(HyperSphere<T, D> const& other) const;
		/**
		 * @brief Computes the distance between a point and this sphere
		 * @param point Point to check
		 * @return Distance
		 */
		T getDistance(Vector<T, D> const& point) const;
		/**
		 * @brief Computes the distance between a sphere and this sphere
		 * @param sphere Sphere to check
		 * @return Unsigned distance
		 */
		T getDistance(HyperSphere<T, D> const& sphere) const;
		/**
		 * @brief Computes the signed distance between a point and this sphere
		 * @param point Point to check
		 * @return Signed distance
		 */
		T getSignedDistance(Vector<T, D> const& point) const;
		/**
		 * @brief Computes the distance between a sphere and this sphere
		 * @param sphere Sphere to check
		 * @return Signed distance
		 */
		T getSignedDistance(HyperSphere<T, D> const& sphere) const;
		/**
		 * @brief Equality operator
		 * @param other Hypersphere to compare with
		 * @return True if both shapes are equal, otherwise false
		 */
		bool operator==(HyperSphere<T, D> const& other) const;
		/**
		 * @brief Inequality operator
		 * @param other Hypersphere to compare with
		 * @return False if both shapes are equal, otherwise true
		 */
		bool operator!=(HyperSphere<T, D> const& other) const;
	    /**
	     * @brief Dimensionality of the hypersphere
	     * @return Dimensionality of the hypersphere
	     */
	    static constexpr unsigned int getDimension();
	    /**
	     * @brief The precision type used by this object
	     */
	    using PrecisionType = T;
	private:
		Vector<T, D> m_center;
		T m_radius;
	};

	/**
	 * @brief A two-dimensional circle
	 */
	template<typename T> using Circle = HyperSphere<T, 2>;
	/**
	 * @brief A three-dimensional sphere
	 */
	template<typename T> using Sphere = HyperSphere<T, 3>;
}

#include "HyperSphere.imp"

#endif /* INCLUDE_DBGL_CORE_MATH_HYPERSPHERE_H_ */
