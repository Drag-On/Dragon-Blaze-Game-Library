//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MESH_H_
#define MESH_H_

#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "Log/Log.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace dbgl
{
    /**
     * @brief Represents a 3D model which can be rendered to the screen
     */
    class Mesh
    {
	public:
	    /**
	     * @brief File types which can be loaded
	     */
	    enum Type
	    {
		OBJ,//!< OBJ
	    };

	    /**
	     * @brief Clean up memory
	     */
	    ~Mesh();
	    /**
	     * @brief Loads a mesh from hard disk
	     * @param path Path of the file
	     * @param type File type to load
	     * @return The loaded mesh or NULL if something went wrong
	     */
	    static Mesh* load(const std::string path, const Type type);
	    /**
	     * @brief Creates a mesh that represents a simple triangle
	     * @warning The allocated memory needs to be freed manually!
	     * @return The triangle mesh
	     */
	    static Mesh* makeTriangle();
	    /**
	     * @brief Creates a mesh that represents a simple plane
	     * @warning The allocated memory needs to be freed manually!
	     * @return The plane mesh
	     */
	    static Mesh* makePlane();
	    /**
	     * @brief Creates a mesh that represents a cube
	     * @warning The allocated memory needs to be freed manually!
	     * @return The cube mesh
	     */
	    static Mesh* makeCube();
	    /**
	     * @brief Creates a mesh that represents a four-sided pyramid
	     * @warning The allocated memory needs to be freed manually!
	     * @return The pyramid mesh
	     */
	    static Mesh* makePyramid();
	private:
	    /**
	     * @brief Private constructor; use factory methods!
	     */
	    Mesh();
	    /**
	     * @brief Checks, if the mesh has a vertex with the passed coordinates
	     * 	      (or at least very, very similar)
	     * @param coords Coordinates to search for
	     * @return True in case the coordinates are already known,
	     * 	       otherwise false
	     */
	    bool hasVertex(Vec3f coords);
	    /**
	     * @brief Generates a gl buffer
	     * @return Buffer identifier
	     * @warning The generated buffer needs to be deleted using glDeleteBuffers
	     */
	    static GLuint generateBuffer();
	    /**
	     * @brief Fills a buffer with data
	     * @param buffer Buffer to fill
	     * @param target Type of buffer, e.g. GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER
	     * @param size Buffer size
	     * @param data Data to store
	     * @param usage Expected usage, e.g. GL_STATIC_DRAW
	     * @return Buffer identifier
	     */
	    static void fillBuffer(GLuint buffer, GLenum target,
		    GLsizeiptr size, const GLvoid* data, GLenum usage);
	    /**
	     * @brief Loads a mesh in OBJ file format
	     * @param path Path of the file
	     * @return The loaded mesh
	     */
	    static Mesh* loadOBJ(const std::string path);

	    std::vector<unsigned short> _indices;
	    GLuint _indexBuffer;
	    std::vector<GLfloat> _vertices;
	    GLuint _vertexBuffer;
	    std::vector<GLfloat> _normals;
	    GLuint _normalBuffer;
	    std::vector<GLfloat> _color;
	    GLuint _colorBuffer;
	    std::vector<GLfloat> _uv;
	    GLuint _uvBuffer; // = GL_INVALID_VALUE

	    friend class RenderContext;
	    // So the render context can render
    };
}

#endif /* MESH_H_ */
