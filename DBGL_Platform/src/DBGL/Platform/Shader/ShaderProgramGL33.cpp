//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Shader/ShaderProgramGL33.h"

namespace dbgl
{
	ShaderProgramGL33::ShaderProgramGL33()
	{
		m_id = glCreateProgram();
		if (m_id == 0)
			throw std::runtime_error("Couldn't create shader program");
	}

	ShaderProgramGL33::~ShaderProgramGL33()
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgramGL33::attach(IShader* shader)
	{
		auto sha = dynamic_cast<ShaderGL33*>(shader);
		if (sha == nullptr)
			throw std::invalid_argument { "Cannot attach null shader to program" };
		glAttachShader(m_id, sha->getHandle());
	}

	void ShaderProgramGL33::link()
	{
		glLinkProgram(m_id);
		// Check if everything went right
		GLint linkOk = GL_FALSE;
		glGetProgramiv(m_id, GL_LINK_STATUS, &linkOk);
		if (!linkOk)
		{
			// Generate log
			GLint logLength = 0;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
			if (logLength > 0)
			{
				char* msg = new char[logLength] { };
				glGetProgramInfoLog(m_id, logLength, nullptr, msg);
				std::string message { msg };
				delete[] msg;
				throw std::runtime_error(message);
			}
		}
	}

	void ShaderProgramGL33::use()
	{
		useInternal();
	}

	auto ShaderProgramGL33::getAttributeHandle(std::string name) const -> AttribHandle
	{
		return glGetAttribLocation(m_id, name.c_str());
	}

	auto ShaderProgramGL33::getUniformHandle(std::string name) const -> UniformHandle
	{
		return glGetUniformLocation(m_id, name.c_str());
	}

	GLuint ShaderProgramGL33::getHandle() const
	{
		return m_id;
	}

	void ShaderProgramGL33::useInternal() const
	{
		glUseProgram(m_id);
	}
}
