//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Texture/Texture.h"

namespace dbgl
{
    Texture::Texture(IGL::TextureHandle handle)
    {
	m_handle = handle;
	GLProvider::get()->texBind(handle);
	GLProvider::get()->texGetSize(m_width, m_height);
    }

    Texture::~Texture()
    {
	GLProvider::get()->texDelete(m_handle);
    }

    GLuint Texture::getHandle() const
    {
	return m_handle->m_handle; // TODO: Remove
    }

    unsigned int Texture::getWidth() const
    {
	return m_width;
    }

    unsigned int Texture::getHeight() const
    {
	return m_height;
    }

    template <class Loader> Texture* Texture::load(const std::string path, Bitmask<> flags, TextureLoader::Filtering filtering)
    {
	Loader loader{};
	Texture* pTex = loader.load(path, flags, filtering);
	if (pTex == nullptr)
	{
	    LOG.warning("Texture % not loaded!", path.c_str());
	}
	return pTex;
    }

    Texture* Texture::load(const Type type, const std::string path, Bitmask<> flags, TextureLoader::Filtering filtering)
    {
	switch (type)
	{
	    case Type::BOGUS:
		return Texture::load<BogusTextureLoader>(path, flags, filtering);
		break;
	    case Type::DDS:
		return Texture::load<DDSTextureLoader>(path, flags, filtering);
		break;
	    case Type::TGA:
		return Texture::load<TGATextureLoader>(path, flags, filtering);
		break;
	}
	return nullptr;
    }
}

