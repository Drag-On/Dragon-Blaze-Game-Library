//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TEST_H_
#define TEST_H_

#include <string>
#include <unordered_map>
#include "TestSuite.h"
#include "TestCase.h"
#include "Assert.h"

namespace dbgl
{
    /**
     * @brief Struct that registers test suites to be run
     */
    struct AutoRegistration
    {
	public:
	    /**
	     * @brief Retrieves the map of test suite names to test suite instances
	     * @return Reference to map
	     */
	    static std::unordered_map<std::string, dbgl::TestSuite>& getMap()
	    {
		static std::unordered_map<std::string, dbgl::TestSuite> s_testSuites {};
		return s_testSuites;
	    }
	    /**
	     * @brief Gets a test suite by it's name
	     * @param name Name of the test suite
	     * @return The test suite
	     */
	    static TestSuite& getTestSuite(std::string const& name)
	    {
		auto& s_testSuites = getMap();
		auto iter = s_testSuites.find(name);
		if (iter == s_testSuites.end())
		{
		    s_testSuites.emplace(name, TestSuite{name});
		    return s_testSuites.at(name);
		}
		else
		    return iter->second;
	    }
	    /**
	     * @brief Registers a test case to a test suite
	     * @param testSuite Test suite to register to
	     * @param testCase Test case to register
	     */
	    AutoRegistration(std::string const& testSuite, TestCase testCase)
	    {
		auto& suite = getTestSuite(testSuite);
		suite.add(testCase);
	    }
    };

    /**
     * @brief Struct that registers initialization routines to test suites
     */
    struct AutoInitializationRegistration
    {
	public:
	    /**
	     * @brief Registers a function to be run on startup of a test suite
	     * @param testSuite Test suite to register to
	     * @param func Function to run on suite startup
	     */
	    AutoInitializationRegistration(std::string const& testSuite, std::function<void()> func)
	    {
		auto& suite = AutoRegistration::getTestSuite(testSuite);
		suite.setInitialize(func);
	    }
    };

    /**
     * @brief Struct that registers termination routines to test suites
     */
    struct AutoTerminationRegistration
    {
	public:
	    /**
	     * @brief Registers a function to be run on termination of a test suite
	     * @param testSuite Test suite to register to
	     * @param func Function to run on suite termination
	     */
	    AutoTerminationRegistration(std::string const& testSuite, std::function<void()> func)
	    {
		auto& suite = AutoRegistration::getTestSuite(testSuite);
		suite.setTerminate(func);
	    }
    };
}

/**
 * @brief Define a test case of a test suite
 * @details The test will automatically be registered and run, no need to define a main()
 * 	    Use like this:
 * 	    TEST(suitename, casename)
 * 	    {
 * 	    	// Do the tests...
 * 	    }
 */
#define TEST(test_suite,test_case)													\
    static void test_suite##_##test_case();												\
    static dbgl::AutoRegistration register_##test_suite##_##test_case(#test_suite, dbgl::TestCase(#test_case, test_suite##_##test_case));	\
    static void test_suite##_##test_case()

/**
 * @brief Define some code to run before any tests of a suite are run
 */
#define TEST_INITIALIZE(test_suite)										\
    static void test_suite##_init();									\
    static dbgl::AutoInitializationRegistration register_##test_suite##_init(#test_suite, test_suite##_init);	\
    static void test_suite##_init()

/**
 * @brief Define some code to run before any tests of a suite are run
 */
#define TEST_TERMINATE(test_suite)										\
    static void test_suite##_term();									\
    static dbgl::AutoTerminationRegistration register_##test_suite##_term(#test_suite, test_suite##_term);	\
    static void test_suite##_term()

#define DBGL_CREATE_TEST_MAIN									\
int main()											\
{												\
    for(auto tc : dbgl::AutoRegistration::getMap())						\
    {												\
	try { tc.second.initialize(); }								\
	catch (...) { std::cerr << tc.second.getName() << " initialize failed!" << std::endl; }	\
	try { tc.second.run(); }								\
	catch (...) { std::cerr << tc.second.getName() << " run failed!" << std::endl; } 	\
	try { tc.second.terminate(); }								\
	catch (...) { std::cerr << tc.second.getName() << " terminate failed!" << std::endl; } 	\
	try { tc.second.printStat(); }								\
	catch (...) { std::cerr << tc.second.getName() << " printstat failed!" << std::endl; } 	\
    }												\
    return 0;											\
}

#ifdef DBGL_TEST_MAIN
/**
 * @brief Test suite main entry point
 * @return Returns 0.
 */
DBGL_CREATE_TEST_MAIN
#endif

#endif /* TEST_H_ */
