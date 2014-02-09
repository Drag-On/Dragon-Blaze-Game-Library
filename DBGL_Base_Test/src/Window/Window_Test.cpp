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
#include "Window/WindowManager.h"
#include "Window/SimpleWindow.h"

using namespace dbgl;

int testWindow()
{
    LOG->info("Starting Window test suite...");
    LOG->info("Constructors... ");
    SimpleWindow* wnd = WindowManager::get()->createWindow<SimpleWindow>();
    SimpleWindow* wnd2 = WindowManager::get()->createWindow<SimpleWindow>("Window 2");
    SimpleWindow* wnd3 = WindowManager::get()->createWindow<SimpleWindow>("Window 3", 640, 480);
    SimpleWindow* wnd4 = WindowManager::get()->createWindow<SimpleWindow>("Window 4", 640, 640, false);
    LOG->info("OK!");
    LOG->info("Methods... ");
    wnd->show();
    wnd2->show();
    wnd3->show();
    wnd4->show();
    while(WindowManager::get()->isRunning())
    {
	WindowManager::get()->update();
    }
    WindowManager::get()->terminate();
    LOG->info("OK!");
    LOG->info("Operators... ");
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
