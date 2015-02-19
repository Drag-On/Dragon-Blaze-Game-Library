//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef OPENGL33_H_
#define OPENGL33_H_

#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Shader/ShaderProgramCommandsGL33.h"
#include "DBGL/Platform/Texture/TextureCommandsGL33.h"

namespace dbgl
{
	/**
	 * @brief OpenGL 3.3 implementation of the platform toolkit
	 */
	class OpenGL33: public Platform::IImplementation
	{
	public:
		/**
		 * @brief Constructor
		 */
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
		virtual IRenderContext* createRenderContext(unsigned int width, unsigned int height, bool createDepthBuf = false);
		virtual IShaderProgramCommands* curShaderProgram();
		virtual ITextureCommands* curTexture();
	private:
		bool m_wndCreated = false;
		static ShaderProgramCommandsGL33 s_shaderProgramCommands;
		static TextureCommandsGL33 s_textureCommands;
	};
}

#endif /* OPENGL33_H_ */
