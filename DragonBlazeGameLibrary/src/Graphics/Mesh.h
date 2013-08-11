/*
 * Mesh.h
 *
 *  Created on: 10.08.2013
 *      Author: Drag-On
 */

#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include "RenderContext.h"

namespace DBGL
{
/**
 * Represents a polygon mesh which can be rendered to any render context
 */
class Mesh
{
public:

	/**
	 * Defines the format of attribute data that is uploaded to the graphics card
	 */
	struct AttributeFormat
	{
		GLuint attributeHandle; // Handle of the dedicated attribute
		GLint size; // Amount of elements per vertex
		GLenum type; // Element type
		GLsizei normalized; // True if data should be normalized
		GLsizei stride; // Byte offset between consecutive generic vertex attributes
		const GLvoid* pointer; // Offset of first element
	};

	/**
	 * Constructor
	 * @param vertices Array containing vertex position data.
	 * @param length Length of the vertices array
	 * @param attrFormat Format of the vertex array
	 * @attention Both heap objects will be maintained by the Mesh class (includes delete)
	 */
	Mesh(GLfloat* vertices, int length, AttributeFormat* attrFormat);

	/**
	 * Destructor
	 */
	virtual ~Mesh();

	/**
	 * @return Vertex array
	 */
	GLfloat* getVertices() const;

	/**
	 * @return Attribute format of the vertex data
	 */
	AttributeFormat* getVertexFormat() const;

	/**
	 * @return Handle of the VBO where the vertex data is stored
	 */
	GLuint getVertexVBOHandle() const;

	/**
	 * @brief Adds some color data to the mesh
	 * @param colorData Raw color data
	 * @param length Length of the colorData array
	 * @param attrFormat Format of the colorData array
	 * @attention Both heap objects will be maintained by the Mesh class (includes delete)
	 */
	void setColorData(GLfloat* colorData, int length,
			AttributeFormat* attrFormat);

	/**
	 * @return Color data array
	 */
	GLfloat* getColorData() const;

	/**
	 * @return Attribute format of the color data
	 */
	AttributeFormat* getColorFormat() const;

	/**
	 * @return Handle of the VBO where the color data is stored
	 */
	GLuint getColorVBOHandle() const;

private:
	GLfloat* _pVertices; // Vertex data
	AttributeFormat* _pVertexFormat; // Attribute format used by vertex data
	GLuint _vertexVBOHandle; // Handle of the vbo where the vertex data is stored
	GLfloat* _pColors; // Albedo data
	AttributeFormat* _pColorFormat; // Attribute format used by color data
	GLuint _colorVBOHandle; // Handle of the vbo where the color data is stored
};

} /* namespace DBGL */
#endif /* MESH_H_ */
