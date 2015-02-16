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

#include "DBGL/Platform/Library/Library.h"
#include "DBGL/Platform/Library/SimpleLibrary.h"
#include "ISimpleLibrary.h"

using namespace dbgl;
using namespace std;

using GimmeZeroType = int(*)();

int main()
{
    Library mod{"test_module." + Library::getFileExtension()};
    if(!mod.load())
    {
	cerr << "Unable to load module" << endl;
	return -1;
    }
    GimmeZeroType gimmeZero = (GimmeZeroType)mod.getFunction("gimmeZero");
    if(!gimmeZero)
    {
	cerr << "Unable to load function" << endl;
	return -2;
    }
    cout << "Simple way: gimmeZero() returned: " << gimmeZero() << endl;

    SimpleLibrary<ISimpleLibrary> amod{"test_module." + Library::getFileExtension()};
    if(!amod.load())
    {
	cerr << "Unable to load advanced module" << endl;
	return -1;
    }
    cout << "Advanced module: 3.5f + 1.9f = " << amod.get()->add(3.5f, 1.9f) << endl;
}


