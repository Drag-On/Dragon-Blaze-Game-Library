//////////////////////////////////////////////////////////////////////
/// Statistical Face Analysis
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Log/Log.h"

using namespace dbgl;

int testLog()
{
    LOG->info("Starting Log test suite...");
    LOG->info("Streams...");
    std::cout << "This should go to the info stream";
    std::cerr << "This should go to the error stream";
    LOG->info("Methods...");
    LOG->debug("Hello world!");
    LOG->debug("Gimme a number: %.", 42);
    LOG->debug("Here, take %$ and buy a nice %.", 1.5f, "dragon");
    try
    {
	LOG->debug("This! Has! Too! Many! ARGUMENTS!", "Bwahaha");
    }
    catch(...)
    {
	try
	{
	    std::rethrow_exception(std::current_exception());
	}
	catch(const std::exception& e)
	{
	    LOG->warning("Thrown: %", e.what());
	}
    }
    try
    {
	LOG->debug("Not enough arguments % %.", "passed");
    }
    catch(...)
    {
	try
	{
	    std::rethrow_exception(std::current_exception());
	}
	catch(const std::exception& e)
	{
	    LOG->warning("Thrown: %", e.what());
	}
    }
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}
