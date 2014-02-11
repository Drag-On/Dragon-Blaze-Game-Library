//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <GL/glew.h>
#include <stdlib.h>
#include <string.h>
#include "Log/Log.h"

namespace dbgl
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
	    ShaderProgram(const char* vert, const char* frag, bool isFiles =
		    true);

	    /**
	     * Destructor
	     */
	    virtual ~ShaderProgram();

	    /**
	     * @brief Sets this shader as the current one
	     */
	    void use();

	    /**
	     * @brief Returns the handle for a shader attribute by it's name
	     * @param name Name of the shader attribute
	     * @return The attributes id
	     */
	    int getAttributeHandle(const char* name) const;

	    /**
	     * @brief Checks, if an attribute with the specified name exists
	     * @param name Name of the shader attribute
	     * @return True in case the attribute exists, otherwise false
	     */
	    bool checkAttributeExists(const char* name) const;

	    /**
	     * @brief Returns the handle for a shader uniform by it's name
	     * @param name Name of the shader uniform
	     * @return The uniform id
	     */
	    int getUniformHandle(const char* name) const;

	    /**
	     * @brief Checks, if a uniform with the specified name exists
	     * @param name Name of the shader uniform
	     * @return True in case the uniform exists, otherwise false
	     */
	    bool checkUniformExists(const char* name) const;

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
	    void setUniformIntArray(int handle, unsigned int count,
		    int* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformInt2Array(int handle, unsigned int count,
		    int* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformInt3Array(int handle, unsigned int count,
		    int* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformInt4Array(int handle, unsigned int count,
		    int* values) const;

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

	    /**
	     * @brief Creates a very simple shader program, mainly intended
	     * 	      for testing purposes
	     * @warning The generated memory needs to be deallocated manually!
	     * @return The newly created shader program
	     */
	    static ShaderProgram* createSimpleShader();

	private:
	    GLuint _shaderProgram; // GL shader program handle

	    /**
	     * @brief Reads in a text file
	     * @param path Path of the file to read
	     * @return Content of the read file
	     */
	    std::string readFile(const char* path);

	    /**
	     * @brief Prints the output of a shader compile process to LOG
	     * @param object Shader to print the log for
	     * @param ok Indicates if compilation was successful
	     */
	    void printLog(GLuint object, GLint ok);

	    /**
	     * @brief Compiles a string as a shader and returns it
	     * @param code Code of the shader to compile
	     * @param type Type of the shader to compile
	     * @param fileName Name of the file if the shader is compiled from a file
	     * @return The compiled shader or 0 in case something went wrong
	     */
	    GLuint compile(const char* code, GLenum type, const char* fileName =
		    "");
    };
}

#endif /* SHADERPROGRAM_H_ */
