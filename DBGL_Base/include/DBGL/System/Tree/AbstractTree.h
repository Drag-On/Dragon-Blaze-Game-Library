//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ABSTRACTTREE_H_
#define ABSTRACTTREE_H_

#include "AbstractTreeVisitable.h"

namespace dbgl
{
    /**
     * @brief Interface class for tree implementations
     */
    class AbstractTree : public AbstractTreeVisitable
    {
	protected:
	    /**
	     * @brief Interface class for tree nodes
	     */
	    class Node : public AbstractTreeVisitable
	    {
	    };
    };
}



#endif /* ABSTRACTTREE_H_ */
