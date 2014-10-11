//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ISHADERPROGRAM_H_
#define ISHADERPROGRAM_H_

#include "IShader.h"

namespace dbgl
{
    class IShaderProgram
    {
	public:
	    virtual ~IShaderProgram() = default;
	    virtual void attach(IShader* shader) = 0;
	    virtual void link() = 0;
	    virtual void use() = 0;
    };
}

#endif /* ISHADERPROGRAM_H_ */
