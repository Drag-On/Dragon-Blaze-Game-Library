//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_CORE_UTILITY_TEXTUREUTILITY_H_
#define INCLUDE_DBGL_CORE_UTILITY_TEXTUREUTILITY_H_

#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Core/Utility/Color.h"

namespace dbgl
{
    /**
     * @brief Provides some static functionality to work with textures
     */
    class TextureUtility
    {
	public:
	    /**
	     * @brief Image data which can be retrieved from a texture
	     */
	    class ImageData
	    {
		public:
		    /**
		     * @brief Construct Image data from an array of pixels
		     * @param imgData Pixel data, layed out in an array row-wise with pixels in the order red-green-blue-alpha
		     * @param width Image width
		     * @param height Image height
		     */
		    ImageData(unsigned char* imgData, unsigned int width, unsigned int height);
		    /**
		     * @brief Copy constructor
		     * @param other Image to copy
		     */
		    ImageData(ImageData const& other);
		    /**
		     * @brief Move constructor
		     * @param other Image to move
		     */
		    ImageData(ImageData&& other);
		    /**
		     * @brief Destructor
		     */
		    ~ImageData();
		    /**
		     * @brief Retrieve the color of a certain pixel
		     * @param x X coordinate
		     * @param y Y coordinate
		     * @return Color of the requested pixel
		     */
		    Color const& getPixel(unsigned int x, unsigned int y) const;
		    /**
		     * @brief Modifies a pixel
		     * @param x X coordinate
		     * @param y Y coordinate
		     * @param color Pixel color
		     */
		    void setPixel(unsigned int x, unsigned int y, Color const& color);
		    /**
		     * @brief Retrieves the image width
		     * @return Image width in pixels
		     */
		    unsigned int getWidth() const;
		    /**
		     * @brief Retrieves the image height
		     * @return Image height in pixels
		     */
		    unsigned int getHeight() const;
		    /**
		     * @brief Assignment operator
		     * @param other Image to assign
		     * @return Reference to this image
		     */
		    ImageData& operator=(ImageData const& other);
		    /**
		     * @brief Move assignment operator
		     * @param other Image to assign
		     * @return Reference to this image
		     */
		    ImageData& operator=(ImageData&& other);
		private:
		    Color* m_pPixels = nullptr;
		    unsigned int m_width;
		    unsigned int m_height;

		    friend class TextureUtility;
	    };

	    /**
	     * @brief Create an ImageData object from a texture
	     * @param tex Texture to get data from
	     * @return ImageData object
	     */
	    static ImageData createImageData(ITexture* tex);
	    /**
	     * @brief Create a texture from a an image data object
	     * @param img Image to use as a texture
	     * @return Created texture
	     */
	    static ITexture* createTexture(ImageData const& img);
	    /**
	     * @brief Replaces the passed texture with a image
	     * @param[out] tex Texture to replace
	     * @param img Image to use as replacement
	     */
	    static void replaceTexture(ITexture* tex, ImageData const& img);
    };
}

#endif /* INCLUDE_DBGL_CORE_UTILITY_TEXTUREUTILITY_H_ */
