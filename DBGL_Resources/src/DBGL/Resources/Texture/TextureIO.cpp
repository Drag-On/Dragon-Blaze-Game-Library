//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Texture/TextureIO.h"

namespace dbgl
{
    TextureIO::TextureIO()
    {
    }

    TextureIO::~TextureIO()
    {
    }

    bool TextureIO::addFormat(std::string const& filename)
    {
	AdvancedModule<ITextureFormat> mod { filename };
	if(mod.load())
	    m_modules.push_back(mod);
	else
	    return false;
	return true;
    }

    bool TextureIO::addFormat(Filename const& filename)
    {
	AdvancedModule<ITextureFormat> mod { filename };
	if(mod.load())
	    m_modules.push_back(mod);
	else
	    return false;
	return true;
    }

    ITexture* TextureIO::load(std::string const& filename) const
    {

    }

    ITexture* TextureIO::load(Filename const& filename) const
    {

    }

    bool TextureIO::write(ITexture* tex, std::string const& filename) const
    {

    }

    bool TextureIO::write(ITexture* tex, Filename const& filename) const
    {

    }

    AdvancedModule<ITextureFormat>* TextureIO::pickModule() const
    {

    }

}
