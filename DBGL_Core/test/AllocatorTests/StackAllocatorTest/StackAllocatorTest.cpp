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
#include "DBGL/Core/Memory/StackAllocator.h"

using namespace dbgl;
using namespace std;

struct foo
{
	int x = 0;
	int y = 0;
};

int main()
{
    cout << "Creating allocator with 32 bytes..." << endl;
    StackAllocator mem{32};
    cout << "Allocating int..." << endl;
    int* number = mem.allocate<int>();
    if(!number)
    {
	cout << "int could not be allocated." << endl;
	return -1;
    }
    *number = 5;
    cout << "Number: " << *number << endl;
    cout << "Allocating foo..." << endl;
    foo* bar = mem.allocate<foo>();
    if(!bar)
    {
	cout << "foo could not be allocated." << endl;
	return -1;
    }
    bar->x = 42;
    bar->y = -10;
    cout << "foo: (" << bar->x << "," << bar->y << ")" << endl;
    cout << "Rolling back..." << endl;
    mem.clear();
    cout << "Done!" << endl;

    return 0;
}


