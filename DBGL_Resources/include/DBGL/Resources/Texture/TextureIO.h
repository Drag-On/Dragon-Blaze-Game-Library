//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_

#include "IImageFormatModule.h"
#include "DBGL/Resources/FileFormat/FileFormatIO.h"
#include "DBGL/Platform/Texture/ITexture.h"

namespace dbgl
{
    /**
     * @brief Loads textures from hard disk and stores them
     * @details This class doesn't contain any code to load or write image files, instead
     * 		it loads dynamic libraries that contain such code. The libraries must
     * 		be compatible with the AdvancedModule class from DBGL_Platform, and
     * 		provide instances of subclasses of ITextureFormat.
     */
    using TextureIO = FileFormatIO<ITexture, IImageFormatLibrary>;
}

#endif /* TEXTURELOADER_H_ */
