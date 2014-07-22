//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <cassert>
#include "cute.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Utility.h"

using namespace dbgl;

void testIsSimilar()
{
    // isSimilar (direct)
    ASSERT(isSimilar(1.1f, 1.2f, 0.15f));
    ASSERT(!isSimilar(1.1f, 1.3f, 0.15f));
    // isSimilar (ulp)
    ASSERT(isSimilar(1.1f, 1.1f, 0));
    ASSERT(!isSimilar(1.1f, 1.1f + std::numeric_limits<float>::epsilon(), 0));
    ASSERT(isSimilar(1.1f, 1.1f + std::numeric_limits<float>::epsilon(), 1));
    ASSERT(isSimilar(1.1f, 1.1f + 2 * std::numeric_limits<float>::epsilon(), 2));
    ASSERT(!isSimilar(1.1f, 1.1f + 3 * std::numeric_limits<float>::epsilon(), 2));
    ASSERT(isSimilar(1.1f, 1.1f + 3 * std::numeric_limits<float>::epsilon(), 3));
}

void testToRadians()
{
    // toRadians
    ASSERT(isSimilar(toRadians(90.0), pi_2(), 2));
}

void testToDegrees()
{
    // toDegrees
    ASSERT(isSimilar(toDegrees(pi_2()), 90.0, 2));
}

cute::suite testUtility()
{
    cute::suite s{};
    s.push_back(CUTE(testIsSimilar));
    s.push_back(CUTE(testToRadians));
    s.push_back(CUTE(testToDegrees));
    return s;
}
