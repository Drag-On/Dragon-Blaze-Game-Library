//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Window/SimpleWindow.h"

namespace dbgl
{
    std::shared_ptr<ShaderProgram> SimpleWindow::spriteShader = std::shared_ptr<ShaderProgram>{};

    SimpleWindow::SimpleWindow(GLFWwindow* share, const char* title, int width, int height, bool fullscreen,
	    unsigned int multisampling) :
	    Window(share, title, width, height, fullscreen, multisampling)
    {
	// Add callback for keyboard input
	addKeyCallback(std::bind(&SimpleWindow::keyCallback, this, std::placeholders::_1));
	if(!spriteShader.get())
	    spriteShader = std::make_shared<ShaderProgram>(*ShaderProgram::createSpriteShader());
    }

    SimpleWindow::~SimpleWindow()
    {
    }

    bool SimpleWindow::getShowFps() const
    {
	return m_showFps;
    }

    void SimpleWindow::setShowFps(bool showFps)
    {
	m_showFps = showFps;
    }

    void SimpleWindow::render()
    {
	Window::render();

	// Calculate fps
	static double frames = 0;
	static double time = 0;
	frames++;
	time += m_deltaTime;
	if (time >= 1)
	{
	    m_fps = frames / time;
	    frames -= m_fps;
	    time -= 1;
	}
	// Show them?
	if(m_showFps)
	{
	    std::string fpsStr = std::string("FPS: ") + std::to_string(m_fps);
	    m_defaultFont.drawText(*m_pRenderContext, *spriteShader.get(), fpsStr, 0,
		    getHeight() - m_defaultFont.getLineHeight());
	}
    }

    void SimpleWindow::postRender()
    {
	// Check if we want to take a screenshot
	if(m_takeScreenshot)
	{
	    m_pRenderContext->saveSnapshot("Snapshot.bmp");
	    m_takeScreenshot = false;
	}

	Window::postRender();
    }

    void SimpleWindow::keyCallback(KeyEventArgs args)
    {
	// Close on escape
	if (args.key == Input::Key::KEY_ESCAPE && args.action == Input::KeyState::PRESSED)
	    close();

	// Switch to fullscreen on alt + enter
	if (args.key == Input::Key::KEY_ENTER && args.action == Input::KeyState::PRESSED
		&& args.mods.isSet(Input::Modifier::KEY_ALT))
	    setFullscreen(!isFullscreen());

	// Take screenshot on print
	if (args.key == Input::Key::KEY_PRINT_SCREEN && args.action == Input::KeyState::RELEASED)
	    m_takeScreenshot = true;
    }
}

