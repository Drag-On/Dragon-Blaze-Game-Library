//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Texture/BogusTextureLoader.h"

namespace dbgl
{
    Texture* BogusTextureLoader::load(std::string /* path */, Bitmask<> /* flags */, TextureLoader::Filtering /* filtering */)
    {
	auto handle = GLProvider::get()->texGenerate(IGL::TextureType::TEX2D);
	GLProvider::get()->texBind(handle);
	unsigned char data[3] = { 255, 255, 255 };
	GLProvider::get()->texWrite(0, 1, 1, IGL::PixelFormat::BGR, IGL::PixelType::UBYTE, &data);
	return new Texture(handle);
    }
}
