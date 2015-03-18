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
#include "DBGL/Resources/Texture/TextureResource.h"
#include "DBGL/Resources/Manager/ResourceManager.h"

using namespace dbgl;
using namespace std;

namespace dbgl_test_TextureResource
{
	IWindow* g_wnd = nullptr;
	ResourceManager<TextureResource> g_manager;
}

using namespace dbgl_test_TextureResource;

TEST_INITIALIZE(TextureResource)
{
	// Init graphics context
	Platform::init<OpenGL33>();
	dbgl_test_TextureResource::g_wnd = Platform::get()->createWindow();
	if (!TextureResource::loader().addFormat("plugins/Texture/BMP/libDBGL_BMP." + Library::getFileExtension()))
		FAIL();
	if (!TextureResource::loader().addFormat("plugins/Texture/TGA/libDBGL_TGA." + Library::getFileExtension()))
		FAIL();
	if (!TextureResource::loader().addFormat("plugins/Texture/DDS/libDBGL_DDS." + Library::getFileExtension()))
		FAIL();
}

TEST_TERMINATE(TextureResource)
{
	delete dbgl_test_TextureResource::g_wnd;
	Platform::destroy();
}

TEST(TextureResource,load)
{
	g_manager.add("Assets/Textures/Bricks01.DDS");
	g_manager.add("Assets/Textures/Bricks01_normal.tga");
	g_manager.add("Assets/Textures/test2x2.bmp");
	g_manager.add("Trullala.fake");
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 4);
	auto resBricksHandle = g_manager.identify("Assets/Textures/Bricks01.DDS");
	auto resBricksNormHandle = g_manager.identify("Assets/Textures/Bricks01_normal.tga");
	auto resTestHandle = g_manager.identify("Assets/Textures/test2x2.bmp");
	auto resFakeHandle = g_manager.identify("Trullala.fake");
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 4);
	ASSERT(resBricksHandle.isValid());
	ASSERT(resBricksNormHandle.isValid());
	ASSERT(resTestHandle.isValid());
	ASSERT(resFakeHandle.isValid());
	auto resBricks = g_manager.request(resBricksHandle);
	auto resTest = g_manager.request(resTestHandle);
	ASSERT_EQ(g_manager.getLoadQueueSize(), 2);
	ASSERT_EQ(g_manager.needLoad(), true);
	ASSERT_EQ(g_manager.size(), 4);
	ASSERT(!resBricks->isLoaded());
	ASSERT(!resTest->isLoaded());
	g_manager.loadNext();
	ASSERT_EQ(g_manager.getLoadQueueSize(), 1);
	ASSERT_EQ(g_manager.needLoad(), true);
	ASSERT_EQ(g_manager.size(), 4);
	ASSERT(resBricks->isLoaded());
	ASSERT(!resTest->isLoaded());
	g_manager.loadNext();
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 4);
	ASSERT(resBricks->isLoaded());
	ASSERT(resTest->isLoaded());
	auto resFake = g_manager.request(resFakeHandle);
	ASSERT_EQ(g_manager.getLoadQueueSize(), 1);
	ASSERT_EQ(g_manager.needLoad(), true);
	ASSERT_EQ(g_manager.size(), 4);
	ASSERT(!resFake->isLoaded());
	g_manager.loadNext();
	ASSERT_EQ(g_manager.getLoadQueueSize(), 0);
	ASSERT_EQ(g_manager.needLoad(), false);
	ASSERT_EQ(g_manager.size(), 4);
	ASSERT(resFake->isLoaded());
}

