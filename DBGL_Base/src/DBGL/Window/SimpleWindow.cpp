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
    SimpleWindow::SimpleWindow(const char* title, int width, int height, bool fullscreen,
	    unsigned int multisampling) :
	    Window(title, width, height, fullscreen, multisampling)
    {
	// Add callback for keyboard input
	addInputCallback(std::bind(&SimpleWindow::inputCallback, this, std::placeholders::_1));
	if(!m_pSpriteShader)
	    m_pSpriteShader = ShaderProgram::createSpriteShader();
    }

    SimpleWindow::~SimpleWindow()
    {
	delete m_pSpriteShader;
    }

    bool SimpleWindow::getShowFps() const
    {
	return m_showFps;
    }

    void SimpleWindow::setShowFps(bool showFps)
    {
	m_showFps = showFps;
    }

    BitmapFont& SimpleWindow::getDefaultFont()
    {
	return m_defaultFont;
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
	    m_pRenderContext->clear(RenderContext::Buffer::DEPTH);
	    std::string fpsStr = std::string("FPS: ") + std::to_string(m_fps);
	    m_defaultFont.drawText(*m_pRenderContext, *m_pSpriteShader, fpsStr, 0,
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

    void SimpleWindow::inputCallback(InputEventArgs args)
    {
	// Close on escape
	if (args.key == Input::Key::KEY_ESCAPE && args.input.isPressed(args.key))
	    close();

	// Switch to fullscreen on alt + enter
	if (args.input.isReleased(Input::Key::KEY_ENTER) && args.input.isDown(Input::Modifier::KEY_ALT))
	    setFullscreen(!isFullscreen());

	// Toggle fps view on ctrl + f
	if (args.input.isReleased(Input::Key::KEY_F) && args.input.isDown(Input::Modifier::KEY_CONTROL))
	    setShowFps(m_showFps = !m_showFps);

	// Take screenshot on print
	if (args.key == Input::Key::KEY_PRINT_SCREEN && args.input.isReleased(args.key))
	    m_takeScreenshot = true;
    }
}

