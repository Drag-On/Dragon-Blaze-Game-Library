//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Shader/ShaderProgramResource.h"

namespace dbgl
{
	ShaderProgramResource::ShaderProgramResource(ResourceHandle h, std::string const& name,
			std::vector<std::string> const& filenames, ResourceManager<ShaderResource>* shaderManager)
			: AbstractResource(h), m_name(name), m_pShaderManager(shaderManager)
	{
		m_shaderFiles.insert(m_shaderFiles.end(), filenames.begin(), filenames.end());
		if (m_shaderFiles.empty() || !m_pShaderManager)
			throw(std::invalid_argument("Can't create a shader program resource without attached shaders!"));
	}

	void ShaderProgramResource::load()
	{
		m_pShaderProgram = Platform::get()->createShaderProgram();
		for (auto s : m_shaderFiles)
		{
			auto handle = m_pShaderManager->identify(s);
			if (handle.isValid())
			{
				auto res = m_pShaderManager->request(handle, true);
				m_pShaderProgram->attach(res->getShader());
			}
			else
			{
				Log::getDefault().warning("File % is not a valid shader for program %. Skipping.", s, m_name);
			}
		}
		try
		{
			m_pShaderProgram->link();
			AbstractResource::load();
		}
		catch (std::runtime_error& e)
		{
			Log::getDefault().error("Couldn't link shader program %. Failed with message: %.", m_name, e.what());
			delete m_pShaderProgram;
			m_pShaderProgram = nullptr;
		}
		catch (...)
		{
			Log::getDefault().error("Couldn't link shader program %. Unknown error.", m_name);
			delete m_pShaderProgram;
			m_pShaderProgram = nullptr;
		}
	}

	void ShaderProgramResource::unload()
	{
		delete m_pShaderProgram;
		m_pShaderProgram = nullptr;
		AbstractResource::unload();
	}

	bool ShaderProgramResource::identify(std::string const& name) const
	{
		return name == m_name;
	}

	IShaderProgram* ShaderProgramResource::getShaderProgram()
	{
		return m_pShaderProgram;
	}
}
