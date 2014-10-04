//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef COMPILEEXCEPTION_H_
#define COMPILEEXCEPTION_H_

#include <exception>

namespace dbgl
{
    class CompileException : public std::runtime_error
    {
	public:
	    CompileException(std::string const& msg) : std::runtime_error{msg} {}
    };
}

#endif /* COMPILEEXCEPTION_H_ */
