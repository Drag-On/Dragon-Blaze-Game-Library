//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/TestCase.h"

#include <iostream>

namespace dbgl
{
    TestCase::TestCase(std::string const& name, std::function<void()> func) : m_func{func}, m_name{name}
    {
    }

    bool TestCase::run()
    {
	try
	{
	    m_func();
	}
	catch (AssertException const& e)
	{
	    std::cerr << "Assertion failed in file \"" << e.getFile() << "\", line " << e.getLine() << "." << std::endl;
	    std::cerr << "\"" << e.what() << "\"" << std::endl;
	    return false;
	}
	return true;
    }

    std::string const& TestCase::getName() const
    {
	return m_name;
    }
}


