//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef HYPERRECTANGLE_H_
#define HYPERRECTANGLE_H_

#include <algorithm>
#include "Vector.h"
#include "Vector2.h"
#include "Vector3.h"

namespace dbgl
{
    /**
     * @brief A general axis-aligned rectangle class (i.e. for arbitrary dimensions)
     */
    template<typename T, unsigned int D> class Hyperrectangle
    {
	public:
	    /**
	     * @brief Constructs a hyperrectangle located at the origin with extent 1
	     */
	    Hyperrectangle();
	    /**
	     * @brief Constructs a hyperrectangle from a position vector and an extent vector
	     * @param pos Coordinates to use
	     * @param extent Extent to use
	     */
	    Hyperrectangle(Vector<T, D> const& pos, Vector<T, D> const& extent);
	    /**
	     * @brief Copies a hyperrectangle
	     * @param other Hyperrectangle to copy
	     */
	    Hyperrectangle(Hyperrectangle<T, D> const& other);
	    /**
	     * @brief Provides access to the hyperrectangles coordinates
	     * @return Position of the hyperrectangle
	     */
	    Vector<T, D> const& getPos() const;
	    /**
	     * @brief Provides access to the hyperrectangles coordinates
	     * @return Position of the hyperrectangle
	     */
	    Vector<T, D>& pos();
	    /**
	     * @brief Provides access to the hyperrectangles extent
	     * @return Extent of the hyperrectangle
	     */
	    Vector<T, D> const& getExtent() const;
	    /**
	     * @brief Provides access to the hyperrectangles extent
	     * @return Extent of the hyperrectangle
	     */
	    Vector<T, D>& extent();
	    /**
	     * @brief Provides the lower bound of the rectangle along a certain dimension
	     * @param dimension Dimension to get the lower coordinate for
	     * @return The lower bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
	     */
	    T lower(unsigned int dimension) const;
	    /**
	     * @brief Provides the upper bound of the rectangle along a certain dimension
	     * @param dimension Dimension to get the upper coordinate for
	     * @return The upper bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
	     */
	    T upper(unsigned int dimension) const;
	    /**
	     * @brief Checks if the passed coordinates are within the bounds of this hyperrectangle
	     * @param point Point to check
	     * @return True in case \p point is within (or on) the bounds of this hyperrectangle, otherwise false
	     */
	    bool contains(Vector<T, D> const& point) const;
	    /**
	     * @brief Checks if the passed hyperrectangle overlaps with this one
	     * @param other Hyperrectangle to check
	     * @return True in case \p other overlaps with (or touches) this hyperrectangle, otherwise false
	     */
	    bool intersects(Hyperrectangle<T, D> const& other) const;
	    /**
	     * @brief Checks, if this hyperrectangle is similar to another one
	     * @param other Other hyperrectangle to check
	     * @param precision Precision of the check
	     * @return True in case the two hyperrectangles are similar, otherwise false
	     */
	    bool isSimilar(Hyperrectangle<T, D> const& other, double precision = 0.1) const;
	    /**
	     * @brief Assigns another hyperrectangle by copying its values
	     * @param rhs Hyperrectangle to copy
	     * @return Reference to this hyperrectangle
	     */
	    Hyperrectangle<T, D>& operator=(Hyperrectangle<T, D> const& rhs);
	    /**
	     * @brief Value comparison
	     * @param rhs Hyperrectangle to compare
	     * @return True in case both hyperrectangles are equal, otherwise false
	     */
	    bool operator==(Hyperrectangle<T, D> const& rhs) const;
	    /**
	     * @brief Value comparison
	     * @param rhs Hyperrectangle to compare
	     * @return False in case both hyperrectangles are equal, otherwise true
	     */
	    bool operator!=(Hyperrectangle<T, D> const& rhs) const;
	    /**
	     * @brief Direct access operator
	     * @param index Index of the component to access
	     * @return Component \p index of the position of this hyperrectangle
	     * @details The returned values are ordered: position.x, position.y, ..., position.x + extent.x, ...
	     */
	    T operator[](std::size_t const& index) const;
	    /**
	     * @brief Dimensionality of the hyperrectangle
	     * @return Dimensionality of the hyperrectangle
	     */
	    static constexpr unsigned int getDimension();
	    /**
	     * @brief The precision type used by this object
	     */
	    using PrecisionType = T;
	private:
	    Vector<T, D> m_pos;
	    Vector<T, D> m_extent;
    };

    /**
     * @brief Axis-aligned rectangle (i.e. 2 dimensions)
     */
    template<typename T> using Rectangle = Hyperrectangle<T, 2>;

    /**
     * @brief A rectangle (i.e. 2 dimensions)
     */
    template<typename T> class Hyperrectangle<T, 2>
    {
	public:
	    /**
	     * @brief Constructs a rectangle located at the origin with extent 1
	     */
	    Hyperrectangle();
	    /**
	     * @brief Constructs a rectangle from a position vector and an extent vector
	     * @param pos Coordinates to use
	     * @param extent Extent to use
	     */
	    Hyperrectangle(Vector<T, 2> const& pos, Vector<T, 2> const& extent);
	    /**
	     * @brief Copies a rectangle
	     * @param other Rectangle to copy
	     */
	    Hyperrectangle(Hyperrectangle<T, 2> const& other);
	    /**
	     * @brief Provides access to the rectangles coordinates
	     * @return Position of the rectangle
	     */
	    Vector2<T> const& getPos() const;
	    /**
	     * @brief Provides access to the rectangles coordinates
	     * @return Position of the rectangle
	     */
	    Vector2<T>& pos();
	    /**
	     * @brief Provides access to the rectangles extent
	     * @return Extent of the rectangle
	     */
	    Vector2<T> const& getExtent() const;
	    /**
	     * @brief Provides access to the rectangles extent
	     * @return Extent of the rectangle
	     */
	    Vector2<T>& extent();
	    /**
	     * @brief Provides the lower bound of the rectangle along a certain dimension
	     * @param dimension Dimension to get the lower coordinate for
	     * @return The lower bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
	     */
	    T lower(unsigned int dimension) const;
	    /**
	     * @brief Provides the upper bound of the rectangle along a certain dimension
	     * @param dimension Dimension to get the upper coordinate for
	     * @return The upper bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
	     */
	    T upper(unsigned int dimension) const;
	    /**
	     * @brief Checks if the passed coordinates are within the bounds of this rectangle
	     * @param point Point to check
	     * @return True in case \p point is within (or on) the bounds of this rectangle, otherwise false
	     */
	    bool contains(Vector<T, 2> const& point) const;
	    /**
	     * @brief Checks if the passed rectangle overlaps with this one
	     * @param other Rectangle to check
	     * @return True in case \p other overlaps with (or touches) this rectangle, otherwise false
	     */
	    bool intersects(Hyperrectangle<T, 2> const& other) const;
	    /**
	     * @brief Checks, if this rectangle is similar to another one
	     * @param other Other rectangle to check
	     * @param precision Precision of the check
	     * @return True in case the two rectangles are similar, otherwise false
	     */
	    bool isSimilar(Hyperrectangle<T, 2> const& other, double precision = 0.1) const;
	    /**
	     * @brief Assigns another rectangle by copying its values
	     * @param rhs Rectangle to copy
	     * @return Reference to this rectangle
	     */
	    Hyperrectangle<T, 2>& operator=(Hyperrectangle<T, 2> const& rhs);
	    /**
	     * @brief Value comparison
	     * @param rhs Rectangle to compare
	     * @return True in case both rectangles are equal, otherwise false
	     */
	    bool operator==(Hyperrectangle<T, 2> const& rhs) const;
	    /**
	     * @brief Value comparison
	     * @param rhs Rectangle to compare
	     * @return False in case both rectangles are equal, otherwise true
	     */
	    bool operator!=(Hyperrectangle<T, 2> const& rhs) const;
	    /**
	     * @brief Direct access operator
	     * @param index Index of the component to access
	     * @return Component \p index of this rectangle
	     * @details The returned values are ordered: position.x, position.y, ..., position.x + extent.x, ...
	     */
	    T operator[](std::size_t const& index) const;
	    /**
	     * @brief Dimensionality of the rectangle
	     * @return 2
	     */
	    static constexpr unsigned int getDimension();
	    /**
	     * @brief The precision type used by this object
	     */
	    using PrecisionType = T;
	private:
	    Vector2<T> m_pos;
	    Vector2<T> m_extent;
    };

    /**
     * @brief Axis-aligned box (i.e. 3 dimensions)
     */
    template<typename T> using Box = Hyperrectangle<T, 3>;

    /**
     * @brief A box (i.e. 3 dimensions)
     */
    template<typename T> class Hyperrectangle<T, 3>
    {
	public:
	    /**
	     * @brief Constructs a box located at the origin with extent 1
	     */
	    Hyperrectangle();
	    /**
	     * @brief Constructs a box from a position vector and an extent vector
	     * @param pos Coordinates to use
	     * @param extent Extent to use
	     */
	    Hyperrectangle(Vector<T, 3> const& pos, Vector<T, 3> const& extent);
	    /**
	     * @brief Copies a box
	     * @param other Box to copy
	     */
	    Hyperrectangle(Hyperrectangle<T, 3> const& other);
	    /**
	     * @brief Provides access to the boxs coordinates
	     * @return Position of the box
	     */
	    Vector3<T> const& getPos() const;
	    /**
	     * @brief Provides access to the boxs coordinates
	     * @return Position of the box
	     */
	    Vector3<T>& pos();
	    /**
	     * @brief Provides access to the boxs extent
	     * @return Extent of the box
	     */
	    Vector3<T> const& getExtent() const;
	    /**
	     * @brief Provides access to the boxs extent
	     * @return Extent of the box
	     */
	    Vector3<T>& extent();
	    /**
	     * @brief Provides the lower bound of the rectangle along a certain dimension
	     * @param dimension Dimension to get the lower coordinate for
	     * @return The lower bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
	     */
	    T lower(unsigned int dimension) const;
	    /**
	     * @brief Provides the upper bound of the rectangle along a certain dimension
	     * @param dimension Dimension to get the upper coordinate for
	     * @return The upper bound coordinate for \p dimension, i.e. the smallest coordinate still within the shape
	     */
	    T upper(unsigned int dimension) const;
	    /**
	     * @brief Checks if the passed coordinates are within the bounds of this box
	     * @param point Point to check
	     * @return True in case \p point is within (or on) the bounds of this box, otherwise false
	     */
	    bool contains(Vector<T, 3> const& point) const;
	    /**
	     * @brief Checks if the passed box overlaps with this one
	     * @param other Box to check
	     * @return True in case \p other overlaps with (or touches) this box, otherwise false
	     */
	    bool intersects(Hyperrectangle<T, 3> const& other) const;
	    /**
	     * @brief Checks, if this box is similar to another one
	     * @param other Other box to check
	     * @param precision Precision of the check
	     * @return True in case the two box are similar, otherwise false
	     */
	    bool isSimilar(Hyperrectangle<T, 3> const& other, double precision = 0.1) const;
	    /**
	     * @brief Assigns another box by copying its values
	     * @param rhs Box to copy
	     * @return Reference to this box
	     */
	    Hyperrectangle<T, 3>& operator=(Hyperrectangle<T, 3> const& rhs);
	    /**
	     * @brief Value comparison
	     * @param rhs Box to compare
	     * @return True in case both boxs are equal, otherwise false
	     */
	    bool operator==(Hyperrectangle<T, 3> const& rhs) const;
	    /**
	     * @brief Value comparison
	     * @param rhs Box to compare
	     * @return False in case both boxs are equal, otherwise true
	     */
	    bool operator!=(Hyperrectangle<T, 3> const& rhs) const;
	    /**
	     * @brief Direct access operator
	     * @param index Index of the component to access
	     * @return Component \p index of of this box
	     * @details The returned values are ordered: position.x, position.y, ..., position.x + extent.x, ...
	     */
	    T operator[](std::size_t const& index) const;
	    /**
	     * @brief Dimensionality of the box
	     * @return 3
	     */
	    static constexpr unsigned int getDimension();
	    /**
	     * @brief The precision type used by this object
	     */
	    using PrecisionType = T;
	private:
	    Vector3<T> m_pos;
	    Vector3<T> m_extent;
    };

    /**
     * @brief Axis-aligned bounding rectangle
     */
    template<typename T> using AABR = Hyperrectangle<T, 2>;
    /**
     * @brief Axis-aligned bounding box
     */
    template<typename T> using AABB = Hyperrectangle<T, 2>;
}

#include "Hyperrectangle.imp"

#endif /* HYPERRECTANGLE_H_ */
