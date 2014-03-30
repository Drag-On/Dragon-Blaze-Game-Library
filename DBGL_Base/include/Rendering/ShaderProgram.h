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

#include <map>
#include <GL/glew.h>
#include <stdlib.h>
#include <string.h>
#include "System/Log/Log.h"

namespace dbgl
{
    /**
     * @brief Represents a shader program consisting of vertex- and fragment shader
     * 	      which can be used to render objects to screen. Includes methods to
     * 	      compile shaders.
     */
    class ShaderProgram
    {
	public:
	    enum Uniform
	    {
		MODEL,
		VIEW,
		PROJECTION,
		MV,
		MVP,
		ITM,
		ITV,
		ITMV,
		TEX_DIFFUSE,
		TEX_NORMAL,
		TEX_SPECULAR,
		COLOR,
		BOGUS,
	    };

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
	    void use() const;

	    /**
	     * @brief Returns the handle for a shader attribute by it's name
	     * @param name Name of the shader attribute
	     * @return The attributes id
	     */
	    GLint getAttributeHandle(const char* name) const;

	    /**
	     * @brief Returns the handle for a shader uniform by it's name
	     * @param name Name of the shader uniform
	     * @return The uniform id
	     */
	    GLint getUniformHandle(const char* name) const;

	    /**
	     * @brief Binds a texture to a certain texture location
	     * @param texLocation Texture location, e.g. GL_TEXTURE0
	     * @param texType Type of the texture, e.g. GL_TEXTURE_2D
	     * @param texHandle Handle of the texture
	     */
	    void bindTexture(int texLocation, int texType, GLuint texHandle) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformFloat(GLint handle, const float value) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformFloat2(GLint handle, const float value[2]) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformFloat3(GLint handle, const float value[3]) const;


	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformFloat4(GLint handle, const float value[4]) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformInt(GLint handle, const int value) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformInt2(GLint handle, const int value[2]) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformInt3(GLint handle, const int value[3]) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformInt4(GLint handle, const int value[4]) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformBool(GLint handle, const bool value) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformBool2(GLint handle, const bool value[2]) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformBool3(GLint handle, const bool value[3]) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformBool4(GLint handle, const bool value[4]) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformFloatArray(GLint handle, unsigned int count,
		    const float* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformFloat2Array(GLint handle, unsigned int count,
		    const float* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformFloat3Array(GLint handle, unsigned int count,
		    const float* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformFloat4Array(GLint handle, unsigned int count,
		    const float* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformIntArray(GLint handle, unsigned int count,
		    const int* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformInt2Array(GLint handle, unsigned int count,
		    const int* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformInt3Array(GLint handle, unsigned int count,
		    const int* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformInt4Array(GLint handle, unsigned int count,
		    const int* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformFloatMatrix2Array(GLint handle, unsigned int count,
		    bool transpose, const float* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformFloatMatrix3Array(GLint handle, unsigned int count,
		    bool transpose, const float* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param count Amount of elements of the uniform array
	     * @param values Pointer to array with count values
	     */
	    void setUniformFloatMatrix4Array(GLint handle, unsigned int count,
		    bool transpose, const float* values) const;

	    /**
	     * @brief Sets a uniform by it's handle
	     * @param handle Uniform handle
	     * @param value New value
	     */
	    void setUniformSampler(GLint handle, const int value) const;

	    /**
	     * @return OpenGL handle of the shader program
	     */
	    GLuint getHandle() const;

	    /**
	     * @brief Returns the handle of a default uniform or -1 if that uniform
	     * 	      is not present in the shader
	     * @param uniform Uniform to get the handle for
	     * @return The uniform handle or -1 if it is not present
	     */
	    GLint getDefaultUniformHandle(Uniform uniform) const;

	    /**
	     * @brief Creates a very simple shader program, mainly intended
	     * 	      for testing purposes
	     * @warning The generated memory needs to be deallocated manually!
	     * @return The newly created shader program
	     */
	    static ShaderProgram* createSimpleShader();

	private:
	    GLuint _shaderProgram; // GL shader program handle
	    std::map<Uniform, GLint> _uniformHandles;

	    static std::map<Uniform, std::string> uniformNames;

	    /**
	     * @brief Checks for common uniform names in the shader to save their
	     * 	      handles for later use
	     */
	    void checkUniforms();

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
