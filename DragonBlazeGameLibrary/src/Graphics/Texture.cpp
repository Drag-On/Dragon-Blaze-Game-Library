/*
 * Texture.cpp
 *
 *  Created on: 19.08.2013
 *      Author: Drag-On
 */

#include "Texture.h"

namespace DBGL
{

Texture::Texture(const char* fileName)
{
	glActiveTexture(GL_TEXTURE0);
	_texHandle = SOIL_load_OGL_texture(fileName, SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (_texHandle == 0)
	{
		LOG->error("Unable to load texture %s. %s", fileName, SOIL_last_result());
	}
}

Texture::~Texture()
{
	if (_texHandle > 0)
		glDeleteTextures(1, &_texHandle);
}

/**
 * @return Texture handle
 */
GLuint Texture::getTextureHandle() const
{
	return _texHandle;
}

} /* namespace DBGL */
