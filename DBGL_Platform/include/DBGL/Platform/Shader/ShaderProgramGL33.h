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
    class ShaderProgramGL33 : public IShaderProgram
    {
	public:
	    virtual ~ShaderProgramGL33();
	    virtual void attach(IShader* shader);
	    virtual void link();
	    virtual void use();
	private:
	    GLuint m_id = 0;
    };
}

#endif /* SHADERPROGRAMGL33_H_ */
