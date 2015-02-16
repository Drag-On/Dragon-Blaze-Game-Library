//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TESTSUITE_H_
#define TESTSUITE_H_

#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include "TestCase.h"

namespace dbgl
{
    /**
     * @brief Test suite, contains test cases
     */
    class TestSuite
    {
	public:
	    /**
	     * @brief Constructor
	     * @param name Test suite name
	     */
	    TestSuite(std::string name);
	    /**
	     * @brief Initializes this test suite if an initialization procedure was set
	     */
	    void initialize();
	    /**
	     * @brief Executes all attached test cases
	     */
	    void run();
	    /**
	     * @brief Deinitializes this test suite if an termination procedure was set
	     */
	    void terminate();
	    /**
	     * @brief Attaches a test case
	     * @param test Test to attach
	     */
	    void add(TestCase test);
	    /**
	     * @brief Retrieves the suite name
	     * @return Suite name
	     */
	    std::string const& getName() const;
	    /**
	     * @brief Prints stats of the last run
	     */
	    void printStat() const;
	    /**
	     * @brief Amount of attached test cases
	     * @return Amount of attached test cases
	     */
	    unsigned int size() const;
	    /**
	     * @brief Sets an initialization function
	     * @param func Function to use
	     */
	    void setInitialize(std::function<void()> func);
	    /**
	     * @brief Sets a termination function
	     * @param func Function to use
	     */
	    void setTerminate(std::function<void()> func);
	private:
	    std::string m_name;
	    std::vector<TestCase> m_testCases;
	    int m_successful = -1;
	    std::function<void()> m_initialize;
	    std::function<void()> m_terminate;
    };
}

#endif /* TESTSUITE_H_ */
