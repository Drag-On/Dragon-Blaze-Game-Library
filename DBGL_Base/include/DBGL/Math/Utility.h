//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef UTILITY_H_
#define UTILITY_H_

#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>

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
     * @return PI / 5
     */
    constexpr double pi_5()
    {
	return pi() / 5;
    }
    /**
     * @return PI / 6
     */
    constexpr double pi_6()
    {
	return pi() / 6;
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
    template<typename T> bool isSimilar(T a, T b, T precision = 0.01);
    /**
     * @brief Checks if two values are similar using units in the last place
     * @param a First value
     * @param b Second value
     * @param ulp Units in last place
     * @return True in case they are similar, otherwise false
     */
    template<typename T> typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type isSimilar(
	    T a, T b, int ulp);
    /**
     * @brief Converts degrees into radians
     * @param degrees Angle to convert
     * @return The angle in radians
     */
    template<typename T> T toRadians(T degrees);
    /**
     * @brief Converts radians into degrees
     * @param radians Angle to convert
     * @return The angle in degrees
     */
    template<typename T> T toDegrees(T radians);
}

#include "Utility.imp"

#endif
