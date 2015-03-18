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
#include "DBGL/Resources/Mesh/MeshResource.h"
#include "DBGL/Resources/Manager/ResourceManager.h"

using namespace dbgl;
using namespace std;

namespace dbgl_test_MeshResource
{
	IWindow* g_wnd = nullptr;
	ResourceManager<MeshResource> g_manager;
}

using namespace dbgl_test_MeshResource;

TEST_INITIALIZE(MeshResource)
{
	// Init graphics context
	Platform::init<OpenGL33>();
	dbgl_test_MeshResource::g_wnd = Platform::get()->createWindow();
	if (!MeshResource::loader().addFormat("plugins/Mesh/OBJ/libDBGL_OBJ." + Library::getFileExtension()))
		FAIL();
}

TEST_TERMINATE(MeshResource)
{
	delete dbgl_test_MeshResource::g_wnd;
	Platform::destroy();
}

TEST(MeshResource,load)
{
	g_manager.add("Assets/Meshes/Cube.obj");
	g_manager.add("Assets/Meshes/Pillar.obj");
	g_manager.add("Trullala.fake");
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 3);
	auto resCubeHandle = g_manager.identify("Assets/Meshes/Cube.obj");
	auto resPillarHandle = g_manager.identify("Assets/Meshes/Pillar.obj");
	auto resFakeHandle = g_manager.identify("Trullala.fake");
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 3);
	ASSERT(resCubeHandle.isValid());
	ASSERT(resPillarHandle.isValid());
	auto resCube = g_manager.request(resCubeHandle);
	ASSERT_EQ(g_manager.getLoadQueueSize(), 1);
	ASSERT_EQ(g_manager.needLoad(), true);
	ASSERT_EQ(g_manager.size(), 3);
	ASSERT(!resCube->isLoaded());
	g_manager.loadNext();
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 3);
	ASSERT(resCube->isLoaded());
	auto resFake = g_manager.request(resFakeHandle);
	ASSERT_EQ(g_manager.getLoadQueueSize(), 1);
	ASSERT_EQ(g_manager.needLoad(), true);
	ASSERT_EQ(g_manager.size(), 3);
	ASSERT(!resFake->isLoaded());
	g_manager.loadNext();
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 3);
	ASSERT(resFake->isLoaded());
}

