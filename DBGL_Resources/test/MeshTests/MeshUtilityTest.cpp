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
#include "DBGL/Resources/Mesh/MeshUtility.h"

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
	ASSERT(mesh2->normals()[i].x() == mesh->normals()[i].x());
	ASSERT(mesh2->normals()[i].y() == mesh->normals()[i].y());
	ASSERT(mesh2->normals()[i].z() == mesh->normals()[i].z());
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

TEST(MeshUtility,optimizeMesh)
{
    auto cube = MeshUtility::createCube(false);
    IMesh* copy{cube};
    ASSERT_EQ(copy->indices().size(), 6 * 6);
    ASSERT_EQ(copy->vertices().size(), 4 * 6);
    ASSERT_EQ(copy->normals().size(), 4 * 6);
    ASSERT_EQ(copy->uvs().size(), 4 * 6);
    MeshUtility::optimize(copy, 0); // Angle of 0°
    ASSERT_EQ(copy->indices().size(), 6 * 6);
    ASSERT_EQ(copy->vertices().size(), 4 * 6);
    ASSERT_EQ(copy->normals().size(), 4 * 6);
    ASSERT_EQ(copy->uvs().size(), 4 * 6);
    copy->uvs().clear(); // Don't use uvs
    ASSERT_EQ(copy->uvs().size(), 0);
    MeshUtility::optimize(copy, 0); // Angle of 0°
    ASSERT_EQ(copy->indices().size(), 6 * 6);
    ASSERT_EQ(copy->vertices().size(), 4 * 6);
    ASSERT_EQ(copy->normals().size(), 4 * 6);
    ASSERT_EQ(copy->uvs().size(), 0);
    MeshUtility::optimize(copy, 1.74532925f); // Angle of 100°
    ASSERT_EQ(copy->indices().size(), 6 * 6);
    ASSERT_EQ(copy->vertices().size(), 8);
    ASSERT_EQ(copy->normals().size(), 8);
    ASSERT_EQ(copy->uvs().size(), 0);
}
