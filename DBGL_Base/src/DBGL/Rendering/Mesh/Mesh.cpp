//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Mesh/Mesh.h"

namespace dbgl
{
    Mesh::~Mesh()
    {
	// Properly delete all buffers
	if (m_indexBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &m_indexBuffer);
	if (m_vertexBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &m_vertexBuffer);
	if (m_normalBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &m_normalBuffer);
	if (m_uvBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &m_uvBuffer);
	if (m_tangentBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &m_tangentBuffer);
	if (m_bitangentBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &m_bitangentBuffer);
    }

    std::vector<unsigned short> const& Mesh::getIndices() const
    {
	return m_indices;
    }

    std::vector<Vector3<GLfloat>> const& Mesh::getVertices() const
    {
	return m_vertices;
    }

    std::vector<Vector3<GLfloat>> const& Mesh::getNormals() const
    {
	return m_normals;
    }

    std::vector<Vector2<GLfloat>> const& Mesh::getUVs() const
    {
	return m_uv;
    }

    std::vector<Vector3<GLfloat>> const& Mesh::getTangents() const
    {
	return m_tangents;
    }

    std::vector<Vector3<GLfloat>> const& Mesh::getBitangents() const
    {
	return m_bitangents;
    }

    std::vector<unsigned short>& Mesh::indices()
    {
	return m_indices;
    }

    std::vector<Vector3<GLfloat>>& Mesh::vertices()
    {
	return m_vertices;
    }

    std::vector<Vector3<GLfloat>>& Mesh::normals()
    {
	return m_normals;
    }

    std::vector<Vector2<GLfloat>>& Mesh::uvs()
    {
	return m_uv;
    }

    std::vector<Vector3<GLfloat>>& Mesh::tangents()
    {
	return m_tangents;
    }

    std::vector<Vector3<GLfloat>>& Mesh::bitangents()
    {
	return m_bitangents;
    }

    Mesh* Mesh::load(const Type type, const std::string path, Bitmask<> flags)
    {
	switch (type)
	{
	    case OBJ:
	    {
		return OBJMeshLoader().load(path, flags);
	    }
	    default:
	    {
		LOG->warning("Format of file % not recognized", path.c_str());
		return nullptr;
	    }
	}
    }

    template<class Loader> Mesh* Mesh::load(const std::string path, Bitmask<> flags)
    {
	return Loader().load(path, flags);
    }

    Mesh* Mesh::load(MeshLoader& loader, const std::string path, Bitmask<> flags)
    {
	return loader.load(path, flags);
    }

    Mesh* Mesh::makeTriangle(Bitmask<> flags)
    {
	Mesh* mesh = new Mesh();
	mesh->m_vertices =
	{   Vec3f(-1, -1, 0), Vec3f(1, -1, 0), Vec3f(0, 1, 0)};

	mesh->m_normals =
	{   Vec3f(0, 0, 1), Vec3f(0, 0, 1), Vec3f(0, 0, 1)};

	mesh->m_uv =
	{   Vec2f(0, 0), Vec2f(0.5, 0.5), Vec2f(1, 0)};

	mesh->m_indices =
	{   0, 1, 2};

	// Generate tangents and bitangents
	if (flags.isSet(GenerateTangentBase))
	    mesh->generateTangentBasis();

	if (flags.isSet(SendToGPU))
	    mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makePlane(Bitmask<> flags)
    {
	Mesh* mesh = new Mesh();
	mesh->m_vertices =
	{   Vec3f(-1, -1, 0), Vec3f(-1, 1, 0), Vec3f(1, 1, 0), Vec3f(1, -1, 0)};

	mesh->m_normals =
	{   Vec3f(0, 0, 1), Vec3f(0, 0, 1), Vec3f(0, 0, 1), Vec3f(0, 0, 1)};

	mesh->m_uv =
	{   Vec2f(0, 0), Vec2f(0, 1), Vec2f(1, 1), Vec2f(1, 0)};

	mesh->m_indices =
	{   0, 2, 1, 0, 3, 2};

	// Generate tangents and bitangents
	if (flags.isSet(GenerateTangentBase))
	    mesh->generateTangentBasis();

	if (flags.isSet(SendToGPU))
	    mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makeCube(Bitmask<> flags)
    {
	Mesh* mesh = new Mesh();

	// Define vertices
	mesh->m_vertices =
	{
	    Vec3f(-1.0, -1.0, 1.0), // front 0
	    Vec3f(1.0, -1.0, 1.0),// 1
	    Vec3f(1.0, 1.0, 1.0),// 2
	    Vec3f(-1.0, 1.0, 1.0),// 3
	    Vec3f(-1.0, 1.0, 1.0),// top 4
	    Vec3f(1.0, 1.0, 1.0),// 5
	    Vec3f(1.0, 1.0, -1.0),// 6
	    Vec3f(-1.0, 1.0, -1.0),// 7
	    Vec3f(1.0, -1.0, -1.0),// back 8
	    Vec3f(-1.0, -1.0, -1.0),// 9
	    Vec3f(-1.0, 1.0, -1.0),// 10
	    Vec3f(1.0, 1.0, -1.0),// 11
	    Vec3f(-1.0, -1.0, -1.0),// bottom 12
	    Vec3f(1.0, -1.0, -1.0),// 13
	    Vec3f(1.0, -1.0, 1.0),// 14
	    Vec3f(-1.0, -1.0, 1.0),// 15
	    Vec3f(-1.0, -1.0, -1.0),// left 16
	    Vec3f(-1.0, -1.0, 1.0),// 17
	    Vec3f(-1.0, 1.0, 1.0),// 18
	    Vec3f(-1.0, 1.0, -1.0),// 19
	    Vec3f(1.0, -1.0, 1.0),// right 20
	    Vec3f(1.0, -1.0, -1.0),// 21
	    Vec3f(1.0, 1.0, -1.0),// 22
	    Vec3f(1.0, 1.0, 1.0),// 23
	};

	// Define elements
	mesh->m_indices =
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

	// Define normals
	mesh->m_normals =
	{
	    Vec3f(0, 0, 1), // 0 Front
	    Vec3f(0, 0, 1),// 1
	    Vec3f(0, 0, 1),// 2
	    Vec3f(0, 0, 1),// 3
	    Vec3f(0, 1, 0),// 10 Top
	    Vec3f(0, 1, 0),// 11
	    Vec3f(0, 1, 0),// 14
	    Vec3f(0, 1, 0),// 15
	    Vec3f(0, 0, -1),// 4 Back
	    Vec3f(0, 0, -1),// 5
	    Vec3f(0, 0, -1),// 6
	    Vec3f(0, 0, -1),// 7
	    Vec3f(0, -1, 0),// 8 Bottom
	    Vec3f(0, -1, 0),// 9
	    Vec3f(0, -1, 0),// 12
	    Vec3f(0, -1, 0),// 13
	    Vec3f(-1, 0, 0),// 16 Left
	    Vec3f(-1, 0, 0),// 19
	    Vec3f(-1, 0, 0),// 20
	    Vec3f(-1, 0, 0),// 23
	    Vec3f(1, 0, 0),// 21 Right
	    Vec3f(1, 0, 0),// 22
	    Vec3f(1, 0, 0),// 17
	    Vec3f(1, 0, 0),// 18
	};

	// Define UVs
	Vec2f uvs[4 * 6] = {
	Vec2f(0.0, 0.0), // front
	Vec2f(1.0, 0.0), //
	Vec2f(1.0, 1.0), //
	Vec2f(0.0, 1.0),
	};
	for (int i = 1; i < 6; i++)
	    memcpy(&uvs[i * 4], &uvs[0], 4 * sizeof(Vec2f));
	mesh->m_uv.insert(mesh->m_uv.begin(), std::begin(uvs), std::end(uvs));

	// Generate tangents and bitangents
	if (flags.isSet(GenerateTangentBase))
	    mesh->generateTangentBasis();

	if (flags.isSet(SendToGPU))
	    mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makePyramid(Bitmask<> flags)
    {
	Mesh* mesh = new Mesh();

	// Define vertices
	mesh->m_vertices =
	{   Vec3f(-1, -1, 1), // Front lower left 0
	    Vec3f(1, -1, 1),// Front lower right 1
	    Vec3f(0, 1, 0),// Front top 2
	    Vec3f(1, -1, 1),// Right lower left 3
	    Vec3f(1, -1, -1),// Right lower right 4
	    Vec3f(0, 1, 0),// Right top 5
	    Vec3f(1, -1, -1),// Back lower left 6
	    Vec3f(-1, -1, -1),// Back lower right 7
	    Vec3f(0, 1, 0),// Back top 8
	    Vec3f(-1, -1, -1),// Left lower left 9
	    Vec3f(-1, -1, 1),// Left lower right 10
	    Vec3f(0, 1, 0),// Left top 11
	    Vec3f(-1, -1, 1),// Bottom front left 12
	    Vec3f(1, -1, 1),// Bottom front right 13
	    Vec3f(-1, -1, -1),// Bottom back left 14
	    Vec3f(1, -1, -1),// Bottom back right 15
	};

	// Define elements
	mesh->m_indices =
	{
	    0, 1, 2, // front
	    3, 4, 5,// right
	    6, 7, 8,// back
	    9, 10, 11,// left
	    12, 14, 13,// bottom left
	    14, 15, 13,// bottom right
	};

	// Define normals
	mesh->m_normals =
	{
	    Vec3f(0, 0.4472, 0.8944), // front
	    Vec3f(0, 0.4472, 0.8944),// front
	    Vec3f(0, 0.4472, 0.8944),// front
	    Vec3f(0.8944, 0.4472, 0),// right
	    Vec3f(0.8944, 0.4472, 0),// right
	    Vec3f(0.8944, 0.4472, 0),// right
	    Vec3f(0, 0.4472, -0.8944),// back
	    Vec3f(0, 0.4472, -0.8944),// back
	    Vec3f(0, 0.4472, -0.8944),// back
	    Vec3f(-0.8944, 0.4472, 0),// left
	    Vec3f(-0.8944, 0.4472, 0),// left
	    Vec3f(-0.8944, 0.4472, 0),// left
	    Vec3f(0, -1, 0),// bottom
	    Vec3f(0, -1, 0),// bottom
	    Vec3f(0, -1, 0),// bottom
	    Vec3f(0, -1, 0),// bottom
	};

	// Define UVs
	mesh->m_uv =
	{
	    Vec2f(0.0, 0.0), // front
	    Vec2f(1.0, 0.0),//
	    Vec2f(0.5, 1.0),//
	    Vec2f(0.0, 0.0),// right
	    Vec2f(1.0, 0.0),//
	    Vec2f(0.5, 1.0),//
	    Vec2f(0.0, 0.0),// back
	    Vec2f(1.0, 0.0),//
	    Vec2f(0.5, 1.0),//
	    Vec2f(0.0, 0.0),// left
	    Vec2f(1.0, 0.0),//
	    Vec2f(0.5, 1.0),//
	    Vec2f(0.0, 0.0),// bottom
	    Vec2f(1.0, 0.0),//
	    Vec2f(0.0, 1.0),//
	    Vec2f(1.0, 1.0),//
	};

	// Generate tangents and bitangents
	if (flags.isSet(GenerateTangentBase))
	    mesh->generateTangentBasis();

	if (flags.isSet(SendToGPU))
	    mesh->updateBuffers();

	return mesh;
    }

    Mesh::Mesh()
    {
	m_vertexBuffer = GL_INVALID_VALUE;
	m_indexBuffer = GL_INVALID_VALUE;
	m_normalBuffer = GL_INVALID_VALUE;
	m_uvBuffer = GL_INVALID_VALUE;
    }

    void Mesh::updateBuffers()
    {
	if (m_vertexBuffer == GL_INVALID_VALUE)
	    m_vertexBuffer = generateBuffer();
	fillBuffer(m_vertexBuffer, GL_ARRAY_BUFFER,
		m_vertices.size() * sizeof(Vec3f), &m_vertices[0],
		GL_STATIC_DRAW);

	if (m_indexBuffer == GL_INVALID_VALUE)
	    m_indexBuffer = generateBuffer();
	fillBuffer(m_indexBuffer, GL_ELEMENT_ARRAY_BUFFER,
		m_indices.size() * sizeof(unsigned short), &m_indices[0],
		GL_STATIC_DRAW);

	if (m_normals.size() > 0)
	{
	    if (m_normalBuffer == GL_INVALID_VALUE)
		m_normalBuffer = generateBuffer();
	    fillBuffer(m_normalBuffer, GL_ARRAY_BUFFER,
		    m_normals.size() * sizeof(Vec3f), &m_normals[0],
		    GL_STATIC_DRAW);
	}

	if (m_uv.size() > 0)
	{
	    if (m_uvBuffer == GL_INVALID_VALUE)
		m_uvBuffer = generateBuffer();
	    fillBuffer(m_uvBuffer, GL_ARRAY_BUFFER, m_uv.size() * sizeof(Vec2f),
		    &m_uv[0], GL_STATIC_DRAW);
	}

	if (m_tangents.size() > 0)
	{
	    if (m_tangentBuffer == GL_INVALID_VALUE)
		m_tangentBuffer = generateBuffer();
	    fillBuffer(m_tangentBuffer, GL_ARRAY_BUFFER,
		    m_tangents.size() * sizeof(Vec3f), &m_tangents[0],
		    GL_STATIC_DRAW);
	}

	if (m_bitangents.size() > 0)
	{
	    if (m_bitangentBuffer == GL_INVALID_VALUE)
		m_bitangentBuffer = generateBuffer();
	    fillBuffer(m_bitangentBuffer, GL_ARRAY_BUFFER,
		    m_bitangents.size() * sizeof(Vec3f), &m_bitangents[0],
		    GL_STATIC_DRAW);
	}
    }

    unsigned int Mesh::getVertexIndex(Vec3f const& coords)
    {
	// TODO: Accelerate w/ more sophisticated search
	for (unsigned int i = 0; i < m_vertices.size(); i++)
	{
	    if (m_vertices[i].isSimilar(coords, 0.001))
	    {
		return i;
	    }
	}
	return m_vertices.size();
    }

    void Mesh::generateTangentBasis()
    {
	// Allocate sufficient memory
	m_tangents.resize(m_vertices.size());
	m_bitangents.resize(m_vertices.size());

	for (unsigned int i = 0; i < m_indices.size(); i += 3)
	{
	    // Shortcuts
	    Vec3f& v0 = m_vertices[m_indices[i + 0]];
	    Vec3f& v1 = m_vertices[m_indices[i + 1]];
	    Vec3f& v2 = m_vertices[m_indices[i + 2]];
	    Vec2f& uv0 = m_uv[m_indices[i + 0]];
	    Vec2f& uv1 = m_uv[m_indices[i + 1]];
	    Vec2f& uv2 = m_uv[m_indices[i + 2]];

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
	    m_tangents[m_indices[i + 0]] += tangent;
	    m_tangents[m_indices[i + 1]] += tangent;
	    m_tangents[m_indices[i + 2]] += tangent;
	    m_bitangents[m_indices[i + 0]] += bitangent;
	    m_bitangents[m_indices[i + 1]] += bitangent;
	    m_bitangents[m_indices[i + 2]] += bitangent;
	}
	// Normalize tangents & bitangents
	for (unsigned int i = 0; i < m_tangents.size(); i++)
	{
	    m_tangents[i].normalize();
	    m_bitangents[i].normalize();
	}
	// Orthogonalize normal/tangent/bitangent system
	for (unsigned int i = 0; i < m_vertices.size(); i++)
	{
	    Vec3f& n = m_normals[i];
	    Vec3f& t = m_tangents[i];
	    Vec3f& b = m_bitangents[i];

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

    void Mesh::removeVertex(unsigned short i)
    {
	// Check if i is valid
	if (i >= m_vertices.size())
	{
	    std::stringstream msg;
	    msg << "Vertex index out of bounds: " << i;
	    throw std::out_of_range(msg.str());
	}

	// Remove vertex from list
	auto itVertex = m_vertices.begin() + i;
	m_vertices.erase(itVertex);
	if (i < m_normals.size())
	{
	    auto itNormal = m_normals.begin() + i;
	    m_normals.erase(itNormal);
	}
	if (i < m_uv.size())
	{
	    auto itUv = m_uv.begin() + i;
	    m_uv.erase(itUv);
	}
	if (i < m_tangents.size())
	{
	    auto itTangent = m_tangents.begin() + i;
	    m_tangents.erase(itTangent);
	}
	if (i < m_bitangents.size())
	{
	    auto itBitangent = m_bitangents.begin() + i;
	    m_bitangents.erase(itBitangent);
	}
	// The previous operation modified the indices of all vertices after the removed one,
	// thus we need to decrement every index greater than the removed one. Also every face
	// using the removed vertex needs to be removed as well
	for(auto it = m_indices.begin(); it != m_indices.end(); ++it)
	{
	    if(*it == i)
	    {
		unsigned int curIndex = it - m_indices.begin();
		unsigned int mod = curIndex % 3;
		for (unsigned int i = 0; i < mod; i++)
		    --it;
		it = m_indices.erase(it);
		it = m_indices.erase(it);
		it = m_indices.erase(it);
	    }
	    if(it == m_indices.end())
		break;
	    if (*it > i)
	    {
		(*it)--;
	    }
	}
    }

    GLuint Mesh::generateBuffer()
    {
	GLuint buffer;
	glGenBuffers(1, &buffer);
	return buffer;
    }

    void Mesh::fillBuffer(GLuint buffer, GLenum target, GLsizeiptr size,
	    const GLvoid* data, GLenum usage)
    {
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, usage);
    }
}

