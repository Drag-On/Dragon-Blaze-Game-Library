//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Resources/Texture/TextureUtility.h"

using namespace dbgl;
using namespace std;

namespace dbgl_test_TextureUtility
{
    IWindow* g_wnd = nullptr;
}

TEST_INITIALIZE(TextureUtility)
{
    Platform::init<OpenGL33>();
    dbgl_test_TextureUtility::g_wnd = Platform::get()->createWindow();
}

TEST_TERMINATE(TextureUtility)
{
    delete dbgl_test_TextureUtility::g_wnd;
    Platform::destroy();
}

TEST(TextureUtility,createImageData)
{
    auto tex = Platform::get()->createTexture(ITexture::Type::TEX2D);
    ASSERT(tex->getHeight() == 0);
    ASSERT(tex->getWidth() == 0);
    unsigned char buffer[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    tex->write(0, 2, 2, ITexture::PixelFormat::RGBA, ITexture::PixelType::UBYTE, &buffer[0]);
    ASSERT(tex->getHeight() == 2);
    ASSERT(tex->getWidth() == 2);
    auto imDat = TextureUtility::createImageData(tex);
    ASSERT(imDat.getHeight() == 2);
    ASSERT(imDat.getWidth() == 2);
    ASSERT(imDat.getPixel(0, 0).getRed() == 0);
    ASSERT(imDat.getPixel(0, 0).getGreen() == 1);
    ASSERT(imDat.getPixel(0, 0).getBlue() == 2);
    ASSERT(imDat.getPixel(0, 0).getAlpha() == 3);
    ASSERT(imDat.getPixel(1, 0).getRed() == 4);
    ASSERT(imDat.getPixel(1, 0).getGreen() == 5);
    ASSERT(imDat.getPixel(1, 0).getBlue() == 6);
    ASSERT(imDat.getPixel(1, 0).getAlpha() == 7);
    ASSERT(imDat.getPixel(0, 1).getRed() == 8);
    ASSERT(imDat.getPixel(0, 1).getGreen() == 9);
    ASSERT(imDat.getPixel(0, 1).getBlue() == 10);
    ASSERT(imDat.getPixel(0, 1).getAlpha() == 11);
    ASSERT(imDat.getPixel(1, 1).getRed() == 12);
    ASSERT(imDat.getPixel(1, 1).getGreen() == 13);
    ASSERT(imDat.getPixel(1, 1).getBlue() == 14);
    ASSERT(imDat.getPixel(1, 1).getAlpha() == 15);
}

TEST(TextureUtility,replaceTexture)
{
    auto tex = Platform::get()->createTexture(ITexture::Type::TEX2D);
    ASSERT(tex->getHeight() == 0);
    ASSERT(tex->getWidth() == 0);
    unsigned char buffer[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    tex->write(0, 2, 2, ITexture::PixelFormat::RGBA, ITexture::PixelType::UBYTE, &buffer[0]);
    ASSERT(tex->getHeight() == 2);
    ASSERT(tex->getWidth() == 2);
    auto imDat = TextureUtility::createImageData(tex);
    unsigned char val = 42;
    imDat.setPixel(0, 0, Color{val, val, val, val});
    TextureUtility::replaceTexture(tex, imDat);
    imDat = TextureUtility::createImageData(tex);
    ASSERT(imDat.getHeight() == 2);
    ASSERT(imDat.getWidth() == 2);
    ASSERT(imDat.getPixel(0, 0).getRed() == 42);
    ASSERT(imDat.getPixel(0, 0).getGreen() == 42);
    ASSERT(imDat.getPixel(0, 0).getBlue() == 42);
    ASSERT(imDat.getPixel(0, 0).getAlpha() == 42);
    ASSERT(imDat.getPixel(1, 0).getRed() == 4);
    ASSERT(imDat.getPixel(1, 0).getGreen() == 5);
    ASSERT(imDat.getPixel(1, 0).getBlue() == 6);
    ASSERT(imDat.getPixel(1, 0).getAlpha() == 7);
    ASSERT(imDat.getPixel(0, 1).getRed() == 8);
    ASSERT(imDat.getPixel(0, 1).getGreen() == 9);
    ASSERT(imDat.getPixel(0, 1).getBlue() == 10);
    ASSERT(imDat.getPixel(0, 1).getAlpha() == 11);
    ASSERT(imDat.getPixel(1, 1).getRed() == 12);
    ASSERT(imDat.getPixel(1, 1).getGreen() == 13);
    ASSERT(imDat.getPixel(1, 1).getBlue() == 14);
    ASSERT(imDat.getPixel(1, 1).getAlpha() == 15);
}
