//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Window/WindowManager.h"

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

	// Free logfile
	LOG->freeDefault();
    }

    bool WindowManager::isRunning() const
    {
	return !WindowManager::s_windows.empty();
    }

    double WindowManager::getTime() const
    {
	return glfwGetTime();
    }

    WindowManager::WindowManager() : m_pShareWindow(NULL)
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
	s_windows[window]->m_closeCallbacks.fire(Window::CloseEventArgs());
    }

    void WindowManager::focusCallback(GLFWwindow* window, int focused)
    {
	s_windows[window]->m_focusCallbacks.fire(Window::FocusEventArgs{focused == GL_TRUE ? true : false});
    }

    void WindowManager::iconifiedCallback(GLFWwindow* window, int iconified)
    {
	s_windows[window]->m_iconifiedCallbacks.fire(Window::IconifiedEventArgs{iconified == GL_TRUE ? true : false});
    }

    void WindowManager::refreshCallback(GLFWwindow* window)
    {
	s_windows[window]->m_refreshCallbacks.fire(Window::RefreshEventArgs());
    }

    void WindowManager::resizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	s_windows[window]->m_resizeCallbacks.fire(Window::ResizeEventArgs{width, height});
    }

    void WindowManager::framebufferResizeCallback(GLFWwindow* window, int width,
	    int height)
    {
	s_windows[window]->m_framebufferResizeCallbacks.fire(Window::FramebufferResizeEventArgs{width, height});
    }

    void WindowManager::positionCallback(GLFWwindow* window, int xpos, int ypos)
    {
	s_windows[window]->m_positionCallbacks.fire(Window::PositionEventArgs{xpos, ypos});
    }

    void WindowManager::characterCallback(GLFWwindow* window,
	    unsigned int codepoint)
    {
	s_windows[window]->m_characterCallbacks.fire(Window::CharacterEventArgs{codepoint});
    }

    void WindowManager::cursorEnterCallback(GLFWwindow* window, int entered)
    {
	s_windows[window]->m_cursorEnterCallbacks.fire(Window::CursorEnterEventArgs{entered == GL_TRUE ? true : false});
    }

    void WindowManager::cursorCallback(GLFWwindow* window, double x, double y)
    {
	s_windows[window]->m_cursorCallbacks.fire(Window::CursorEventArgs{x, y});
    }

    void WindowManager::mouseButtonCallback(GLFWwindow* window, int button,
	    int action, int mods)
    {
	// Translate GLFW button into Input::Key
	Input::Key keyConst = Input::Key(Input::mouse_offset + button);
	// Translate GLFW action int Input::KeyState
	Input::KeyState keyState;
	if(action == GLFW_RELEASE)
	    keyState = Input::KeyState::RELEASED;
	else if(action == GLFW_PRESS)
	    keyState = Input::KeyState::PRESSED;
	else if(action == GLFW_REPEAT)
	    keyState = Input::KeyState::DOWN;
	else
	    keyState = Input::KeyState::UP;
	s_windows[window]->m_mouseButtonCallbacks.fire(Window::MouseButtonEventArgs{button, keyConst, keyState, mods});
	s_windows[window]->m_inputCallbacks.fire(Window::InputEventArgs{s_windows[window]->m_input, keyConst});
    }

    void WindowManager::scrollCallback(GLFWwindow* window, double xOffset,
	    double yOffset)
    {
	s_windows[window]->m_scrollCallbacks.fire(Window::ScrollEventArgs{xOffset, yOffset});
    }

    void WindowManager::keyCallback(GLFWwindow* window, int key, int scancode,
	    int action, int mods)
    {
	// Translate GLFW key into Input::Key
	Input::Key keyConst = Input::Key(Input::keyboard_offset + key);
	// Translate GLFW action int Input::KeyState
	Input::KeyState keyState;
	if(action == GLFW_RELEASE)
	    keyState = Input::KeyState::RELEASED;
	else if(action == GLFW_PRESS)
	    keyState = Input::KeyState::PRESSED;
	else if(action == GLFW_REPEAT)
	    keyState = Input::KeyState::DOWN;
	else
	    keyState = Input::KeyState::UP;
	s_windows[window]->m_keyCallbacks.fire(Window::KeyEventArgs{keyConst, scancode, keyState, mods});
	s_windows[window]->m_inputCallbacks.fire(Window::InputEventArgs{s_windows[window]->m_input, keyConst});
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
