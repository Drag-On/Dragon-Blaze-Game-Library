//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TESTCASE_H_
#define TESTCASE_H_

#include <functional>
#include <string>
#include "DBGL/Core/Test/Assert.h"

namespace dbgl
{
    class TestCase
    {
	public:
	    TestCase(std::string const& name, std::function<void()> func);
	    bool run();
	    std::string const& getName() const;
	private:
	    std::function<void()> m_func;
	    std::string m_name;
    };
}

#endif /* TESTCASE_H_ */
