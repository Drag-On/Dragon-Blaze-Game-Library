//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "DBGL/System/Log/Log.h"
#include "TextureLoader.h"
#include "BogusTextureLoader.h"
#include "DDSTextureLoader.h"
#include "TGATextureLoader.h"

namespace dbgl
{
    /**
     * @brief Used to load textures from hard disk
     */
    class Texture
    {
	public:
	    /**
	     * @brief File types of textures that can be loaded
	     */
	    enum Type
	    {
		BOGUS, //!< BOGUS
		DDS, //!< DDS
		TGA, //!< TGA
	    };

	    static const int FlipVertically = 1 << 0;
	    static const int FlipHorizontally = 1 << 1;

	    /**
	     * @brief Creates a texture object from an already allocated OpenGL texture
	     * @param texID ID of the allocated texture
	     * @details Use the appropriate static load methods to load a texture from disk!
	     */
	    Texture(GLuint texID);
	    /**
	     * @brief Clean up used memory
	     */
	    ~Texture();
	    /**
	     * @return GL texture handle
	     */
	    GLuint getHandle();
	    /**
	     * @brief Constructs a new texture on the heap
	     * @details Needs to be freed manually!
	     * @param path File path
	     * @param flags Flags to consider while loading
	     * @return Pointer to the newly created texture object
	     */
	    template <class Loader> static Texture* load(const std::string path, Bitmask<> flags = 0);
	    /**
	     * @brief Constructs a new texture on the heap
	     * @details Needs to be freed manually!
	     * @param type Texture type
	     * @param path File path
	     * @param flags Flags to consider while loading
	     * @return Pointer to the newly created texture object
	     */
	    static Texture* load(const Type type, const std::string path, Bitmask<> flags = 0);
	private:
	    /**
	     * @brief GL texture handle
	     */
	    GLuint m_textureId;
    };
}

#endif /* TEXTURE_H_ */
