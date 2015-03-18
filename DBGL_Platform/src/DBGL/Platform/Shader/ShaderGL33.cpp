//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Shader/ShaderGL33.h"

namespace dbgl
{
	ShaderGL33::ShaderGL33(Type type, std::string code)
			: m_type { type }, m_code { code }
	{
	}

	ShaderGL33::~ShaderGL33()
	{
		glDeleteShader(m_id);
	}

	void ShaderGL33::compile()
	{
		if (m_code.length() == 0)
			throw std::runtime_error { "No code to compile." };

		// In case the shader has already been compiled -> delete old result
		if (m_id != 0)
			glDeleteShader(m_id);

		// Create shader object
		m_id = glCreateShader(shaderType2GL(m_type));

		// Compile
		const char* codePtr = m_code.c_str();
		glShaderSource(m_id, 1, &codePtr, nullptr);
		glCompileShader(m_id);

		// Check if everything went right
		GLint result = GL_FALSE;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint logLength { 0 };
			glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
			char* msg = new char[logLength] { };
			// Get actual log
			glGetShaderInfoLog(m_id, logLength, nullptr, msg);
			std::string message { msg };
			delete msg;
			throw std::runtime_error { message };
		}
	}

	GLuint ShaderGL33::getHandle() const
	{
		return m_id;
	}

	GLenum ShaderGL33::shaderType2GL(Type type)
	{
		switch (type)
		{
		case Type::COMPUTE:
			return GL_COMPUTE_SHADER;
		case Type::FRAGMENT:
			return GL_FRAGMENT_SHADER;
		case Type::GEOMETRY:
			return GL_GEOMETRY_SHADER;
		case Type::VERTEX:
			return GL_VERTEX_SHADER;
		default:
			return GL_INVALID_ENUM;
		}
	}
}
