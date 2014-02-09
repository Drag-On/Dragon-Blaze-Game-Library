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
#include <functional>
#include "Log/Log.h"
#include "Window/WindowManager.h"
#include "Window/SimpleWindow.h"

using namespace dbgl;

class TestWindow: public SimpleWindow
{
	friend class dbgl::WindowManager;
    protected:
	TestWindow() : SimpleWindow()
	{
	    addCloseCallback(std::bind(&TestWindow::closeCallback, this));
	    addFocusCallback(std::bind(&TestWindow::focusCallback, this,
	    			std::placeholders::_1));
	    addIconifiedCallback(std::bind(&TestWindow::iconifiedCallback, this,
	    			std::placeholders::_1));
	    addRefreshCallback(std::bind(&TestWindow::refreshCallback, this));
	    addResizeCallback(std::bind(&TestWindow::resizeCallback, this,
	    			std::placeholders::_1, std::placeholders::_2));
	    addFramebufferResizeCallback(
	    		std::bind(&TestWindow::framebufferResizeCallback, this,
	    			std::placeholders::_1, std::placeholders::_2));
	    addPositionCallback(std::bind(&TestWindow::positionCallback, this,
	    			std::placeholders::_1, std::placeholders::_2));
	    addCharacterCallback(std::bind(&TestWindow::characterCallback, this,
	    			std::placeholders::_1));
	    addCursorEnterCallback(std::bind(&TestWindow::cursorEnterCallback, this,
	    			std::placeholders::_1));
	    addCursorCallback(std::bind(&TestWindow::cursorCallback, this,
	    			std::placeholders::_1, std::placeholders::_2));
	    addMouseButtonCallback(std::bind(&TestWindow::mouseButtonCallback, this,
	    			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	    addScrollCallback(std::bind(&TestWindow::scrollCallback, this,
	    			std::placeholders::_1, std::placeholders::_2));
	    addKeyCallback(
	    		std::bind(&TestWindow::keyCallback, this,
	    			std::placeholders::_1, std::placeholders::_2,
	    			std::placeholders::_3, std::placeholders::_4));
	};
	virtual void closeCallback() {LOG->info("closeCallback called!");};
	virtual void focusCallback(int focused) {LOG->info("focusCallback called: %d!", focused);};
	virtual void iconifiedCallback(int iconified) {LOG->info("iconifiedCallback called: %d!", iconified);};
	virtual void refreshCallback() {LOG->info("refreshCallback called!");};
	virtual void resizeCallback(int width, int height) {LOG->info("resizeCallback called: %d,%d!", width, height);};
	virtual void framebufferResizeCallback(int width, int height) {LOG->info("framebufferResizeCallback called: %d,%d!", width, height);};
	virtual void positionCallback(int xpos, int ypos) {LOG->info("positionCallback called: %d,%d!", xpos, ypos);};
	virtual void characterCallback(unsigned int codepoint) {LOG->info("characterCallback called: %d!", codepoint);};
	virtual void cursorEnterCallback(int entered) {LOG->info("cursorEnterCallback called: %d!", entered);};
	virtual void cursorCallback(double x, double y) {LOG->info("cursorCallback called: %d,%d!", x, y);};
	virtual void mouseButtonCallback(int button, int action, int mods) {LOG->info("mouseButtonCallback called: %d,%d,%d!", button, action, mods);};
	virtual void scrollCallback(double xOffset, double yOffset) {LOG->info("scrollCallback called: %f,%f!", xOffset, yOffset);};
	virtual void keyCallback(int key, int scancode, int action, int mods) {LOG->info("keyCallback called: %d,%d,%d,%d!", key, scancode, action, mods);};
};

int testWindow()
{
    LOG->info("Starting Window test suite...");
    LOG->info("Constructors... ");
    TestWindow* wnd = WindowManager::get()->createWindow<TestWindow>();
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
    //LOG->info("Operators... ");
    //LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
