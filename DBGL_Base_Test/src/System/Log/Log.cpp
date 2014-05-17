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
    LOG->info("OK!");
    LOG->info("Done!");
    return 0;
}
