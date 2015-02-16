//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/Assert.h"

namespace dbgl
{
    AssertException::AssertException(std::string const& file, unsigned int line, std::string const& msg) :
	    std::runtime_error { msg }, m_file { file }, m_line { line }
    {
    }

    std::string const& AssertException::getFile() const
    {
	return m_file;
    }

    unsigned int AssertException::getLine() const
    {
	return m_line;
    }
}
