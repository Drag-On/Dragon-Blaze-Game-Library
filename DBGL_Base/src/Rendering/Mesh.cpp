//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/Mesh.h"

namespace dbgl
{
    Mesh::~Mesh()
    {
	// Properly delete all buffers
	if (_indexBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_indexBuffer);
	if (_vertexBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_vertexBuffer);
	if (_normalBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_normalBuffer);
	if (_uvBuffer != GL_INVALID_VALUE)
	    glDeleteBuffers(1, &_uvBuffer);
    }

    Mesh* Mesh::load(const std::string path, const Type type,
	    bool generateTangentBase)
    {
	switch (type)
	{
	    case OBJ:
	    {
		Mesh* mesh = loadOBJ(path);
		if (generateTangentBase)
		{
		    mesh->generateTangentBasis();
		    mesh->updateBuffers();
		}
		return mesh;
	    }
	    default:
	    {
		LOG->warning("Format of file %s not recognized", path.c_str());
		return NULL;
	    }
	}
    }

    Mesh* Mesh::makeTriangle(bool generateTangentBase)
    {
	Mesh* mesh = new Mesh();
	mesh->_vertices =
	{   Vec3f(-1, -1, 0), Vec3f(1, -1, 0), Vec3f(0, 1, 0)};

	mesh->_normals =
	{   Vec3f(0, 0, 1), Vec3f(0, 0, 1), Vec3f(0, 0, 1)};

	mesh->_uv =
	{   Vec2f(0, 0), Vec2f(0.5, 0.5), Vec2f(1, 0)};

	mesh->_indices =
	{   0, 1, 2};

	// Generate tangents and bitangents
	if (generateTangentBase)
	    mesh->generateTangentBasis();

	mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makePlane(bool generateTangentBase)
    {
	Mesh* mesh = new Mesh();
	mesh->_vertices =
	{   Vec3f(-1, -1, 0), Vec3f(-1, 1, 0), Vec3f(1, 1, 0), Vec3f(1, -1, 0)};

	mesh->_normals =
	{   Vec3f(0, 0, 1), Vec3f(0, 0, 1), Vec3f(0, 0, 1), Vec3f(0, 0, 1)};

	mesh->_uv =
	{   Vec2f(0, 0), Vec2f(0, 1), Vec2f(1, 1), Vec2f(1, 0)};

	mesh->_indices =
	{   0, 2, 1, 0, 3, 2};

	// Generate tangents and bitangents
	if (generateTangentBase)
	    mesh->generateTangentBasis();

	mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makeCube(bool generateTangentBase)
    {
	Mesh* mesh = new Mesh();

	// Define vertices
	mesh->_vertices =
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
	mesh->_indices =
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
	mesh->_normals =
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
	mesh->_uv.insert(mesh->_uv.begin(), std::begin(uvs), std::end(uvs));

	// Generate tangents and bitangents
	if (generateTangentBase)
	    mesh->generateTangentBasis();

	mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makePyramid(bool generateTangentBase)
    {
	Mesh* mesh = new Mesh();

	// Define vertices
	mesh->_vertices =
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
	mesh->_indices =
	{
	    0, 1, 2, // front
	    3, 4, 5,// right
	    6, 7, 8,// back
	    9, 10, 11,// left
	    12, 14, 13,// bottom left
	    14, 15, 13,// bottom right
	};

	// Define normals
	mesh->_normals =
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
	mesh->_uv =
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
	if (generateTangentBase)
	    mesh->generateTangentBasis();

	mesh->updateBuffers();

	return mesh;
    }

    Mesh::Mesh()
    {
	_vertexBuffer = GL_INVALID_VALUE;
	_indexBuffer = GL_INVALID_VALUE;
	_normalBuffer = GL_INVALID_VALUE;
	_uvBuffer = GL_INVALID_VALUE;
    }

    void Mesh::updateBuffers()
    {
	if (_vertexBuffer == GL_INVALID_VALUE)
	    _vertexBuffer = generateBuffer();
	fillBuffer(_vertexBuffer, GL_ARRAY_BUFFER,
		_vertices.size() * sizeof(Vec3f), &_vertices[0],
		GL_STATIC_DRAW);

	if (_indexBuffer == GL_INVALID_VALUE)
	    _indexBuffer = generateBuffer();
	fillBuffer(_indexBuffer, GL_ELEMENT_ARRAY_BUFFER,
		_indices.size() * sizeof(unsigned short), &_indices[0],
		GL_STATIC_DRAW);

	if (_normals.size() > 0)
	{
	    if (_normalBuffer == GL_INVALID_VALUE)
		_normalBuffer = generateBuffer();
	    fillBuffer(_normalBuffer, GL_ARRAY_BUFFER,
		    _normals.size() * sizeof(Vec3f), &_normals[0],
		    GL_STATIC_DRAW);
	}

	if (_uv.size() > 0)
	{
	    if (_uvBuffer == GL_INVALID_VALUE)
		_uvBuffer = generateBuffer();
	    fillBuffer(_uvBuffer, GL_ARRAY_BUFFER, _uv.size() * sizeof(Vec2f),
		    &_uv[0], GL_STATIC_DRAW);
	}

	if (_tangents.size() > 0)
	{
	    if (_tangentBuffer == GL_INVALID_VALUE)
		_tangentBuffer = generateBuffer();
	    fillBuffer(_tangentBuffer, GL_ARRAY_BUFFER,
		    _tangents.size() * sizeof(Vec3f), &_tangents[0],
		    GL_STATIC_DRAW);
	}

	if (_bitangents.size() > 0)
	{
	    if (_bitangentBuffer == GL_INVALID_VALUE)
		_bitangentBuffer = generateBuffer();
	    fillBuffer(_bitangentBuffer, GL_ARRAY_BUFFER,
		    _bitangents.size() * sizeof(Vec3f), &_bitangents[0],
		    GL_STATIC_DRAW);
	}
    }

    unsigned int Mesh::getVertexIndex(Vec3f const& coords, Vec3f const& normal,
	    Vec2f const& uv)
    {
	for (unsigned int i = 0; i < _vertices.size(); i++)
	{
	    if (_vertices[i].isSimilar(coords) && _normals[i].isSimilar(normal)
		    && _uv[i].isSimilar(uv))
	    {
		return i;
	    }
	}
	return _vertices.size();
    }

    void Mesh::generateTangentBasis()
    {
	// Allocate sufficient memory
	_tangents.resize(_vertices.size());
	_bitangents.resize(_vertices.size());

	for (unsigned int i = 0; i < _indices.size(); i += 3)
	{
	    // Shortcuts
	    Vec3f& v0 = _vertices[_indices[i + 0]];
	    Vec3f& v1 = _vertices[_indices[i + 1]];
	    Vec3f& v2 = _vertices[_indices[i + 2]];
	    Vec2f& uv0 = _uv[_indices[i + 0]];
	    Vec2f& uv1 = _uv[_indices[i + 1]];
	    Vec2f& uv2 = _uv[_indices[i + 2]];

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
	    _tangents[_indices[i + 0]] += tangent;
	    _tangents[_indices[i + 1]] += tangent;
	    _tangents[_indices[i + 2]] += tangent;
	    _bitangents[_indices[i + 0]] += bitangent;
	    _bitangents[_indices[i + 1]] += bitangent;
	    _bitangents[_indices[i + 2]] += bitangent;
	}
	// TODO: Normalize tangents & bitangents?
//	for (unsigned int i = 0; i < _tangents.size(); i++)
//	{
//	    _tangents[i].normalize();
//	    _bitangents[i].normalize();
//	}
	// Orthogonalize normal/tangent/bitangent system
	for (unsigned int i = 0; i < _vertices.size(); i++)
	{
	    Vec3f& n = _normals[i];
	    Vec3f& t = _tangents[i];
	    Vec3f& b = _bitangents[i];

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

    Mesh* Mesh::loadOBJ(const std::string path)
    {
	Mesh* mesh = NULL;
	// Read file
	std::ifstream file;
	file.open(path.c_str(), std::ios::in);
	if (file.is_open())
	{
	    file.seekg(0, std::ios::beg);
	    std::vector<Vec3f> vertices, normals;
	    std::vector<Vec2f> uvs;
	    std::vector<float> curValues;
	    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	    std::string token;
	    std::string line;
	    // Scan whole file
	    while (file.good())
	    {
		// Read line
		std::getline(file, line);
		if (line.length() == 0) // Skip empty lines
		    continue;
		std::istringstream lineStream;
		lineStream.str(line);
		// Check first token
		lineStream >> token;
		if (token == "v") // Vertex definition
		{
		    // Read in all coordinates that follow
		    std::vector<float> coords;
		    float coord = 0;
		    while (lineStream >> coord)
		    {
			coords.push_back(coord);
		    }
		    // Everything after the 3rd coordinate will be discarded, so warn
		    if (coords.size() > 3)
		    {
			LOG->warning("File %s has vertex definitions with more than 3 coordinates", path.c_str());
		    }
		    // If less than 3 coordinates the file is misformatted
		    else if(coords.size() < 3)
		    {
			LOG->error("File %s has vertex definitions with less than 3 coordinates", path.c_str());
			file.close();
			return NULL;
		    }
		    // Store vertex
		    vertices.push_back(Vec3f(coords[0], coords[1], coords[2]));
		}
		else if (token == "vt") // UV definition
		{
		    // Read in all coordinates that follow
		    std::vector<float> coords;
		    float coord;
		    while (lineStream >> coord)
		    {
			coords.push_back(coord);
		    }
		    // Everything after the 2rd coordinate will be discarded, so warn
		    if (coords.size() > 3)
		    {
			LOG->warning("File %s has UV definitions with more than 3 coordinates", path.c_str());
		    }
		    // If less than 2 coordinates the file is misformatted
		    else if(coords.size() < 2)
		    {
			LOG->error("File %s has UV definitions with less than 2 coordinates", path.c_str());
			file.close();
			return NULL;
		    }
		    // Store uv
		    uvs.push_back(Vec2f(coords[0], coords[1]));
		}
		else if (token == "vn") // Normal definition
		{
		    // Read in all coordinates that follow
		    std::vector<float> coords;
		    float coord;
		    while (lineStream >> coord)
		    {
			coords.push_back(coord);
		    }
		    // Everything after the 3rd coordinate will be discarded, so warn
		    if (coords.size() > 3)
		    {
			LOG->warning("File %s has normal definitions with more than 3 coordinates", path.c_str());
		    }
		    // If less than 3 coordinates the file is misformatted
		    else if(coords.size() < 3)
		    {
			LOG->error("File %s has normal definitions with less than 3 coordinates", path.c_str());
			file.close();
			return NULL;
		    }
		    // Store normal; normals in OBJs might not be normalized, so normalize them here
		    normals.push_back(
			    Vec3f(coords[0], coords[1], coords[2]).normalize());
		}
		else if (token == "f") // Face definition
		{
		    // Read in all indices
		    std::string faceToken;
		    for (int j = 0; lineStream >> faceToken; j++)
		    {
			if (j >= 3)
			{
			    LOG->warning("File %s contains polygons with more than 3 vertices", path.c_str());
			    break;
			}
			std::string curElement;
			std::stringstream tokenStream;
			tokenStream.str(faceToken);
			for (int k = 0;
				std::getline(tokenStream, curElement, '/'); k++)
			{
			    int curIndex;
			    std::stringstream(curElement) >> curIndex;
			    switch (k)
			    {
				case 0:
				{
				    vertexIndices.push_back(curIndex - 1); // OBJ indices start with 1
				    break;
				}
				case 1:
				{
				    uvIndices.push_back(curIndex - 1);
				    break;
				}
				case 2:
				{
				    normalIndices.push_back(curIndex - 1);
				    break;
				}
				default:
				{
				    LOG->warning("File %s misformatted: more than 3 indices", path.c_str());
				    break;
				}
			    }
			}
		    }
		}
		else
		{
		    // Might be a comment or some other line we can skip
		    continue;
		}
	    }
	    // Close file
	    file.close();
	    // Merge to one single index and save in new mesh
	    mesh = new Mesh();
	    for (unsigned int i = 0; i < vertexIndices.size(); i++)
	    {
		// Generate normal if none has been in the file
		Vec3f normal;
		unsigned int vertIndex;
		if (normalIndices.size() > i
			&& normals.size() > normalIndices[i])
		{
		    // Use normal from file
		    normal = normals[normalIndices[i]];
		}
		else
		{
		    // No normal specified in file, so generate new one
		    unsigned int firstIndex = i / 3 * 3;
		    Vec3f dir1 = vertices[vertexIndices[firstIndex]]
			    - vertices[vertexIndices[firstIndex + 1]];
		    Vec3f dir2 = vertices[vertexIndices[firstIndex + 2]]
			    - vertices[vertexIndices[firstIndex + 1]];
		    normal = dir2.cross(dir1).normalize();
		}
		// If the vertex has not been added yet, add it and the appropriate normals and uvs
		vertIndex = mesh->getVertexIndex(vertices[vertexIndices[i]],
			normal, uvs[uvIndices[i]]);
		if (vertIndex == mesh->_vertices.size())
		{
		    mesh->_vertices.push_back(vertices[vertexIndices[i]]);
		    if (uvIndices.size() > i && uvs.size() > uvIndices[i])
		    {
			mesh->_uv.push_back(uvs[uvIndices[i]]);
		    }
		    mesh->_normals.push_back(normal);
		}
		mesh->_indices.push_back(vertIndex);
	    }
	}
	else
	{
	    LOG->warning("File %s not found", path.c_str());
	    return NULL;
	}
	// Send data to gl buffers
	mesh->updateBuffers();
	return mesh;
    }
}

