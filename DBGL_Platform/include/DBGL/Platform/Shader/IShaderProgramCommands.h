//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_PLATFORM_SHADER_ISHADERPROGRAMCOMMANDS_H_
#define INCLUDE_DBGL_PLATFORM_SHADER_ISHADERPROGRAMCOMMANDS_H_

#include "IShaderProgram.h"

namespace dbgl
{
	/**
	 * @brief Provides commands working on the currently bound shader program.
	 */
	class IShaderProgramCommands
	{
	public:
		using AttribHandle = IShaderProgram::AttribHandle;
		using UniformHandle = IShaderProgram::UniformHandle;
		/**
		 * @brief Default destructor
		 */
		virtual ~IShaderProgramCommands() = default;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformFloat(UniformHandle handle, const float value) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformFloat2(UniformHandle handle, const float value[2]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformFloat3(UniformHandle handle, const float value[3]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformFloat4(UniformHandle handle, const float value[4]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformInt(UniformHandle handle, const int value) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformInt2(UniformHandle handle, const int value[2]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformInt3(UniformHandle handle, const int value[3]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformInt4(UniformHandle handle, const int value[4]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformBool(UniformHandle handle, const bool value) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformBool2(UniformHandle handle, const bool value[2]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformBool3(UniformHandle handle, const bool value[3]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformBool4(UniformHandle handle, const bool value[4]) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformFloatArray(UniformHandle handle, unsigned int count, const float* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformFloat2Array(UniformHandle handle, unsigned int count, const float* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformFloat3Array(UniformHandle handle, unsigned int count, const float* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformFloat4Array(UniformHandle handle, unsigned int count, const float* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformIntArray(UniformHandle handle, unsigned int count, const int* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformInt2Array(UniformHandle handle, unsigned int count, const int* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformInt3Array(UniformHandle handle, unsigned int count, const int* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformInt4Array(UniformHandle handle, unsigned int count, const int* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param transpose Indicates if the matrix should get transposed
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformFloatMatrix2Array(UniformHandle handle, unsigned int count, bool transpose,
				const float* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param transpose Indicates if the matrix should get transposed
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformFloatMatrix3Array(UniformHandle handle, unsigned int count, bool transpose,
				const float* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param count Amount of elements of the uniform array
		 * @param transpose Indicates if the matrix should get transposed
		 * @param values Pointer to array with count values
		 */
		virtual void setUniformFloatMatrix4Array(UniformHandle handle, unsigned int count, bool transpose,
				const float* values) = 0;
		/**
		 * @brief Sets a uniform by it's handle
		 * @param handle Uniform handle
		 * @param value New value
		 */
		virtual void setUniformSampler(UniformHandle handle, const int value) = 0;
	private:
	};
}

#endif /* INCLUDE_DBGL_PLATFORM_SHADER_ISHADERPROGRAMCOMMANDS_H_ */
