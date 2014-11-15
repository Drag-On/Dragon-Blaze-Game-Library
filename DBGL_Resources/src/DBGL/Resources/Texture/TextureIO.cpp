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

#include <iostream>

namespace dbgl
{
    TextureIO::TextureIO()
    {
    }

    TextureIO::~TextureIO()
    {
	for(auto mod : m_modules)
	    delete mod;
    }

    bool TextureIO::addFormat(std::string const& filename)
    {
	return addFormat(Filename{filename});
    }

    bool TextureIO::addFormat(Filename const& filename)
    {
	auto mod = new AdvancedModule<IImageFormatModule>{ filename };
	if(mod->load())
	    m_modules.push_back(mod);
	else
	    return false;
	return true;
    }

    ITexture* TextureIO::load(std::string const& filename) const
    {
	return load(Filename{filename});
    }

    ITexture* TextureIO::load(Filename const& filename) const
    {
	for(auto mod : m_modules)
	{
	    if(mod->get()->matchExtension(filename.getExtension()) && mod->get()->canLoad())
	    {
		return mod->get()->load(filename);
	    }
	}
	return nullptr;
    }

    bool TextureIO::write(ITexture* tex, std::string const& filename) const
    {
	return write(tex, Filename{filename});
    }

    bool TextureIO::write(ITexture* tex, Filename const& filename) const
    {
	for(auto mod : m_modules)
	{
	    if(mod->get()->matchExtension(filename.getExtension()) && mod->get()->canWrite())
	    {
		return mod->get()->write(tex, filename);
	    }
	}
	return false;
    }

}
