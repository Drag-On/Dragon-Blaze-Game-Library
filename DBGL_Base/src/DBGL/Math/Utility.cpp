//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Math/Utility.h"

namespace dbgl
{
    bool isSimilar(float a, float b, float precision)
    {
	return std::abs(a - b) < precision;
    }

    template<typename T> T toRadians(T degrees)
    {
	return degrees * (pi() / 180);
    }

    template<typename T> T toDegrees(T radians)
    {
	return radians * (180 / pi());
    }
}
