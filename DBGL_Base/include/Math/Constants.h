//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include<cmath>

constexpr double pi()
{
    return std::atan2(0, -1);
}

constexpr double pi_2()
{
    return pi() / 2;
}

constexpr double pi_4()
{
    return pi() / 4;
}

#endif /* CONSTANTS_H_ */
