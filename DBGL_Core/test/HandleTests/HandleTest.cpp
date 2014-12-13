//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Handle/HandleFactory.h"

using namespace dbgl;
using namespace std;

TEST(Handle,constructor)
{
    HandleFactory<> handleFactory;

    auto handle1 = handleFactory.next();
    ASSERT(handle1.isValid() == true);
    ASSERT_EQ(0, handle1.getValue());
    auto handle2 = handleFactory.next();
    ASSERT(handle2.isValid() == true);
    ASSERT_EQ(1, handle2.getValue());
    auto handle3 = handleFactory.request(3);
    ASSERT(handle3.isValid() == true);
    ASSERT_EQ(3, handle3.getValue());
    auto handle4 = handleFactory.next();
    ASSERT(handle4.isValid() == true);
    ASSERT_EQ(2, handle4.getValue());
    auto handle5 = handleFactory.next();
    ASSERT(handle5.isValid() == true);
    ASSERT_EQ(4, handle5.getValue());

    HandleFactory<> handleFactory2;
    auto otherHandle = handleFactory2.next();
    ASSERT(otherHandle.isValid() == true);
    ASSERT_EQ(0, otherHandle.getValue());

    HandleFactory<>::Handle invalidHandle;
    ASSERT(invalidHandle.isValid() == false);
    ASSERT_EQ(HandleFactory<>::Handle::InvalidHandle, invalidHandle.getValue());
}

TEST(Handle,destruction)
{
    HandleFactory<> handleFactoryOut;
    auto handle4 = handleFactoryOut.next();
    ASSERT_EQ(handle4.getValue(), 0);

    {
	HandleFactory<> handleFactory;

	{
	    auto handle1 = handleFactory.next();
	    ASSERT_EQ(0, handle1.getValue());
	    auto handle2 = handleFactory.next();
	    ASSERT_EQ(1, handle2.getValue());
	    auto handle3 = handleFactory.request(3);
	    ASSERT_EQ(3, handle3.getValue());
	}
	auto handle1 = handleFactory.next();
	ASSERT_EQ(0, handle1.getValue());
	auto handle2 = handleFactory.next();
	ASSERT_EQ(1, handle2.getValue());
	auto handle3 = handleFactory.request(3);
	ASSERT_EQ(3, handle3.getValue());
	handle4 = handleFactory.next();
	ASSERT_EQ(2, handle4.getValue());
    }
    ASSERT_EQ(handle4.isValid(), false);
}

TEST(Handle,copy)
{
    HandleFactory<> handleFactory;

    auto handle1 = handleFactory.next();
    ASSERT(handle1.isValid() == true);
    ASSERT_EQ(0, handle1.getValue());
    HandleFactory<>::Handle copy{handle1};
    ASSERT(copy.isValid() == true);
    ASSERT_EQ(0, copy.getValue());
    handle1.invalidate();
    ASSERT(handle1.isValid() == false);
    ASSERT(copy.isValid() == false);

    auto handle2 = handleFactory.next();
    ASSERT(handle2.isValid() == true);
    ASSERT_EQ(0, handle2.getValue());
}

TEST(Handle,overflow)
{
    auto codefunc = [] ()
    {
	HandleFactory<uint8_t> handleFactory;
	HandleFactory<uint8_t>::Handle handles[257];
	for(int i = 0; i < 257; i++)
	    handles[i] = handleFactory.next();
    };
    ASSERT_THROWS(codefunc(), std::overflow_error);
}

TEST(Handle,manual)
{
    HandleFactory<uint8_t> handleFactory;

    auto handle1 = handleFactory.request(2);
    ASSERT_EQ(2, handle1.getValue());
    auto handle2 = handleFactory.request(1);
    ASSERT_EQ(1, handle2.getValue());
    auto handle3 = handleFactory.next();
    ASSERT_EQ(0, handle3.getValue());
    ASSERT_THROWS(handleFactory.request(2), std::runtime_error);
}

TEST(Handle,clean)
{
    HandleFactory<> handleFactory;

    auto handle1 = handleFactory.request(10);
    { // Create a mess
	HandleFactory<>::Handle handles[100];
	for(int i = 0; i < 100; i++)
	    handles[i] = handleFactory.next();

	handles[55] = handleFactory.request(200);
    }
    handleFactory.clean();
    auto handle = handleFactory.next();
    ASSERT_EQ(0, handle.getValue());
}
