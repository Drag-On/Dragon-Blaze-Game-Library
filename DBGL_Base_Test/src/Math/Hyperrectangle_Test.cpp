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
#include <cassert>
#include <cmath>
#include "DBGL/System/Log/Log.h"
#include "DBGL/Math/Hyperrectangle.h"
#include "DBGL/Math/Vector2.h"

using namespace dbgl;

int testHyperrectangle()
{
    LOG->info("Starting Hyperrectangle test suite...");
    LOG->info("Constructors... ");
    Hyperrectangle<float, 2> rect2d;
    Hyperrectangle<float, 2> rect2d_2(Vec2f(1, 0.5f), Vec2f(8, 10));
    Hyperrectangle<float, 2> rect2d_2Copy(rect2d_2);
    Rectangle<double> rect(Vec2d(2, 2), Vec2d(42, 23));
    Box<int> box(Vec3i(1, 3, 3), Vec3i(7, 1, 1));
    assert(rect2d.getPos() == Vec2f(0, 0));
    assert(rect2d.getExtent() == Vec2f(1, 1));
    assert(rect2d_2.getPos() == Vec2f(1, 0.5f));
    assert(rect2d_2.getExtent() == Vec2f(8, 10));
    assert(rect2d_2Copy.getPos() == rect2d_2.getPos());
    assert(rect2d_2Copy.getExtent() == rect2d_2.getExtent());
    assert(rect.getPos() == Vec2d(2, 2));
    assert(rect.getExtent() == Vec2d(42, 23));
    assert(box.getPos() == Vec3i(1, 3, 3));
    assert(box.getExtent() == Vec3i(7, 1, 1));
    LOG->info("OK!");
    LOG->info("Methods... ");
    // isIn
    assert(rect.isIn(Vec2d(0, 0)) == false);
    assert(rect.isIn(Vec2d(2, 2)));
    assert(rect.isIn(Vec2d(2.1, 3)));
    assert(rect.isIn(Vec2d(44.1, 3)) == false);
    // overlaps
    assert(rect.overlaps(Rectangle<double>(Vec2d(0, 3), Vec2d(50, 1))));
    assert(rect.overlaps(Rectangle<double>(Vec2d(0, 0), Vec2d(1, 1))) == false);
    assert(rect.overlaps(Rectangle<double>(Vec2d(2, 3), Vec2d(0, 0))));
    assert(rect.overlaps(Rectangle<double>(Vec2d(-4, 10), Vec2d(15, 1))));
    LOG->info("OK!");
    LOG->info("Operators... ");
    // =
    auto copy(rect2d);
    copy = rect2d_2;
    assert(copy.getPos() == rect2d_2.getPos());
    assert(copy.getExtent() == rect2d_2.getExtent());
    // ==
    assert(copy == rect2d_2);
    assert(rect2d_2Copy == copy);
    // !=
    assert(copy != rect2d);
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
