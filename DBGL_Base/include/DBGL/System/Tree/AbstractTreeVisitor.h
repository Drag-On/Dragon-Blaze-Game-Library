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

    class AbstractTreeVisitor
    {
	public:
	    virtual ~AbstractTreeVisitor() {}
	    virtual void visit(AbstractTreeVisitable& visitable) = 0;
    };
}



#endif /* ABSTRACTTREEVISITOR_H_ */
