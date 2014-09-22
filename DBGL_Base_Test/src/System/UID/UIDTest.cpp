//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "cute.h"
#include "DBGL/System/UID/UID.h"

using namespace dbgl;

namespace UIDTest
{
    void testConstructor()
    {
	UID<> uid{};
	ASSERT(uid.isValid() == true);
	ASSERT_EQUAL(0, uid.getNumber());
	UID<> uid2{};
	ASSERT(uid2.isValid() == true);
	ASSERT_EQUAL(1, uid2.getNumber());
	UID<> uid3{3};
	ASSERT(uid3.isValid() == true);
	ASSERT_EQUAL(3, uid3.getNumber());
	UID<> uid4{};
	ASSERT(uid4.isValid() == true);
	ASSERT_EQUAL(2, uid4.getNumber());
	UID<> uid5{};
	ASSERT(uid5.isValid() == true);
	ASSERT_EQUAL(4, uid5.getNumber());

	UID<42> otherGroup{};
	ASSERT(otherGroup.isValid() == true);
	ASSERT_EQUAL(0, otherGroup.getNumber());
    }

    void testDestruction()
    {
	UID<1> uid {};
	ASSERT_EQUAL(0, uid.getNumber());
	UID<1> uid1 {};
	ASSERT_EQUAL(1, uid1.getNumber());
	UID<1>* uid2 = new UID<1>{};
	ASSERT_EQUAL(2, uid2->getNumber());
	delete uid2;
	UID<1>* uid3 = new UID<1>{};
	ASSERT_EQUAL(2, uid3->getNumber());
	delete uid3;
    }

    void testCopy()
    {
	UID<> uid{};
	ASSERT(uid.isValid() == true);
	ASSERT_EQUAL(0, uid.getNumber());
	UID<> copy{uid};
	ASSERT(copy.isValid() == true);
	ASSERT_EQUAL(0, copy.getNumber());
	uid.invalidate();
	ASSERT(uid.isValid() == false);
	ASSERT(copy.isValid() == false);

	UID<> uid2{};
	ASSERT(uid2.isValid() == true);
	ASSERT_EQUAL(0, uid2.getNumber());
    }

    void testOverflow()
    {
	auto codefunc = [] ()
	{
	    UID<21, uint8_t> arr[257]{};
	};
	ASSERT_THROWS(codefunc(), std::overflow_error);
    }

    void testManual()
    {
	UID<3> uid1{2};
	ASSERT_EQUAL(2, uid1.getNumber());
	UID<3> uid2{1};
	ASSERT_EQUAL(1, uid2.getNumber());
	UID<3> uid3{};
	ASSERT_EQUAL(0, uid3.getNumber());
	ASSERT_THROWS(UID<3> uid4{2}, std::runtime_error);
    }
}

using namespace UIDTest;

cute::suite testUID()
{
    cute::suite s{};
    s.push_back(CUTE(testConstructor));
    s.push_back(CUTE(testDestruction));
    s.push_back(CUTE(testCopy));
    s.push_back(CUTE(testOverflow));
    s.push_back(CUTE(testManual));
    return s;
}
