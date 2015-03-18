//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Texture/TextureResource.h"
#include "DBGL/Resources/Texture/TextureUtility.h"
#include "DBGL/Platform/Platform.h"

namespace dbgl
{
	TextureIO TextureResource::s_textureIO { };

	TextureResource::TextureResource(ResourceHandle h, std::string const& filename, bool createMip)
			: AbstractResource(h), m_filename { filename }, m_createMip { createMip }
	{
	}

	void TextureResource::load()
	{
		m_pTexture = s_textureIO.load(m_filename);
		if (!m_pTexture)
		{
			Log::getDefault().error("Couldn't load texture \"%\". Using a bright red 1x1 texture instead.", m_filename);
			unsigned char whiteVal[] = { 255, 255, 255, 255 };
			m_pTexture = TextureUtility::createTexture(TextureUtility::ImageData(&whiteVal[0], 1, 1));
		}
		if (m_createMip)
		{
			m_pTexture->bind();
			Platform::get()->curTexture()->generateMipMaps();
		}
		AbstractResource::load();
	}

	void TextureResource::unload()
	{
		delete m_pTexture;
		m_pTexture = nullptr;
		AbstractResource::unload();
	}

	bool TextureResource::identify(std::string const& filename) const
	{
		return m_filename == filename;
	}

	ITexture* TextureResource::getTexture()
	{
		return m_pTexture;
	}

	TextureIO& TextureResource::loader()
	{
		return TextureResource::s_textureIO;
	}
}
