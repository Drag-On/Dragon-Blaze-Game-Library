//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/ResourceManager/IResource.h"

namespace dbgl
{
    IResource::IResource(std::string filename) : m_filename(filename)
    {
    }

    std::string const& IResource::getFilename() const
    {
	return m_filename;
    }

    ResourceHandle IResource::getHandle() const
    {
	return m_handle;
    }

    bool IResource::isLoaded() const
    {
	return m_loaded;
    }

    void IResource::load()
    {
	m_loaded = true;
    }

    void IResource::unload()
    {
	m_loaded = false;
    }

}
