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
#include "DBGL/Core/Test/Test.h"

using namespace dbgl;
using namespace std;

struct foo
{
	int x = 0;
	int y = 0;
	~foo()
	{
//	    cout << "foo destructor called for (" << x << "," << y << ") :)" << endl;
	}
};

TEST(StackAllocator,main)
{
    StackAllocator mem{32};
    int* number = mem.allocate<int>();
    ASSERT(number)
    *number = 5;
    ASSERT(*number == 5);
    auto mark = mem.top();
    foo* bar = mem.allocate<foo>();
    ASSERT(bar);
    bar->x = 42;
    bar->y = -10;
    ASSERT(bar->x == 42 && bar->y == -10);
    for(unsigned int i = 0; i < 3; i++)
    {
	ASSERT(mem.allocate<foo>() || i == 2);
    }
    bar->~foo();
    ASSERT_NOTHROW(mem.rollBack(mark));
    ASSERT_NOTHROW(mem.clear());
    for(unsigned int i = 0; i < 4; i++)
    {
	ASSERT(mem.allocate<foo>());
    }
}


