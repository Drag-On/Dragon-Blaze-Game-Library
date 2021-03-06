//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
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

    void TestSuite::initialize()
    {
	if(m_initialize)
	    m_initialize();
    }

    void TestSuite::run()
    {
	std::cout << m_name << "..." << std::endl;
	m_successful = 0;
	for(auto test : m_testCases)
	{
	    bool success = false;
	    try
	    {
		success = test.run();
	    }
	    catch (std::exception& e)
	    {
		std::cerr << "::\"" + test.getName() + "\" threw an unexpected exception!" << std::endl;
		std::cerr << e.what() << std::endl;
	    }
	    if(success)
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

    void TestSuite::terminate()
    {
	if(m_terminate)
	    m_terminate();
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
	float percent = 0;
	if (m_testCases.size() > 0)
	    percent = m_successful / static_cast<float>(m_testCases.size()) * 100.0f;
	std::cout << m_successful << " of " << m_testCases.size() << " successful ("
		<< percent << "%)" << std::endl;
    }

    unsigned int TestSuite::size() const
    {
	return m_testCases.size();
    }

    void TestSuite::setInitialize(std::function<void()> func)
    {
	m_initialize = func;
    }

    void TestSuite::setTerminate(std::function<void()> func)
    {
	m_terminate = func;
    }

}
