//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef HYPERRECTANGLE_H_
#define HYPERRECTANGLE_H_

#include "Vector.h"
#include "Vector2.h"

namespace dbgl
{
    /**
     * @brief A general rectangle class (i.e. for arbitrary dimensions)
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
	     * @brief Dimensionality of the hyperrectangle
	     * @return Dimensionality of the hyperrectangle
	     */
	    static unsigned int getDimension();
	private:
	    Vector<T, D> m_pos;
	    Vector<T, D> m_extent;
    };

    /**
     * @brief Rectangle (i.e. 2 dimensions)
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
	     * @brief Dimensionality of the rectangle
	     * @return Dimensionality of the rectangle
	     */
	    static unsigned int getDimension();
	private:
	    Vector2<T> m_pos;
	    Vector2<T> m_extent;
    };
}

#include "Hyperrectangle.imp"

#endif /* HYPERRECTANGLE_H_ */
