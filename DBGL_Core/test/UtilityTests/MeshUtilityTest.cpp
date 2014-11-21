//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Platform.h"
#include "DBGL/PLatform/Implementation/OpenGL33.h"
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Utility/MeshUtility.h"

using namespace dbgl;
using namespace std;

namespace dbgl_test_MeshUtility
{
    IWindow* g_wnd = nullptr;
}

TEST_INITIALIZE(MeshUtility)
{
    Platform::init<OpenGL33>();
    dbgl_test_MeshUtility::g_wnd = Platform::get()->createWindow();
}

TEST_TERMINATE(MeshUtility)
{
    delete dbgl_test_MeshUtility::g_wnd;
    Platform::destroy();
}

TEST(MeshUtility,generateNormals)
{
    auto mesh = MeshUtility::createTriangle(false);
    auto mesh2 = MeshUtility::createTriangle(false);
    mesh2->normals().clear();
    MeshUtility::generateNormals(mesh2);
    ASSERT(mesh2->normals().size() == mesh->normals().size());
    for(unsigned int i = 0; i < mesh2->normals().size(); i++)
    {
	ASSERT(mesh2->normals()[i].x == mesh->normals()[i].x);
	ASSERT(mesh2->normals()[i].y == mesh->normals()[i].y);
	ASSERT(mesh2->normals()[i].z == mesh->normals()[i].z);
    }
}

TEST(MeshUtility,generateTangentBase)
{
    auto mesh = MeshUtility::createTriangle(false);
    MeshUtility::generateTangentBase(mesh);
    ASSERT(mesh->normals().size() == mesh->tangents().size());
    ASSERT(mesh->normals().size() == mesh->bitangents().size());
    for(unsigned int i = 0; i < mesh->normals().size(); i++)
    {
	Vec3f normal = mesh->normals()[i];
	Vec3f tangent = mesh->tangents()[i];
	Vec3f bitangent = mesh->bitangents()[i];
	ASSERT(tangent * normal == 0);
	ASSERT(bitangent * normal == 0);
    }
}

TEST(MeshUtility,reverseNormals)
{
    auto mesh = MeshUtility::createTriangle(false);
    auto mesh2 = MeshUtility::createTriangle(false);
    MeshUtility::reverseNormals(mesh2);
    ASSERT(mesh2->normals().size() == mesh->normals().size());
    for(unsigned int i = 0; i < mesh2->normals().size(); i++)
    {
	Vec3f normal1 = mesh->normals()[i];
	Vec3f normal2 = mesh2->normals()[i];
	ASSERT(normal1 == - normal2);
    }
}
