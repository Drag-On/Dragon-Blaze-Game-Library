//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/Mesh/OBJMeshLoader.h"

namespace dbgl
{
    Mesh* OBJMeshLoader::load(std::string path, Bitmask flags)
    {
	Mesh* mesh = nullptr;
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
			return nullptr;
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
			return nullptr;
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
			return nullptr;
		    }
		    // Store normal; normals in OBJs might not be normalized, so normalize them here
		    normals.push_back(Vec3f(coords[0], coords[1], coords[2]).normalize());
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
			    if(curElement.empty())
			    continue;
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
	    // Check if UVs have been read from file
	    if (uvIndices.size() < vertexIndices.size())
	    {
		LOG->warning("No UVs specified in %s. This is currently not supported.", path.c_str());
		return nullptr;
	    }
	    // Merge to one single index and save in new mesh
	    mesh = new Mesh();
	    for (unsigned int i = 0; i < vertexIndices.size(); i++)
	    {
		// Generate normal if none has been in the file
		Vec3f normal;
		unsigned int vertIndex;
		if (normalIndices.size() > i && normals.size() > normalIndices[i])
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
		vertIndex = mesh->getVertexIndex(vertices[vertexIndices[i]]);
		if (vertIndex < mesh->vertices().size())
		{
		    // Vertex with similar coordinates has been found
		    // Check if normal and UVs are compatible and average them if they are
		    if (flags.isSet(Mesh::Optimize) && mesh->normals()[vertIndex].dot(normal) < 1.3962634 &&  // < 80°
			    mesh->uvs()[vertIndex].isSimilar(uvs[uvIndices[i]]))
		    {
			mesh->normals()[vertIndex] += normal;
			mesh->normals()[vertIndex].normalize();
			mesh->uvs()[vertIndex] += uvs[uvIndices[i]];
			mesh->uvs()[vertIndex] /= 2;
		    }
		    else
		    {
			// Normal or UVs don't match, so a new vertex has to be added
			vertIndex = mesh->vertices().size();
		    }
		}
		if (vertIndex == mesh->vertices().size())
		{
		    // No vertex with similar coordinates has been found
		    mesh->vertices().push_back(vertices[vertexIndices[i]]);
		    if (uvIndices.size() > i && uvs.size() > uvIndices[i])
		    {
			mesh->uvs().push_back(uvs[uvIndices[i]]);
		    }
		    mesh->normals().push_back(normal);
		}
		mesh->indices().push_back(vertIndex);
	    }
	}
	else
	{
	    LOG->warning("File %s not found", path.c_str());
	    return nullptr;
	}

	// Generate tangent base if requested
	if (flags.isSet(Mesh::GenerateTangentBase))
	    mesh->generateTangentBasis();

	// Send data to gl buffers if requested
	if (flags.isSet(Mesh::SendToGPU))
	    mesh->updateBuffers();

	return mesh;
    }
}
