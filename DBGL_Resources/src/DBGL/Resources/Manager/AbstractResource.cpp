//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Manager/AbstractResource.h"

namespace dbgl
{
    AbstractResource::AbstractResource(ResourceHandle handle) : m_handle { handle }
    {
    }

    auto AbstractResource::getHandle() const -> ResourceHandle
    {
	return m_handle;
    }

    bool AbstractResource::isLoaded() const
    {
	return m_loaded;
    }

    void AbstractResource::load()
    {
	m_loaded = true;
    }

    void AbstractResource::unload()
    {
	m_loaded = false;
    }

}
