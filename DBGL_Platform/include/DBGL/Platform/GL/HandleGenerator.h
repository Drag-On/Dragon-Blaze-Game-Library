//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef HANDLEGENERATOR_H_
#define HANDLEGENERATOR_H_

#include "stack"
#include "stdint.h"
#include "limits"

namespace dbgl
{
    /**
     * @brief Generates handles for the use of GL implementations
     */
    class HandleGenerator
    {
	public:
	    /**
	     * @brief Uses unsigned integers as handles
	     */
	    using Handle = uint32_t;
	    /**
	     * @brief Value that serves as an indicator for invalid handles
	     */
	    static constexpr Handle InvalidHandle = std::numeric_limits<Handle>::max();

	    /**
	     * @brief Generates a new handle
	     * @return The newly generated handle
	     */
	    Handle generate();
	    /**
	     * @brief Invalidates the passed handle
	     * @param[in,out] handle Handle that will be invalidated
	     */
	    void invalidate(Handle& handle);
	private:
	    Handle m_nextHandle = 0;
	    std::stack<Handle> m_openStack {};
    };
}

#endif /* HANDLEGENERATOR_H_ */
