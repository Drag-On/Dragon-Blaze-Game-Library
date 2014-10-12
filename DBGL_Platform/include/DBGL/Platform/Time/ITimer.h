//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef ITIMER_H_
#define ITIMER_H_

namespace dbgl
{
    /**
     * @brief Interface class for a high-precision timer
     */
    class ITimer
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~ITimer() = default;
	    /**
	     * @brief Provides the current time in seconds since platform startup
	     * @details The resolution of the timer is dependent of the underlying system;
	     * 		Generally the timer with the highest precision available is used.
	     * @return Time in seconds since startup
	     */
	    virtual double getTime() = 0;
	    /**
	     * @brief Provides the time that has passed since the last call of this mehod
	     * @return Time in seconds since the last call of getDelta()
	     */
	    virtual double getDelta() = 0;
    };
}

#endif /* ITIMER_H_ */
