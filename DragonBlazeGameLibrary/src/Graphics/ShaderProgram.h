/*
 * ShaderProgram.h
 *
 *  Created on: 09.08.2013
 *      Author: Drag-On
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <stdio.h>
#include <GL/glew.h>
#include "../Main/Log.h"

namespace DBGL
{
/**
 * @brief Represents a shader program consisting of vertex- and fragment shader
 * 		  which can be used to render objects to screen. Includes methods to
 * 		  compile shaders.
 */
class ShaderProgram
{
public:
	/**
	 * Constructor
	 * @param vert Code of the vertex shader
	 * @param frag Code of the fragment shader
	 * @param isFiles Indicates, if vert and frag contain only paths of files that contain the code
	 */
	ShaderProgram(const char* vert, const char* frag, bool isFiles = false);

	/**
	 * Destructor
	 */
	virtual ~ShaderProgram();

	/**
	 * @brief Returns the handle for a shader attribute by it's name
	 * @param name Name of the shader attribute
	 * @return The attributes id
	 */
	int getAttributeHandle(const char* name) const;

	/**
	 * @brief Returns the handle for a shader uniform by it's name
	 * @param name Name of the shader uniform
	 * @return The uniform id
	 */
	int getUniformHandle(const char* name) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformFloat(int handle, float value) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformFloat2(int handle, float value[2]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformFloat3(int handle, float value[3]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformFloat4(int handle, float value[4]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformInt(int handle, int value) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformInt2(int handle, int value[2]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformInt3(int handle, int value[3]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformInt4(int handle, int value[4]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformBool(int handle, bool value) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformBool2(int handle, bool value[2]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformBool3(int handle, bool value[3]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformBool4(int handle, bool value[4]) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformFloatArray(int handle, unsigned int count,
			float* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformFloat2Array(int handle, unsigned int count,
			float* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformFloat3Array(int handle, unsigned int count,
			float* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformFloat4Array(int handle, unsigned int count,
			float* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformIntArray(int handle, unsigned int count, int* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformInt2Array(int handle, unsigned int count, int* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformInt3Array(int handle, unsigned int count, int* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformInt4Array(int handle, unsigned int count, int* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformFloatMatrix2Array(int handle, unsigned int count,
			bool transpose, float* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformFloatMatrix3Array(int handle, unsigned int count,
			bool transpose, float* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param count Amount of elements of the uniform array
	 * @param values Pointer to array with count values
	 */
	void setUniformFloatMatrix4Array(int handle, unsigned int count,
			bool transpose, float* values) const;

	/**
	 * @brief Sets a uniform by it's handle
	 * @param handle Uniform handle
	 * @param value New value
	 */
	void setUniformSampler(int handle, int value) const;

	/**
	 * @return OpenGL handle of the shader program
	 */
	GLuint getHandle() const;

private:
	GLuint _shaderProgram; // GL shader program handle

	/**
	 * @brief Reads in a text file
	 * @param input File to read
	 * @return Content of the read file
	 */
	char* readFile(FILE* input);

	/**
	 * @brief Prints the output of a shader compile process to LOG
	 * @param object Shader to print the log for
	 */
	void printLog(GLuint object);

	/**
	 * @brief Compiles a string as a shader and returns it
	 * @param code Code of the shader to compile
	 * @param type Type of the shader to compile
	 * @return The compiled shader or 0 in case something went wrong
	 */
	GLuint compile(const char* code, GLenum type);
};

} /* namespace DBGL */
#endif /* SHADERPROGRAM_H_ */
