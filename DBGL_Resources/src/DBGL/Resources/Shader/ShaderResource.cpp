//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Shader/ShaderResource.h"

namespace dbgl
{
	ShaderResource::ShaderResource(ResourceHandle h, std::string const& filename, IShader::Type type)
			: AbstractResource(h), m_filename(filename), m_type(type)
	{
	}

	void ShaderResource::load()
	{
		try
		{
			std::ifstream inputStream(m_filename);
			std::string shaderCode((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
			inputStream.close();
			m_pShader = Platform::get()->createShader(m_type, shaderCode);
			m_pShader->compile();
			AbstractResource::load();
		}
		catch (std::runtime_error& e)
		{
			Log::getDefault().error("Couldn't compile shader %. Failed with message: %.", m_filename, e.what());
			delete m_pShader;
			m_pShader = nullptr;
		}
		catch (...)
		{
			Log::getDefault().error("Couldn't load shader %. Unknown error.", m_filename);
			delete m_pShader;
			m_pShader = nullptr;
		}
	}

	void ShaderResource::unload()
	{
		delete m_pShader;
		m_pShader = nullptr;
		AbstractResource::unload();
	}

	bool ShaderResource::identify(std::string const& filename) const
	{
		return m_filename == filename;
	}

	IShader* ShaderResource::getShader()
	{
		return m_pShader;
	}
}
