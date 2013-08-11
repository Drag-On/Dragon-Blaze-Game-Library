/*
 * ShaderProgram.cpp
 *
 *  Created on: 09.08.2013
 *      Author: Drag-On
 */

#include "ShaderProgram.h"

namespace DBGL
{

/**
 * Constructor
 * @param vert Code of the vertex shader
 * @param frag Code of the fragment shader
 * @param isFiles Indicates, if vert and frag contain only paths of files that contain the code
 */
ShaderProgram::ShaderProgram(const char* vert, const char* frag, bool isFiles)
{
	const char* vertCode, *fragCode;
	if (isFiles)
	{
		// Read content from file
		FILE* vertFile = fopen(vert, "rb");
		vertCode = readFile(vertFile);
		fclose(vertFile);

		FILE* fragFile = fopen(frag, "rb");
		fragCode = readFile(fragFile);
		fclose(fragFile);
	}
	else
	{
		vertCode = vert;
		fragCode = frag;
	}

	// Compile shaders
	GLuint vs, fs;
	if ((vs = compile(vertCode, GL_VERTEX_SHADER)) < 0)
	{
		if (isFiles)
		{
			LOG->error("Vertex shader from %s not compiled.", vert);
		}
		else
		{
			LOG->error("Vertex shader not compiled.");
		}
	}
	if ((fs = compile(fragCode, GL_FRAGMENT_SHADER)) < 0)
	{
		if (isFiles)
		{
			LOG->error("Fragment shader from %s not compiled.", vert);
		}
		else
		{
			LOG->error("Fragment shader not compiled.");
		}
	}

	// Link shaders
	GLint link_ok = GL_FALSE;
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vs);
	glAttachShader(_shaderProgram, fs);
	glLinkProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &link_ok);
	if (!link_ok)
	{
		LOG->error("Error while linking shaders.");
		printLog(_shaderProgram);
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_shaderProgram);
}

/**
 * @brief Returns the handle for a shader attribute by it's name
 * @param name Name of the shader attribute
 * @return The attributes id or -1 in case the attribute could not be found
 */
int ShaderProgram::getAttributeHandle(const char* name) const
{
	GLint handle = glGetAttribLocation(_shaderProgram, name);
	if (handle < 0)
	{
		LOG->warning("Attribute %s could not be found.", name);
		return -1;
	}
	return handle;
}

/**
 * @brief Returns the handle for a shader uniform by it's name
 * @param name Name of the shader uniform
 * @return The uniform id
 */
int ShaderProgram::getUniformHandle(const char* name) const
{
	GLint handle = glGetUniformLocation(_shaderProgram, name);
	if (handle < 0)
	{
		LOG->warning("Uniform %s could not be found.", name);
		return -1;
	}
	return handle;
}

/**
 * @brief Sets a uniform by it's handle
 * @param handle Uniform handle
 * @param value New value
 */
void ShaderProgram::setUniformFloat(int handle, float value) const
{
	glUniform1f(handle, value);
}

/**
 * @return OpenGL handle of the shader program
 */
GLuint ShaderProgram::getHandle() const
{
	return _shaderProgram;
}

/**
 * @brief Reads in a text file
 * @param input File to read
 * @return Content of the read file or NULL in case something went wrong
 */
char* ShaderProgram::readFile(FILE* input)
{
	// Return if no input
	if (input == NULL)
		return NULL;

	// Return if we can't seek to EOF
	if (fseek(input, 0, SEEK_END) < 0)
		return NULL;

	long size = ftell(input);

	// Return if size is not positive (i.e. an error occured)
	if (size < 0)
		return NULL;

	// Return if we can't seek to SOF
	if (fseek(input, 0, SEEK_SET) < 0)
		return NULL;

	// Make char with appropriate size
	char* content = new char[size + 1]; //(char*) malloc((size_t) size + 1);
	if (content == NULL)
		return NULL;

	// Read actual file content
	fread(content, 1, (size_t) size, input);
	if (ferror(input))
	{
		delete (content);
		return NULL;
	}

	content[size] = '\0';
	return content;
}

/**
 * @brief Prints the output of a shader compile process to LOG
 * @param object Shader to print the log for
 */
void ShaderProgram::printLog(GLuint object)
{
	GLint log_length = 0;

	// Get length of the log depending on object type
	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else
	{
		LOG->warning("Tried to print compile log for an object that is not a shader or program.");
		return;
	}

	char* log = new char[log_length]; //(char*) malloc(log_length);

	// Get actual log
	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);

	LOG->info(log);
	delete log;
}

/**
 * @brief Compiles a string as a shader and returns it
 * @attention Shader must be version 120 (100 for GLES)
 * @param code Code of the shader to compile
 * @param type Type of the shader to compile
 * @return The compiled shader or -1 in case something went wrong
 */
GLuint ShaderProgram::compile(const char* code, GLenum type)
{
	//const GLchar* source = code;

	if (code == NULL)
	{
		LOG->error("Error compiling NULL shader");
		return -1;
	}

	// Create shader object
	GLuint res = glCreateShader(type);

	// Add version to shader
	const GLchar* sources[] =
	{
#ifdef GL_ES_VERSION_2_0
		"#version 100\n"
		"#define GLES2\n"
#else
		"#version 120\n"
#endif
		,
		// GLES2 precision hints
#ifdef GL_ES_VERSION_2_0
		(type == GL_FRAGMENT_SHADER) ?
		"#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
		"precision highp float;           \n"
		"#else                            \n"
		"precision mediump float;         \n"
		"#endif                           \n"
		: ""
#else
		// Ignore hints on traditional OpenGL 2.1
		"#define lowp   \n"
		"#define mediump\n"
		"#define highp  \n"
#endif
		,
		code};

	glShaderSource(res, 3, sources, NULL);

	glCompileShader (res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE)
	{
		LOG->error("ERROR while compiling shader!");
		printLog(res);
		glDeleteShader(res);
		return -1;
	}

	return res;
}

}
/* namespace DBGL */
