//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include "DBGL/Core/Parsers/CSV.h"
#include "DBGL/Core/Test/Test.h"

using namespace dbgl;
using namespace std;

TEST_INITIALIZE(CSV)
{
    // Write test file
	std::ofstream fout("test.csv");
	fout << "Hello;World;0;3.74" << std::endl;
	fout << "42;true;foo;bar" << std::endl;
	fout << "\"baz\";;;" << std::endl;
}

TEST(CSV,access)
{
    try
    {
	CSV csv { "test.csv" };
	ASSERT(csv.getStringValue(0, 0) == "Hello");
	ASSERT(csv.getStringValue(1, 0) == "World");
	ASSERT(csv.getStringValue(2, 0) == "0");
	ASSERT(csv.getStringValue(3, 0) == "3.74");
	ASSERT(csv.getStringValue(0, 1) == "42");
	ASSERT(csv.getStringValue(1, 1) == "true");
	ASSERT(csv.getStringValue(2, 1) == "foo");
	ASSERT(csv.getStringValue(3, 1) == "bar");
	ASSERT(csv.getStringValue(0, 2) == "\"baz\"");
	ASSERT(csv.getStringValue(1, 2) == "");
	ASSERT(csv.getBoolValue(1, 1) == true);
	ASSERT(csv.getFloatValue(3, 0) == 3.74f);
	ASSERT(csv.getFloatValue(0, 1) == 42.0f);
	ASSERT(csv.getIntValue(2, 0) == 0);
    }
    catch(...)
    {
	FAIL();
    }
}

TEST(CSV,except)
{
    try
    {
	CSV csv { "test.csv" };
	ASSERT_THROWS(csv.getStringValue(42,100), std::exception);
    }
    catch (...)
    {
	FAIL();
    }
}

