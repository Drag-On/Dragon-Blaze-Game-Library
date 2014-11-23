//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IMESHFORMATMODULE_H_
#define IMESHFORMATMODULE_H_

#include "DBGL/Platform/Mesh/IMesh.h"
#include "DBGL/Resources/FileFormat/IFileFormatModule.h"

namespace dbgl
{
    /**
     * @brief Interface class for all mesh loader and writer modules
     */
    using IMeshFormatModule = IFileFormatModule<IMesh>;
}

#endif /* IMESHFORMATMODULE_H_ */
