//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include "DBGL/Resources/Texture/IImageFormatModule.h"
#include "DBGL/Platform/Platform.h"

namespace dbgl
{
    class TGAModule : public IImageFormatModule
    {
	private:
	    void flipVertical(char* img, unsigned int width, unsigned int height, unsigned int lineSize) const
	    {
		char* lineBuffer = new char[lineSize];
		for (unsigned int i = 0; i < height / 2; i++)
		{
		    int frontOffset = i * lineSize;
		    int backOffset = ((height - 1) - i) * lineSize;
		    memcpy(lineBuffer, img + frontOffset, lineSize);
		    memcpy(img + frontOffset, img + backOffset, lineSize);
		    memcpy(img + backOffset, lineBuffer, lineSize);
		}
		delete [] lineBuffer;
	    }

	public:
	    struct FileHeaderTGA
	    {
		unsigned char idLength = 0;		/* 1 byte */
		unsigned char colorMapType = 0;		/* 1 byte */
		unsigned char imageType = 0;		/* 1 byte */
		unsigned short colorMapOffset = 0;	/* 2 bytes */
		unsigned short colorMapEntries = 0;	/* 2 bytes */
		unsigned char colorMapBPP = 0;		/* 1 byte */
		unsigned short xOrig = 0;		/* 2 bytes */
		unsigned short yOrig = 0;		/* 2 bytes */
		unsigned short imWidth = 0;		/* 2 bytes */
		unsigned short imHeight = 0;		/* 2 bytes */
		unsigned char bpp = 0;			/* 1 byte */
		unsigned char imDescriptor = 0;		/* 1 byte */
	    };

	    virtual ~TGAModule() = default;

	    virtual bool canLoad() const
	    {
		return true;
	    }

	    virtual bool canWrite() const
	    {
		return false;
	    }

	    virtual bool matchExtension(std::string const& extension) const
	    {
		std::string lowercaseExt{};
		std::transform(extension.begin(), extension.end(), std::back_inserter(lowercaseExt), ::tolower);
		return lowercaseExt == ".tga" || lowercaseExt == "tga";
	    }

	    virtual ITexture* load(std::string const& path) const
	    {
		return load(Filename{path});
	    }

	    virtual ITexture* load(Filename const& path) const
	    {
		// Open file stream
		std::ifstream file(path.get(), std::fstream::in | std::fstream::binary);
		if(!file.good())
		    return nullptr;
		// Read file header
		file.seekg(0, std::ios::beg);
		FileHeaderTGA fileHeader{};
		char fHeader[18];
		file.read(&fHeader[0], 18);
		fileHeader.idLength = fHeader[0];
		fileHeader.colorMapType = fHeader[1];
		fileHeader.imageType = fHeader[2];
		fileHeader.colorMapOffset = (fHeader[3] << 0) | (fHeader[4] << 8);
		fileHeader.colorMapEntries = (fHeader[5] << 0) | (fHeader[6] << 8);
		fileHeader.colorMapBPP = fHeader[7];
		fileHeader.xOrig = (fHeader[8] << 0) | (fHeader[9] << 8);
		fileHeader.yOrig = (fHeader[10] << 0) | (fHeader[11] << 8);
		fileHeader.imWidth = (fHeader[12]<<0) | (fHeader[13]<<8);
		fileHeader.imHeight = (fHeader[14]<<0) | (fHeader[15]<<8);
		fileHeader.bpp = fHeader[16];
		fileHeader.imDescriptor = fHeader[17];
		if (fileHeader.colorMapType != 0 || (fileHeader.imageType != 2 && fileHeader.imageType != 3)
			|| fileHeader.imWidth <= 0 || fileHeader.imHeight <= 0)
		    return nullptr;
		// Skip to image data
		file.seekg(fileHeader.idLength + fileHeader.colorMapEntries * fileHeader.colorMapBPP, std::ios::cur);
		// Read actual image
		int colorMode = fileHeader.bpp / 8;
		const unsigned int imageDataLength = fileHeader.imWidth * fileHeader.imHeight * colorMode;
		char img[imageDataLength];
		file.read(img, imageDataLength);
		// Close file
		file.close();

		// Flip vertically since tgas are layed out the wrong way
		flipVertical(&img[0], fileHeader.imWidth, fileHeader.imHeight, fileHeader.imWidth * colorMode);
		// Create texture
		auto tex = Platform::get()->createTexture(ITexture::Type::TEX2D);
		tex->setRowAlignment(ITexture::RowAlignment::UNPACK, 1);
		auto pixelFormat = colorMode == 3 ? ITexture::PixelFormat::BGR : ITexture::PixelFormat::BGRA;
		tex->write(0, fileHeader.imWidth, fileHeader.imHeight, pixelFormat, ITexture::PixelType::UBYTE, &img[0]);
		return tex;
	    }

	    virtual bool write(ITexture* tex, std::string const& path) const
	    {
		return write(tex, Filename{path});
	    }

	    virtual bool write(ITexture* /* tex */, Filename const& /* path */) const
	    {
		return false;
	    }
    };
}

extern "C" dbgl::IImageFormatModule* create()
{
    return new dbgl::TGAModule{};
}

extern "C" void destroy(dbgl::IImageFormatModule* mod)
{
    delete mod;
}
