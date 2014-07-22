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

int testUtility()
{
    LOG.info("Starting Utility test suite...");
    LOG.info("Methods... ");
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
    // toRadians
    ASSERT(isSimilar(toRadians(90.0), pi_2(), 2));
    // toDegrees
    ASSERT(isSimilar(toDegrees(pi_2()), 90.0, 2));
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}
