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
#include "DBGL/System/Log/Log.h"
#include "DBGL/Platform/GL/GLProvider.h"
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

	    /**
	     * @brief Constant to request vertical flipping
	     */
	    static const int FlipVertically = 1 << 0;
	    /**
	     * @brief Constant to request horizontal flipping
	     */
	    static const int FlipHorizontally = 1 << 1;

	    /**
	     * @brief Creates a texture object from an already allocated texture
	     * @param handle Handle of the texture
	     */
	    Texture(IGL::TextureHandle handle);
	    /**
	     * @brief Clean up used memory
	     */
	    ~Texture();
	    /**
	     * @brief Binds this texture
	     */
	    void bind() const;
	    /**
	     * @return Texture handle
	     */
	    IGL::TextureHandle getHandle() const;
	    /**
	     * @brief Provides the texture width
	     * @return Width of the texture in pixels
	     */
	    unsigned int getWidth() const;
	    /**
	     * @brief Provides the texture height
	     * @return Height of the texture in pixels
	     */
	    unsigned int getHeight() const;
	    /**
	     * @brief Constructs a new texture on the heap
	     * @details Needs to be freed manually!
	     * @param path File path
	     * @param flags Flags to consider while loading
	     * @param filtering Filter method to use
	     * @return Pointer to the newly created texture object
	     */
	    template<class Loader> static Texture* load(const std::string path, Bitmask<> flags = 0,
		    TextureLoader::Filtering filtering = TextureLoader::Filtering::LINEAR);
	    /**
	     * @brief Constructs a new texture on the heap
	     * @details Needs to be freed manually!
	     * @param type Texture type
	     * @param path File path
	     * @param flags Flags to consider while loading
	     * @param filtering Filter method to use
	     * @return Pointer to the newly created texture object
	     */
	    static Texture* load(const Type type, const std::string path, Bitmask<> flags = 0,
		    TextureLoader::Filtering filtering = TextureLoader::Filtering::LINEAR);
	private:
	    /**
	     * @brief GL texture handle
	     */
	    IGL::TextureHandle m_handle;
	    unsigned int m_width;
	    unsigned int m_height;
    };
}

#endif /* TEXTURE_H_ */
