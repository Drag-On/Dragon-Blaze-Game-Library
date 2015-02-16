//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RESOURCEEXCEPTION_H_
#define RESOURCEEXCEPTION_H_

#include <string>
#include <stdexcept>

namespace dbgl
{
    /**
     * @brief Exception that is thrown if there are issues regarding resources
     */
    class ResourceException: public std::runtime_error
    {
	public:
	    /**
	     * @brief Constructor
	     * @param what_arg Description
	     */
	    explicit ResourceException(const std::string& what_arg);
    };
}

#endif /* RESOURCEEXCEPTION_H_ */
