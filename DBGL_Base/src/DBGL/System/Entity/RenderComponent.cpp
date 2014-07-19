//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Entity/RenderComponent.h"

namespace dbgl
{
    void RenderComponent::init()
    {
	//TODO: TBD
    }

    void RenderComponent::update(Entity* owner, double deltaTime)
    {
	//TODO: TBD
    }

    void RenderComponent::render(Entity* /* owner */, RenderContext const* rc)
    {
	//TODO: TBD
    }

    bool RenderComponent::needUpdate() const
    {
	return false;
    }

    bool RenderComponent::needRender() const
    {
	return true;
    }
}

