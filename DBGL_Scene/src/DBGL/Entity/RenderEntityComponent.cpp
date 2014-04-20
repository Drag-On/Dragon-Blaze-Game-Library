//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Entity/RenderEntityComponent.h"

namespace dbgl
{
    RenderEntityComponent::~RenderEntityComponent()
    {
	delete m_pRenderable;
    }

    void RenderEntityComponent::init(Renderable const& renderable)
    {
	m_pRenderable = new Renderable(renderable);
    }

    void RenderEntityComponent::update(std::map<std::type_index, EntityComponent*> const& components, double deltaTime)
    {
	// Update transform
	auto result = components.find(typeid(TransformEntityComponent));
	auto transform = dynamic_cast<TransformEntityComponent*>(result->second);
	if(transform)
	{
	    m_pRenderable->position = transform->position();
	    m_pRenderable->scale = transform->scale();
	    m_pRenderable->rotation = transform->rotation();
	}
    }

    void RenderEntityComponent::render(SceneRenderContext const* rc)
    {
	rc->draw(*m_pRenderable);
    }
}

