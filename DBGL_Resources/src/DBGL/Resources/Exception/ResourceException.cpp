//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Resources/Exception/ResourceException.h"

namespace dbgl
{
    ResourceException::ResourceException(const std::string& what_arg) :
	    std::runtime_error(what_arg)
    {
    }
}
