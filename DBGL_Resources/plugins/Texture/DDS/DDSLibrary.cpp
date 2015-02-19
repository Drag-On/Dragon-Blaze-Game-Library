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
			fileHeader.size = (fHeader[4] << 0) | (fHeader[5] << 8) | (fHeader[6] << 16) | (fHeader[7] << 24);
			fileHeader.flags = (fHeader[8] << 0) | (fHeader[9] << 8) | (fHeader[10] << 16) | (fHeader[11] << 24);
			fileHeader.height = (fHeader[12] << 0) | (fHeader[13] << 8) | (fHeader[14] << 16) | (fHeader[15] << 24);
			fileHeader.width = (fHeader[16] << 0) | (fHeader[17] << 8) | (fHeader[18] << 16) | (fHeader[19] << 24);
			fileHeader.pitchLinearSize = (fHeader[20] << 0) | (fHeader[21] << 8) | (fHeader[22] << 16)
					| (fHeader[23] << 24);
			fileHeader.depth = (fHeader[24] << 0) | (fHeader[25] << 8) | (fHeader[26] << 16) | (fHeader[27] << 24);
			fileHeader.mipMapCount = (fHeader[28] << 0) | (fHeader[29] << 8) | (fHeader[30] << 16)
					| (fHeader[31] << 24);
			/* fileHeader.reserved */
			fileHeader.pixelFormat.size = (fHeader[76] << 0) | (fHeader[77] << 8) | (fHeader[78] << 16)
					| (fHeader[79] << 24);
			fileHeader.pixelFormat.flags = (fHeader[80] << 0) | (fHeader[81] << 8) | (fHeader[82] << 16)
					| (fHeader[83] << 24);
			fileHeader.pixelFormat.fourCC = (fHeader[84] << 0) | (fHeader[85] << 8) | (fHeader[86] << 16)
					| (fHeader[87] << 24);
			fileHeader.pixelFormat.rgbBitCount = (fHeader[88] << 0) | (fHeader[89] << 8) | (fHeader[90] << 16)
					| (fHeader[91] << 24);
			fileHeader.pixelFormat.rBitMask = (fHeader[92] << 0) | (fHeader[93] << 8) | (fHeader[94] << 16)
					| (fHeader[95] << 24);
			fileHeader.pixelFormat.gBitMask = (fHeader[96] << 0) | (fHeader[97] << 8) | (fHeader[98] << 16)
					| (fHeader[99] << 24);
			fileHeader.pixelFormat.bBitMask = (fHeader[100] << 0) | (fHeader[101] << 8) | (fHeader[102] << 16)
					| (fHeader[103] << 24);
			fileHeader.pixelFormat.aBitMask = (fHeader[104] << 0) | (fHeader[105] << 8) | (fHeader[106] << 16)
					| (fHeader[107] << 24);
			fileHeader.caps = (fHeader[108] << 0) | (fHeader[109] << 8) | (fHeader[110] << 16) | (fHeader[111] << 24);
			fileHeader.caps2 = (fHeader[112] << 0) | (fHeader[113] << 8) | (fHeader[114] << 16) | (fHeader[115] << 24);
			fileHeader.caps3 = (fHeader[116] << 0) | (fHeader[116] << 8) | (fHeader[118] << 16) | (fHeader[119] << 24);
			fileHeader.caps4 = (fHeader[120] << 0) | (fHeader[121] << 8) | (fHeader[122] << 16) | (fHeader[123] << 24);
			/* fileHeader.reserved 2 */
			if (strncmp(fileHeader.id, "DDS ", 4) != 0 || fileHeader.height <= 0 || fileHeader.width <= 0
					|| (fileHeader.pixelFormat.fourCC != static_cast<uint32_t>(FourCC::DXT1)
							&& fileHeader.pixelFormat.fourCC != static_cast<uint32_t>(FourCC::DXT3)
							&& fileHeader.pixelFormat.fourCC != static_cast<uint32_t>(FourCC::DXT5)))
				return nullptr;
			// Read actual image data
			const unsigned int bufsize {
					fileHeader.mipMapCount > 1 ? fileHeader.pitchLinearSize * 2 : fileHeader.pitchLinearSize };
			char buffer[bufsize] { };
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
