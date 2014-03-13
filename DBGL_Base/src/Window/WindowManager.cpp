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
	for (std::vector<CloseCallbackType>::iterator it =
		s_windows[window]->m_closeCallbacks.begin();
		it != s_windows[window]->m_closeCallbacks.end(); ++it)
	    (*it)();
    }

    void WindowManager::focusCallback(GLFWwindow* window, int focused)
    {
	for (std::vector<FocusCallbackType>::iterator it =
		s_windows[window]->m_focusCallbacks.begin();
		it != s_windows[window]->m_focusCallbacks.end(); ++it)
	    (*it)(focused);
    }

    void WindowManager::iconifiedCallback(GLFWwindow* window, int iconified)
    {
	for (std::vector<IconifiedCallbackType>::iterator it =
		s_windows[window]->m_iconifiedCallbacks.begin();
		it != s_windows[window]->m_iconifiedCallbacks.end(); ++it)
	    (*it)(iconified);
    }

    void WindowManager::refreshCallback(GLFWwindow* window)
    {
	for (std::vector<RefreshCallbackType>::iterator it =
		s_windows[window]->m_refreshCallbacks.begin();
		it != s_windows[window]->m_refreshCallbacks.end(); ++it)
	    (*it)();
    }

    void WindowManager::resizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	for (std::vector<ResizeCallbackType>::iterator it =
		s_windows[window]->m_resizeCallbacks.begin();
		it != s_windows[window]->m_resizeCallbacks.end(); ++it)
	    (*it)(width, height);
    }

    void WindowManager::framebufferResizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	for (std::vector<FramebufferResizeCallbackType>::iterator it =
		s_windows[window]->m_framebufferResizeCallbacks.begin();
		it != s_windows[window]->m_framebufferResizeCallbacks.end();
		++it)
	    (*it)(width, height);
    }

    void WindowManager::positionCallback(GLFWwindow* window, int xpos, int ypos)
    {
	for (std::vector<PositionCallbackType>::iterator it =
		s_windows[window]->m_positionCallbacks.begin();
		it != s_windows[window]->m_positionCallbacks.end(); ++it)
	    (*it)(xpos, ypos);
    }

    void WindowManager::characterCallback(GLFWwindow* window,
	    unsigned int codepoint)
    {
	for (std::vector<CharacterCallbackType>::iterator it =
		s_windows[window]->m_characterCallbacks.begin();
		it != s_windows[window]->m_characterCallbacks.end(); ++it)
	    (*it)(codepoint);
    }

    void WindowManager::cursorEnterCallback(GLFWwindow* window, int entered)
    {
	for (std::vector<CursorEnterCallbackType>::iterator it =
		s_windows[window]->m_cursorEnterCallbacks.begin();
		it != s_windows[window]->m_cursorEnterCallbacks.end(); ++it)
	    (*it)(entered);
    }

    void WindowManager::cursorCallback(GLFWwindow* window, double x, double y)
    {
	for (std::vector<CursorCallbackType>::iterator it =
		s_windows[window]->m_cursorCallbacks.begin();
		it != s_windows[window]->m_cursorCallbacks.end(); ++it)
	    (*it)(x, y);
    }

    void WindowManager::mouseButtonCallback(GLFWwindow* window, int button,
	    int action, int mods)
    {
	for (std::vector<MouseButtonCallbackType>::iterator it =
		s_windows[window]->m_mouseButtonCallbacks.begin();
		it != s_windows[window]->m_mouseButtonCallbacks.end(); ++it)
	    (*it)(button, action, mods);
    }

    void WindowManager::scrollCallback(GLFWwindow* window, double xOffset,
	    double yOffset)
    {
	for (std::vector<ScrollCallbackType>::iterator it =
		s_windows[window]->m_scrollCallbacks.begin();
		it != s_windows[window]->m_scrollCallbacks.end(); ++it)
	    (*it)(xOffset, yOffset);
    }

    void WindowManager::keyCallback(GLFWwindow* window, int key, int scancode,
	    int action, int mods)
    {
	for (std::vector<KeyCallbackType>::iterator it =
		s_windows[window]->m_keyCallbacks.begin();
		it != s_windows[window]->m_keyCallbacks.end(); ++it)
	    (*it)(key, scancode, action, mods);
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
