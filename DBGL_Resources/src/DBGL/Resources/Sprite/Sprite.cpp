//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <type_traits>
#include <typeinfo>
#include "DBGL/Resources/Sprite/Sprite.h"
#include "DBGL/Resources/Mesh/MeshUtility.h"

namespace dbgl
{
	Sprite::Sprite(ITexture* tex)
			: m_pTexture(tex)
	{
		if (tex != nullptr)
		{
			tex->bind();
			m_rect.pos() = Vector2<unsigned int> { 0, 0 };
			m_rect.extent() = Vector2<unsigned int> { Platform::get()->curTexture()->getWidth(),
					Platform::get()->curTexture()->getHeight() };
			m_pMesh = MeshUtility::createRectangle(true, IMesh::Usage::DynamicDraw);
			tl = 1;
			tr = 2;
			ll = 0;
			lr = 3;
			recomputeMesh();
		}
	}

	Sprite::~Sprite()
	{
		delete m_pMesh;
	}

	Sprite::Sprite(Sprite const& other)
			: m_pTexture(other.m_pTexture), m_rect(other.m_rect), m_pMesh(other.m_pMesh->clone()), tl(other.tl), tr(other.tr), ll(other.ll), lr(
					other.lr)
	{

	}

	Sprite& Sprite::operator=(Sprite const& other)
	{
		if (this != &other)
		{
			m_pTexture = other.m_pTexture;
			m_rect = other.m_rect;
			delete m_pMesh;
			m_pMesh = other.m_pMesh->clone();
			tl = other.tl;
			tr = other.tr;
			ll = other.ll;
			lr = other.lr;
		}
		return *this;
	}

	ITexture* Sprite::getTexture() const
	{
		return m_pTexture;
	}

	void Sprite::setTexture(ITexture* tex)
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

	IMesh* Sprite::getMesh() const
	{
		return m_pMesh;
	}

	unsigned int Sprite::getWidth() const
	{
		return m_rect.getExtent().x();
	}

	unsigned int Sprite::getHeight() const
	{
		return m_rect.getExtent().y();
	}

	bool Sprite::getFlipX() const
	{
		return m_flipX;
	}

	void Sprite::setFlipX(bool flip)
	{
		m_flipX = flip;
	}

	bool Sprite::getFlipY() const
	{
		return m_flipY;
	}

	void Sprite::setFlipY(bool flip)
	{
		m_flipY = flip;
	}

	void Sprite::recomputeMesh()
	{
		m_pTexture->bind();
		float width = Platform::get()->curTexture()->getWidth();
		float height = Platform::get()->curTexture()->getHeight();
		// Calculate new uvs
		Rectangle<float> uvs { };
		uvs.pos().x() = m_rect.pos().x() / width;
		uvs.pos().y() = m_rect.pos().y() / height;
		uvs.extent().x() = m_rect.extent().x() / width;
		uvs.extent().y() = m_rect.extent().y() / height;
		// Set them
		float lowerX = m_flipX ? uvs.right(0) : uvs.left(0);
		float upperX = m_flipX ? uvs.left(0) : uvs.right(0);
		float lowerY = m_flipY ? uvs.right(1) : uvs.left(1);
		float upperY = m_flipY ? uvs.left(1) : uvs.right(1);
		m_pMesh->uvs()[tl] = Vec2f { lowerX, upperY };
		m_pMesh->uvs()[tr] = Vec2f { upperX, upperY };
		m_pMesh->uvs()[ll] = Vec2f { lowerX, lowerY };
		m_pMesh->uvs()[lr] = Vec2f { upperX, lowerY };
		// Set appropriate coordinates
		m_pMesh->vertices()[tl] = Vec3f { 0, static_cast<float>(m_rect.right(1)) - m_rect.left(1), 0 };
		m_pMesh->vertices()[tr] = Vec3f { static_cast<float>(m_rect.right(0)) - m_rect.left(0),
				static_cast<float>(m_rect.right(1)) - m_rect.left(1), 0 };
		m_pMesh->vertices()[ll] = Vec3f { 0, 0, 0 };
		m_pMesh->vertices()[lr] = Vec3f { static_cast<float>(m_rect.right(0)) - m_rect.left(0), 0, 0 };
		m_pMesh->updateBuffers();
	}

	void Sprite::validateRect()
	{
		m_pTexture->bind();
		float width = Platform::get()->curTexture()->getWidth();
		float height = Platform::get()->curTexture()->getHeight();
		// Crop rectangle if needed
		if (m_rect.right(0) > width)
			m_rect.extent()[0] = width - m_rect.pos()[0];
		if (m_rect.right(1) > height)
			m_rect.extent()[1] = height - m_rect.pos()[1];
	}

}
