//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Mesh/OBJMeshLoader.h"

namespace dbgl
{
    Mesh* OBJMeshLoader::load(std::string path, Bitmask flags)
    {
	clear();

	Mesh* mesh = nullptr;
	if(!loadData(path, flags))
	{
	    LOG->error("Loading file %s failed.", path.c_str());
	    return nullptr;
	}
	mesh = interpret(flags);
	if(!mesh)
	{
	    LOG->error("Postprocessing of file %s failed.", path.c_str());
	    return nullptr;
	}

	// Generate tangent base if requested
	if (flags.isSet(Mesh::GenerateTangentBase))
	    mesh->generateTangentBasis();

	// Send data to gl buffers if requested
	if (flags.isSet(Mesh::SendToGPU))
	    mesh->updateBuffers();

	Log::inf << "Loaded model " << path << " with " << mesh->getIndices().size() / 3 << " faces, ";
	Log::inf << mesh->getVertices().size() << " vertices." << std::flush;

	return mesh;
    }

    void OBJMeshLoader::clear()
    {
	m_origFaces.clear();
	m_origVertices.clear();
	m_origUvs.clear();
	m_origNormals.clear();
    }

    bool OBJMeshLoader::loadData(std::string path, Bitmask /* flags */)
    {
	// Read file
	std::ifstream file;
	file.open(path.c_str(), std::ios::in);
	if (file.is_open())
	{
	    file.seekg(0, std::ios::beg);
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
		    float curCoord = 0;
		    while (lineStream >> curCoord)
			coords.push_back(curCoord);
		    // Everything after the 3rd coordinate will be discarded, so warn
		    if (coords.size() > 3)
			LOG->warning("File %s has vertex definitions with more than 3 coordinates", path.c_str());
		    // If less than 3 coordinates the file is misformatted
		    else if(coords.size() < 3)
		    {
			LOG->error("File %s has vertex definitions with less than 3 coordinates", path.c_str());
			file.close();
			return false;
		    }
		    // Store vertex
		    m_origVertices.push_back(Vec3f(coords[0], coords[1], coords[2]));
		}
		else if (token == "vt") // UV definition
		{
		    // Read in all coordinates that follow
		    std::vector<float> uvs;
		    float curUv;
		    while (lineStream >> curUv)
			uvs.push_back(curUv);
		    // Everything after the 3rd coordinate will be discarded, so warn
		    if (uvs.size() > 3)
			LOG->warning("File %s has UV definitions with more than 3 coordinates", path.c_str());
		    // If less than 2 coordinates the file is misformatted
		    else if(uvs.size() < 2)
		    {
			LOG->error("File %s has UV definitions with less than 2 coordinates", path.c_str());
			file.close();
			return false;
		    }
		    // Store uv
		    m_origUvs.push_back(Vec2f(uvs[0], uvs[1]));
		}
		else if (token == "vn") // Normal definition
		{
		    // Read in all coordinates that follow
		    std::vector<float> normals;
		    float curCoord;
		    while (lineStream >> curCoord)
			normals.push_back(curCoord);
		    // Everything after the 3rd coordinate will be discarded, so warn
		    if (normals.size() > 3)
			LOG->warning("File %s has normal definitions with more than 3 coordinates", path.c_str());
		    // If less than 3 coordinates the file is misformatted
		    else if(normals.size() < 3)
		    {
			LOG->error("File %s has normal definitions with less than 3 coordinates", path.c_str());
			file.close();
			return false;
		    }
		    // Store normal; normals in OBJs might not be normalized, so normalize them here
		    m_origNormals.push_back(Vec3f(normals[0], normals[1], normals[2]).normalize());
		}
		else if (token == "f") // Face definition
		{
		    // Read in all indices
		    std::string faceToken;
		    Face curFace;
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
			FaceComponent curFaceComponent;
			for (int k = 0; std::getline(tokenStream, curElement, '/'); k++)
			{
			    if(curElement.empty())
				continue;
			    int curIndex;
			    std::stringstream(curElement) >> curIndex;
			    switch (k)
			    {
				case 0:
				{
				    curFaceComponent.vertexIndex = curIndex - 1; // OBJ indices start with 1
				    break;
				}
				case 1:
				{
				    curFaceComponent.uvIndex = curIndex - 1;
				    break;
				}
				case 2:
				{
				    curFaceComponent.normalIndex = curIndex - 1;
				    break;
				}
				default:
				{
				    LOG->warning("File %s misformatted: more than 3 indices", path.c_str());
				    break;
				}
			    }
			}
			curFace.components[j] = curFaceComponent;
		    }
		    // Store face
		    m_origFaces.push_back(curFace);
		}
		else
		{
		    // Might be a comment or some other line we can skip
		    continue;
		}
	    }
	    // Close file
	    file.close();

	    return true;
	}
	else
	{
	    LOG->warning("File %s not found", path.c_str());
	    return false;
	}
    }

    Mesh* OBJMeshLoader::interpret(Bitmask flags)
    {
	// Merge to one single index and save in new mesh
	auto mesh = new Mesh();
	// Iterate over all faces
	for(unsigned int i = 0; i < m_origFaces.size(); i++)
	{
	    auto curFace = m_origFaces[i];
	    // Iterate over all 3 vertices in a face
	    for(unsigned int j = 0; j < 3; j++)
	    {
		Vec3f vertex, normal;
		Vec2f uv;
		// Get vertex
		if(m_origVertices.size() > curFace.components[j].vertexIndex)
		    vertex = m_origVertices[curFace.components[j].vertexIndex];
		else
		{
		    // This should never happen
		    LOG->warning("Misformatted mesh: Vertex index points to non-existent vertex.");
		    return nullptr;
		}
		// Get UV
		bool useUv = true;
		if(m_origUvs.size() > curFace.components[j].uvIndex)
		    uv = m_origUvs[curFace.components[j].uvIndex];
		else
		    useUv = false;
		// Get normal
		if (m_origNormals.size() > curFace.components[j].normalIndex)
		    normal = m_origNormals[curFace.components[j].normalIndex];
		else
		{
		    // No normal specified in file, so generate one
		    Vec3f dir1 = m_origVertices[curFace.components[0].vertexIndex]
			    - m_origVertices[curFace.components[1].vertexIndex];
		    Vec3f dir2 = m_origVertices[curFace.components[2].vertexIndex]
			    - m_origVertices[curFace.components[1].vertexIndex];
		    normal = dir2.cross(dir1).normalize();
		}
		// Check if there already is a vertex with the same (or very similar) coordinates.
		// If a vertex like this is found and the normals are compatible they can be merged,
		// otherwise we need to add a new vertex
		auto vertIndex = mesh->getVertexIndex(vertex);
		bool compatible = false;
		if (vertIndex < mesh->vertices().size() && flags.isSet(Mesh::Optimize))
		{
		    // A vertex with appropriate coordinates has been found; now check if normals
		    // are compatible (and, if there are uvs, they need to be compatible too
		    auto theta = mesh->normals()[vertIndex].getNormalized().dot(normal.getNormalized());
		    if (theta < -1.0)
			theta = -1.0f;
		    else if (theta > 1.0)
			theta = 1.0f;
		    auto angle = std::acos(theta);
		    bool uvCompatibility = useUv ? mesh->uvs()[vertIndex].isSimilar(uv, 0.01) : true;
		    if ((angle < NormalCompatibilityAngle) && uvCompatibility)
		    {
			auto prev = mesh->normals()[vertIndex];

			// They are compatible, now average normal and uv
			mesh->normals()[vertIndex] += normal;
			mesh->normals()[vertIndex].normalize();
			if (useUv)
			{
			    mesh->uvs()[vertIndex] += uv;
			    mesh->uvs()[vertIndex] /= 2;
			}
			compatible = true;
		    }
		}
		if (!compatible)
		{
		    // No compatibility in one way or another, thus add new vertex, normal and uv.
		    // Since there is no compatible vertex the new one has to be added in the end.
		    vertIndex = mesh->vertices().size();
		    mesh->vertices().push_back(vertex);
		    if (useUv)
			mesh->uvs().push_back(uv);
		    mesh->normals().push_back(normal);
		}
		// Add the index (which either points to the end of the list or to previously added elements)
		mesh->indices().push_back(vertIndex);
	    }
	}
	return mesh;
    }
}
