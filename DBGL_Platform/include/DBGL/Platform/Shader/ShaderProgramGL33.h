//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SHADERPROGRAMGL33_H_
#define SHADERPROGRAMGL33_H_

#include "IShaderProgram.h"
#include "ShaderGL33.h"

namespace dbgl
{
    /**
     * @brief OpenGL 3.3 implementation of the shader program class
     */
    class ShaderProgramGL33: public IShaderProgram
    {
	public:
	    /**
	     * @brief Constructor
	     */
	    ShaderProgramGL33();
	    virtual ~ShaderProgramGL33();
	    virtual void attach(IShader* shader);
	    virtual void link();
	    virtual void use();
	    virtual AttribHandle getAttributeHandle(std::string name) const;
	    virtual UniformHandle getUniformHandle(std::string name) const;
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

	    /**
	     * @return Internal shader program handle
	     */
	    GLuint getHandle() const;

	private:
	    GLuint m_id;

	    static GLuint s_activeProgram;

	    void useInternal() const;
    };
}

#endif /* SHADERPROGRAMGL33_H_ */
