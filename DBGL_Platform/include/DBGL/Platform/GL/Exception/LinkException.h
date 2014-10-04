//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef LINKEXCEPTION_H_
#define LINKEXCEPTION_H_

#include <exception>

namespace dbgl
{
    class LinkException : public std::runtime_error
    {
	public:
	    LinkException(std::string const& msg) : std::runtime_error{msg} {}
    };
}

#endif /* LINKEXCEPTION_H_ */
