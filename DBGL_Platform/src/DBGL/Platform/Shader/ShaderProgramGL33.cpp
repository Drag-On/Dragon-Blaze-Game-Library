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
    ShaderProgramGL33::ShaderProgramGL33()
    {
	m_id = glCreateProgram();
	if(m_id == 0)
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
	glAttachShader(m_id, sha->m_id);
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
		char* msg = new char[logLength] {};
		glGetProgramInfoLog(m_id, logLength, nullptr, msg);
		std::string message { msg };
		delete[] msg;
		throw std::runtime_error(message);
	    }
	}
    }

    void ShaderProgramGL33::use()
    {
	glUseProgram(m_id);
    }

    auto ShaderProgramGL33::getAttributeHandle(std::string name) const -> AttribHandle
    {
	return glGetAttribLocation(m_id, name.c_str());
    }

    auto ShaderProgramGL33::getUniformHandle(std::string name) const -> UniformHandle
    {
	return glGetUniformLocation(m_id, name.c_str());
    }

    void ShaderProgramGL33::setUniformFloat(UniformHandle handle, const float value)
    {
	glUniform1f(handle, value);
    }

    void ShaderProgramGL33::setUniformFloat2(UniformHandle handle, const float value[2])
    {
	glUniform2f(handle, value[0], value[1]);
    }

    void ShaderProgramGL33::setUniformFloat3(UniformHandle handle, const float value[3])
    {
	glUniform3f(handle, value[0], value[1], value[2]);
    }

    void ShaderProgramGL33::setUniformFloat4(UniformHandle handle, const float value[4])
    {
	glUniform4f(handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgramGL33::setUniformInt(UniformHandle handle, const int value)
    {
	glUniform1i(handle, value);
    }

    void ShaderProgramGL33::setUniformInt2(UniformHandle handle, const int value[2])
    {
	glUniform2i(handle, value[0], value[1]);
    }

    void ShaderProgramGL33::setUniformInt3(UniformHandle handle, const int value[3])
    {
	glUniform3i(handle, value[0], value[1], value[2]);
    }

    void ShaderProgramGL33::setUniformInt4(UniformHandle handle, const int value[4])
    {
	glUniform4i(handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgramGL33::setUniformBool(UniformHandle handle, const bool value)
    {
	glUniform1i(handle, value);
    }

    void ShaderProgramGL33::setUniformBool2(UniformHandle handle, const bool value[2])
    {
	glUniform2i(handle, value[0], value[1]);
    }

    void ShaderProgramGL33::setUniformBool3(UniformHandle handle, const bool value[3])
    {
	glUniform3i(handle, value[0], value[1], value[2]);
    }

    void ShaderProgramGL33::setUniformBool4(UniformHandle handle, const bool value[4])
    {
	glUniform4i(handle, value[0], value[1], value[2], value[3]);
    }

    void ShaderProgramGL33::setUniformFloatArray(UniformHandle handle, unsigned int count,
	    const float* values)
    {
	glUniform1fv(handle, count, values);
    }

    void ShaderProgramGL33::setUniformFloat2Array(UniformHandle handle, unsigned int count,
	    const float* values)
    {
	glUniform2fv(handle, count, values);
    }

    void ShaderProgramGL33::setUniformFloat3Array(UniformHandle handle, unsigned int count,
	    const float* values)
    {
	glUniform3fv(handle, count, values);
    }

    void ShaderProgramGL33::setUniformFloat4Array(UniformHandle handle, unsigned int count,
	    const float* values)
    {
	glUniform4fv(handle, count, values);
    }

    void ShaderProgramGL33::setUniformIntArray(UniformHandle handle, unsigned int count, const int* values)
    {
	glUniform1iv(handle, count, values);
    }

    void ShaderProgramGL33::setUniformInt2Array(UniformHandle handle, unsigned int count, const int* values)
    {
	glUniform2iv(handle, count, values);
    }

    void ShaderProgramGL33::setUniformInt3Array(UniformHandle handle, unsigned int count, const int* values)
    {
	glUniform3iv(handle, count, values);
    }

    void ShaderProgramGL33::setUniformInt4Array(UniformHandle handle, unsigned int count, const int* values)
    {
	glUniform4iv(handle, count, values);
    }

    void ShaderProgramGL33::setUniformFloatMatrix2Array(UniformHandle handle, unsigned int count,
	    bool transpose, const float* values)
    {
	glUniformMatrix2fv(handle, count, transpose, values);
    }

    void ShaderProgramGL33::setUniformFloatMatrix3Array(UniformHandle handle, unsigned int count,
	    bool transpose, const float* values)
    {
	glUniformMatrix3fv(handle, count, transpose, values);
    }

    void ShaderProgramGL33::setUniformFloatMatrix4Array(UniformHandle handle, unsigned int count,
	    bool transpose, const float* values)
    {
	glUniformMatrix4fv(handle, count, transpose, values);
    }

    void ShaderProgramGL33::setUniformSampler(UniformHandle handle, const int value)
    {
	glUniform1i(handle, value);
    }
}
