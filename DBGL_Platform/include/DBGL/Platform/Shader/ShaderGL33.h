//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SHADERGL33_H_
#define SHADERGL33_H_

#include <stdexcept>
#include <GL/glew.h>
#include "IShader.h"

namespace dbgl
{
    class ShaderGL33 : public IShader
    {
	public:
	    ShaderGL33(Type type, std::string code);
	    virtual ~ShaderGL33();
	    virtual void compile();
	private:
	    Type m_type;
	    std::string m_code;
	    GLuint m_id = 0;

	    GLenum shaderType2GL(Type type);

	    friend class ShaderProgramGL33;
    };
}

#endif /* SHADERGL33_H_ */
