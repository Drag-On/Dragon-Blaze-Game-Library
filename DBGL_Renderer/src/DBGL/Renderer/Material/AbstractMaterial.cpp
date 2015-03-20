//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Renderer/Material/AbstractMaterial.h"

namespace dbgl
{
	AbstractMaterial::AbstractMaterial(ResourceManager<TextureResource>* texManager,
			ResourceManager<ShaderProgramResource>* shaManager)
			: m_pTexManager(texManager), m_pShaManager(shaManager)
	{
	}

	AbstractMaterial::~AbstractMaterial()
	{
	}

	void AbstractMaterial::load()
	{
		unload();
		for (auto s : m_texPaths)
		{
			m_loadedTextures.push_back(m_pTexManager->identify(s));
			m_pTexManager->request(*m_loadedTextures.rbegin(), true);
		}
		for (auto s : m_shaNames)
		{
			m_loadedShaders.push_back(m_pShaManager->identify(s));
			m_pShaManager->request(*m_loadedShaders.rbegin(), true);
		}
	}

	void AbstractMaterial::unload()
	{
		m_loadedTextures.clear();
		m_loadedShaders.clear();
	}

	TextureResource* AbstractMaterial::getTexture(unsigned int i) const
	{
		if (i < m_loadedTextures.size())
			return m_pTexManager->request(m_loadedTextures[i], true);
		else
			return nullptr;
	}

	ShaderProgramResource* AbstractMaterial::getShaderProgram(unsigned int i) const
	{
		if (i < m_loadedShaders.size())
			return m_pShaManager->request(m_loadedShaders[i], true);
		else
			return nullptr;
	}
}
