//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Math/Tools.h"

namespace dbgl
{
    bool isSimilar(double a, double b, double precision)
    {
	return std::abs(a - b) < precision;
    }
}
