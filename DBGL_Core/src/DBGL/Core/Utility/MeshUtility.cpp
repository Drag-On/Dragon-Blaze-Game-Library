//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Utility/MeshUtility.h"

namespace dbgl
{
    IMesh* MeshUtility::createTriangle(bool sendToGPU, IMesh::Usage usage)
    {
	auto mesh = Platform::get()->createMesh();
	mesh->setUsage(usage);
	mesh->vertices() = { {-1, -1, 0}, {1, -1, 0}, {0, 1, 0} };
	mesh->normals() = { {0, 0, 1}, {0, 0, 1}, {0, 0, 1} };
	mesh->uvs() = { {0, 0}, {0.5f, 0.5f}, {1, 0} };
	mesh->indices() = { 0, 1, 2 };
	if(sendToGPU)
	    mesh->updateBuffers();
	return mesh;
    }

    IMesh* MeshUtility::createRectangle(bool sendToGPU, IMesh::Usage usage)
    {
	auto mesh = Platform::get()->createMesh();
	mesh->setUsage(usage);
	mesh->vertices() = { {-1, -1, 0}, {-1, 1, 0}, {1, 1, 0}, {1, -1, 0} };
	mesh->normals() = { {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1} };
	mesh->uvs() = { {0, 0}, {0, 1}, {1, 1}, {1, 0} };
	mesh->indices() = { 0, 2, 1, 0, 3, 2 };
	if(sendToGPU)
	    mesh->updateBuffers();
	return mesh;
    }

    IMesh* MeshUtility::createCube(bool sendToGPU, IMesh::Usage usage)
    {
	auto mesh = Platform::get()->createMesh();
	mesh->setUsage(usage);
	mesh->vertices() =
	{
	    {-1.0, -1.0, 1.0}, // front 0
	    {1.0, -1.0, 1.0},// 1
	    {1.0, 1.0, 1.0},// 2
	    {-1.0, 1.0, 1.0},// 3
	    {-1.0, 1.0, 1.0},// top 4
	    {1.0, 1.0, 1.0},// 5
	    {1.0, 1.0, -1.0},// 6
	    {-1.0, 1.0, -1.0},// 7
	    {1.0, -1.0, -1.0},// back 8
	    {-1.0, -1.0, -1.0},// 9
	    {-1.0, 1.0, -1.0},// 10
	    {1.0, 1.0, -1.0},// 11
	    {-1.0, -1.0, -1.0},// bottom 12
	    {1.0, -1.0, -1.0},// 13
	    {1.0, -1.0, 1.0},// 14
	    {-1.0, -1.0, 1.0},// 15
	    {-1.0, -1.0, -1.0},// left 16
	    {-1.0, -1.0, 1.0},// 17
	    {-1.0, 1.0, 1.0},// 18
	    {-1.0, 1.0, -1.0},// 19
	    {1.0, -1.0, 1.0},// right 20
	    {1.0, -1.0, -1.0},// 21
	    {1.0, 1.0, -1.0},// 22
	    {1.0, 1.0, 1.0},// 23
	};
	mesh->indices() =
	{
	    0, 1, 2, // front
	    2, 3, 0,//
	    4, 5, 6,// top
	    6, 7, 4,//
	    8, 9, 10,// back
	    10, 11, 8,//
	    12, 13, 14,// bottom
	    14, 15, 12,//
	    16, 17, 18,// left
	    18, 19, 16,//
	    20, 21, 22,// right
	    22, 23, 20,//
	};
	mesh->normals() =
	{
	    {0, 0, 1}, // 0 Front
	    {0, 0, 1},// 1
	    {0, 0, 1},// 2
	    {0, 0, 1},// 3
	    {0, 1, 0},// 10 Top
	    {0, 1, 0},// 11
	    {0, 1, 0},// 14
	    {0, 1, 0},// 15
	    {0, 0, -1},// 4 Back
	    {0, 0, -1},// 5
	    {0, 0, -1},// 6
	    {0, 0, -1},// 7
	    {0, -1, 0},// 8 Bottom
	    {0, -1, 0},// 9
	    {0, -1, 0},// 12
	    {0, -1, 0},// 13
	    {-1, 0, 0},// 16 Left
	    {-1, 0, 0},// 19
	    {-1, 0, 0},// 20
	    {-1, 0, 0},// 23
	    {1, 0, 0},// 21 Right
	    {1, 0, 0},// 22
	    {1, 0, 0},// 17
	    {1, 0, 0},// 18
	};
	IMesh::UV uvs[4 * 6] = {
	    {0.0, 0.0}, // front
	    {1.0, 0.0}, //
	    {1.0, 1.0}, //
	    {0.0, 1.0},
	};
	for (int i = 1; i < 6; i++)
	    memcpy(&uvs[i * 4], &uvs[0], 4 * sizeof(decltype(uvs)));
	mesh->uvs().insert(mesh->uvs().begin(), std::begin(uvs), std::end(uvs));
	if (sendToGPU)
	    mesh->updateBuffers();
	return mesh;
    }

    IMesh* MeshUtility::createPyramid(bool sendToGPU, IMesh::Usage usage)
    {
	auto mesh = Platform::get()->createMesh();
	mesh->setUsage(usage);
	mesh->vertices() =
	{   {-1, -1, 1}, // Front lower left 0
	    {1, -1, 1},// Front lower right 1
	    {0, 1, 0},// Front top 2
	    {1, -1, 1},// Right lower left 3
	    {1, -1, -1},// Right lower right 4
	    {0, 1, 0},// Right top 5
	    {1, -1, -1},// Back lower left 6
	    {-1, -1, -1},// Back lower right 7
	    {0, 1, 0},// Back top 8
	    {-1, -1, -1},// Left lower left 9
	    {-1, -1, 1},// Left lower right 10
	    {0, 1, 0},// Left top 11
	    {-1, -1, 1},// Bottom front left 12
	    {1, -1, 1},// Bottom front right 13
	    {-1, -1, -1},// Bottom back left 14
	    {1, -1, -1},// Bottom back right 15
	};
	mesh->indices() =
	{
	    0, 1, 2, // front
	    3, 4, 5,// right
	    6, 7, 8,// back
	    9, 10, 11,// left
	    12, 14, 13,// bottom left
	    14, 15, 13,// bottom right
	};
	mesh->normals() =
	{
	    {0, 0.4472, 0.8944}, // front
	    {0, 0.4472, 0.8944},// front
	    {0, 0.4472, 0.8944},// front
	    {0.8944, 0.4472, 0},// right
	    {0.8944, 0.4472, 0},// right
	    {0.8944, 0.4472, 0},// right
	    {0, 0.4472, -0.8944},// back
	    {0, 0.4472, -0.8944},// back
	    {0, 0.4472, -0.8944},// back
	    {-0.8944, 0.4472, 0},// left
	    {-0.8944, 0.4472, 0},// left
	    {-0.8944, 0.4472, 0},// left
	    {0, -1, 0},// bottom
	    {0, -1, 0},// bottom
	    {0, -1, 0},// bottom
	    {0, -1, 0},// bottom
	};
	mesh->uvs() =
	{
	    {0.0, 0.0}, // front
	    {1.0, 0.0},//
	    {0.5, 1.0},//
	    {0.0, 0.0},// right
	    {1.0, 0.0},//
	    {0.5, 1.0},//
	    {0.0, 0.0},// back
	    {1.0, 0.0},//
	    {0.5, 1.0},//
	    {0.0, 0.0},// left
	    {1.0, 0.0},//
	    {0.5, 1.0},//
	    {0.0, 0.0},// bottom
	    {1.0, 0.0},//
	    {0.0, 1.0},//
	    {1.0, 1.0},//
	};
	if (sendToGPU)
	    mesh->updateBuffers();
	return mesh;
    }

    IMesh* MeshUtility::generateTangentBase(IMesh* mesh)
    {
	// Allocate sufficient memory
	mesh->tangents().resize(mesh->vertices().size());
	mesh->bitangents().resize(mesh->vertices().size());

	for (unsigned int i = 0; i < mesh->indices().size(); i += 3)
	{
	    // Shortcuts
	    Vec3f v0 = mesh->vertices()[mesh->indices()[i + 0]];
	    Vec3f v1 = mesh->vertices()[mesh->indices()[i + 1]];
	    Vec3f v2 = mesh->vertices()[mesh->indices()[i + 2]];
	    Vec2f uv0 = mesh->uvs()[mesh->indices()[i + 0]];
	    Vec2f uv1 = mesh->uvs()[mesh->indices()[i + 1]];
	    Vec2f uv2 = mesh->uvs()[mesh->indices()[i + 2]];

	    // Position delta
	    Vec3f deltaPos1 = v1 - v0;
	    Vec3f deltaPos2 = v2 - v0;

	    // UV delta
	    Vec2f deltaUV1 = uv1 - uv0;
	    Vec2f deltaUV2 = uv2 - uv0;

	    // Calculate tangent and bitangent
	    float r = 1 / (deltaUV1.x() * deltaUV2.y()
				    - deltaUV1.y() * deltaUV2.x());
	    Vec3f tangent =
		    (deltaPos1 * deltaUV2.y() - deltaPos2 * deltaUV1.y()) * r;
	    Vec3f bitangent = (deltaPos2 * deltaUV1.x()
		    - deltaPos1 * deltaUV2.x()) * r;

	    // Average tangents and bitangents if already present
	    mesh->tangents()[mesh->indices()[i + 0]] = static_cast<Vec3f>(tangent + Vec3f(mesh->tangents()[mesh->indices()[i + 0]]));
	    mesh->tangents()[mesh->indices()[i + 1]] = static_cast<Vec3f>(tangent + Vec3f(mesh->tangents()[mesh->indices()[i + 1]]));
	    mesh->tangents()[mesh->indices()[i + 2]] = static_cast<Vec3f>(tangent + Vec3f(mesh->tangents()[mesh->indices()[i + 2]]));
	    mesh->bitangents()[mesh->indices()[i + 0]] = static_cast<Vec3f>(bitangent + Vec3f(mesh->bitangents()[mesh->indices()[i + 0]]));
	    mesh->bitangents()[mesh->indices()[i + 1]] = static_cast<Vec3f>(bitangent + Vec3f(mesh->bitangents()[mesh->indices()[i + 1]]));
	    mesh->bitangents()[mesh->indices()[i + 2]] = static_cast<Vec3f>(bitangent + Vec3f(mesh->bitangents()[mesh->indices()[i + 2]]));
	}
	// Normalize tangents & bitangents
	for (unsigned int i = 0; i < mesh->tangents().size(); i++)
	{
	    mesh->tangents()[i] = static_cast<Vec3f>(static_cast<Vec3f>(mesh->tangents()[i]).normalize());
	    mesh->bitangents()[i] = static_cast<Vec3f>(static_cast<Vec3f>(mesh->bitangents()[i]).normalize());
	}
	// Orthogonalize normal/tangent/bitangent system
	for (unsigned int i = 0; i < mesh->vertices().size(); i++)
	{
	    Vec3f n = mesh->normals()[i];
	    Vec3f t = mesh->tangents()[i];
	    Vec3f b = mesh->bitangents()[i];

	    // Gram-Schmidt orthogonalize
	    t = t - n * n.dot(t);
	    t.normalize();

	    // Calculate handedness
	    if (n.cross(t).dot(b) < 0.0f)
	    {
		t = t * -1.0f;
	    }

	    // Write back
	    mesh->normals()[i] = n;
	    mesh->tangents()[i] = t;
	    mesh->bitangents()[i] = b;
	}

	return mesh;
    }

}
