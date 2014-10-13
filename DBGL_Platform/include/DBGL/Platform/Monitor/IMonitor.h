//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef IMONITOR_H_
#define IMONITOR_H_

namespace dbgl
{
    /**
     * @brief Interface class for monitor implementations. Provides data about the monitor.
     */
    class IMonitor
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~IMonitor() = default;
	    /**
	     * @brief Retrieves the resolution of the pc's monitor
	     * @param width Monitor width in pixels
	     * @param height Monitor height in pixels
	     */
	    virtual void getResolution(int& width, int& height) = 0;
    };
}

#endif /* IMONITOR_H_ */
