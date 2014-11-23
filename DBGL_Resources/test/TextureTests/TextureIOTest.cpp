//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Math/Utility.h"
#include "DBGL/Resources/Texture/TextureIO.h"
#include "DBGL/Resources/Texture/TextureUtility.h"

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

void testImg(TextureIO& io, std::string const& path, unsigned char accuracy = 0)
{
    auto tex = io.load(path);
    ASSERT(tex);
    ASSERT(tex->getWidth() == 2);
    ASSERT(tex->getHeight() == 2);
    auto img = TextureUtility::createImageData(tex);
    ASSERT(dbgl::isSimilar(img.getPixel(0, 0).getRed(), static_cast<unsigned char>(0), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(0, 0).getGreen(), static_cast<unsigned char>(0), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(0, 0).getBlue(), static_cast<unsigned char>(0), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(0, 0).getAlpha(), static_cast<unsigned char>(255), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(1, 0).getRed(), static_cast<unsigned char>(255), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(1, 0).getGreen(), static_cast<unsigned char>(255), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(1, 0).getBlue(), static_cast<unsigned char>(255), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(1, 0).getAlpha(), static_cast<unsigned char>(255), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(0, 1).getRed(), static_cast<unsigned char>(0), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(0, 1).getGreen(), static_cast<unsigned char>(255), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(0, 1).getBlue(), static_cast<unsigned char>(0), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(0, 1).getAlpha(), static_cast<unsigned char>(255), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(1, 1).getRed(), static_cast<unsigned char>(255), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(1, 1).getGreen(), static_cast<unsigned char>(0), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(1, 1).getBlue(), static_cast<unsigned char>(0), accuracy));
    ASSERT(dbgl::isSimilar(img.getPixel(1, 1).getAlpha(), static_cast<unsigned char>(255), accuracy));
}

TEST(TextureIO,bmp)
{
    // TextureIO object
    TextureIO io {};
    if (!io.addFormat("plugins\\Texture\\BMP\\libDBGL_BMP." + Module::getFileExtension()))
	FAIL();
    else
	testImg(io, "plugins\\Texture\\BMP\\test.bmp");
}

TEST(TextureIO,tga)
{
    // TextureIO object
    TextureIO io {};
    if (!io.addFormat("plugins\\Texture\\TGA\\libDBGL_TGA." + Module::getFileExtension()))
	FAIL();
    else
	testImg(io, "plugins\\Texture\\TGA\\test.tga");
}

TEST(TextureIO,dds)
{
    // TextureIO object
    TextureIO io {};
    if (!io.addFormat("plugins\\Texture\\DDS\\libDBGL_DDS." + Module::getFileExtension()))
	FAIL();
    else
    {
	testImg(io, "plugins\\Texture\\DDS\\test.dds", 200); // DDS compression destroys a lot of information...
    }
}
