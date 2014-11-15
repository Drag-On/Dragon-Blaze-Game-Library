//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <string>
#include <algorithm>
#include <fstream>
#include "DBGL/Resources/Texture/IImageFormatModule.h"
#include "DBGL/Platform/Platform.h"

namespace dbgl
{
    class BMPModule : public IImageFormatModule
    {
	public:
	    struct FileHeaderBMP
	    {
		    uint16_t id = 0x4D42;
		    uint32_t fileSize = 0;
		    uint32_t res = 0;
		    uint32_t off = 54;
	    };

	    struct InfoHeaderBMP
	    {
		    uint32_t size = 40;
		    int32_t width = 0;
		    int32_t height = 0;
		    uint16_t panes = 1;
		    uint16_t bpp = 24;
		    uint32_t compr = 0;
		    uint32_t imgSize = 0;
		    int32_t xPixPerMeter = 0;
		    int32_t yPixPerMeter = 0;
		    uint32_t indexClr = 0;
		    uint32_t clr = 0;
	    };

	    virtual ~BMPModule() = default;

	    virtual bool canLoad() const
	    {
		return true;
	    }

	    virtual bool canWrite() const
	    {
		return true;
	    }

	    virtual bool matchExtension(std::string const& extension) const
	    {
		std::string lowercaseExt{};
		std::transform(extension.begin(), extension.end(), std::back_inserter(lowercaseExt), ::tolower);
		return lowercaseExt == ".bmp" || lowercaseExt == "bmp";
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
		FileHeaderBMP fileHeader{};
		char fHeader[14];
		file.read(&fHeader[0], 14);
		fileHeader.id = *reinterpret_cast<uint16_t*>(&fHeader[0]);
		fileHeader.fileSize = *reinterpret_cast<uint32_t*>(&fHeader[2]);
		fileHeader.res = *reinterpret_cast<uint32_t*>(&fHeader[6]);
		fileHeader.off = *reinterpret_cast<uint32_t*>(&fHeader[10]);
		if(fileHeader.id != 0x4D42 || fileHeader.fileSize <= 0)
		    return nullptr;
		// Read info header
		InfoHeaderBMP infoHeader{};
		char iHeader[40];
		file.read(&iHeader[0], 40);
		infoHeader.size = *reinterpret_cast<uint32_t*>(&iHeader[0]);
		infoHeader.width = *reinterpret_cast<uint32_t*>(&iHeader[4]);
		infoHeader.height = *reinterpret_cast<uint32_t*>(&iHeader[8]);
		infoHeader.panes = *reinterpret_cast<uint16_t*>(&iHeader[10]);
		infoHeader.bpp = *reinterpret_cast<uint16_t*>(&iHeader[12]);
		infoHeader.compr = *reinterpret_cast<uint32_t*>(&iHeader[16]);
		infoHeader.imgSize = *reinterpret_cast<uint32_t*>(&iHeader[20]);
		infoHeader.xPixPerMeter = *reinterpret_cast<uint32_t*>(&iHeader[24]);
		infoHeader.yPixPerMeter = *reinterpret_cast<uint32_t*>(&iHeader[28]);
		infoHeader.indexClr = *reinterpret_cast<uint32_t*>(&iHeader[32]);
		infoHeader.clr = *reinterpret_cast<uint32_t*>(&iHeader[36]);
		if(infoHeader.size != 40 || infoHeader.width <= 0 || infoHeader.height <= 0 || infoHeader.compr != 0)
		    return nullptr;
		// Read image data
		if(fileHeader.off > 0)
		    file.seekg(fileHeader.off, std::ios::beg);
		const unsigned int imgSize { static_cast<unsigned int>(((infoHeader.width * infoHeader.bpp + 31) & ~31) / 8
			* infoHeader.height) };
		char img[imgSize];
		file.read(&img[0], imgSize);
		// Close file
		file.close();

		// Create texture
		auto tex = Platform::get()->createTexture(ITexture::Type::TEX2D);
		tex->setRowAlignment(ITexture::RowAlignment::UNPACK, 4);
		tex->bind(0);
		tex->write(0, infoHeader.width, infoHeader.height, ITexture::PixelFormat::BGR, ITexture::PixelType::UBYTE, &img[0]);
		return tex;
	    }

	    virtual bool write(ITexture* tex, std::string const& path) const
	    {
		return write(tex, Filename{path});
	    }

	    virtual bool write(ITexture* tex, Filename const& path) const
	    {
		unsigned int imgDataSize { tex->getWidth() * tex->getHeight() * 3 };
		char* bmpBuf = new char[imgDataSize];
		if(!bmpBuf)
		    return false;
		// Copy pixel data to buffer
		tex->setRowAlignment(ITexture::RowAlignment::PACK, 4);
		tex->getPixelData(ITexture::PixelFormat::BGR, ITexture::PixelType::UBYTE, bmpBuf);
		// Open file stream
		std::ofstream file(path.get(), std::fstream::out | std::fstream::binary | std::fstream::trunc);
		if(!file.good())
		    return false;
		// Write file header
		FileHeaderBMP fileHeader{};
		fileHeader.fileSize = imgDataSize;
		file.write(reinterpret_cast<const char*>(&fileHeader.id), sizeof(uint16_t)); // "BM"
		file.write(reinterpret_cast<const char*>(&fileHeader.fileSize), sizeof(uint32_t)); // File size
		file.write(reinterpret_cast<const char*>(&fileHeader.res), sizeof(uint32_t)); // Reserved
		file.write(reinterpret_cast<const char*>(&fileHeader.off), sizeof(uint32_t)); // Offset to image data
		// Write info header
		InfoHeaderBMP infoHeader{};
		infoHeader.width = static_cast<int32_t>(tex->getWidth());
		infoHeader.height = static_cast<int32_t>(tex->getHeight());
		file.write(reinterpret_cast<const char*>(&infoHeader.size), sizeof(uint32_t)); // Size of info header
		file.write(reinterpret_cast<const char*>(&infoHeader.width), sizeof(int32_t)); // Width in pixels
		file.write(reinterpret_cast<const char*>(&infoHeader.height), sizeof(int32_t)); // Height in pixels
		file.write(reinterpret_cast<const char*>(&infoHeader.panes), sizeof(uint16_t)); // Color planes (unused)
		file.write(reinterpret_cast<const char*>(&infoHeader.bpp), sizeof(uint16_t)); // BPP
		file.write(reinterpret_cast<const char*>(&infoHeader.compr), sizeof(uint32_t)); // Not compressed
		file.write(reinterpret_cast<const char*>(&infoHeader.imgSize), sizeof(uint32_t)); // Size of image data (unused)
		file.write(reinterpret_cast<const char*>(&infoHeader.xPixPerMeter), sizeof(int32_t)); // X pixel per meter (unused)
		file.write(reinterpret_cast<const char*>(&infoHeader.yPixPerMeter), sizeof(int32_t)); // Y pixel per meter (unused)
		file.write(reinterpret_cast<const char*>(&infoHeader.indexClr), sizeof(uint32_t)); // Amount of indexed colors (no indexing)
		file.write(reinterpret_cast<const char*>(&infoHeader.clr), sizeof(uint32_t)); // Use all colors
		// Write actual image
		file.write(bmpBuf, imgDataSize);
		file.close();
		delete [] bmpBuf;

		return true;
	    }
    };
}

extern "C" dbgl::IImageFormatModule* create()
{
    return new dbgl::BMPModule{};
}

extern "C" void destroy(dbgl::IImageFormatModule* mod)
{
    delete mod;
}
