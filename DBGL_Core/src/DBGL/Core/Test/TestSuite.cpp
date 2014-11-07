//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/TestSuite.h"

namespace dbgl
{
    TestSuite::TestSuite(std::string name) : m_name{name}
    {

    }

    void TestSuite::run()
    {
	std::cout << m_name << "..." << std::endl;
	m_successful = 0;
	for(auto test : m_testCases)
	{
	    if(test.run())
	    {
		m_successful++;
		std::cout << "::\"" + test.getName() + "\" OK!" << std::endl;
	    }
	    else
	    {
		std::cerr << "::\"" + test.getName() + "\" FAILED!" << std::endl;
	    }
	}
    }

    void TestSuite::add(TestCase test)
    {
	m_testCases.push_back(test);
    }

    std::string const& TestSuite::getName() const
    {
	return m_name;
    }

    void TestSuite::printStat() const
    {
	std::cout << m_successful << " of " << m_testCases.size() << " successful ("
		<< m_successful / static_cast<float>(m_testCases.size()) * 100.0f << "%)" << std::endl;
    }

}
