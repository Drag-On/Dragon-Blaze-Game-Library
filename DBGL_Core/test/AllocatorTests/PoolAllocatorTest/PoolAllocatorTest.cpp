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
#include "DBGL/Core/Memory/PoolAllocator.h"

using namespace dbgl;
using namespace std;

struct foo
{
	int x = 1;
	int y = 2;
	~foo()
	{
	    cout << "foo destructor called for (" << x << "," << y << ") :)" << endl;
	    x = y = 0;
	}
};

int main()
{
    cout << "Creating allocator for 8 foo objects" << endl;
    PoolAllocator<foo> mem{8};
    cout << "Allocating new foo..." << endl;
    foo* bar = mem.allocate();
    cout << "Deallocate foo again..." << endl;
    mem.deallocate(bar);
    cout << "Allocating 8 foos..." << endl;
    foo* arr[8];
    for(unsigned int i = 0; i< 8; i++)
    {
	if(!(arr[i] = mem.allocate()))
	    cout << "Allocation not possible for element " << i << "!" << endl;
    }
    cout << "Allocating another foo..." << endl;
    foo* baz ;
    if(!(baz = mem.allocate()))
	cout << "Couldn't allocate foo!" << endl;
    cout <<"Deallocate everything..." << endl;
    for(unsigned int i = 0; i < 8; i++)
	mem.deallocate(arr[i]);
    mem.deallocate(baz);
    cout << "Allocate another foo..." << endl;
    if(!(bar = mem.allocate()))
	cout << "Couldn't allocate!" << endl;
    cout << "Deallocate again..." << endl;
    mem.deallocate(bar);
    cout << "Done!" << endl;
    return 0;
}


