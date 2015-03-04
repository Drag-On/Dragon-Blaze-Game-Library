//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_SHAPE_ISHAPE_H_
#define INCLUDE_DBGL_CORE_SHAPE_ISHAPE_H_

#include "DBGL/Core/Math/Vector.h"

namespace dbgl
{
	/**
	 * @brief Interface class for shapes
	 */
	template<typename T, unsigned int D> class IShape
	{
	public:
		virtual ~IShape() = default;
		/**
		 * @brief Center of mass
		 * @return Point of the shape center
		 */
		virtual Vector<T, D> getCenter() const = 0;
		/**
		 * @brief Provides the lower bound of the shape along a certain dimension
		 * @param dimension Dimension to get the lower coordinate for
		 * @return The lower bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
		 */
		virtual T lower(unsigned int dimension) const = 0;
		/**
		 * @brief Provides the upper bound of the shape along a certain dimension
		 * @param dimension Dimension to get the upper coordinate for
		 * @return The upper bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
		 */
		virtual T upper(unsigned int dimension) const = 0;
		/**
		 * @brief Checks if the passed coordinates are within the bounds of this shape
		 * @param point Point to check
		 * @return True in case \p point is within (or on) the bounds of this shape, otherwise false
		 */
		virtual bool contains(Vector<T, D> const& point) const = 0;
		/**
		 * @brief Checks if the passed shape overlaps with this one
		 * @param other Shape to check
		 * @return True in case \p other overlaps with (or touches) this shape, otherwise false
		 */
		virtual bool intersects(IShape<T, D> const& other) const = 0;
		/**
		 * @brief Resizes the shape so that it includes the passed one. Does nothing if the passed shape is already completely contained
		 * @param other Shape to include
		 */
		virtual void resizeInclude(IShape<T, D> const& other) = 0;
		/**
		 * @brief Provides the radius of the smallest sphere fully containing this shape
		 * @return Radius of bounding sphere
		 */
		virtual T getBoundingRadius() const = 0;
		/**
		 * @brief Dimensionality of the shape
		 * @return Dimensionality of the shape
		 */
		static constexpr unsigned int getDimension()
		{
			return D;
		}
		/**
		 * @brief The precision type used by this object
		 */
		using PrecisionType = T;
	};
}

#endif /* INCLUDE_DBGL_CORE_SHAPE_ISHAPE_H_ */
