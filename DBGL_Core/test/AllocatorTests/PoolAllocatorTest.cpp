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
#include "DBGL/Core/Test/Test.h"

using namespace dbgl;
using namespace std;

struct foo
{
	int x = 1;
	int y = 2;
	~foo()
	{
//	    cout << "foo destructor called for (" << x << "," << y << ") :)" << endl;
	    x = y = 0;
	}
};

TEST(PoolAllocator,main)
{
    PoolAllocator<foo> mem{8};
    foo* bar = mem.allocate();
    mem.deallocate(bar);
    foo* arr[8];
    for(unsigned int i = 0; i < 8; i++)
    {
	ASSERT((arr[i] = mem.allocate()) || i == 7);
    }
    foo* baz ;
    ASSERT(!(baz = mem.allocate()));
    for(unsigned int i = 0; i < 8; i++)
	mem.deallocate(arr[i]);
    mem.deallocate(baz);
    ASSERT(bar = mem.allocate());
    mem.deallocate(bar);
}
