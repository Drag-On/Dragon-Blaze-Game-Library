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
    int test = 42;
    bool foo = true;
    Log::inf << "This goes to the info stream. "  << test << " " << foo << std::flush;
    Log::dbg << "This goes to the debug stream. " << test << " " << foo << std::flush;
    Log::wrn << "This goes to the warning stream. " << test << " " << foo << std::flush;
    Log::err << "This goes to the error stream. " << test << " " << foo << std::flush;
    std::cout << "This should go to the info stream, too";
    std::cerr << "This should go to the error stream, too";
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}
