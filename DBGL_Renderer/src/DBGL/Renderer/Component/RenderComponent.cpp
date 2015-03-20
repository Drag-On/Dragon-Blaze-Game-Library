//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/Component/RenderComponent.h"

namespace dbgl
{
	RenderComponent::RenderComponent(IMaterial* material, IMesh* mesh)
			: m_pMaterial(material), m_pMesh(mesh)
	{
		// Make sure vertices don't get modified
		std::vector<Vec3f> const& vertices = mesh->vertices();
		m_boundingSphere = Sphere<float>(vertices);
	}

	RenderComponent::RenderComponent(IMaterial* material, IMesh* mesh, Sphere<float> const& boundingSphere)
			: m_pMaterial(material), m_pMesh(mesh), m_boundingSphere(boundingSphere)
	{
	}

	void RenderComponent::update()
	{
	}

	IMesh* RenderComponent::getMesh() const
	{
		return m_pMesh;
	}

	void RenderComponent::setMesh(IMesh* mesh)
	{
		m_pMesh = mesh;
		// Make sure vertices don't get modified
		std::vector<Vec3f> const& vertices = mesh->vertices();
		m_boundingSphere = Sphere<float>(vertices);
	}

	void RenderComponent::setMesh(IMesh* mesh, Sphere<float> boundingSphere)
	{
		m_pMesh = mesh;
		m_boundingSphere = boundingSphere;
	}

	IMaterial* RenderComponent::getMaterial() const
	{
		return m_pMaterial;
	}

	void RenderComponent::setMaterial(IMaterial* material)
	{
		m_pMaterial = material;
	}

	Sphere<float> const& RenderComponent::getBoundingSphere() const
	{
		return m_boundingSphere;
	}
}
