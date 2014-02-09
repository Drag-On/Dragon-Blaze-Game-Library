//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Window/WindowManager.h"

namespace dbgl
{
    WindowManager WindowManager::instance = WindowManager();
    std::map<GLFWwindow*, AbstractWindow*> WindowManager::windows = std::map<
	    GLFWwindow*, AbstractWindow*>();

    WindowManager* WindowManager::get()
    {
	return &instance;
    }

    void WindowManager::update()
    {
	// Poll events
	glfwPollEvents();
	// Update and render all windows
	for (auto wnd = windows.begin(); wnd != windows.end();)
	{
	    wnd->second->preUpdate();
	    wnd->second->update();
	    wnd->second->postUpdate();
	    wnd->second->preRender();
	    wnd->second->render();
	    wnd->second->postRender();
	    if (glfwWindowShouldClose(wnd->first))
	    {
		delete (wnd->second);
		wnd->second = NULL;
		wnd = windows.erase(wnd);
	    }
	    else
		++wnd;
	}
    }

    void WindowManager::terminate()
    {
	glfwTerminate();
    }

    bool WindowManager::isRunning()
    {
	return !WindowManager::windows.empty();
    }

    WindowManager::WindowManager()
    {

    }

    WindowManager::~WindowManager()
    {

    }

    void WindowManager::closeCallback(GLFWwindow* window)
    {
	windows[window]->closeCallback();
    }

    void WindowManager::focusCallback(GLFWwindow* window, int focused)
    {
	windows[window]->focusCallback(focused);
    }

    void WindowManager::iconifiedCallback(GLFWwindow* window, int iconified)
    {
	windows[window]->iconifiedCallback(iconified);
    }

    void WindowManager::refreshCallback(GLFWwindow* window)
    {
	windows[window]->refreshCallback();
    }

    void WindowManager::sizeCallback(GLFWwindow* window, int width, int height)
    {
	windows[window]->sizeCallback(width, height);
    }

    void WindowManager::framebufferSizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	windows[window]->framebufferSizeCallback(width, height);
    }

    void WindowManager::positionCallback(GLFWwindow* window, int xpos, int ypos)
    {
	windows[window]->windowPosCallback(xpos, ypos);
    }

    void WindowManager::characterCallback(GLFWwindow* window,
	    unsigned int codepoint)
    {
	windows[window]->characterCallback(codepoint);
    }

    void WindowManager::cursorEnterCallback(GLFWwindow* window, int entered)
    {
	windows[window]->cursorEnterCallback(entered);
    }

    void WindowManager::cursorCallback(GLFWwindow* window, double x, double y)
    {
	windows[window]->cursorCallback(x, y);
    }

    void WindowManager::mouseButtonCallback(GLFWwindow* window, int button,
	    int action, int mods)
    {
	windows[window]->mouseButtonCallback(button, action, mods);
    }

    void WindowManager::scrollCallback(GLFWwindow* window, double xOffset,
	    double yOffset)
    {
	windows[window]->scrollCallback(xOffset, yOffset);
    }

    void WindowManager::keyCallback(GLFWwindow* window, int key, int scancode,
	    int action, int mods)
    {
	windows[window]->keyCallback(key, scancode, action, mods);
    }

    // void WindowManager::monitorCallback(GLFWmonitor* monitor, int event){}

    void WindowManager::add(GLFWwindow* wndH, AbstractWindow* window)
    {
	windows.insert(std::pair<GLFWwindow*, AbstractWindow*>(wndH, window));

	// TODO: Add other callbacks
	glfwSetCharCallback(wndH, characterCallback);
	glfwSetCursorEnterCallback(wndH, cursorEnterCallback);
	glfwSetCursorPosCallback(wndH, cursorCallback);
	//glfwSetDropCallback();
	glfwSetFramebufferSizeCallback(wndH, framebufferSizeCallback);
	glfwSetKeyCallback(wndH, keyCallback);
	//glfwSetMonitorCallback(monitorCallback);
	glfwSetMouseButtonCallback(wndH, mouseButtonCallback);
	glfwSetScrollCallback(wndH, scrollCallback);
	glfwSetWindowCloseCallback(wndH, closeCallback);
	glfwSetWindowFocusCallback(wndH, focusCallback);
	glfwSetWindowIconifyCallback(wndH, iconifiedCallback);
	glfwSetWindowPosCallback(wndH, positionCallback);
	glfwSetWindowRefreshCallback(wndH, refreshCallback);
	glfwSetWindowSizeCallback(wndH, sizeCallback);
    }
}
