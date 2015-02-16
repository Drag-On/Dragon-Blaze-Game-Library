//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
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
    /**
     * @brief Test case, part of a test suite
     */
    class TestCase
    {
	public:
	    /**
	     * @brief Constructor
	     * @param name Test name
	     * @param func Function to execute for the test
	     */
	    TestCase(std::string const& name, std::function<void()> func);
	    /**
	     * @brief Executes the test
	     * @return True in case the test succeeded, otherwise false
	     */
	    bool run();
	    /**
	     * @brief Retrieves the name of this test
	     * @return Name of the test
	     */
	    std::string const& getName() const;
	private:
	    std::function<void()> m_func;
	    std::string m_name;
    };
}

#endif /* TESTCASE_H_ */
