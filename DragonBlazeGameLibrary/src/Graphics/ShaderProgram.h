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
