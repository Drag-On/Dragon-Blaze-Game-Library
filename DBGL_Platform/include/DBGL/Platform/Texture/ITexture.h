//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ITEXTURE_H_
#define ITEXTURE_H_

namespace dbgl
{
    /**
     * @brief Interface class for textures
     */
    class ITexture
    {
	public:
	    /**
	     * @brief Lists all supported texture types
	     */
	    enum class Type
	    {
		TEX2D, //!< TEX2D
	    };
	    /**
	     * @brief Lists all supported uncompressed pixel formats
	     */
	    enum class PixelFormat
	    {
		RGB, 	  //!< RGB
		BGR, 	  //!< BGR
		RGBA,	  //!< RGBA
		BGRA,	  //!< BGRA
		LUMINANCE,	  //!< LUMINANCE
	    };
	    /**
	     * @brief Lists all supported compressed pixel formats
	     */
	    enum class PixelFormatCompressed
	    {
		COMP_DXT1,	  //!< COMP_DXT1
		COMP_DXT3,	  //!< COMP_DXT3
		COMP_DXT5,	  //!< COMP_DXT5
	    };
	    /**
	     * @brief Lists all supported pixel types
	     */
	    enum class PixelType
	    {
		UBYTE, //!< UBYTE
		BYTE,  //!< BYTE
		USHORT,  //!< USHORT
		SHORT, //!< SHORT
		UINT,  //!< UINT
		INT,   //!< INT
		FLOAT, //!< FLOAT
	    };
	    /**
	     * @brief Lists all supported row alignment types
	     */
	    enum class RowAlignment
	    {
		PACK,  //!< PACK
		UNPACK,  //!< UNPACK
	    };
	    /**
	     * @brief Lists all supported minifying filters
	     */
	    enum class MinFilter
	    {
		NEAREST,               //!< NEAREST
		LINEAR,                //!< LINEAR
		NEAREST_MIPMAP_NEAREST,                //!< NEAREST_MIPMAP_NEAREST
		NEAREST_MIPMAP_LINEAR, //!< NEAREST_MIPMAP_LINEAR
		LINEAR_MIPMAP_NEAREST, //!< LINEAR_MIPMAP_NEAREST
		LINEAR_MIPMAP_LINEAR,  //!< LINEAR_MIPMAP_LINEAR
	    };
	    /**
	     * @brief Lists all supported magnifying filters
	     */
	    enum class MagFilter
	    {
		NEAREST,  //!< NEAREST
		LINEAR, //!< LINEAR
	    };

	    /**
	     * @brief Destructor
	     */
	    virtual ~ITexture() = default;
	    /**
	     * @brief Binds the texture to a texture unit
	     * @param unit Texture unit to bind to (defaults to unit 0)
	     */
	    virtual void bind(unsigned int unit = 0) = 0;
	    /**
	     * @brief Modifies a certain mip level of this texture
	     * @note Texture needs to be bound
	     * @param level MipMap level to write
	     * @param width Image width
	     * @param height Image height
	     * @param format Pixel format
	     * @param type Pixel type
	     * @param data Pointer to image data
	     */
	    virtual void write(unsigned int level, unsigned int width, unsigned int height,
		    PixelFormat format, PixelType type, void const* data) = 0;
	    /**
	     * @brief Modifies a vertain mip level of this texture
	     * @note Texture needs to be bound
	     * @param level Mip map level to write
	     * @param width Image width
	     * @param height Image height
	     * @param format Compressed pixel format
	     * @param size Size of the passed image data
	     * @param data Pointer to image data
	     */
	    virtual void writeCompressed(unsigned int level, unsigned int width, unsigned int height,
		    PixelFormatCompressed format, unsigned int size, void const* data) = 0;
	    /**
	     * @brief Modifies the row alignment used when transfering image data
	     * @param type Alignment type
	     * @param align Alignment to set
	     */
	    virtual void setRowAlignment(RowAlignment type, unsigned int align) = 0;
	    /**
	     * @brief Sets the filter used to minify the texture
	     * @note Texture needs to be bound
	     * @param filter New filter
	     */
	    virtual void setMinFilter(MinFilter filter) = 0;
	    /**
	     * @brief Sets the filter used to magnify the texture
	     * @note Texture needs to be bound
	     * @param filter New filter
	     */
	    virtual void setMagFilter(MagFilter filter) = 0;
	    /**
	     * @brief Generates mip maps for the texture.
	     * @note Texture needs to be bound
	     * @details Overwrites any previously set mip maps
	     */
	    virtual void generateMipMaps() = 0;
	    /**
	     * @brief Retrieves the size of the texture (or a mip map thereof)
	     * @note Texture needs to be bound
	     * @param[out] width Texture width will be copied here
	     * @param[out] height Texture height will be copied here
	     * @param level Mip level, defaults to 0
	     */
	    virtual void getSize(unsigned int& width, unsigned int& height, unsigned int level = 0) = 0;
	    /**
	     * @brief Retrieves the texture width
	     * @return Width of the texture in pixels
	     */
	    virtual unsigned int getWidth() const = 0;
	    /**
	     * @brief Retrieves the texture height
	     * @return Height of the texture in pixels
	     */
	    virtual unsigned int getHeight() const = 0;
	    /**
	     * @brief Retrieves the pixel data of the texture
	     * @note Texture needs to be bound
	     * @param format Format to convert to
	     * @param type Type to convert to
	     * @param buffer[out] Buffer to write to. Must be big enough to hold the data.
	     * @param level Mip level
	     */
	    virtual void getPixelData(PixelFormat format, PixelType type, char* buffer, unsigned int level = 0) const = 0;
    };
}

#endif /* ITEXTURE_H_ */
