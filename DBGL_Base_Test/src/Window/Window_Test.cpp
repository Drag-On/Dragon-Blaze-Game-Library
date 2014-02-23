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
#include "Rendering/RenderContext.h"
#include "Rendering/Mesh.h"
#include "Rendering/ShaderProgram.h"
#include "Rendering/Camera.h"
#include "Rendering/Texture.h"
#include "Math/Tools.h"

using namespace dbgl;

class TestWindow: public SimpleWindow
{
	friend class dbgl::WindowManager;
    protected:
	TestWindow(GLFWwindow* share) :
		SimpleWindow(share)
	{
	    addCloseCallback(std::bind(&TestWindow::closeCallback, this));
	    addFocusCallback(
		    std::bind(&TestWindow::focusCallback, this,
			    std::placeholders::_1));
	    addIconifiedCallback(
		    std::bind(&TestWindow::iconifiedCallback, this,
			    std::placeholders::_1));
	    addRefreshCallback(std::bind(&TestWindow::refreshCallback, this));
	    addResizeCallback(
		    std::bind(&TestWindow::resizeCallback, this,
			    std::placeholders::_1, std::placeholders::_2));
	    addFramebufferResizeCallback(
		    std::bind(&TestWindow::framebufferResizeCallback, this,
			    std::placeholders::_1, std::placeholders::_2));
	    addPositionCallback(
		    std::bind(&TestWindow::positionCallback, this,
			    std::placeholders::_1, std::placeholders::_2));
	    addCharacterCallback(
		    std::bind(&TestWindow::characterCallback, this,
			    std::placeholders::_1));
	    addCursorEnterCallback(
		    std::bind(&TestWindow::cursorEnterCallback, this,
			    std::placeholders::_1));
	    addCursorCallback(
		    std::bind(&TestWindow::cursorCallback, this,
			    std::placeholders::_1, std::placeholders::_2));
	    addMouseButtonCallback(
		    std::bind(&TestWindow::mouseButtonCallback, this,
			    std::placeholders::_1, std::placeholders::_2,
			    std::placeholders::_3));
	    addScrollCallback(
		    std::bind(&TestWindow::scrollCallback, this,
			    std::placeholders::_1, std::placeholders::_2));
	    addKeyCallback(
		    std::bind(&TestWindow::keyCallback, this,
			    std::placeholders::_1, std::placeholders::_2,
			    std::placeholders::_3, std::placeholders::_4));
	}
	virtual void closeCallback()
	{
	    LOG->info("closeCallback called!");};
	virtual void focusCallback(int focused)
	{   LOG->info("focusCallback called: %d!", focused);};
	virtual void iconifiedCallback(int iconified)
	{   LOG->info("iconifiedCallback called: %d!", iconified);};
	virtual void refreshCallback()
	{   LOG->info("refreshCallback called!");};
	virtual void resizeCallback(int width, int height)
	{   LOG->info("resizeCallback called: %d,%d!", width, height);};
	virtual void framebufferResizeCallback(int width, int height)
	{   LOG->info("framebufferResizeCallback called: %d,%d!", width, height);};
	virtual void positionCallback(int xpos, int ypos)
	{   LOG->info("positionCallback called: %d,%d!", xpos, ypos);};
	virtual void characterCallback(unsigned int codepoint)
	{   LOG->info("characterCallback called: %d!", codepoint);};
	virtual void cursorEnterCallback(int entered)
	{   LOG->info("cursorEnterCallback called: %d!", entered);};
	virtual void cursorCallback(double x, double y)
	{   LOG->info("cursorCallback called: %d,%d!", x, y);};
	virtual void mouseButtonCallback(int button, int action, int mods)
	{   LOG->info("mouseButtonCallback called: %d,%d,%d!", button, action, mods);};
	virtual void scrollCallback(double xOffset, double yOffset)
	{   LOG->info("scrollCallback called: %f,%f!", xOffset, yOffset);};
	virtual void keyCallback(int key, int scancode, int action, int mods)
	{   LOG->info("keyCallback called: %d,%d,%d,%d!", key, scancode, action, mods);};
    };

ShaderProgram* shader;
Texture* tex;
Mesh* pMesh;
Mesh* pMesh2;
Mesh* pMesh3;
Mesh* pMesh4;

void renderCallbackWin(const RenderContext* rc)
{
    shader->use();
    rc->draw(pMesh, Mat4f(), shader, tex);
}

void renderCallbackWin2(const RenderContext* rc)
{
    shader->use();
    rc->draw(pMesh2, Mat4f(), shader, tex);
}

void renderCallbackWin3(const RenderContext* rc)
{
    shader->use();
    rc->draw(pMesh3, Mat4f(), shader, tex);
}

void renderCallbackWin4(const RenderContext* rc)
{
    shader->use();
    rc->draw(pMesh4, Mat4f(), shader, tex);
}

int testWindow()
{
    LOG->info("Starting Window test suite...");
    LOG->info("Constructors... ");
    Window* wnd = WindowManager::get()->createWindow<SimpleWindow>();
    Window* wnd2 = WindowManager::get()->createWindow<SimpleWindow>("Window 2");
    Window* wnd3 = WindowManager::get()->createWindow<SimpleWindow>("Window 3", 640, 480);
    Window* wnd4 = WindowManager::get()->createWindow<SimpleWindow>("Window 4", 640, 640, false);
    LOG->info("OK!");
    LOG->info("Methods... ");
    // Init
    wnd->init();
    Viewport* viewport = new Viewport(0, 0, 1, 1);
    Camera* cam = new Camera(Vec3f(-2, 2, 5), Vec3f(0, 0, 0), Vec3f(0, 1, 0), pi_4(), 0.1, 10);
    viewport->setCamera(cam);
    wnd->getRenderContext()->addViewport(viewport);
    wnd2->init();
    Viewport* viewport2 = new Viewport(0, 0, 1, 1);
    Camera* cam2 = new Camera(Vec3f(3, 2, 5), Vec3f(0, 0, 0), Vec3f(0, 1, 0), pi_4(), 0.1, 10);
    viewport2->setCamera(cam2);
    wnd2->getRenderContext()->addViewport(viewport2);
    wnd3->init();
    Viewport* viewport3_1 = new Viewport(0, 0, 0.5, 1);
    Viewport* viewport3_2 = new Viewport(0.5, 0, 1, 1);
    Camera* cam3_1 = new Camera(Vec3f(1, 1, 5), Vec3f(0, 0, 0), Vec3f(0, 1, 0), pi_4(), 0.1, 10);
    Camera* cam3_2 = new Camera(Vec3f(-5, 1, 5), Vec3f(0, 0, 0), Vec3f(0, 1, 0), pi_4(), 0.1, 10);
    viewport3_1->setCamera(cam3_1);
    viewport3_2->setCamera(cam3_2);
    wnd3->getRenderContext()->addViewport(viewport3_1);
    wnd3->getRenderContext()->addViewport(viewport3_2);
    wnd4->init();
    Viewport* viewport4 = new Viewport(0, 0, 1, 1);
    Camera* cam4 = new Camera(Vec3f(-1, 1, 5), Vec3f(0, 0, 0), Vec3f(0, 1, 0), pi_4(), 0.1, 10);
    viewport4->setCamera(cam4);
    wnd4->getRenderContext()->addViewport(viewport4);
    // Load meshes and shader
    wnd->makeCurrent();
    pMesh = Mesh::makePyramid();
    pMesh2 = Mesh::makeCube();
    pMesh3 = Mesh::makePlane();
    pMesh4 = Mesh::makeTriangle();
    shader = ShaderProgram::createSimpleShader();
    tex = new Texture(Texture::BOGUS, "");
    // Show windows
    wnd->show();
    wnd->addRenderCallback(std::bind(&renderCallbackWin, std::placeholders::_1));
    wnd2->show();
    wnd2->addRenderCallback(std::bind(&renderCallbackWin2, std::placeholders::_1));
    wnd3->show();
    wnd3->addRenderCallback(std::bind(&renderCallbackWin3, std::placeholders::_1));
    wnd4->show();
    wnd4->addRenderCallback(std::bind(&renderCallbackWin4, std::placeholders::_1));
    // Run update loop
    while(WindowManager::get()->isRunning())
    {
	WindowManager::get()->update();
    }
    delete pMesh;
    delete pMesh2;
    delete pMesh3;
    delete pMesh4;
    delete shader;
    delete tex;
    delete cam;
    delete cam2;
    delete cam3_1;
    delete cam3_2;
    delete cam4;
    delete viewport;
    delete viewport2;
    delete viewport3_1;
    delete viewport3_2;
    delete viewport4;
    WindowManager::get()->terminate();
    LOG->info("OK!");
    LOG->info("Operators... ");
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}

#endif
