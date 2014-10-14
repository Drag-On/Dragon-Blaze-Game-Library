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
    /**
     * @brief Interface class for objects that can be visited by TreeVisitors
     */
    class AbstractTreeVisitable
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~AbstractTreeVisitable();
	    /**
	     * @brief Accepts a visitor
	     * @param visitor Visitor to accept
	     */
	    virtual void accept(AbstractTreeVisitor& visitor);
	    /**
	     * @brief Accepts a visitor
	     * @param visitor Visitor to accept
	     */
	    template <class Visitor, class MyType = AbstractTreeVisitable*> void accept(Visitor& visitor);
    };
}

#include "AbstractTreeVisitable.imp"

#endif /* ABSTRACTTREEVISITABLE_H_ */
