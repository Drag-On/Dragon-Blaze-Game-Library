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

namespace dbgl
{
    template<typename T, unsigned int D> class Hyperrectangle
    {
	public:
	    Hyperrectangle();
	    Hyperrectangle(Vector<T, D> const& pos, Vector<T, D> const& extent);
	    Hyperrectangle(Hyperrectangle const& other);
	    Vector<T, D> const& getPos() const;
	    Vector<T, D>& pos();
	    Vector<T, D> const& getExtent() const;
	    Vector<T, D>& extent();
	    Hyperrectangle<T, D>& operator=(Hyperrectangle<T, D> const& rhs);
	    bool operator==(Hyperrectangle<T, D> const& rhs) const;
	    bool operator!=(Hyperrectangle<T, D> const& rhs) const;
	    static unsigned int getDimension();
	private:
	    Vector<T, D> m_pos;
	    Vector<T, D> m_extent;
    };
}

#include "Hyperrectangle.imp"

#endif /* HYPERRECTANGLE_H_ */
