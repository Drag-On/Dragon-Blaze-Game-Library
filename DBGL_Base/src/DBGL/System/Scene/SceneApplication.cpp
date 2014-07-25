//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Scene/SceneApplication.h"

namespace dbgl
{
    void SceneApplication::init()
    {
	// Create window
	m_pWindow = createWindow();
	// Initialize it
	m_pWindow->init();
	// Load required resources
	loadResources();
	// Add update- and render callback so we can draw the mesh
	m_pWindow->addUpdateCallback(std::bind(&SceneApplication::update, this, std::placeholders::_1));
	m_pWindow->addRenderCallback(std::bind(&SceneApplication::render, this, std::placeholders::_1));
	// Show window
	m_pWindow->show();
    }

    void SceneApplication::run()
    {
	// Run update loop
	while (dbgl::isRunning())
	{
	    dbgl::update();
	}
    }

    void SceneApplication::update(Window::UpdateEventArgs const& args)
    {
	// Pre-order traversal of the scene graph
	std::stack<SceneGraph<Entity>::Node*> stack{};
	stack.push(nullptr);
	auto top = m_sceneGraph.getRoot();
	while(top)
	{
	    top->getEntity()->update(args.deltaTime);
	    auto children = top->getChildren();
	    for(auto it = children.rend(); it != children.rbegin(); --it)
	    {
		SceneGraph<Entity>::Node* entity = *it;
		stack.push(entity);
	    }
	    top = stack.top();
	    stack.pop();
	}
    }

    void SceneApplication::render(Window::RenderEventArgs const& args)
    {
	// Pre-order traversal of the scene graph
	std::stack<SceneGraph<Entity>::Node*> stack{};
	stack.push(nullptr);
	auto top = m_sceneGraph.getRoot();
	while(top)
	{
	    top->getEntity()->render(args.rc);
	    auto children = top->getChildren();
	    for(auto it = children.rend(); it != children.rbegin(); --it)
	    {
		SceneGraph<Entity>::Node* entity = *it;
		stack.push(entity);
	    }
	    top = stack.top();
	    stack.pop();
	}
    }
}
