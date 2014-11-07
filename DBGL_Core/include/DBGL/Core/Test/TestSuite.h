//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TESTSUITE_H_
#define TESTSUITE_H_

#include <vector>
#include <string>
#include <iostream>
#include "TestCase.h"

namespace dbgl
{
    class TestSuite
    {
	public:
	    TestSuite(std::string name);
	    void run();
	    void add(TestCase test);
	    std::string const& getName() const;
	    void printStat() const;
	private:
	    std::string m_name;
	    std::vector<TestCase> m_testCases;
	    int m_successful = -1;
    };
}

#endif /* TESTSUITE_H_ */
