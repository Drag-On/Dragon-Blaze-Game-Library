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
	    virtual Mesh* load(std::string path, Bitmask<> flags = 0);
	    /**
	     * @brief Sets the angle which is used to determine if an edge is phong shaded or not
	     * @param angle Normals with an angle smaller than this are phong shaded
	     */
	    void setNormalCompatibilityAngle(float angle);
	protected:
	    /**
	     * @brief Clears the loaders temporary data
	     */
	    void clear();
	    /**
	     * @brief Used internally to load an obj file into memory
	     * @param path Path of the obj file to load
	     * @param flags Flags to consider
	     * @return True in case the mesh was loaded, otherwise false
	     */
	    bool loadData(std::string path, Bitmask<> flags = 0);
	    /**
	     * @brief Analyzes the previously loaded data and creates a Mesh out of them
	     * @param flags Flags to consider
	     * @return Pointer to the created mesh. The mesh is created on the heap and thus needs
	     * 	       to be freed manually.
	     */
	    Mesh* interpret(Bitmask<> flags = 0);

	    /**
	     * @brief Every OBJ face consists of three vertices having a position and (possibly)
	     * 	      a UV and/or normal.
	     */
	    struct FaceComponent
	    {
		public:
		    /**
		     * @brief Index of the vertex (coordinate)
		     */
		    unsigned short vertexIndex = std::numeric_limits<unsigned short>::max();
		    /**
		     * @brief Index of the UV
		     */
		    unsigned short uvIndex = std::numeric_limits<unsigned short>::max();
		    /**
		     * @brief Index of the normal
		     */
		    unsigned short normalIndex = std::numeric_limits<unsigned short>::max();
	    };
	    /**
	     * @brief One face (i.e. polygon)
	     */
	    struct Face
	    {
		public:
		    /**
		     * @brief Components of a face. Currently only polygons with 3 vertices are allowed.
		     */
		    FaceComponent components[3];
	    };

	    /**
	     * @brief Angle used by interpret() to split phong shaded edges from others. Default: 80°.
	     */
	    float m_normalCompatibilityAngle = 1.3962634f;
	    /**
	     * @brief List the faces are written to
	     */
	    std::vector<Face> m_origFaces;
	    /**
	     * @brief List the normals are written to
	     */
	    std::vector<Vec3f> m_origVertices;
	    /**
	     * @brief List the vertices are written to
	     */
	    std::vector<Vec3f> m_origNormals;
	    /**
	     * @brief List the UVs are written to
	     */
	    std::vector<Vec2f> m_origUvs;
    };
}

#endif /* OBJMESHLOADER_H_ */
