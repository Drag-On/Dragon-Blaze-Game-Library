//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
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
#include "DBGL/Core/Utility/BitUtility.h"
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Texture/ITextureCommands.h"

namespace dbgl
{
	/**
	 * @brief Loads tga image files from hard disk
	 */
	class TGAModule: public IImageFormatLibrary
	{
	private:
		void flipVertical(char* img, unsigned int height, unsigned int lineSize) const
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
			delete[] lineBuffer;
		}

		struct FileHeaderTGA
		{
			unsigned char idLength = 0; /* 1 byte */
			unsigned char colorMapType = 0; /* 1 byte */
			unsigned char imageType = 0; /* 1 byte */
			unsigned short colorMapOffset = 0; /* 2 bytes */
			unsigned short colorMapEntries = 0; /* 2 bytes */
			unsigned char colorMapBPP = 0; /* 1 byte */
			unsigned short xOrig = 0; /* 2 bytes */
			unsigned short yOrig = 0; /* 2 bytes */
			unsigned short imWidth = 0; /* 2 bytes */
			unsigned short imHeight = 0; /* 2 bytes */
			unsigned char bpp = 0; /* 1 byte */
			unsigned char imDescriptor = 0; /* 1 byte */
		};

	public:
		/**
		 * @brief Destructor
		 */
		virtual ~TGAModule() = default;
		/**
		 * @copydoc IImageFormatLibrary::canLoad()
		 */
		virtual bool canLoad() const
		{
			return true;
		}
		/**
		 * @copydoc IImageFormatLibrary::canWrite()
		 */
		virtual bool canWrite() const
		{
			return false;
		}
		/**
		 * @copydoc IImageFormatLibrary::matchExtension()
		 */
		virtual bool matchExtension(std::string const& extension) const
		{
			std::string lowercaseExt { };
			std::transform(extension.begin(), extension.end(), std::back_inserter(lowercaseExt), ::tolower);
			return lowercaseExt == ".tga" || lowercaseExt == "tga";
		}
		/**
		 * @copydoc IImageFormatLibrary::load()
		 */
		virtual ITexture* load(std::string const& path) const
		{
			return load(Filename { path });
		}
		/**
		 * @copydoc IImageFormatLibrary::load()
		 */
		virtual ITexture* load(Filename const& path) const
		{
			// Open file stream
			std::ifstream file(path.get(), std::fstream::in | std::fstream::binary);
			if (!file.good())
				return nullptr;
			// Read file header
			file.seekg(0, std::ios::beg);
			FileHeaderTGA fileHeader { };
			unsigned char fHeader[18];
			file.read(reinterpret_cast<char*>(&fHeader[0]), 18);
			fileHeader.idLength = fHeader[0];
			fileHeader.colorMapType = fHeader[1];
			fileHeader.imageType = fHeader[2];
			fileHeader.colorMapOffset = BitUtility::readUInt16_LE(&fHeader[3]);
			fileHeader.colorMapEntries = BitUtility::readUInt16_LE(&fHeader[5]);
			fileHeader.colorMapBPP = fHeader[7];
			fileHeader.xOrig = BitUtility::readUInt16_LE(&fHeader[8]);
			fileHeader.yOrig = BitUtility::readUInt16_LE(&fHeader[10]);
			fileHeader.imWidth = BitUtility::readUInt16_LE(&fHeader[12]);
			fileHeader.imHeight = BitUtility::readUInt16_LE(&fHeader[14]);
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
			char* img = new char[imageDataLength];
			file.read(img, imageDataLength);
			// Close file
			file.close();

			// Flip vertically since tgas are layed out the wrong way
//			flipVertical(&img[0], fileHeader.imHeight, fileHeader.imWidth * colorMode);
			// Create texture
			auto tex = Platform::get()->createTexture(ITexture::Type::TEX2D);
			tex->bind();
			Platform::get()->curTexture()->setRowAlignment(ITextureCommands::RowAlignment::UNPACK, 1);
			auto pixelFormat =
					colorMode == 3 ? ITextureCommands::PixelFormat::BGR : ITextureCommands::PixelFormat::BGRA;
			Platform::get()->curTexture()->write(0, fileHeader.imWidth, fileHeader.imHeight, pixelFormat,
					ITextureCommands::PixelType::UBYTE, img);
			delete[] img;
			return tex;
		}
		/**
		 * @copydoc IImageFormatLibrary::write()
		 */
		virtual bool write(ITexture* data, std::string const& path) const
		{
			return write(data, Filename { path });
		}
		/**
		 * @copydoc IImageFormatLibrary::write()
		 */
		virtual bool write(ITexture* /* tex */, Filename const& /* path */) const
		{
			return false;
		}
	};
}

/**
 * @brief Create library object
 */
extern "C" dbgl::IImageFormatLibrary* create()
{
	return new dbgl::TGAModule { };
}

/**
 * @brief Destroy library object
 */
extern "C" void destroy(dbgl::IImageFormatLibrary* mod)
{
	delete mod;
}
