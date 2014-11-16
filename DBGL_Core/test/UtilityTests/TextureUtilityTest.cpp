//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Platform/Platform.h"
#include "DBGL/PLatform/Implementation/OpenGL33.h"
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Utility/TextureUtility.h"

using namespace dbgl;
using namespace std;

IWindow* g_pWnd = nullptr;

TEST_INITIALIZE(TextureUtility)
{
    Platform::init<OpenGL33>();
    g_pWnd = Platform::get()->createWindow();
}

TEST_TERMINATE(TextureUtility)
{
    g_pWnd->close();
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
    ASSERT(imDat.getPixel(0, 0).r == 0);
    ASSERT(imDat.getPixel(0, 0).g == 1);
    ASSERT(imDat.getPixel(0, 0).b == 2);
    ASSERT(imDat.getPixel(0, 0).a == 3);
    ASSERT(imDat.getPixel(1, 0).r == 4);
    ASSERT(imDat.getPixel(1, 0).g == 5);
    ASSERT(imDat.getPixel(1, 0).b == 6);
    ASSERT(imDat.getPixel(1, 0).a == 7);
    ASSERT(imDat.getPixel(0, 1).r == 8);
    ASSERT(imDat.getPixel(0, 1).g == 9);
    ASSERT(imDat.getPixel(0, 1).b == 10);
    ASSERT(imDat.getPixel(0, 1).a == 11);
    ASSERT(imDat.getPixel(1, 1).r == 12);
    ASSERT(imDat.getPixel(1, 1).g == 13);
    ASSERT(imDat.getPixel(1, 1).b == 14);
    ASSERT(imDat.getPixel(1, 1).a == 15);
}
