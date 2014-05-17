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
    Texture::Texture(GLuint texID)
    {
	m_textureId = texID;
    }

    Texture::~Texture()
    {
	glDeleteTextures(1, &m_textureId);
    }

    GLuint Texture::getHandle()
    {
	return m_textureId;
    }

    template <class Loader> Texture* Texture::load(const std::string path, Bitmask<> flags)
    {
	Loader loader;
	Texture* pTex = loader.load(path, flags);
	if (pTex == nullptr)
	{
	    LOG.warning("Texture % not loaded!", path.c_str());
	}
	return pTex;
    }

    Texture* Texture::load(const Type type, const std::string path, Bitmask<> flags)
    {
	switch (type)
	{
	    case BOGUS:
		return Texture::load<BogusTextureLoader>(path, flags);
		break;
	    case DDS:
		return Texture::load<DDSTextureLoader>(path, flags);
		break;
	    case TGA:
		return Texture::load<TGATextureLoader>(path, flags);
		break;
	}
	return nullptr;
    }
}

