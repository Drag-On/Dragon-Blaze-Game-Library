//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ABSTRACTTREEVISITABLE_H_
#define ABSTRACTTREEVISITABLE_H_

#include "AbstractTreeVisitor.h"

namespace dbgl
{
    class AbstractTreeVisitable
    {
	public:
	    virtual ~AbstractTreeVisitable();
	    virtual void accept(AbstractTreeVisitor& visitor);
    };
}



#endif /* ABSTRACTTREEVISITABLE_H_ */
