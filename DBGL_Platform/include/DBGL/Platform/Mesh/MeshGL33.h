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
    class MeshGL33 : public IMesh
    {
	public:
	    virtual ~MeshGL33();
	    virtual std::vector<unsigned short>& indices();
	    virtual std::vector<Vertex>& vertices();
	    virtual std::vector<Vertex>& normals();
	    virtual std::vector<UV>& uvs();
	    virtual std::vector<Vertex>& tangents();
	    virtual std::vector<Vertex>& bitangents();
	    virtual void setUsage(Usage usage);
	    virtual Usage getUsage() const;
	    virtual void updateBuffers();

	private:
	    std::vector<unsigned short> m_indices;
	    GLuint m_indexBuffer = GL_INVALID_VALUE;
	    std::vector<Vertex> m_vertices;
	    GLuint m_vertexBuffer = GL_INVALID_VALUE;
	    std::vector<Vertex> m_normals;
	    GLuint m_normalBuffer = GL_INVALID_VALUE;
	    std::vector<UV> m_uv;
	    GLuint m_uvBuffer = GL_INVALID_VALUE;
	    std::vector<Vertex> m_tangents;
	    GLuint m_tangentBuffer = GL_INVALID_VALUE;
	    std::vector<Vertex> m_bitangents;
	    GLuint m_bitangentBuffer = GL_INVALID_VALUE;
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

	    friend class RenderContextGL33;
    };
}

#endif /* MESHGL33_H_ */