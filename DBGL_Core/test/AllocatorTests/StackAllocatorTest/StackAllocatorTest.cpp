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
	~foo()
	{
	    cout << "foo destructor called for (" << x << "," << y << ") :)" << endl;
	}
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
    cout << "Retrieving marker..." << endl;
    auto mark = mem.top();
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
    cout << "Trying to allocate another 4 foos..." << endl;
    for(unsigned int i = 0; i < 4; i++)
    {
	if(!mem.allocate<foo>())
	    cout << "Couldn't allocate " << i << ". foo instance." << endl;
    }
    cout << "Rolling back to marker, manually calling destructor on first created foo..." << endl;
    bar->~foo();
    mem.rollBack(mark);
    cout << "Clearing..." << endl;
    mem.clear();
    cout << "Allocating 4 foos..." << endl;
    for(unsigned int i = 0; i < 4; i++)
    {
	if(!mem.allocate<foo>())
	    cout << "Couldn't allocate " << i << "th foo instance." << endl;
    }
    cout << "Done!" << endl;

    return 0;
}


