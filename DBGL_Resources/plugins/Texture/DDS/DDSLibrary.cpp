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
#include <cstdint>
#include <string>
#include <algorithm>
#include <fstream>
#include "DBGL/Resources/Texture/IImageFormatModule.h"
#include "DBGL/Core/Utility/BitUtility.h"
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Texture/ITextureCommands.h"

namespace dbgl
{
	class DDSModule: public IImageFormatLibrary
	{
	private:
		enum class FourCC
		{
			DXT1 = 0x31545844, DXT3 = 0x33545844, DXT5 = 0x35545844,
		};

		void ddsFlipDXT1Block(unsigned char *data) const
		{
			std::swap(data[4], data[7]);
			std::swap(data[5], data[6]);
		}

		void ddsFlipDXT3Block(unsigned char *data) const
		{
			std::swap(data[0], data[6]);
			std::swap(data[1], data[7]);
			std::swap(data[2], data[4]);
			std::swap(data[3], data[5]);
			ddsFlipDXT1Block(data + 8);
		}

		void ddsFlipDXT5Block(unsigned char *data) const
		{
			unsigned int row0_1 = data[2] + 256 * (data[3] + 256 * data[4]);
			unsigned int row2_3 = data[5] + 256 * (data[6] + 256 * data[7]);
			unsigned int row1_0 = ((row0_1 & 0x000fff) << 12) | ((row0_1 & 0xfff000) >> 12);
			unsigned int row3_2 = ((row2_3 & 0x000fff) << 12) | ((row2_3 & 0xfff000) >> 12);
			data[2] = row3_2 & 0xff;
			data[3] = (row3_2 & 0xff00) >> 8;
			data[4] = (row3_2 & 0xff0000) >> 16;
			data[5] = row1_0 & 0xff;
			data[6] = (row1_0 & 0xff00) >> 8;
			data[7] = (row1_0 & 0xff0000) >> 16;
			ddsFlipDXT1Block(data + 8);
		}
		void flipVertical(char* buffer, unsigned int offset, unsigned int width, unsigned int height,
				unsigned int blockSize, FourCC fourCC) const
		{
			const unsigned int bytesInARow { ((width + 3) / 4) * blockSize };
			unsigned char temp[bytesInARow];
			unsigned char* sourceRow = (unsigned char*) buffer + offset;
			unsigned char* destinationRow = (unsigned char*) buffer + offset + ((height + 3) / 4 - 1) * bytesInARow;
			for (unsigned int i = 0; i < (height + 3) / 4 / 2; i++)
			{
				// Swap source row with appropriate mirror row
				memcpy(temp, destinationRow, bytesInARow);
				memcpy(destinationRow, sourceRow, bytesInARow);
				memcpy(sourceRow, &temp[0], bytesInARow);
				// Also swap pixels in blocks
				switch (fourCC)
				{
				case FourCC::DXT1:
				{
					for (unsigned int j = 0; j < bytesInARow / blockSize; j++)
					{
						ddsFlipDXT1Block(sourceRow + j * blockSize);
						ddsFlipDXT1Block(destinationRow + j * blockSize);
					}
					break;
				}
				case FourCC::DXT3:
				{
					for (unsigned int j = 0; j < bytesInARow / blockSize; j++)
					{
						ddsFlipDXT3Block(sourceRow + j * blockSize);
						ddsFlipDXT3Block(destinationRow + j * blockSize);
					}
					break;
				}
				case FourCC::DXT5:
				{
					for (unsigned int j = 0; j < bytesInARow / blockSize; j++)
					{
						ddsFlipDXT5Block(sourceRow + j * blockSize);
						ddsFlipDXT5Block(destinationRow + j * blockSize);
					}
					break;
				}
				}
				sourceRow += bytesInARow;
				destinationRow -= bytesInARow;
			}
		}

	public:
		struct PixelFormatDDS
		{
			uint32_t size = 0;
			uint32_t flags = 0;
			uint32_t fourCC = 0;
			uint32_t rgbBitCount = 0;
			uint32_t rBitMask = 0;
			uint32_t gBitMask = 0;
			uint32_t bBitMask = 0;
			uint32_t aBitMask = 0;
		};
		struct FileHeaderDDS
		{
			char id[4] = "";
			uint32_t size = 0;
			uint32_t flags = 0;
			uint32_t height = 0;
			uint32_t width = 0;
			uint32_t pitchLinearSize = 0;
			uint32_t depth = 0;
			uint32_t mipMapCount = 0;
			uint32_t reserved[11] { };
			PixelFormatDDS pixelFormat;
			uint32_t caps = 0;
			uint32_t caps2 = 0;
			uint32_t caps3 = 0;
			uint32_t caps4 = 0;
			uint32_t reserved2 = 0;
		};

		virtual ~DDSModule() = default;

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
			std::string lowercaseExt { };
			std::transform(extension.begin(), extension.end(), std::back_inserter(lowercaseExt), ::tolower);
			return lowercaseExt == ".dds" || lowercaseExt == "dds";
		}

		virtual ITexture* load(std::string const& path) const
		{
			return load(Filename { path });
		}

		virtual ITexture* load(Filename const& path) const
		{
			// Open file stream
			std::ifstream file(path.get(), std::fstream::in | std::fstream::binary);
			if (!file.good())
				return nullptr;
			// Read file header
			file.seekg(0, std::ios::beg);
			FileHeaderDDS fileHeader { };
			unsigned char fHeader[128];
			file.read(reinterpret_cast<char*>(&fHeader[0]), 128);
			for (auto i = 0; i < 4; i++)
				fileHeader.id[i] = fHeader[i];
			fileHeader.size = BitUtility::readUInt32_LE(&fHeader[4]);
			fileHeader.flags = BitUtility::readUInt32_LE(&fHeader[8]);
			fileHeader.height = BitUtility::readUInt32_LE(&fHeader[12]);
			fileHeader.width = BitUtility::readUInt32_LE(&fHeader[16]);
			fileHeader.pitchLinearSize = BitUtility::readUInt32_LE(&fHeader[20]);
			fileHeader.depth = BitUtility::readUInt32_LE(&fHeader[24]);
			fileHeader.mipMapCount = BitUtility::readUInt32_LE(&fHeader[28]);
			/* fileHeader.reserved */
			fileHeader.pixelFormat.size = BitUtility::readUInt32_LE(&fHeader[76]);
			fileHeader.pixelFormat.flags = BitUtility::readUInt32_LE(&fHeader[80]);
			fileHeader.pixelFormat.fourCC = BitUtility::readUInt32_LE(&fHeader[84]);
			fileHeader.pixelFormat.rgbBitCount = BitUtility::readUInt32_LE(&fHeader[88]);
			fileHeader.pixelFormat.rBitMask = BitUtility::readUInt32_LE(&fHeader[92]);
			fileHeader.pixelFormat.gBitMask = BitUtility::readUInt32_LE(&fHeader[96]);
			fileHeader.pixelFormat.bBitMask = BitUtility::readUInt32_LE(&fHeader[100]);
			fileHeader.pixelFormat.aBitMask = BitUtility::readUInt32_LE(&fHeader[104]);
			fileHeader.caps = BitUtility::readUInt32_LE(&fHeader[108]);
			fileHeader.caps2 = BitUtility::readUInt32_LE(&fHeader[112]);
			fileHeader.caps3 = BitUtility::readUInt32_LE(&fHeader[116]);
			fileHeader.caps4 = BitUtility::readUInt32_LE(&fHeader[120]);
			/* fileHeader.reserved 2 */
			if (strncmp(fileHeader.id, "DDS ", 4) != 0 || fileHeader.height <= 0 || fileHeader.width <= 0
					|| (fileHeader.pixelFormat.fourCC != static_cast<uint32_t>(FourCC::DXT1)
							&& fileHeader.pixelFormat.fourCC != static_cast<uint32_t>(FourCC::DXT3)
							&& fileHeader.pixelFormat.fourCC != static_cast<uint32_t>(FourCC::DXT5)))
				return nullptr;
			// Read actual image data
			const unsigned int bufsize {
					fileHeader.mipMapCount > 1 ? fileHeader.pitchLinearSize * 2 : fileHeader.pitchLinearSize };
			char* buffer = new char[bufsize];
			file.read(buffer, bufsize);
			// Close file
			file.close();

			// Analyze data
			ITextureCommands::PixelFormatCompressed format;
			switch (fileHeader.pixelFormat.fourCC)
			{
			case static_cast<uint32_t>(FourCC::DXT1):
				format = ITextureCommands::PixelFormatCompressed::COMP_DXT1;
				break;
			case static_cast<uint32_t>(FourCC::DXT3):
				format = ITextureCommands::PixelFormatCompressed::COMP_DXT3;
				break;
			case static_cast<uint32_t>(FourCC::DXT5):
				format = ITextureCommands::PixelFormatCompressed::COMP_DXT5;
				break;
			default:
				delete[] buffer;
				// Should never get here
				return nullptr;
			}

			// Create texture
			auto tex = Platform::get()->createTexture(ITexture::Type::TEX2D);
			tex->bind();
			Platform::get()->curTexture()->setRowAlignment(ITextureCommands::RowAlignment::UNPACK, 1);
			unsigned int offset = 0;
			unsigned int blockSize = (format == ITextureCommands::PixelFormatCompressed::COMP_DXT1) ? 8 : 16;
			unsigned int width = fileHeader.width;
			unsigned int height = fileHeader.height;
			// Load mipmaps
			for (unsigned int level = 0; level < fileHeader.mipMapCount && (fileHeader.width || fileHeader.height);
					++level)
			{
				// Vertically flip texture to fit OpenGL needs
				flipVertical(buffer, offset, width, height, blockSize,
						static_cast<FourCC>(fileHeader.pixelFormat.fourCC));
				// Send compressed image to GL
				unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
				Platform::get()->curTexture()->writeCompressed(level, width, height, format, size, buffer + offset);
				// Prepare for next mipmap
				offset += size;
				width /= 2;
				height /= 2;
				// If the texture is not squared, width or height might become 0
				// All mipmaps must have at least a width and height of 1
				if (width < 1)
					width = 1;
				if (height < 1)
					height = 1;
			}
			delete[] buffer;
			return tex;
		}

		virtual bool write(ITexture* tex, std::string const& path) const
		{
			return write(tex, Filename { path });
		}

		virtual bool write(ITexture* /* tex */, Filename const& /* path */) const
		{
			return false;
		}
	};
}

extern "C" dbgl::IImageFormatLibrary* create()
{
	return new dbgl::DDSModule { };
}

extern "C" void destroy(dbgl::IImageFormatLibrary* mod)
{
	delete mod;
}
