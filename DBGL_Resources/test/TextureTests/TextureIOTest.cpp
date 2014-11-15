//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Resources/Texture/TextureIO.h"
#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"

using namespace dbgl;
using namespace std;

TEST_INITIALIZE(TextureIO)
{
    // Init graphics context
    Platform::init<OpenGL33>();
    Platform::get()->createWindow();
}

TEST_TERMINATE(TextureIO)
{
    Platform::destroy();
}

TEST(TextureIO,bmp)
{
    // TextureIO object
    TextureIO io {};
    if (!io.addFormat("plugins\\Texture\\BMP\\libDBGL_BMP.dll"))
    {
	FAIL();
    }
    else
    {
	auto tex = io.load("plugins\\Texture\\BMP\\test.bmp");
	ASSERT(tex);
	ASSERT(tex->getWidth() == 2);
	ASSERT(tex->getHeight() == 2);
	unsigned char pixelDat[2 * 2 * 3];
	tex->bind(0);
	tex->setRowAlignment(ITexture::RowAlignment::PACK, 1);
	tex->getPixelData(ITexture::PixelFormat::RGB, ITexture::PixelType::BYTE,
		reinterpret_cast<char*>(&(pixelDat[0])), 0);
	ASSERT(pixelDat[0] == 0);
	ASSERT(pixelDat[1] == 0);
	ASSERT(pixelDat[2] == 0);
	ASSERT(pixelDat[3] == 254);
	ASSERT(pixelDat[4] == 254);
	ASSERT(pixelDat[5] == 254);
	ASSERT(pixelDat[6] == 0);
	ASSERT(pixelDat[7] == 254);
	ASSERT(pixelDat[8] == 0);
	ASSERT(pixelDat[9] == 254);
	ASSERT(pixelDat[10] == 0);
	ASSERT(pixelDat[11] == 0);
    }
}
