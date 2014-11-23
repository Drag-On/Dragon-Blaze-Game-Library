//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IIMAGEFORMATMODULE_H_
#define IIMAGEFORMATMODULE_H_

#include "DBGL/Platform/Texture/ITexture.h"
#include "DBGL/Resources/FileFormat/IFileFormatModule.h"

namespace dbgl
{
    /**
     * @brief Interface class for all image loader and writer modules
     */
    using IImageFormatModule = IFileFormatModule<ITexture>;
}

#endif /* IIMAGEFORMATMODULE_H_ */
