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
    class ShaderProgramGL33: public IShaderProgram
    {
	public:
	    virtual ~ShaderProgramGL33();
	    virtual void attach(IShader* shader);
	    virtual void link();
	    virtual void use();
	    virtual AttribHandle getAttributeHandle(std::string name);
	    virtual UniformHandle getUniformHandle(std::string name);
	    virtual void setUniformFloat(UniformHandle handle, const float value) const;
	    virtual void setUniformFloat2(UniformHandle handle, const float value[2]) const;
	    virtual void setUniformFloat3(UniformHandle handle, const float value[3]) const;
	    virtual void setUniformFloat4(UniformHandle handle, const float value[4]) const;
	    virtual void setUniformInt(UniformHandle handle, const int value) const;
	    virtual void setUniformInt2(UniformHandle handle, const int value[2]) const;
	    virtual void setUniformInt3(UniformHandle handle, const int value[3]) const;
	    virtual void setUniformInt4(UniformHandle handle, const int value[4]) const;
	    virtual void setUniformBool(UniformHandle handle, const bool value) const;
	    virtual void setUniformBool2(UniformHandle handle, const bool value[2]) const;
	    virtual void setUniformBool3(UniformHandle handle, const bool value[3]) const;
	    virtual void setUniformBool4(UniformHandle handle, const bool value[4]) const;
	    virtual void setUniformFloatArray(UniformHandle handle, unsigned int count,
		    const float* values) const;
	    virtual void setUniformFloat2Array(UniformHandle handle, unsigned int count,
		    const float* values) const;
	    virtual void setUniformFloat3Array(UniformHandle handle, unsigned int count,
		    const float* values) const;
	    virtual void setUniformFloat4Array(UniformHandle handle, unsigned int count,
		    const float* values) const;
	    virtual void setUniformIntArray(UniformHandle handle, unsigned int count,
		    const int* values) const;
	    virtual void setUniformInt2Array(UniformHandle handle, unsigned int count,
		    const int* values) const;
	    virtual void setUniformInt3Array(UniformHandle handle, unsigned int count,
		    const int* values) const;
	    virtual void setUniformInt4Array(UniformHandle handle, unsigned int count,
		    const int* values) const;
	    virtual void setUniformFloatMatrix2Array(UniformHandle handle, unsigned int count, bool transpose,
		    const float* values) const;
	    virtual void setUniformFloatMatrix3Array(UniformHandle handle, unsigned int count, bool transpose,
		    const float* values) const;
	    virtual void setUniformFloatMatrix4Array(UniformHandle handle, unsigned int count, bool transpose,
		    const float* values) const;
	    virtual void setUniformSampler(UniformHandle handle, const int value) const;

	private:
	    GLuint m_id;
    };
}

#endif /* SHADERPROGRAMGL33_H_ */
