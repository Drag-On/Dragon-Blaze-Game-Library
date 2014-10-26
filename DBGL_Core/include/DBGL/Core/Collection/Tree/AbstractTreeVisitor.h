//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ABSTRACTTREEVISITOR_H_
#define ABSTRACTTREEVISITOR_H_

namespace dbgl
{
    class AbstractTreeVisitable;

    /**
     * @brief Interface class for tree visitors
     */
    class AbstractTreeVisitor
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~AbstractTreeVisitor() {}
	    /**
	     * @brief Called by the tree on visit
	     * @param visitable Object that got visited
	     */
	    virtual void visit(AbstractTreeVisitable& visitable) = 0;
    };
}



#endif /* ABSTRACTTREEVISITOR_H_ */
