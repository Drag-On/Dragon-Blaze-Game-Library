//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef DBGLAPPLICATION_H_
#define DBGLAPPLICATION_H_

namespace dbgl
{
    /**
     * @brief Pure virtual base class which can be used to build an application from
     */
    class IDbglApplication
    {
	public:
	    /**
	     * @brief Constructor
	     */
	    virtual ~IDbglApplication() = default;
	    /**
	     * @brief Called upon initialization
	     */
	    virtual void init() = 0;
	    /**
	     * @brief Called in order to run the main loop
	     */
	    virtual void run() = 0;
	    /**
	     * @brief Called upon termination
	     */
	    virtual void terminate() = 0;
    };
}

#endif /* DBGLAPPLICATION_H_ */
