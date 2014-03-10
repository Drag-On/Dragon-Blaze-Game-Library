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
    WindowManager WindowManager::s_instance = WindowManager();
    std::map<GLFWwindow*, Window*> WindowManager::s_windows = std::map<
	    GLFWwindow*, Window*>();

    WindowManager* WindowManager::get()
    {
	return &s_instance;
    }

    void WindowManager::update()
    {
	// Poll events
	glfwPollEvents();
	// Update and render all windows
	for (auto wnd = s_windows.begin(); wnd != s_windows.end();)
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
		wnd = s_windows.erase(wnd);
	    }
	    else
		++wnd;
	}
    }

    void WindowManager::terminate()
    {
	// Delete windows that are still open
	if (!s_windows.empty())
	    for (auto wnd = s_windows.begin(); wnd != s_windows.end();)
		delete (wnd->second);

	// Terminate glfw context
	glfwTerminate();
    }

    bool WindowManager::isRunning() const
    {
	return !WindowManager::s_windows.empty();
    }

    double WindowManager::getTime() const
    {
	return glfwGetTime();
    }

    WindowManager::WindowManager()
    {
	glfwSetErrorCallback(WindowManager::errorCallback);
    }

    WindowManager::~WindowManager()
    {

    }

    void WindowManager::errorCallback(int error, const char* description)
    {
	LOG->error("Error %d: %s!", error, description);
    }

    void WindowManager::closeCallback(GLFWwindow* window)
    {
	s_windows[window]->m_closeCallback();
    }

    void WindowManager::focusCallback(GLFWwindow* window, int focused)
    {
	s_windows[window]->m_focusCallback(focused);
    }

    void WindowManager::iconifiedCallback(GLFWwindow* window, int iconified)
    {
	s_windows[window]->m_iconifiedCallback(iconified);
    }

    void WindowManager::refreshCallback(GLFWwindow* window)
    {
	s_windows[window]->m_refreshCallback();
    }

    void WindowManager::resizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	s_windows[window]->m_resizeCallback(width, height);
    }

    void WindowManager::framebufferResizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	s_windows[window]->m_framebufferResizeCallback(width, height);
    }

    void WindowManager::positionCallback(GLFWwindow* window, int xpos, int ypos)
    {
	s_windows[window]->m_positionCallback(xpos, ypos);
    }

    void WindowManager::characterCallback(GLFWwindow* window,
	    unsigned int codepoint)
    {
	s_windows[window]->m_characterCallback(codepoint);
    }

    void WindowManager::cursorEnterCallback(GLFWwindow* window, int entered)
    {
	s_windows[window]->m_cursorEnterCallback(entered);
    }

    void WindowManager::cursorCallback(GLFWwindow* window, double x, double y)
    {
	s_windows[window]->m_cursorCallback(x, y);
    }

    void WindowManager::mouseButtonCallback(GLFWwindow* window, int button,
	    int action, int mods)
    {
	s_windows[window]->m_mouseButtonCallback(button, action, mods);
    }

    void WindowManager::scrollCallback(GLFWwindow* window, double xOffset,
	    double yOffset)
    {
	s_windows[window]->m_scrollCallback(xOffset, yOffset);
    }

    void WindowManager::keyCallback(GLFWwindow* window, int key, int scancode,
	    int action, int mods)
    {
	s_windows[window]->m_keyCallback(key, scancode, action, mods);
    }

    // void WindowManager::monitorCallback(GLFWmonitor* monitor, int event){}

    void WindowManager::updateHandle(GLFWwindow* oldHandle,
	    GLFWwindow* newHandle)
    {
	if (oldHandle != newHandle)
	{
	    auto i = s_windows.find(oldHandle);
	    auto temp = i->second;
	    s_windows.erase(i);
	    s_windows.insert(std::pair<GLFWwindow*, Window*>(newHandle, temp));
	}
    }
}
