//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Shader/ShaderProgramGL33.h"

namespace dbgl
{
    ShaderProgramGL33::~ShaderProgramGL33()
    {
	glDeleteProgram(m_id);
    }

    void ShaderProgramGL33::attach(IShader* shader)
    {
	auto sha = dynamic_cast<ShaderGL33*>(shader);
	if(sha == nullptr)
	    throw std::invalid_argument{"Cannot attach null shader to program"};
	glAttachShader(m_id, sha->m_id);
    }

    void ShaderProgramGL33::link()
    {
	glLinkProgram(m_id);
	GLint linkOk = GL_FALSE;
	glGetProgramiv(m_id, GL_LINK_STATUS, &linkOk);
	// Check if everything went right
	GLint result = GL_FALSE;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
	    GLint logLength {0};
	    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);
	    char* msg = new char[logLength] {};
	    // Get actual log
	    glGetProgramInfoLog(m_id, logLength, nullptr, msg);
	    std::string message{msg};
	    delete msg;
	    throw std::runtime_error {message};
	}
    }

    void ShaderProgramGL33::use()
    {
	glUseProgram(m_id);
    }
}
