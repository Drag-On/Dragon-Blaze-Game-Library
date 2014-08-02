//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Sprite/Sprite.h"

namespace dbgl
{
    Sprite::Sprite(Texture* tex) : m_pTexture(tex)
    {
	if (tex != nullptr)
	{
	    m_rect.pos() = Vector2<unsigned int>{0, 0};
	    m_rect.extent() = Vector2<unsigned int>{tex->getWidth(), tex->getHeight()};
	    m_pMesh = Mesh::makePlane();
	    tl = m_pMesh->getVertexIndex({-1, 1, 0});
	    tr = m_pMesh->getVertexIndex({1, 1, 0});
	    ll = m_pMesh->getVertexIndex({-1, -1, 0});
	    lr = m_pMesh->getVertexIndex({1, -1, 0});
	    recomputeMesh();
	}
    }

    Sprite::~Sprite()
    {
	delete m_pMesh;
    }

    Sprite::Sprite(Sprite const& other) :
	    m_pTexture(other.m_pTexture), m_rect(other.m_rect), m_pMesh(new Mesh { *other.m_pMesh }),
	    tl(other.tl), tr(other.tr), ll(other.ll), lr(other.lr)
    {
    }

    Sprite& Sprite::operator=(Sprite const& other)
    {
	m_pTexture = other.m_pTexture;
	m_rect = other.m_rect;
	delete m_pMesh;
	m_pMesh = new Mesh{*other.m_pMesh};
	tl = other.tl;
	tr = other.tr;
	ll = other.ll;
	lr = other.lr;
	return *this;
    }

    Texture* Sprite::getTexture() const
    {
	return m_pTexture;
    }

    void Sprite::setTexture(Texture* tex)
    {
	m_pTexture = tex;
	// Crop rectangle if needed
	validateRect();
	recomputeMesh();
    }

    Rectangle<unsigned int> const& Sprite::getRect() const
    {
	return m_rect;
    }

    void Sprite::setRect(Rectangle<unsigned int> rect)
    {
	m_rect = rect;
	// Crop rectangle if needed
	validateRect();
	recomputeMesh();
    }

    Mesh* Sprite::getMesh() const
    {
	return m_pMesh;
    }

    void Sprite::recomputeMesh()
    {
	float width = m_pTexture->getWidth();
	float height = m_pTexture->getHeight();
	// Calculate new uvs
	Rectangle<float> uvs{};
	uvs.pos().x() = m_rect.pos().x() / width;
	uvs.pos().y() = m_rect.pos().y() / height;
	uvs.extent().x() = m_rect.extent().x() / width;
	uvs.extent().y() = m_rect.extent().y() / height;
	// Set them
	m_pMesh->uvs()[tl] = Vec2f{uvs.left(0), uvs.right(1)};
	m_pMesh->uvs()[tr] = Vec2f{uvs.right(0), uvs.right(1)};
	m_pMesh->uvs()[ll] = Vec2f{uvs.left(0), uvs.left(1)};
	m_pMesh->uvs()[lr] = Vec2f{uvs.right(0), uvs.left(1)};
	// Set appropriate coordinates
	m_pMesh->vertices()[tl] = Vec3f{m_rect.left(0), m_rect.right(1), 0};
	m_pMesh->vertices()[tr] = Vec3f{m_rect.right(0), m_rect.right(1), 0};
	m_pMesh->vertices()[ll] = Vec3f{m_rect.left(0), m_rect.left(1), 0};
	m_pMesh->vertices()[lr] = Vec3f{m_rect.right(0), m_rect.left(1), 0};
	m_pMesh->updateBuffers();
    }

    void Sprite::validateRect()
    {
	// Crop rectangle if needed
	if(m_rect.right(0) > m_pTexture->getWidth())
	    m_rect.extent()[0] = m_pTexture->getWidth() - m_rect.pos()[0];
	if(m_rect.right(1) > m_pTexture->getHeight())
	    m_rect.extent()[1] = m_pTexture->getHeight() - m_rect.pos()[1];
    }

}
