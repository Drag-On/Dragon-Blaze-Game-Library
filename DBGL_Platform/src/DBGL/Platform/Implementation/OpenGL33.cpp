//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Implementation/OpenGL33.h"
#include "DBGL/Platform/Window/WindowGL33.h"
#include "DBGL/Platform/Monitor/MonitorGL33.h"
#include "DBGL/Platform/Time/TimerGL33.h"
#include "DBGL/Platform/Shader/ShaderGL33.h"
#include "DBGL/Platform/Shader/ShaderProgramGL33.h"
#include "DBGL/Platform/Texture/TextureGL33.h"
#include "DBGL/Platform/RenderContext/RenderContextGL33Texture.h"

namespace dbgl
{
	ShaderProgramCommandsGL33 OpenGL33::s_shaderProgramCommands{};

	OpenGL33::OpenGL33()
	{
		// Initialize window manager
		if (!glfwInit())
			throw "Unable to initialize glfw!";
	}

	OpenGL33::~OpenGL33()
	{
		// Terminate window manager
		glfwTerminate();
	}

	IWindow* OpenGL33::createWindow(std::string title, int width, int height, bool fullscreen,
			unsigned int multisampling)
	{
		if (!m_wndCreated)
		{
			m_wndCreated = true;
			return new WindowGL33 { title, width, height, fullscreen, multisampling };
		}
		else
			throw "Creation of multiple windows is currently not supported";
	}

	IMonitor* OpenGL33::createMonitor()
	{
		return new MonitorGL33 { };
	}

	ITimer* OpenGL33::createTimer()
	{
		return new TimerGL33 { };
	}

	IShader* OpenGL33::createShader(IShader::Type type, std::string code)
	{
		return new ShaderGL33 { type, code };
	}

	IShaderProgram* OpenGL33::createShaderProgram()
	{
		return new ShaderProgramGL33 { };
	}

	ITexture* OpenGL33::createTexture(ITexture::Type type)
	{
		return new TextureGL33 { type };
	}

	IMesh* OpenGL33::createMesh()
	{
		return new MeshGL33 { };
	}

	IRenderContext* OpenGL33::createRenderContext(ITexture* tex, bool createDepthBuf)
	{
		return new RenderContextGL33Texture { tex, createDepthBuf };
	}

	IShaderProgramCommands* OpenGL33::curShaderProgram()
	{
		return &s_shaderProgramCommands;
	}
}
