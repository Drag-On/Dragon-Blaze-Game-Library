//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Resources/Shader/ShaderResource.h"
#include "DBGL/Resources/Shader/ShaderProgramResource.h"
#include "DBGL/Resources/Manager/ResourceManager.h"
#include <vector>

using namespace dbgl;
using namespace std;

namespace dbgl_test_ShaderResource
{
	IWindow* g_wnd = nullptr;
	ResourceManager<ShaderResource> g_manager;
	ResourceManager<ShaderProgramResource> g_progManager;
}

using namespace dbgl_test_ShaderResource;

TEST_INITIALIZE(ShaderResource)
{
	// Init graphics context
	Platform::init<OpenGL33>();
	g_wnd = Platform::get()->createWindow();
}

TEST_TERMINATE(ShaderResource)
{
	delete g_wnd;
	Platform::destroy();
}

TEST(ShaderResource,load)
{
	auto fragHandle = g_manager.add("Assets/Shaders/CamLight.frag", IShader::Type::FRAGMENT);
	auto vertHandle = g_manager.add("Assets/Shaders/CamLight.vert", IShader::Type::VERTEX);
	ASSERT(fragHandle.isValid());
	ASSERT(vertHandle.isValid());
	g_manager.add("Trullala.fake", IShader::Type::COMPUTE);
	std::vector<std::string> shaderHandles = { "Assets/Shaders/CamLight.frag", "Assets/Shaders/CamLight.vert" };
	g_progManager.add("CamLight", shaderHandles, &g_manager);
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 3);
	ASSERT_EQ(g_progManager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_progManager.needLoad(), false);
	ASSERT_EQ(g_progManager.size(), 1);
	auto resFakeHandle = g_manager.identify("Trullala.fake");
	auto programHandle = g_progManager.identify("CamLight");
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 3);
	ASSERT_EQ(g_progManager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_progManager.needLoad(), false);
	ASSERT_EQ(g_progManager.size(), 1);
	ASSERT(resFakeHandle.isValid());
	ASSERT(programHandle.isValid());
	auto resProgram = g_progManager.request(programHandle);
	ASSERT_EQ(g_progManager.getLoadQueueSize(), 1);
	ASSERT_EQ(g_progManager.needLoad(), true);
	ASSERT_EQ(g_progManager.size(), 1);
	ASSERT(!resProgram->isLoaded());
	g_progManager.loadNext();
	ASSERT_EQ(g_progManager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_progManager.needLoad(), false);
	ASSERT_EQ(g_progManager.size(), 1);
	ASSERT(resProgram->isLoaded());
	auto resFake = g_manager.request(resFakeHandle);
	ASSERT_EQ(g_manager.getLoadQueueSize(), 1);
	ASSERT_EQ(g_manager.needLoad(), true);
	ASSERT_EQ(g_manager.size(), 3);
	ASSERT(!resFake->isLoaded());
	g_manager.loadNext();
	ASSERT(!resFake->isLoaded());
}

