//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/ResourceManager/Resource.h"

namespace dbgl
{
    Resource::ResourceInfo::ResourceInfo(std::string filename) : m_filename(filename)
    {
    }

    Resource::Resource(std::string const& filename) : m_filename(filename)
    {
    }

    Resource::Resource(ResourceInfo const& info) : Resource(info.m_filename)
    {
    }

    std::string const& Resource::getFilename() const
    {
	return m_filename;
    }

    ResourceHandle Resource::getHandle() const
    {
	return m_handle;
    }

    bool Resource::isLoaded() const
    {
	return m_loaded;
    }

    void Resource::load()
    {
	m_loaded = true;
    }

    void Resource::unload()
    {
	m_loaded = false;
    }

}
