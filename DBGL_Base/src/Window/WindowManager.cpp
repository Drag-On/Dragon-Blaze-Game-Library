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
    std::map<GLFWwindow*, Window*> WindowManager::windows = std::map<
	    GLFWwindow*, Window*>();

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
	// Delete windows that are still open
	if (!windows.empty())
	    for (auto wnd = windows.begin(); wnd != windows.end();)
		delete (wnd->second);

	// Terminate glfw context
	glfwTerminate();
    }

    bool WindowManager::isRunning() const
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
	windows[window]->_closeCallback();
    }

    void WindowManager::focusCallback(GLFWwindow* window, int focused)
    {
	windows[window]->_focusCallback(focused);
    }

    void WindowManager::iconifiedCallback(GLFWwindow* window, int iconified)
    {
	windows[window]->_iconifiedCallback(iconified);
    }

    void WindowManager::refreshCallback(GLFWwindow* window)
    {
	windows[window]->_refreshCallback();
    }

    void WindowManager::resizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	windows[window]->_resizeCallback(width, height);
    }

    void WindowManager::framebufferResizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	windows[window]->_framebufferResizeCallback(width, height);
    }

    void WindowManager::positionCallback(GLFWwindow* window, int xpos, int ypos)
    {
	windows[window]->_positionCallback(xpos, ypos);
    }

    void WindowManager::characterCallback(GLFWwindow* window,
	    unsigned int codepoint)
    {
	windows[window]->_characterCallback(codepoint);
    }

    void WindowManager::cursorEnterCallback(GLFWwindow* window, int entered)
    {
	windows[window]->_cursorEnterCallback(entered);
    }

    void WindowManager::cursorCallback(GLFWwindow* window, double x, double y)
    {
	windows[window]->_cursorCallback(x, y);
    }

    void WindowManager::mouseButtonCallback(GLFWwindow* window, int button,
	    int action, int mods)
    {
	windows[window]->_mouseButtonCallback(button, action, mods);
    }

    void WindowManager::scrollCallback(GLFWwindow* window, double xOffset,
	    double yOffset)
    {
	windows[window]->_scrollCallback(xOffset, yOffset);
    }

    void WindowManager::keyCallback(GLFWwindow* window, int key, int scancode,
	    int action, int mods)
    {
	windows[window]->_keyCallback(key, scancode, action, mods);
    }

    // void WindowManager::monitorCallback(GLFWmonitor* monitor, int event){}

    void WindowManager::updateHandle(GLFWwindow* oldHandle,
	    GLFWwindow* newHandle)
    {
	if (oldHandle != newHandle)
	{
	    auto i = windows.find(oldHandle);
	    auto temp = i->second;
	    windows.erase(i);
	    windows.insert(
		    std::pair<GLFWwindow*, Window*>(newHandle, temp));
	}
    }
}
