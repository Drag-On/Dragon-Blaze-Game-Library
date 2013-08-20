/*
 * Texture.h
 *
 *  Created on: 19.08.2013
 *      Author: Drag-On
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include <SOIL.h>
#include "../Main/Log.h"

namespace DBGL
{

/**
 * @brief Provides functionality to load images and upload them to the graphics card
 */
class Texture
{
public:
	/**
	 * Constructor
	 * @param fileName Name (and possibly path) of the image to load
	 */
	Texture(const char* fileName);

	/**
	 * Destructor
	 */
	virtual ~Texture();

	/**
	 * @return Texture handle
	 */
	GLuint getTextureHandle() const;

private:
	GLuint _texHandle; // Handle of the texture
};

} /* namespace DBGL */
#endif /* TEXTURE_H_ */
