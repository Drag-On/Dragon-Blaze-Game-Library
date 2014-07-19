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
    RenderComponent::RenderComponent(Mesh& mesh, Material& mat) : m_pMesh(&mesh), m_pMaterial(&mat)
    {
    }

    void RenderComponent::update(Entity* /* owner */, double /* deltaTime */)
    {
	// No update needed
    }

    void RenderComponent::render(Entity* /* owner */, RenderContext const* rc)
    {
	m_pMaterial->prepare();
	rc->draw(*m_pMesh);
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

