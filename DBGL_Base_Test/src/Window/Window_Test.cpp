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

class TestWindow: public SimpleWindow
{
    protected:
	// Constructors
	TestWindow();
	TestWindow(const char* title);
	TestWindow(const char* title, int width, int height);
	TestWindow(const char* title, int width, int height,
		bool fullscreen);
	// Callbacks
	virtual void closeCallback();
	virtual void focusCallback(int focused);
	virtual void iconifiedCallback(int iconified);
	virtual void refreshCallback();
	virtual void sizeCallback(int width, int height);
	virtual void framebufferSizeCallback(int width, int height);
	virtual void windowPosCallback(int xpos, int ypos);
	virtual void characterCallback(unsigned int codepoint);
	virtual void cursorEnterCallback(int entered);
	virtual void cursorCallback(double x, double y);
	virtual void mouseButtonCallback(int button, int action, int mods);
	virtual void scrollCallback(double xOffset, double yOffset);
	virtual void keyCallback(int key, int scancode, int action, int mods);
};

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
