//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef OBJMESHLOADER_H_
#define OBJMESHLOADER_H_

#include <limits>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Mesh.h"
#include "MeshLoader.h"
#include "DBGL/Math/Vector2.h"
#include "DBGL/Math/Vector3.h"

namespace dbgl
{
    /**
     * @brief Capable of loading meshes in OBJ file format
     */
    class OBJMeshLoader: public MeshLoader
    {
	public:
	    virtual Mesh* load(std::string path, Bitmask flags = 0);
	    void setNormalCompatibilityAngle(float angle);
	protected:
	    void clear();
	    bool loadData(std::string path, Bitmask flags = 0);
	    Mesh* interpret(Bitmask flags = 0);

	    struct FaceComponent
	    {
		public:
		    unsigned short vertexIndex = std::numeric_limits<unsigned short>::max();
		    unsigned short uvIndex = std::numeric_limits<unsigned short>::max();
		    unsigned short normalIndex = std::numeric_limits<unsigned short>::max();
	    };
	    struct Face
	    {
		public:
		    FaceComponent components[3];
	    };

	    float m_normalCompatibilityAngle = 1.3962634f; // 80°
	    std::vector<Face> m_origFaces;
	    std::vector<Vec3f> m_origVertices, m_origNormals;
	    std::vector<Vec2f> m_origUvs;
    };
}

#endif /* OBJMESHLOADER_H_ */
