//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/ResourceManager/TextureResource.h"

namespace dbgl
{
    TextureResource::TextureResource(std::string const& filename) : Resource(filename), m_pTextureLoader(new TGATextureLoader{})
    {
    }

    template<class T> TextureResource::TextureResource(TextureResourceInfo<T> const& info) :
	    Resource(info), m_pTextureLoader(new T {}), m_flags(info.m_flags), m_filtering(info.m_filtering)
    {
    }

    TextureResource::~TextureResource()
    {
	unload();
	delete m_pTextureLoader;
    }

    void TextureResource::load()
    {
	if(m_pTexture != nullptr)
	    LOG.warning("Tried to load a texture resource multiple times in a row. Keeping previous state.");
	m_pTexture = m_pTextureLoader->load(m_filename, m_flags, m_filtering);
	Resource::load();
    }

    void TextureResource::unload()
    {
	delete m_pTexture;
	m_pTexture = nullptr;
	Resource::unload();
    }

    Texture* TextureResource::getTexture() const
    {
	return m_pTexture;
    }

}
