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

namespace dbgl
{
    /**
     * @brief Provides some static functionality to work with textures
     */
    class TextureUtility
    {
	public:
	    /**
	     * @brief Information about one pixel
	     */
	    struct PixelData
	    {
		public:
		    /**
		     *  @brief Red value
		     */
		    unsigned char r;
		    /**
		     * @brief Green value
		     */
		    unsigned char g;
		    /**
		     * @brief Blue value
		     */
		    unsigned char b;
		    /**
		     * @brief Alpha value
		     */
		    unsigned char a;
	    };
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
		    ImageData(char* imgData, unsigned int width, unsigned int height);
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
		    PixelData& getPixel(unsigned int x, unsigned int y);
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
		private:
		    PixelData* m_pPixels = nullptr;
		    unsigned int m_width;
		    unsigned int m_height;
	    };

	    /**
	     * @brief Create an ImageData object from a texture
	     * @param tex Texture to get data from
	     * @return ImageData object
	     */
	    static ImageData createImageData(ITexture* tex);
    };
}



#endif /* INCLUDE_DBGL_CORE_UTILITY_TEXTUREUTILITY_H_ */
