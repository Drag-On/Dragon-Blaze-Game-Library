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
#include "DBGL/Core/Utility/UID.h"

using namespace dbgl;
using namespace std;

TEST(UID,constructor)
{
    UID<> uid{};
    ASSERT(uid.isValid() == true);
    ASSERT_EQ(0, uid.getNumber());
    UID<> uid2{};
    ASSERT(uid2.isValid() == true);
    ASSERT_EQ(1, uid2.getNumber());
    UID<> uid3{3};
    ASSERT(uid3.isValid() == true);
    ASSERT_EQ(3, uid3.getNumber());
    UID<> uid4{};
    ASSERT(uid4.isValid() == true);
    ASSERT_EQ(2, uid4.getNumber());
    UID<> uid5{};
    ASSERT(uid5.isValid() == true);
    ASSERT_EQ(4, uid5.getNumber());

    UID<42> otherGroup{};
    ASSERT(otherGroup.isValid() == true);
    ASSERT_EQ(0, otherGroup.getNumber());
}

TEST(UID,destruction)
{
    UID<1> uid {};
    ASSERT_EQ(0, uid.getNumber());
    UID<1> uid1 {};
    ASSERT_EQ(1, uid1.getNumber());
    UID<1>* uid2 = new UID<1>{};
    ASSERT_EQ(2, uid2->getNumber());
    delete uid2;
    UID<1>* uid3 = new UID<1>{};
    ASSERT_EQ(2, uid3->getNumber());
    delete uid3;
}

TEST(UID,copy)
{
    UID<> uid{};
    ASSERT(uid.isValid() == true);
    ASSERT_EQ(0, uid.getNumber());
    UID<> copy{uid};
    ASSERT(copy.isValid() == true);
    ASSERT_EQ(0, copy.getNumber());
    uid.invalidate();
    ASSERT(uid.isValid() == false);
    ASSERT(copy.isValid() == false);

    UID<> uid2{};
    ASSERT(uid2.isValid() == true);
    ASSERT_EQ(0, uid2.getNumber());
}

TEST(UID,overflow)
{
    auto codefunc = [] ()
    {
	UID<21, uint8_t> arr[257]{};
    };
    ASSERT_THROWS(codefunc(), std::overflow_error);
}

TEST(UID,manual)
{
    UID<3> uid1{2};
    ASSERT_EQ(2, uid1.getNumber());
    UID<3> uid2{1};
    ASSERT_EQ(1, uid2.getNumber());
    UID<3> uid3{};
    ASSERT_EQ(0, uid3.getNumber());
    ASSERT_THROWS(UID<3> uid4{2}, std::runtime_error);
}

TEST(UID,clean)
{
    UID<666> uid{10};
    { // Create a mess
	UID<666> arr[100]{};
	arr[55] = UID<666>{200};
    }
    UID<666>::clean();
    UID<666> uid2{};
    ASSERT_EQ(0, uid2.getNumber());
}
