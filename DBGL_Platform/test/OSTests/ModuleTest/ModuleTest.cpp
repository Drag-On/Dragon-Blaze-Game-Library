//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include "DBGL/Platform/Module/Module.h"

using namespace dbgl;
using namespace std;

using GimmeZeroType = int(*)();

int main()
{
    Module mod{"test_module.dll"};
    if(!mod.load())
    {
	cerr << "Unable to load module" << endl;
	return -1;
    }
    GimmeZeroType gimmeZero = mod.getFunction<GimmeZeroType>("gimmeZero");
    if(!gimmeZero)
    {
	cerr << "Unable to load function" << endl;
	return -2;
    }
    cout << gimmeZero() << endl;
}


