//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR_TEST_CPP
#define VECTOR_TEST_CPP

#include <cstdio>
#include "cute.h"
#include <cmath>
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Hyperrectangle.h"
#include "DBGL/Math/Vector2.h"

using namespace dbgl;

int testHyperrectangle()
{
    LOG.info("Starting Hyperrectangle test suite...");
    LOG.info("Constructors... ");
    Hyperrectangle<float, 2> rect2d;
    Hyperrectangle<float, 2> rect2d_2(Vec2f(1, 0.5f), Vec2f(8, 10));
    Hyperrectangle<float, 2> rect2d_2Copy(rect2d_2);
    Rectangle<double> rect(Vec2d(2, 2), Vec2d(42, 23));
    Box<int> box(Vec3i(1, 3, 3), Vec3i(7, 1, 1));
    Rectangle<double> weirdRect(Vec2d(5, 5), Vec2d(-5, -5));
    ASSERT(rect2d.getPos() == Vec2f(0, 0));
    ASSERT(rect2d.getExtent() == Vec2f(1, 1));
    ASSERT(rect2d_2.getPos() == Vec2f(1, 0.5f));
    ASSERT(rect2d_2.getExtent() == Vec2f(8, 10));
    ASSERT(rect2d_2Copy.getPos() == rect2d_2.getPos());
    ASSERT(rect2d_2Copy.getExtent() == rect2d_2.getExtent());
    ASSERT(rect.getPos() == Vec2d(2, 2));
    ASSERT(rect.getExtent() == Vec2d(42, 23));
    ASSERT(box.getPos() == Vec3i(1, 3, 3));
    ASSERT(box.getExtent() == Vec3i(7, 1, 1));
    LOG.info("OK!");
    LOG.info("Methods... ");
    // contains
    ASSERT(rect.contains(Vec2d(0, 0)) == false);
    ASSERT(rect.contains(Vec2d(2, 2)));
    ASSERT(rect.contains(Vec2d(2.1, 3)));
    ASSERT(rect.contains(Vec2d(44.1, 3)) == false);
    ASSERT(weirdRect.contains(Vec2d(0, 0)));
    ASSERT(weirdRect.contains(Vec2d(1, 1.5f)));
    ASSERT(weirdRect.contains(Vec2d(-1, 4)) == false);
    // overlaps
    ASSERT(rect.overlaps(Rectangle<double>(Vec2d(0, 3), Vec2d(50, 1))));
    ASSERT(rect.overlaps(Rectangle<double>(Vec2d(0, 0), Vec2d(1, 1))) == false);
    ASSERT(rect.overlaps(Rectangle<double>(Vec2d(2, 3), Vec2d(0, 0))));
    ASSERT(rect.overlaps(Rectangle<double>(Vec2d(-4, 10), Vec2d(15, 1))));
    ASSERT(rect.overlaps(weirdRect));
    ASSERT(weirdRect.overlaps(Rectangle<double>(Vec2d(-1, 1), Vec2d(1.5f, 1))));
    LOG.info("OK!");
    LOG.info("Operators... ");
    // =
    auto copy(rect2d);
    copy = rect2d_2;
    ASSERT(copy.getPos() == rect2d_2.getPos());
    ASSERT(copy.getExtent() == rect2d_2.getExtent());
    // ==
    ASSERT(copy == rect2d_2);
    ASSERT(rect2d_2Copy == copy);
    // !=
    ASSERT(copy != rect2d);
    // []
    ASSERT(copy.getPos()[0] == copy[0]);
    ASSERT(copy.getPos()[1] == copy[1]);
    ASSERT(copy.getPos()[0] + copy.getExtent()[0] == copy[2]);
    ASSERT(copy.getPos()[1] + copy.getExtent()[1] == copy[3]);
    LOG.info("OK!");
    LOG.info("Done!");
    return 0;
}

#endif
