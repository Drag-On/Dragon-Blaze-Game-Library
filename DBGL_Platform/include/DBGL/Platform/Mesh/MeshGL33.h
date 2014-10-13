//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MESHGL33_H_
#define MESHGL33_H_

#include <GL/glew.h>
#include "IMesh.h"

namespace dbgl
{
    /**
     * @brief OpenGL 3.3 implementation of the mesh class.
     */
    class MeshGL33 : public IMesh
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~MeshGL33();
	    /**
	     * @copydoc IMesh::indices()
	     */
	    virtual std::vector<unsigned short>& indices();
	    /**
	     * @copydoc IMesh::vertices()
	     */
	    virtual std::vector<Vertex>& vertices();
	    /**
	     * @copydoc IMesh::normals()
	     */
	    virtual std::vector<Vertex>& normals();
	    /**
	     * @copydoc IMesh::uvs()
	     */
	    virtual std::vector<UV>& uvs();
	    /**
	     * @copydoc IMesh::tangents()
	     */
	    virtual std::vector<Vertex>& tangents();
	    /**
	     * @copydoc IMesh::bitangents()
	     */
	    virtual std::vector<Vertex>& bitangents();
	    /**
	     * @copydoc IMesh::getIndexCount()
	     */
	    virtual unsigned int getIndexCount() const;
	    /**
	     * @copydoc IMesh::getVertexCount()
	     */
	    virtual unsigned int getVertexCount() const;
	    /**
	     * @copydoc IMesh::getUVCount()
	     */
	    virtual unsigned int getUVCount() const;
	    /**
	     * @copydoc IMesh::getNormalCount()
	     */
	    virtual unsigned int getNormalCount() const;
	    /**
	     * @copydoc IMesh::getTangentCount()
	     */
	    virtual unsigned int getTangentCount() const;
	    /**
	     * @copydoc IMesh::getBitangentCount()
	     */
	    virtual unsigned int getBitangentCount() const;
	    /**
	     * @copydoc IMesh::setUsage()
	     */
	    virtual void setUsage(Usage usage);
	    /**
	     * @copydoc IMesh::getUsage()
	     */
	    virtual Usage getUsage() const;
	    /**
	     * @copydoc IMesh::updateBuffers()
	     */
	    virtual void updateBuffers();
	    /**
	     * @return Internal index buffer handle
	     */
	    GLuint getIndexHandle() const;
	    /**
	     * @return Internal vertex buffer handle
	     */
	    GLuint getVertexHandle() const;
	    /**
	     * @return Internal normal buffer handle
	     */
	    GLuint getNormalHandle() const;
	    /**
	     * @return Internal uv buffer handle
	     */
	    GLuint getUVHandle() const;
	    /**
	     * @return Internal tangent buffer handle
	     */
	    GLuint getTangentHandle() const;
	    /**
	     * @return Internal bitangent buffer handle
	     */
	    GLuint getBitangentHandle() const;

	private:
	    std::vector<unsigned short> m_indices;
	    GLuint m_indexBuffer = GL_INVALID_VALUE;
	    unsigned int m_indexCount = 0;
	    std::vector<Vertex> m_vertices;
	    GLuint m_vertexBuffer = GL_INVALID_VALUE;
	    unsigned int m_vertexCount = 0;
	    std::vector<Vertex> m_normals;
	    GLuint m_normalBuffer = GL_INVALID_VALUE;
	    unsigned int m_normalsCount = 0;
	    std::vector<UV> m_uv;
	    GLuint m_uvBuffer = GL_INVALID_VALUE;
	    unsigned int m_uvCount = 0;
	    std::vector<Vertex> m_tangents;
	    GLuint m_tangentBuffer = GL_INVALID_VALUE;
	    unsigned int m_tangentCount = 0;
	    std::vector<Vertex> m_bitangents;
	    GLuint m_bitangentBuffer = GL_INVALID_VALUE;
	    unsigned int m_bitangentCount = 0;
	    Usage m_usage = Usage::StaticDraw;

	    /**
	     * @brief Converts the Usage enum into a GLenum
	     * @return
	     */
	    static GLenum convertUsage(Usage usage);
	    /**
	     * @brief Generates a gl buffer
	     * @return Buffer identifier or GL_INVALID_VALUE if something went wrong
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
	    static void fillBuffer(GLuint buffer, GLenum target, GLsizeiptr size, const GLvoid* data,
		    GLenum usage);
    };
}

#endif /* MESHGL33_H_ */
