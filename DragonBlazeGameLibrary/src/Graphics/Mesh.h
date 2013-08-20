/*
 * Mesh.h
 *
 *  Created on: 10.08.2013
 *      Author: Drag-On
 */

#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include <SOIL.h>
#include "RenderContext.h"
#include "Texture.h"

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
	 * @return Attribute format of the color data
	 */
	AttributeFormat* getColorFormat() const;

	/**
	 * @return Handle of the VBO where the color data is stored
	 */
	GLuint getColorVBOHandle() const;

	/**
	 * @return Handle of the IBO where the elements are stored
	 */
	GLuint getElementIBOHandle() const;

	/**
	 * @brief Adds some normal data to the mesh
	 * @param normalData Raw normal data
	 * @param length Length of the normalData array
	 * @param attrFormat Format of the normalData array
	 * @attention Both heap objects will be maintained by the Mesh class (includes delete)
	 */
	void setNormalData(GLfloat* normalData, int length,
			AttributeFormat* attrFormat);

	/**
	 * @return Attribute format of the normal data
	 */
	AttributeFormat* getNormalFormat() const;

	/**
	 * @return Handle of the VBO where the normal data is stored
	 */
	GLuint getNormalVBOHandle() const;

	/**
	 * @brief Adds some UV coordinates to the mesh
	 * @param uvData Raw uv coordinates
	 * @param length Length of the uvData array
	 * @param attrFormat Format of the uvData array
	 * @attention Both heap objects will be maintained by the Mesh class (includes delete)
	 */
	void setUVData(GLfloat* uvData, int length, AttributeFormat* attrFormat);

	/**
	 * @return Attribute format of the UV coordinate data
	 */
	AttributeFormat* getUVFormat() const;

	/**
	 * @return Handle of the VBO where the UVs are stored
	 */
	GLuint getUVVBOHandle() const;

	/**
	 * @brief Makes the mesh render using the passed texture
	 * @param tex Texture to use
	 * @attention You need to manage the passed texture by yourself!
	 */
	void setTexture(Texture* tex);

	/**
	 * @return Texture used for rendering or NULL in case none
	 */
	Texture* getTexture() const;

	/**
	 * Creates a new Mesh object representing a cube
	 * @return Pointer to the newly created mesh object
	 */
	static Mesh* createCube();

	/**
	 * Creates a new Mesh object representing a four-sided pyramid
	 * @return Pointer to the newly created mesh object
	 */
	static Mesh* createPyramid();

private:
	AttributeFormat* _pVertexFormat; // Attribute format used by vertex data
	GLuint _vertexVBOHandle; // Handle of the vbo where the vertex data is stored
	AttributeFormat* _pColorFormat; // Attribute format used by color data
	GLuint _colorVBOHandle; // Handle of the vbo where the color data is stored
	GLuint _elementIBOHandle; // Handle of the ibo where all elements are stored
	AttributeFormat* _pNormalFormat; // Attribute format used by normal data
	GLuint _normalVBOHandle; // Handle of the vbo where the normal data is stored
	AttributeFormat* _pUVFormat; // Attribute format used for UV data
	GLuint _UVVBOHandle; // Handle of the vbo where the UV data is stored
	Texture* _pTexture; // Texture to display on the mesh
};

} /* namespace DBGL */
#endif /* MESH_H_ */
