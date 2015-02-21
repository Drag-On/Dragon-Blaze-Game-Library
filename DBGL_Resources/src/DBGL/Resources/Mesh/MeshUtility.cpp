//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <array>
#include <map>
#include <type_traits>
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Math/Vector2.h"
#include "DBGL/Core/Collection/Tree/KdTree.h"
#include "DBGL/Resources/Mesh/MeshUtility.h"

namespace dbgl
{
	IMesh* MeshUtility::createTriangle(bool sendToGPU, IMesh::Usage usage)
	{
		auto mesh = Platform::get()->createMesh();
		mesh->setUsage(usage);
		mesh->vertices() =
		{
			{	-1, -1, 0},
			{	1, -1, 0},
			{	0, 1, 0}};
		mesh->normals() =
		{
			{	0, 0, 1},
			{	0, 0, 1},
			{	0, 0, 1}};
		mesh->uvs() =
		{
			{	0, 0},
			{	0.5f, 0.5f},
			{	1, 0}};
		mesh->indices() =
		{	0, 1, 2};
		if (sendToGPU)
			mesh->updateBuffers();
		return mesh;
	}

	IMesh* MeshUtility::createRectangle(bool sendToGPU, IMesh::Usage usage)
	{
		auto mesh = Platform::get()->createMesh();
		mesh->setUsage(usage);
		mesh->vertices() =
		{
			{	-1, -1, 0},
			{	-1, 1, 0},
			{	1, 1, 0},
			{	1, -1, 0}};
		mesh->normals() =
		{
			{	0, 0, 1},
			{	0, 0, 1},
			{	0, 0, 1},
			{	0, 0, 1}};
		mesh->uvs() =
		{
			{	0, 0},
			{	0, 1},
			{	1, 1},
			{	1, 0}};
		mesh->indices() =
		{	0, 2, 1, 0, 3, 2};
		if (sendToGPU)
			mesh->updateBuffers();
		return mesh;
	}

	IMesh* MeshUtility::createCube(bool sendToGPU, IMesh::Usage usage)
	{
		auto mesh = Platform::get()->createMesh();
		mesh->setUsage(usage);
		mesh->vertices() =
		{
			{	-1.0, -1.0, 1.0}, // front 0
			{	1.0, -1.0, 1.0}, // 1
			{	1.0, 1.0, 1.0}, // 2
			{	-1.0, 1.0, 1.0}, // 3
			{	-1.0, 1.0, 1.0}, // top 4
			{	1.0, 1.0, 1.0}, // 5
			{	1.0, 1.0, -1.0}, // 6
			{	-1.0, 1.0, -1.0}, // 7
			{	1.0, -1.0, -1.0}, // back 8
			{	-1.0, -1.0, -1.0}, // 9
			{	-1.0, 1.0, -1.0}, // 10
			{	1.0, 1.0, -1.0}, // 11
			{	-1.0, -1.0, -1.0}, // bottom 12
			{	1.0, -1.0, -1.0}, // 13
			{	1.0, -1.0, 1.0}, // 14
			{	-1.0, -1.0, 1.0}, // 15
			{	-1.0, -1.0, -1.0}, // left 16
			{	-1.0, -1.0, 1.0}, // 17
			{	-1.0, 1.0, 1.0}, // 18
			{	-1.0, 1.0, -1.0}, // 19
			{	1.0, -1.0, 1.0}, // right 20
			{	1.0, -1.0, -1.0}, // 21
			{	1.0, 1.0, -1.0}, // 22
			{	1.0, 1.0, 1.0}, // 23
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
			{	0, 0, 1}, // 0 Front
			{	0, 0, 1}, // 1
			{	0, 0, 1}, // 2
			{	0, 0, 1}, // 3
			{	0, 1, 0}, // 10 Top
			{	0, 1, 0}, // 11
			{	0, 1, 0}, // 14
			{	0, 1, 0}, // 15
			{	0, 0, -1}, // 4 Back
			{	0, 0, -1}, // 5
			{	0, 0, -1}, // 6
			{	0, 0, -1}, // 7
			{	0, -1, 0}, // 8 Bottom
			{	0, -1, 0}, // 9
			{	0, -1, 0}, // 12
			{	0, -1, 0}, // 13
			{	-1, 0, 0}, // 16 Left
			{	-1, 0, 0}, // 19
			{	-1, 0, 0}, // 20
			{	-1, 0, 0}, // 23
			{	1, 0, 0}, // 21 Right
			{	1, 0, 0}, // 22
			{	1, 0, 0}, // 17
			{	1, 0, 0}, // 18
		};
		Vec2f uvs[4 * 6] = { { 0.0, 0.0 }, // front
				{ 1.0, 0.0 }, //
				{ 1.0, 1.0 }, //
				{ 0.0, 1.0 }, };
		for (int i = 1; i < 6; i++)
			memcpy(&uvs[i * 4], &uvs[0], 4 * sizeof(Vec2f));
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
		{
			{	-1, -1, 1}, // Front lower left 0
			{	1, -1, 1}, // Front lower right 1
			{	0, 1, 0}, // Front top 2
			{	1, -1, 1}, // Right lower left 3
			{	1, -1, -1}, // Right lower right 4
			{	0, 1, 0}, // Right top 5
			{	1, -1, -1}, // Back lower left 6
			{	-1, -1, -1}, // Back lower right 7
			{	0, 1, 0}, // Back top 8
			{	-1, -1, -1}, // Left lower left 9
			{	-1, -1, 1}, // Left lower right 10
			{	0, 1, 0}, // Left top 11
			{	-1, -1, 1}, // Bottom front left 12
			{	1, -1, 1}, // Bottom front right 13
			{	-1, -1, -1}, // Bottom back left 14
			{	1, -1, -1}, // Bottom back right 15
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
			{	0, 0.4472, 0.8944}, // front
			{	0, 0.4472, 0.8944}, // front
			{	0, 0.4472, 0.8944}, // front
			{	0.8944, 0.4472, 0}, // right
			{	0.8944, 0.4472, 0}, // right
			{	0.8944, 0.4472, 0}, // right
			{	0, 0.4472, -0.8944}, // back
			{	0, 0.4472, -0.8944}, // back
			{	0, 0.4472, -0.8944}, // back
			{	-0.8944, 0.4472, 0}, // left
			{	-0.8944, 0.4472, 0}, // left
			{	-0.8944, 0.4472, 0}, // left
			{	0, -1, 0}, // bottom
			{	0, -1, 0}, // bottom
			{	0, -1, 0}, // bottom
			{	0, -1, 0}, // bottom
		};
		mesh->uvs() =
		{
			{	0.0, 0.0}, // front
			{	1.0, 0.0}, //
			{	0.5, 1.0}, //
			{	0.0, 0.0}, // right
			{	1.0, 0.0}, //
			{	0.5, 1.0}, //
			{	0.0, 0.0}, // back
			{	1.0, 0.0}, //
			{	0.5, 1.0}, //
			{	0.0, 0.0}, // left
			{	1.0, 0.0}, //
			{	0.5, 1.0}, //
			{	0.0, 0.0}, // bottom
			{	1.0, 0.0}, //
			{	0.0, 1.0}, //
			{	1.0, 1.0}, //
		};
		if (sendToGPU)
			mesh->updateBuffers();
		return mesh;
	}

	IMesh* MeshUtility::createIcosahedron(bool sendToGPU, IMesh::Usage usage)
	{
		auto mesh = Platform::get()->createMesh();
		mesh->setUsage(usage);

		mesh->vertices() =
		{
			{	0, 0.5, 0.809017},
			{	0.5, 0.809017, 0},
			{	-0.5, 0.809017, 0},
			{	0, 0.5, 0.809017},
			{	0.809017, 0, 0.5},
			{	0.5, 0.809017, 0},
			{	0.809017, 0, 0.5},
			{	0.809017, 0, -0.5},
			{	0.5, 0.809017, 0},
			{	0.809017, 0, -0.5},
			{	0, 0.5, -0.809017},
			{	0.5, 0.809017, 0},
			{	0, 0.5, -0.809017},
			{	-0.5, 0.809017, 0},
			{	0.5, 0.809017, 0},
			{	-0.809017, 0, -0.5},
			{	-0.5, 0.809017, 0},
			{	0, 0.5, -0.809017},
			{	-0.809017, 0, 0.5},
			{	-0.5, 0.809017, 0},
			{	-0.809017, 0, -0.5},
			{	-0.809017, 0, 0.5},
			{	0, 0.5, 0.809017},
			{	-0.5, 0.809017, 0},
			{	0, -0.5, 0.809017},
			{	-0.5, -0.809017, 0},
			{	0.5, -0.809017, 0},
			{	0, -0.5, 0.809017},
			{	0.5, -0.809017, 0},
			{	0.809017, 0, 0.5},
			{	0.5, -0.809017, 0},
			{	0.809017, 0, -0.5},
			{	0.809017, 0, 0.5},
			{	0.5, -0.809017, 0},
			{	0, -0.5, -0.809017},
			{	0.809017, 0, -0.5},
			{	0.5, -0.809017, 0},
			{	-0.5, -0.809017, 0},
			{	0, -0.5, -0.809017},
			{	-0.5, -0.809017, 0},
			{	-0.809017, 0, -0.5},
			{	0, -0.5, -0.809017},
			{	-0.5, -0.809017, 0},
			{	-0.809017, 0, 0.5},
			{	-0.809017, 0, -0.5},
			{	-0.5, -0.809017, 0},
			{	0, -0.5, 0.809017},
			{	-0.809017, 0, 0.5},
			{	0, 0.5, 0.809017},
			{	-0.809017, 0, 0.5},
			{	0, -0.5, 0.809017},
			{	0, 0.5, 0.809017},
			{	0, -0.5, 0.809017},
			{	0.809017, 0, 0.5},
			{	0.809017, 0, -0.5},
			{	0, -0.5, -0.809017},
			{	0, 0.5, -0.809017},
			{	0, -0.5, -0.809017},
			{	-0.809017, 0, -0.5},
			{	0, 0.5, -0.809017},
		};
		mesh->indices() =
		{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
			28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
			54, 55, 56, 57, 58, 59,
		};
		mesh->uvs() =
		{
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
			{	0.5, 0},
			{	1, 1},
			{	0, 1},
		};
		generateNormals(mesh);

		if (sendToGPU)
			mesh->updateBuffers();
		return mesh;
	}

	IMesh* MeshUtility::createIcoSphere(unsigned int refine, bool sendToGPU, IMesh::Usage usage)
	{
		auto mesh = Platform::get()->createMesh();
		mesh->setUsage(usage);

		// Generate icosahedron
		float t = (1.0f + std::sqrt(5.0f)) / 2.0f;
		mesh->vertices() =
		{
			Vec3f {-1, t, 0}.normalize(),
			Vec3f {1, t, 0}.normalize(),
			Vec3f {-1, -t, 0}.normalize(),
			Vec3f {1, -t, 0}.normalize(),
			Vec3f {0, -1, t}.normalize(),
			Vec3f {0, 1, t}.normalize(),
			Vec3f {0, -1, -t}.normalize(),
			Vec3f {0, 1, -t}.normalize(),
			Vec3f {t, 0, -1}.normalize(),
			Vec3f {t, 0, 1}.normalize(),
			Vec3f {-t, 0, -1}.normalize(),
			Vec3f {-t, 0, 1}.normalize(),
		};
		mesh->indices() =
		{
			0, 11, 5,
			0, 5, 1,
			0, 1, 7,
			0, 7, 10,
			0, 10, 11,
			1, 5, 9,
			5, 11, 4,
			11, 10, 2,
			10, 7, 6,
			7, 1, 8,
			3, 9, 4,
			3, 4, 2,
			3, 2, 6,
			3, 6, 8,
			3, 8, 9,
			4, 9, 5,
			2, 4, 11,
			6, 2, 10,
			8, 6, 7,
			9, 8, 1,
		};
		// Refine by subdividing the basic triangles
		std::remove_reference<decltype(mesh->indices())>::type newIndices;
		std::map<uint64_t, unsigned int> subdivisionIndices;
		// Computes the vertex in-between two other vertices by their index and inserts it into vertices
		auto subdivideEdge = [&](unsigned int i, unsigned int j)
		{
			// Compute hash
			uint64_t key = (static_cast<uint64_t>(std::min(i, j)) << 32) + std::max(i, j);
			// Check if vertex already exists
			auto vertIter = subdivisionIndices.find(key);
			if(vertIter != subdivisionIndices.end())
				return vertIter->second;
			else
			{
				// Otherwise compute vertex between the passed vertices
				auto& v1 = mesh->vertices()[i];
				auto& v2 = mesh->vertices()[j];
				Vec3f middle = (v1 + v2).normalize();// On unit sphere
				unsigned int index = mesh->vertices().size();
				subdivisionIndices.insert({key, index});
				mesh->vertices().push_back(middle);
				return index;
			}
		};
		for (unsigned int i = 0; i < refine; i++)
		{
			newIndices.clear();
			for (unsigned int i = 0; i < mesh->indices().size(); i += 3)
			{
				unsigned int index0 = mesh->indices()[i + 0];
				unsigned int index1 = mesh->indices()[i + 1];
				unsigned int index2 = mesh->indices()[i + 2];

				// replace triangle by 4 triangles
				int a = subdivideEdge(index0, index1);
				int b = subdivideEdge(index1, index2);
				int c = subdivideEdge(index2, index0);

				newIndices.push_back(index0);
				newIndices.push_back(a);
				newIndices.push_back(c);
				newIndices.push_back(index1);
				newIndices.push_back(b);
				newIndices.push_back(a);
				newIndices.push_back(index2);
				newIndices.push_back(c);
				newIndices.push_back(b);
				newIndices.push_back(a);
				newIndices.push_back(b);
				newIndices.push_back(c);
			}
			mesh->indices().clear();
			mesh->indices().insert(mesh->indices().begin(), newIndices.begin(), newIndices.end());
		}

		// Compute UVs
		auto computeUV = [&](Vec3f normal)
		{
			float u;
			float v;
			float normalisedX = 0;
			float normalisedZ = -1;
			if (((normal.x() * normal.x()) + (normal.z() * normal.z())) > 0)
			{
				normalisedX = std::sqrt((normal.x() * normal.x()) / ((normal.x() * normal.x()) + (normal.z() * normal.z())));
				if (normal.x() < 0)
					normalisedX = -normalisedX;
				normalisedZ = std::sqrt((normal.z() * normal.z()) / ((normal.x() * normal.x()) + (normal.z() * normal.z())));
				if (normal.z() < 0)
					normalisedZ = -normalisedZ;
			}
			if (normalisedZ == 0)
				u = (normalisedX * dbgl::pi()) / 2;
			else
			{
				u = std::atan(normalisedX / normalisedZ);
				if (normalisedZ < 0)
					u += dbgl::pi();
			}
			if (u < 0)
				u += 2 * dbgl::pi();
			u /= 2 * dbgl::pi();
			v = (-normal.y() + 1) / 2;
			return Vec2f {u, v};
		};
		for (auto vertex : mesh->vertices())
			mesh->uvs().push_back(computeUV(vertex));
		// Repair texture seams by duplicating the vertices that need to wrap around the texture border
		newIndices.clear();
		std::map<uint64_t, unsigned int> correctionList;
		for (int i = mesh->indices().size() - 3; i >= 0; i -= 3)
		{
			Vec2f& uv1 = mesh->uvs()[mesh->indices()[i + 0]];
			Vec2f& uv2 = mesh->uvs()[mesh->indices()[i + 1]];
			Vec2f& uv3 = mesh->uvs()[mesh->indices()[i + 2]];
			Vec3f uv1_3d { uv1.x(), uv1.y(), 0 };
			Vec3f uv2_3d { uv2.x(), uv2.y(), 0 };
			Vec3f uv3_3d { uv3.x(), uv3.y(), 0 };
			Vec3f cross = ((uv1_3d - uv2_3d).cross(uv3_3d - uv2_3d));
			if (cross.z() <= 0)
			{ // UVs are mapped in counter-clockwise order, thus there is a seam
				for (int j = i; j < i + 3; j++)
				{
					unsigned int index = mesh->indices()[j];
					Vec3f& vertex = mesh->vertices()[index];
					Vec2f& uv = mesh->uvs()[index];
					if (uv.x() >= 0.9f)
					{
						if (correctionList.count(index) > 0)
							newIndices.push_back(correctionList[index]);
						else
						{
							Vec2f newUV = uv;
							newUV.x() -= 1;
							mesh->uvs().push_back(newUV);
							mesh->vertices().push_back(mesh->vertices()[index]);
							unsigned int correctedVertexIndex = mesh->vertices().size() - 1;
							correctionList.insert( { index, correctedVertexIndex });
							newIndices.push_back(correctedVertexIndex);
						}
					}
					else
						newIndices.push_back(index);
				}
			}
			else
				newIndices.insert(newIndices.begin(), mesh->indices().begin() + i, mesh->indices().begin() + i + 3);
		}
		mesh->indices().clear();
		mesh->indices().insert(mesh->indices().begin(), newIndices.begin(), newIndices.end());

		// Compute normals
		mesh->normals().insert(mesh->normals().begin(), mesh->vertices().begin(), mesh->vertices().end());

		if (sendToGPU)
			mesh->updateBuffers();
		return mesh;
	}

	void MeshUtility::generateNormals(IMesh* mesh)
	{
		mesh->normals().clear();
		mesh->normals().resize(mesh->vertices().size());
		for (unsigned int i = 0; i < mesh->indices().size(); i += 3)
		{
			// Shortcuts
			Vec3f& v0 = mesh->vertices()[mesh->indices()[i + 0]];
			Vec3f& v1 = mesh->vertices()[mesh->indices()[i + 1]];
			Vec3f& v2 = mesh->vertices()[mesh->indices()[i + 2]];
			Vec3f newNormal = ((v0 - v1).cross(v0 - v2)).normalize();
			for (unsigned int j = 0; j < 3; j++)
			{
				if (mesh->normals()[mesh->indices()[i + j]].getSquaredLength() == 0)
					mesh->normals()[mesh->indices()[i + j]] = newNormal;
				else
				{
					mesh->normals()[mesh->indices()[i + j]] += newNormal;
					mesh->normals()[mesh->indices()[i + j]].normalize();
				}
			}
		}
	}

	void MeshUtility::generateTangentBase(IMesh* mesh)
	{
		// Allocate sufficient memory
		mesh->tangents().resize(mesh->vertices().size());
		mesh->bitangents().resize(mesh->vertices().size());

		for (unsigned int i = 0; i < mesh->indices().size(); i += 3)
		{
			// Shortcuts
			Vec3f& v0 = mesh->vertices()[mesh->indices()[i + 0]];
			Vec3f& v1 = mesh->vertices()[mesh->indices()[i + 1]];
			Vec3f& v2 = mesh->vertices()[mesh->indices()[i + 2]];
			Vec2f& uv0 = mesh->uvs()[mesh->indices()[i + 0]];
			Vec2f& uv1 = mesh->uvs()[mesh->indices()[i + 1]];
			Vec2f& uv2 = mesh->uvs()[mesh->indices()[i + 2]];

			// Position delta
			Vec3f deltaPos1 = v1 - v0;
			Vec3f deltaPos2 = v2 - v0;

			// UV delta
			Vec2f deltaUV1 = uv1 - uv0;
			Vec2f deltaUV2 = uv2 - uv0;

			// Calculate tangent and bitangent
			float r = 1 / (deltaUV1.x() * deltaUV2.y() - deltaUV1.y() * deltaUV2.x());
			Vec3f tangent = (deltaPos1 * deltaUV2.y() - deltaPos2 * deltaUV1.y()) * r;
			Vec3f bitangent = (deltaPos2 * deltaUV1.x() - deltaPos1 * deltaUV2.x()) * r;

			// Average tangents and bitangents if already present
			mesh->tangents()[mesh->indices()[i + 0]] += tangent;
			mesh->tangents()[mesh->indices()[i + 1]] += tangent;
			mesh->tangents()[mesh->indices()[i + 2]] += tangent;
			mesh->bitangents()[mesh->indices()[i + 0]] += bitangent;
			mesh->bitangents()[mesh->indices()[i + 1]] += bitangent;
			mesh->bitangents()[mesh->indices()[i + 2]] += bitangent;
		}
		// Normalize tangents & bitangents
		for (unsigned int i = 0; i < mesh->tangents().size(); i++)
		{
			mesh->tangents()[i].normalize();
			mesh->bitangents()[i].normalize();
		}
		// Orthogonalize normal/tangent/bitangent system
		for (unsigned int i = 0; i < mesh->vertices().size(); i++)
		{
			Vec3f& n = mesh->normals()[i];
			Vec3f& t = mesh->tangents()[i];
			Vec3f& b = mesh->bitangents()[i];

			// Gram-Schmidt orthogonalize
			t = t - n * n.dot(t);
			t.normalize();

			// Calculate handedness
			if (n.cross(t).dot(b) < 0.0f)
			{
				t = t * -1.0f;
			}
		}
	}

	void MeshUtility::reverseNormals(IMesh* mesh)
	{
		for (unsigned int i = 0; i < mesh->normals().size(); i++)
		{
			Vec3f normal = mesh->normals()[i];
			mesh->normals()[i] = -normal;
		}
	}

	void MeshUtility::optimize(IMesh* mesh, float maxCompatibilityAngle)
	{
		// Vertices into kd-tree for better performance
		std::vector<unsigned int> indices(mesh->vertices().size());
		std::iota(std::begin(indices), std::end(indices), 0); // Fill with increasing values, starting with 0
		KdTree<unsigned int, Vec3f> vertexTree { mesh->vertices().begin(), mesh->vertices().end(), indices.begin(),
				indices.end() };

		std::map<unsigned int, unsigned int> replace { };

		// Method to check normal compatibility
		auto checkNormalCompat = [&maxCompatibilityAngle, &mesh](unsigned int id1, unsigned int id2) -> bool
		{
			if(mesh->normals().size() < std::max(id1, id2))
			return true;
			auto theta = mesh->normals()[id1].getNormalized().dot(mesh->normals()[id2].getNormalized());
			if (theta < -1.0)
			theta = -1.0f;
			else if (theta > 1.0)
			theta = 1.0f;
			auto angle = std::acos(theta);
			return (angle < maxCompatibilityAngle);
		};
		// Method to check uv compatibility
		auto checkUvCompat = [&mesh](unsigned int id1, unsigned int id2) -> bool
		{
			if(mesh->uvs().size() < std::max(id1, id2))
			return true;
			return (mesh->uvs()[id1].isSimilar(mesh->uvs()[id2], 0.000001f));
		};
		auto mergeVertices = [&mesh, &replace](unsigned int id1, unsigned int id2)
		{
			// Average coordinates
				mesh->vertices()[id1] = (mesh->vertices()[id1] + mesh->vertices()[id2]) / 2;
				// Average normals
				if(mesh->normals().size() > std::max(id1, id2))
				{
					mesh->normals()[id1] += mesh->normals()[id2];
					mesh->normals()[id1].normalize();
				}
				// Average uvs
				if(mesh->uvs().size() > std::max(id1, id2))
				{
					mesh->uvs()[id1] = (mesh->uvs()[id1] + mesh->uvs()[id2]) / 2;
				}
				// Memorize index to replace
				replace.insert(
						{	id1, id2});
			};

		// Iterate over all vertices
		for (unsigned int i = 0; i < mesh->vertices().size(); i++)
		{
			if (replace.find(i) != replace.end())
				continue;
			auto& vert = mesh->vertices()[i];
			// Find all similar vertices
			std::vector<KdTree<unsigned int, Vec3f>::Container> possible { };
			Box<float> range { vert - Vec3f { 0.0001f, 0.0001f, 0.0001f }, Vec3f { 0.0002f, 0.0002f, 0.0002f } };
			vertexTree.findRange(range, possible);
			for (auto c : possible)
			{
				auto curId = c.data;
				if (curId == i)
					continue;
				if (replace.find(curId) != replace.end())
					continue;
				bool normalCompat = checkNormalCompat(i, curId);
				bool uvCompat = checkUvCompat(i, curId);
				// If everything is compatible -> merge vertices
				if (normalCompat && uvCompat)
					mergeVertices(curId, i);
			}
		}
		// Replace merged vertices
		for (unsigned int i = 0; i < mesh->indices().size(); i++)
		{
			auto it = replace.find(mesh->indices()[i]);
			if (it != replace.end())
			{
				mesh->indices()[i] = it->second;
			}
		}
		// Remove unused vertices
		std::vector<unsigned int> replaceIndices { };
		replaceIndices.reserve(replace.size());
		for (auto it = replace.begin(); it != replace.end(); ++it)
		{
			replaceIndices.push_back(it->first);
		}
		std::sort(replaceIndices.begin(), replaceIndices.end());
		unsigned int offset = 0;
		for (auto it = replaceIndices.begin(); it != replaceIndices.end(); ++it)
		{
			unsigned int rIndex = *it - offset;
			mesh->vertices().erase(mesh->vertices().begin() + rIndex);
			if (mesh->normals().size() > rIndex)
				mesh->normals().erase(mesh->normals().begin() + rIndex);
			if (mesh->uvs().size() > rIndex)
				mesh->uvs().erase(mesh->uvs().begin() + rIndex);
			offset++;
			// Decrement all indices higher than that by 1
			for (unsigned int i = 0; i < mesh->indices().size(); i++)
			{
				if (mesh->indices()[i] > rIndex)
					mesh->indices()[i] = mesh->indices()[i] - 1;
			}
		}
		// If there are tangents and bitangents, recalculate them
		if (mesh->tangents().size() > 0 || mesh->bitangents().size() > 0)
		{
			mesh->tangents().clear();
			mesh->bitangents().clear();
			generateTangentBase(mesh);
		}
	}

}
