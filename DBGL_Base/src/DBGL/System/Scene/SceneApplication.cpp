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
    void SceneApplication::update(float deltaTime)
    {
	// Pre-order traversal of the scene graph
	std::stack<SceneGraph<Entity>::Node*> stack{};
	stack.push(nullptr);
	auto top = m_sceneGraph.getRoot();
	while(top)
	{
	    top->getEntity()->update(deltaTime);
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

    void SceneApplication::render(RenderContext const* rc)
    {
	// Pre-order traversal of the scene graph
	std::stack<SceneGraph<Entity>::Node*> stack{};
	stack.push(nullptr);
	auto top = m_sceneGraph.getRoot();
	while(top)
	{
	    top->getEntity()->render(rc);
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
