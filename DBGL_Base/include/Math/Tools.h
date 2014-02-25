//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TOOLS_H_
#define TOOLS_H_

#include<cmath>

namespace dbgl
{
    /**
     * @return PI
     */
    constexpr double pi()
    {
	return std::atan2(0, -1);
    }
    /**
     * @return PI / 2
     */
    constexpr double pi_2()
    {
	return pi() / 2;
    }
    /**
     * @return PI / 3
     */
    constexpr double pi_3()
    {
	return pi() / 3;
    }
    /**
     * @return PI / 4
     */
    constexpr double pi_4()
    {
	return pi() / 4;
    }
    /**
     * @return sqrt(PI)
     */
    constexpr double sqrtPi()
    {
	return std::sqrt(pi());
    }
    /**
     * @return golden ratio
     */
    constexpr double goldenRatio()
    {
	return 1.61803398874989484820458683436563811;
    }
    /**
     * @brief Checks if two values are similar
     * @param a First value
     * @param b Second value
     * @param precision How close they need to be
     * @return True in case they are similar, otherwise false
     */
    bool isSimilar(double a, double b, double precision = 0.01);
}

#endif /* TOOLS_H_ */
