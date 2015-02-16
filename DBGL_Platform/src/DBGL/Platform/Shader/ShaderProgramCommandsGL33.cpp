//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Shader/ShaderProgramCommandsGL33.h"

namespace dbgl
{
	void ShaderProgramCommandsGL33::setUniformFloat(UniformHandle handle, const float value)
	{
		glUniform1f(handle, value);
	}

	void ShaderProgramCommandsGL33::setUniformFloat2(UniformHandle handle, const float value[2])
	{
		glUniform2f(handle, value[0], value[1]);
	}

	void ShaderProgramCommandsGL33::setUniformFloat3(UniformHandle handle, const float value[3])
	{
		glUniform3f(handle, value[0], value[1], value[2]);
	}

	void ShaderProgramCommandsGL33::setUniformFloat4(UniformHandle handle, const float value[4])
	{
		glUniform4f(handle, value[0], value[1], value[2], value[3]);
	}

	void ShaderProgramCommandsGL33::setUniformInt(UniformHandle handle, const int value)
	{
		glUniform1i(handle, value);
	}

	void ShaderProgramCommandsGL33::setUniformInt2(UniformHandle handle, const int value[2])
	{
		glUniform2i(handle, value[0], value[1]);
	}

	void ShaderProgramCommandsGL33::setUniformInt3(UniformHandle handle, const int value[3])
	{
		glUniform3i(handle, value[0], value[1], value[2]);
	}

	void ShaderProgramCommandsGL33::setUniformInt4(UniformHandle handle, const int value[4])
	{
		glUniform4i(handle, value[0], value[1], value[2], value[3]);
	}

	void ShaderProgramCommandsGL33::setUniformBool(UniformHandle handle, const bool value)
	{
		glUniform1i(handle, value);
	}

	void ShaderProgramCommandsGL33::setUniformBool2(UniformHandle handle, const bool value[2])
	{
		glUniform2i(handle, value[0], value[1]);
	}

	void ShaderProgramCommandsGL33::setUniformBool3(UniformHandle handle, const bool value[3])
	{
		glUniform3i(handle, value[0], value[1], value[2]);
	}

	void ShaderProgramCommandsGL33::setUniformBool4(UniformHandle handle, const bool value[4])
	{
		glUniform4i(handle, value[0], value[1], value[2], value[3]);
	}

	void ShaderProgramCommandsGL33::setUniformFloatArray(UniformHandle handle, unsigned int count, const float* values)
	{
		glUniform1fv(handle, count, values);
	}

	void ShaderProgramCommandsGL33::setUniformFloat2Array(UniformHandle handle, unsigned int count, const float* values)
	{
		glUniform2fv(handle, count, values);
	}

	void ShaderProgramCommandsGL33::setUniformFloat3Array(UniformHandle handle, unsigned int count, const float* values)
	{
		glUniform3fv(handle, count, values);
	}

	void ShaderProgramCommandsGL33::setUniformFloat4Array(UniformHandle handle, unsigned int count, const float* values)
	{
		glUniform4fv(handle, count, values);
	}

	void ShaderProgramCommandsGL33::setUniformIntArray(UniformHandle handle, unsigned int count, const int* values)
	{
		glUniform1iv(handle, count, values);
	}

	void ShaderProgramCommandsGL33::setUniformInt2Array(UniformHandle handle, unsigned int count, const int* values)
	{
		glUniform2iv(handle, count, values);
	}

	void ShaderProgramCommandsGL33::setUniformInt3Array(UniformHandle handle, unsigned int count, const int* values)
	{
		glUniform3iv(handle, count, values);
	}

	void ShaderProgramCommandsGL33::setUniformInt4Array(UniformHandle handle, unsigned int count, const int* values)
	{
		glUniform4iv(handle, count, values);
	}

	void ShaderProgramCommandsGL33::setUniformFloatMatrix2Array(UniformHandle handle, unsigned int count,
			bool transpose, const float* values)
	{
		glUniformMatrix2fv(handle, count, transpose, values);
	}

	void ShaderProgramCommandsGL33::setUniformFloatMatrix3Array(UniformHandle handle, unsigned int count,
			bool transpose, const float* values)
	{
		glUniformMatrix3fv(handle, count, transpose, values);
	}

	void ShaderProgramCommandsGL33::setUniformFloatMatrix4Array(UniformHandle handle, unsigned int count,
			bool transpose, const float* values)
	{
		glUniformMatrix4fv(handle, count, transpose, values);
	}

	void ShaderProgramCommandsGL33::setUniformSampler(UniformHandle handle, const int value)
	{
		glUniform1i(handle, value);
	}
}
