//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/ShaderProgram.h"

namespace dbgl
{
    /**
     * Constructor
     * @param vert Code of the vertex shader
     * @param frag Code of the fragment shader
     * @param isFiles Indicates, if vert and frag contain only paths of files that contain the code
     */
    ShaderProgram::ShaderProgram(const char* vert, const char* frag,
	    bool isFiles)
    {
	LOG->info("Creating shader program...");
	std::string vertCode, fragCode;
	if (isFiles)
	{
	    // Read vertex shader code from file
	    vertCode = readFile(vert);

	    // Read fragment shader code from file
	    fragCode = readFile(frag);
	}
	else
	{
	    vertCode = vert;
	    fragCode = frag;
	}

	// Compile shaders
	GLuint vsId, fsId;
	const char* vertFileName = isFiles ? vert : "";
	const char* fragFileName = isFiles ? frag : "";
	vsId = compile(vertCode.c_str(), GL_VERTEX_SHADER, vertFileName);
	fsId = compile(fragCode.c_str(), GL_FRAGMENT_SHADER, fragFileName);

	// Link shaders
	GLint linkOk = GL_FALSE;
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vsId);
	glAttachShader(_shaderProgram, fsId);
	glLinkProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &linkOk);
	if (!linkOk)
	    LOG->error("Error while linking shaders.");
	printLog(_shaderProgram, linkOk);

	// Delete vertex- and fragment shader objects again
	glDeleteShader(vsId);
	glDeleteShader(fsId);
    }

    ShaderProgram::~ShaderProgram()
    {
	glDeleteProgram(_shaderProgram);
    }

    /**
     * @brief Sets this shader as the current one
     */
    void ShaderProgram::use()
    {
	glUseProgram(_shaderProgram);
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
     * @brief Checks, if an attribute with the specified name exists
     * @param name Name of the shader attribute
     * @return True in case the attribute exists, otherwise false
     */
    bool ShaderProgram::checkAttributeExists(const char* name) const
    {
	return glGetAttribLocation(_shaderProgram, name) >= 0;
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
     * @brief Checks, if a uniform with the specified name exists
     * @param name Name of the shader uniform
     * @return True in case the uniform exists, otherwise false
     */
    bool ShaderProgram::checkUniformExists(const char* name) const
    {
	return glGetUniformLocation(_shaderProgram, name) >= 0;
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
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformFloat2(int handle, float value[2]) const
    {
	glUniform2f(handle, value[0], value[1]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformFloat3(int handle, float value[3]) const
    {
	glUniform3f(handle, value[0], value[1], value[2]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformFloat4(int handle, float value[4]) const
    {
	glUniform4f(handle, value[0], value[1], value[2], value[3]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformInt(int handle, int value) const
    {
	glUniform1i(handle, value);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformInt2(int handle, int value[2]) const
    {
	glUniform2i(handle, value[0], value[1]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformInt3(int handle, int value[3]) const
    {
	glUniform3i(handle, value[0], value[1], value[2]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformInt4(int handle, int value[4]) const
    {
	glUniform4i(handle, value[0], value[1], value[2], value[3]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformBool(int handle, bool value) const
    {
	glUniform1i(handle, value);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformBool2(int handle, bool value[2]) const
    {
	glUniform2i(handle, value[0], value[1]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformBool3(int handle, bool value[3]) const
    {
	glUniform3i(handle, value[0], value[1], value[2]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformBool4(int handle, bool value[4]) const
    {
	glUniform4i(handle, value[0], value[1], value[2], value[3]);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformFloatArray(int handle, unsigned int count,
	    float* values) const
    {
	glUniform1fv(handle, count, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformFloat2Array(int handle, unsigned int count,
	    float* values) const
    {
	glUniform2fv(handle, count, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformFloat3Array(int handle, unsigned int count,
	    float* values) const
    {
	glUniform3fv(handle, count, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformFloat4Array(int handle, unsigned int count,
	    float* values) const
    {
	glUniform4fv(handle, count, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformIntArray(int handle, unsigned int count,
	    int* values) const
    {
	glUniform1iv(handle, count, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformInt2Array(int handle, unsigned int count,
	    int* values) const
    {
	glUniform2iv(handle, count, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformInt3Array(int handle, unsigned int count,
	    int* values) const
    {
	glUniform3iv(handle, count, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformInt4Array(int handle, unsigned int count,
	    int* values) const
    {
	glUniform4iv(handle, count, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformFloatMatrix2Array(int handle,
	    unsigned int count, bool transpose, float* values) const
    {
	glUniformMatrix2fv(handle, count, transpose, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformFloatMatrix3Array(int handle,
	    unsigned int count, bool transpose, float* values) const
    {
	glUniformMatrix3fv(handle, count, transpose, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param count Amount of elements of the uniform array
     * @param values Pointer to array with count values
     */
    void ShaderProgram::setUniformFloatMatrix4Array(int handle,
	    unsigned int count, bool transpose, float* values) const
    {
	glUniformMatrix4fv(handle, count, transpose, values);
    }

    /**
     * @brief Sets a uniform by it's handle
     * @param handle Uniform handle
     * @param value New value
     */
    void ShaderProgram::setUniformSampler(int handle, int value) const
    {
	glUniform1i(handle, value);
    }

    /**
     * @return OpenGL handle of the shader program
     */
    GLuint ShaderProgram::getHandle() const
    {
	return _shaderProgram;
    }

    ShaderProgram* ShaderProgram::createSimpleShader()
    {
	const char* vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec4 vertexPos;\n"
		"void main(){\n"
		"gl_Position = vertexPos;\n"
		"}";
	const char* fragmentShader = "#version 330 core\n"
		"out vec4 color;\n"
		"void main(){\n"
		"color = vec4(1,0,0,1);\n"
		"}";
	return new ShaderProgram(vertexShader, fragmentShader, false);
    }

    /**
     * @brief Reads in a text file
     * @param path Path of the file to read
     * @return Content of the read file
     */
    std::string ShaderProgram::readFile(const char* path)
    {
	std::string code;
	std::ifstream inStream(path, std::ios::in);
	if (inStream.is_open())
	{
	    std::string line = "";
	    while (getline(inStream, line))
		code += "\n" + line;
	    inStream.close();
	}
	else
	    LOG->error("Unable to open %s.", path);
	return code;
    }

    /**
     * @brief Prints the output of a shader compile process to LOG
     * @param object Shader to print the log for
     * @param ok Indicates if compilation was successful
     */
    void ShaderProgram::printLog(GLuint object, GLint ok)
    {
	GLint logLength = 0;

	// Get length of the log depending on object type
	if (glIsShader(object))
	    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &logLength);
	else if (glIsProgram(object))
	    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &logLength);
	else
	{
	    LOG->warning(
		    "Tried to print compile log for an object that is not a shader or program.");
	    return;
	}
	if (logLength > 0)
	{
	    char* msg = new char[logLength];

	    // Get actual log
	    if (glIsShader(object))
		glGetShaderInfoLog(object, logLength, NULL, msg);
	    else if (glIsProgram(object))
		glGetProgramInfoLog(object, logLength, NULL, msg);

	    if(msg[logLength-2] == '\n')
	    	msg[logLength-2] = 0;

	    if (ok)
		LOG->info(msg);
	    else
		LOG->error(msg);
	    delete (msg);
	}
    }

    /**
     * @brief Compiles a string as a shader and returns it
     * @attention Shader must be version 120 (100 for GLES)
     * @param code Code of the shader to compile
     * @param type Type of the shader to compile
     * @param fileName Name of the file if the shader is compiled from a file
     * @return The compiled shader or -1 in case something went wrong
     */
    GLuint ShaderProgram::compile(const char* code, GLenum type,
	    const char* fileName)
    {
	if (code == NULL)
	{
	    LOG->error("Error compiling NULL shader");
	return -1;
    }

    // Create shader object
    GLuint id = glCreateShader(type);

    // Compile
    glShaderSource(id, 1, &code , NULL);
    glCompileShader(id);

    // Check if everything went right
    GLint result = GL_FALSE;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    LOG->error("Error while compiling shader %s", fileName);
    printLog(id, result);
    return id;
}

}
