//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef WINDOW_TEST_CPP
#define WINDOW_TEST_CPP

#include <cassert>
#include "Log/Log.h"
#include "Window/Window.h"

using namespace dbgl;

int testWindow()
{
    LOG->info("Starting Window test suite...");
    LOG->info("Constructors... ");
    Window wnd;
    LOG->info("OK!");
    LOG->info("Methods... ");
    wnd.open();
    LOG->info("OK!");
    LOG->info("Operators... ");
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
