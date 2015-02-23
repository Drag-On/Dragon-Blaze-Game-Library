//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Mesh/IMesh.h"
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Math/Utility.h"
#include "DBGL/Resources/Mesh/MeshUtility.h"
#include "DBGL/Resources/Mesh/MeshIO.h"

using namespace dbgl;
using namespace std;

namespace dbgl_test_MeshIO
{
	IWindow* g_wnd = nullptr;
}

TEST_INITIALIZE(MeshIO)
{
	// Init graphics context
	Platform::init<OpenGL33>();
	dbgl_test_MeshIO::g_wnd = Platform::get()->createWindow();
}

TEST_TERMINATE(MeshIO)
{
	delete dbgl_test_MeshIO::g_wnd;
	Platform::destroy();
}

TEST(MeshIO,obj)
{
	// MeshIO object
	MeshIO io { };
	if (!io.addFormat("plugins/Mesh/OBJ/libDBGL_OBJ." + Library::getFileExtension()))
		FAIL();
	else
	{
		auto mesh = io.load("Assets/Meshes/Cube.obj");
		ASSERT(mesh);
		ASSERT(mesh->vertices().size() == 6 * 6);
		ASSERT(mesh->normals().size() == 0);
		ASSERT(mesh->uvs().size() == 6 * 6);
		ASSERT(mesh->tangents().size() == 0);
		ASSERT(mesh->bitangents().size() == 0);
		ASSERT(mesh->indices().size() == 6 * 6);
	}
}

