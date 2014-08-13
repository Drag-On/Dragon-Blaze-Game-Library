//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/ResourceManager/ShaderResource.h"

namespace dbgl
{
    ShaderResource::ShaderResource(ShaderResourceInfo const& info) :
	    Resource(info), m_fragmentShaderFileName(info.m_fragmentShaderFileName)
    {
    }

    ShaderResource::~ShaderResource()
    {
	unload();
    }

    void ShaderResource::load()
    {
	if(m_pShader != nullptr)
	    LOG.warning("Tried to load a shader resource multiple times in a row. Keeping previous state.");
	m_pShader = new ShaderProgram{m_filename, m_fragmentShaderFileName};
	Resource::load();
    }

    void ShaderResource::unload()
    {
	delete m_pShader;
	m_pShader = nullptr;
	Resource::unload();
    }

    ShaderProgram* ShaderResource::getShader() const
    {
	return m_pShader;
    }

}
