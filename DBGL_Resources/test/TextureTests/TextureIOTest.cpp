//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Utility/TextureUtility.h"
#include "DBGL/Resources/Texture/TextureIO.h"
#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"

using namespace dbgl;
using namespace std;

namespace dbgl_test_TextureIO
{
    IWindow* g_wnd = nullptr;
}

TEST_INITIALIZE(TextureIO)
{
    // Init graphics context
    Platform::init<OpenGL33>();
    dbgl_test_TextureIO::g_wnd = Platform::get()->createWindow();
}

TEST_TERMINATE(TextureIO)
{
    delete dbgl_test_TextureIO::g_wnd;
    Platform::destroy();
}

void testImg(TextureIO& io, std::string const& path)
{
    auto tex = io.load(path);
    ASSERT(tex);
    ASSERT(tex->getWidth() == 2);
    ASSERT(tex->getHeight() == 2);
    auto img = TextureUtility::createImageData(tex);
    ASSERT(img.getPixel(0, 0).getRed() == 0);
    ASSERT(img.getPixel(0, 0).getGreen() == 0);
    ASSERT(img.getPixel(0, 0).getBlue() == 0);
    ASSERT(img.getPixel(0, 0).getAlpha() == 255);
    ASSERT(img.getPixel(1, 0).getRed() == 255);
    ASSERT(img.getPixel(1, 0).getGreen() == 255);
    ASSERT(img.getPixel(1, 0).getBlue() == 255);
    ASSERT(img.getPixel(1, 0).getAlpha() == 255);
    ASSERT(img.getPixel(0, 1).getRed() == 0);
    ASSERT(img.getPixel(0, 1).getGreen() == 255);
    ASSERT(img.getPixel(0, 1).getBlue() == 0);
    ASSERT(img.getPixel(0, 1).getAlpha() == 255);
    ASSERT(img.getPixel(1, 1).getRed() == 255);
    ASSERT(img.getPixel(1, 1).getGreen() == 0);
    ASSERT(img.getPixel(1, 1).getBlue() == 0);
    ASSERT(img.getPixel(1, 1).getAlpha() == 255);
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
	testImg(io, "plugins\\Texture\\BMP\\test.bmp");
    }
}

TEST(TextureIO,tga)
{
    // TextureIO object
    TextureIO io {};
    if (!io.addFormat("plugins\\Texture\\TGA\\libDBGL_TGA.dll"))
    {
	FAIL();
    }
    else
    {
	testImg(io, "plugins\\Texture\\TGA\\test.tga");
    }
}
