//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef OPENGL33_H_
#define OPENGL33_H_

#include "DBGL/Platform/Platform.h"

namespace dbgl
{
    class OpenGL33: public Platform::IType
    {
	public:
	    OpenGL33();
	    virtual ~OpenGL33();
	    virtual IWindow* createWindow(std::string title = "Dragon Blaze Game Library", int width = 800,
		    int height = 600, bool fullscreen = false, unsigned int multisampling = 2);
	    virtual IMonitor* createMonitor();
	    virtual ITimer* createTimer();
	    virtual IShader* createShader(IShader::Type type, std::string code);
	    virtual IShaderProgram* createShaderProgram();
	    virtual ITexture* createTexture(ITexture::Type type);
	    virtual IMesh* createMesh();
	    virtual IRenderContext* createRenderContext(ITexture* tex, bool createDepthBuf = false);
    };
}

#endif /* OPENGL33_H_ */
