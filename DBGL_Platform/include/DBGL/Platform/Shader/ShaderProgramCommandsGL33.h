//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_PLATFORM_SHADER_SHADERPROGRAMCOMMANDSGL33_H_
#define INCLUDE_DBGL_PLATFORM_SHADER_SHADERPROGRAMCOMMANDSGL33_H_

#include <GL/glew.h>
#include "IShaderProgramCommands.h"

namespace dbgl
{
	/**
	 * @brief OpenGL 3.3 implementation of the shader program commands
	 */
	class ShaderProgramCommandsGL33: public IShaderProgramCommands
	{
	public:
		/**
		 * @brief Default destructor
		 */
		virtual ~ShaderProgramCommandsGL33() = default;
		virtual void setUniformFloat(UniformHandle handle, const float value);
		virtual void setUniformFloat2(UniformHandle handle, const float value[2]);
		virtual void setUniformFloat3(UniformHandle handle, const float value[3]);
		virtual void setUniformFloat4(UniformHandle handle, const float value[4]);
		virtual void setUniformInt(UniformHandle handle, const int value);
		virtual void setUniformInt2(UniformHandle handle, const int value[2]);
		virtual void setUniformInt3(UniformHandle handle, const int value[3]);
		virtual void setUniformInt4(UniformHandle handle, const int value[4]);
		virtual void setUniformBool(UniformHandle handle, const bool value);
		virtual void setUniformBool2(UniformHandle handle, const bool value[2]);
		virtual void setUniformBool3(UniformHandle handle, const bool value[3]);
		virtual void setUniformBool4(UniformHandle handle, const bool value[4]);
		virtual void setUniformFloatArray(UniformHandle handle, unsigned int count, const float* values);
		virtual void setUniformFloat2Array(UniformHandle handle, unsigned int count, const float* values);
		virtual void setUniformFloat3Array(UniformHandle handle, unsigned int count, const float* values);
		virtual void setUniformFloat4Array(UniformHandle handle, unsigned int count, const float* values);
		virtual void setUniformIntArray(UniformHandle handle, unsigned int count, const int* values);
		virtual void setUniformInt2Array(UniformHandle handle, unsigned int count, const int* values);
		virtual void setUniformInt3Array(UniformHandle handle, unsigned int count, const int* values);
		virtual void setUniformInt4Array(UniformHandle handle, unsigned int count, const int* values);
		virtual void setUniformFloatMatrix2Array(UniformHandle handle, unsigned int count, bool transpose,
				const float* values);
		virtual void setUniformFloatMatrix3Array(UniformHandle handle, unsigned int count, bool transpose,
				const float* values);
		virtual void setUniformFloatMatrix4Array(UniformHandle handle, unsigned int count, bool transpose,
				const float* values);
		virtual void setUniformSampler(UniformHandle handle, const int value);
	};
}

#endif /* INCLUDE_DBGL_PLATFORM_SHADER_SHADERPROGRAMCOMMANDSGL33_H_ */
