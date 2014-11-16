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
    class TextureUtility
    {
	public:
	    struct PixelData
	    {
		public:
		    unsigned char r;
		    unsigned char g;
		    unsigned char b;
		    unsigned char a;
	    };
	    class ImageData
	    {
		public:
		    explicit ImageData(char* imgData, unsigned int width, unsigned int height);
		    ~ImageData();
		    PixelData& getPixel(unsigned int x, unsigned int y);
		    unsigned int getWidth() const;
		    unsigned int getHeight() const;
		private:
		    PixelData* m_pPixels = nullptr;
		    unsigned int m_width;
		    unsigned int m_height;
	    };

	    static ImageData createImageData(ITexture* tex);
    };
}



#endif /* INCLUDE_DBGL_CORE_UTILITY_TEXTUREUTILITY_H_ */
