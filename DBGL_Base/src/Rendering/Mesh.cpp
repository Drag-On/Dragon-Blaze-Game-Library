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

    Mesh* Mesh::load(const std::string path, const Type type)
    {
	switch (type)
	{
	    case OBJ:
		return loadOBJ(path);
	    default:
		LOG->warning("Format of file %s not recognized", path.c_str());
		return NULL;
	    }
	}

    Mesh* Mesh::makeTriangle()
    {
	Mesh* mesh = new Mesh();
	mesh->_vertices =
	{   -1, -1, 0, 1, -1, 0, 0, 1, 0};

	mesh->_normals =
	{   0, 0, 1, 0, 0, 1, 0, 0, 1};

	mesh->_uv =
	{   -1, -1, -1, 1, 1, 0};

	mesh->_indices =
	{   0, 1, 2};

	mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makePlane()
    {
	Mesh* mesh = new Mesh();
	mesh->_vertices =
	{   -1, -1, 0, -1, 1, 0, 1, 1, 0, 1, -1, 0};

	mesh->_normals =
	{   0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};

	mesh->_uv =
	{   -1, -1, -1, 1, 1, 1, 1, -1};

	mesh->_indices =
	{   0, 2, 1, 0, 3, 2};

	mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makeCube()
    {
	Mesh* mesh = new Mesh();

	// Define vertices
	mesh->_vertices =
	{
	    -1.0, -1.0, 1.0, // front 0
	    1.0, -1.0, 1.0,// 1
	    1.0, 1.0, 1.0,// 2
	    -1.0, 1.0, 1.0,// 3
	    -1.0, 1.0, 1.0,// top 4
	    1.0, 1.0, 1.0,// 5
	    1.0, 1.0, -1.0,// 6
	    -1.0, 1.0, -1.0,// 7
	    1.0, -1.0, -1.0,// back 8
	    -1.0, -1.0, -1.0,// 9
	    -1.0, 1.0, -1.0,// 10
	    1.0, 1.0, -1.0,// 11
	    -1.0, -1.0, -1.0,// bottom 12
	    1.0, -1.0, -1.0,// 13
	    1.0, -1.0, 1.0,// 14
	    -1.0, -1.0, 1.0,// 15
	    -1.0, -1.0, -1.0,// left 16
	    -1.0, -1.0, 1.0,// 17
	    -1.0, 1.0, 1.0,// 18
	    -1.0, 1.0, -1.0,// 19
	    1.0, -1.0, 1.0,// right 20
	    1.0, -1.0, -1.0,// 21
	    1.0, 1.0, -1.0,// 22
	    1.0, 1.0, 1.0,// 23
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
	    0, 0, 1, // 0 Front
	    0, 0, 1,// 1
	    0, 0, 1,// 2
	    0, 0, 1,// 3
	    0, 1, 0,// 10 Top
	    0, 1, 0,// 11
	    0, 1, 0,// 14
	    0, 1, 0,// 15
	    0, 0, -1,// 4 Back
	    0, 0, -1,// 5
	    0, 0, -1,// 6
	    0, 0, -1,// 7
	    0, -1, 0,// 8 Bottom
	    0, -1, 0,// 9
	    0, -1, 0,// 12
	    0, -1, 0,// 13
	    -1, 0, 0,// 16 Left
	    -1, 0, 0,// 19
	    -1, 0, 0,// 20
	    -1, 0, 0,// 23
	    1, 0, 0,// 21 Right
	    1, 0, 0,// 22
	    1, 0, 0,// 17
	    1, 0, 0,// 18
	};

	// Define UVs
	GLfloat uvs[2 * 4 * 6] = {
	0.0, 0.0, // front
	1.0, 0.0, //
	1.0, 1.0, //
	0.0, 1.0,
	};
	for (int i = 1; i < 6; i++)
	    memcpy(&uvs[i * 4 * 2], &uvs[0], 2 * 4 * sizeof(GLfloat));
	mesh->_uv.insert(mesh->_uv.begin(), std::begin(uvs), std::end(uvs));

	mesh->updateBuffers();

	return mesh;
    }

    Mesh* Mesh::makePyramid()
    {
	Mesh* mesh = new Mesh();

	// Define vertices
	mesh->_vertices =
	{   -1, -1, 1, // Front lower left 0
	    1, -1, 1,// Front lower right 1
	    0, 1, 0,// Front top 2
	    1, -1, 1,// Right lower left 3
	    1, -1, -1,// Right lower right 4
	    0, 1, 0,// Right top 5
	    1, -1, -1,// Back lower left 6
	    -1, -1, -1,// Back lower right 7
	    0, 1, 0,// Back top 8
	    -1, -1, -1,// Left lower left 9
	    -1, -1, 1,// Left lower right 10
	    0, 1, 0,// Left top 11
	    -1, -1, 1,// Bottom front left 12
	    1, -1, 1,// Bottom front right 13
	    -1, -1, -1,// Bottom back left 14
	    1, -1, -1,// Bottom back right 15
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
	    0, 0.4472, 0.8944, // front
	    0, 0.4472, 0.8944,// front
	    0, 0.4472, 0.8944,// front
	    0.8944, 0.4472, 0,// right
	    0.8944, 0.4472, 0,// right
	    0.8944, 0.4472, 0,// right
	    0, 0.4472, -0.8944,// back
	    0, 0.4472, -0.8944,// back
	    0, 0.4472, -0.8944,// back
	    -0.8944, 0.4472, 0,// left
	    -0.8944, 0.4472, 0,// left
	    -0.8944, 0.4472, 0,// left
	    0, -1, 0,// bottom
	    0, -1, 0,// bottom
	    0, -1, 0,// bottom
	    0, -1, 0,// bottom
	};

	// Define UVs
	mesh->_uv =
	{
	    0.0, 0.0, // front
	    1.0, 0.0,//
	    0.5, 1.0,//
	    0.0, 0.0,// right
	    1.0, 0.0,//
	    0.5, 1.0,//
	    0.0, 0.0,// back
	    1.0, 0.0,//
	    0.5, 1.0,//
	    0.0, 0.0,// left
	    1.0, 0.0,//
	    0.5, 1.0,//
	    0.0, 0.0,// bottom
	    1.0, 0.0,//
	    1.0, 1.0,//
	    0.0, 1.0,//
	};

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
		_vertices.size() * sizeof(GLfloat), &_vertices[0],
		GL_STATIC_DRAW);

	if (_indexBuffer == GL_INVALID_VALUE)
	    _indexBuffer = generateBuffer();
	fillBuffer(_indexBuffer, GL_ELEMENT_ARRAY_BUFFER,
		_indices.size() * sizeof(unsigned short), &_indices[0],
		GL_STATIC_DRAW);

	if (_normalBuffer == GL_INVALID_VALUE)
	    _normalBuffer = generateBuffer();
	fillBuffer(_normalBuffer, GL_ARRAY_BUFFER,
		_normals.size() * sizeof(GLfloat), &_normals[0],
		GL_STATIC_DRAW);

	if (_uvBuffer == GL_INVALID_VALUE)
	    _uvBuffer = generateBuffer();
	fillBuffer(_uvBuffer, GL_ARRAY_BUFFER, _uv.size() * sizeof(GLfloat),
		&_uv[0], GL_STATIC_DRAW);
    }

    unsigned int Mesh::getVertexIndex(Vec3f const& coords, Vec3f const& normal,
	    Vec2f const& uv)
    {
	for (unsigned int i = 0; i < _vertices.size(); i += 3)
	{
	    if (std::abs(_vertices[i + 0] - coords[0]) < 0.01
		    && std::abs(_vertices[i + 1] - coords[1]) < 0.01
		    && std::abs(_vertices[i + 2] - coords[2]) < 0.01
		    && std::abs(_normals[i + 0] - normal[0]) < 0.01
		    && std::abs(_normals[i + 1] - normal[1]) < 0.01
		    && std::abs(_normals[i + 2] - normal[2]) < 0.01
		    && std::abs(_uv[i / 3 * 2 + 0] - uv[0]) < 0.01
		    && std::abs(_uv[i / 3 * 2 + 1] - uv[1]) < 0.01)
	    {
		return i / 3;
	    }
	}
	return _vertices.size();
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
		    while (lineStream >> faceToken)
		    {
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
				    vertexIndices.push_back(curIndex - 1); // OBJ indices start with 1
				    break;
				case 1:
				    uvIndices.push_back(curIndex - 1);
				    break;
				case 2:
				    normalIndices.push_back(curIndex - 1);
				    break;
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
		// If the vertex has not been added yet, add it and the appropriate normals and uvs
		vertIndex = mesh->getVertexIndex(vertices[vertexIndices[i]],
			normal, uvs[uvIndices[i]]);
		if (normal.isZero() || vertIndex >= mesh->_vertices.size())
		{
		    vertIndex = mesh->_vertices.size() / 3;
		    mesh->_vertices.push_back(vertices[vertexIndices[i]][0]);
		    mesh->_vertices.push_back(vertices[vertexIndices[i]][1]);
		    mesh->_vertices.push_back(vertices[vertexIndices[i]][2]);
		    if (uvIndices.size() > i && uvs.size() > uvIndices[i])
		    {
			mesh->_uv.push_back(uvs[uvIndices[i]][0]);
			mesh->_uv.push_back(uvs[uvIndices[i]][1]);
		    }
		    if (normalIndices.size() > i
			    && normals.size() > normalIndices[i])
		    {
			mesh->_normals.push_back(normals[normalIndices[i]][0]);
			mesh->_normals.push_back(normals[normalIndices[i]][1]);
			mesh->_normals.push_back(normals[normalIndices[i]][2]);
		    }
		    else
		    {
			// No normal specified in file, so generate new one
			unsigned int firstIndex = i / 3 * 3;
			Vec3f dir1 = vertices[vertexIndices[firstIndex]]
				- vertices[vertexIndices[firstIndex + 1]];
			Vec3f dir2 = vertices[vertexIndices[firstIndex + 2]]
				- vertices[vertexIndices[firstIndex + 1]];
			Vec3f normal = dir2.getCrossProduct(dir1);
			mesh->_normals.push_back(normal[0]);
			mesh->_normals.push_back(normal[1]);
			mesh->_normals.push_back(normal[2]);
		    }
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

