//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Collection/Tree/AbstractTreeVisitable.h"

namespace dbgl
{
    AbstractTreeVisitable::~AbstractTreeVisitable()
    {
    }

    void AbstractTreeVisitable::accept(AbstractTreeVisitor& visitor)
    {
	visitor.visit(*this);
    }
}
