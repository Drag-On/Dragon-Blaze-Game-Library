//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Core/Utility/StringUtility.h"
#include "DBGL/Core/Test/Test.h"

#include <type_traits>

using namespace dbgl;
using namespace std;

TEST(StringUtility,trim)
{
    std::string testStr = "  hello world ";
    std::string copy = testStr;
    ASSERT_EQ(StringUtility::trim(copy), "hello world");
    copy = testStr;
    ASSERT_EQ(StringUtility::trimLeft(copy), "hello world ");
    copy = testStr;
    ASSERT_EQ(StringUtility::trimRight(copy), "  hello world");
}

template<typename T>
void testParseAsIntegral()
{
    ASSERT_NOTHROW(StringUtility::parseAs<T>("100"));
    ASSERT_EQ(StringUtility::parseAs<T>("100"), 100);
    ASSERT_NOTHROW(StringUtility::parseAs<typename std::make_signed<T>::type>("100"));
    ASSERT_EQ(StringUtility::parseAs<typename std::make_signed<T>::type>("100"), 100);
    ASSERT_NOTHROW(StringUtility::parseAs<typename std::make_unsigned<T>::type>("100"));
    ASSERT_EQ(StringUtility::parseAs<typename std::make_unsigned<T>::type>("100"), 100);
}

template<typename T>
void testParseAsFloat()
{
    ASSERT_NOTHROW(StringUtility::parseAs<T>("100"));
    ASSERT_EQ(StringUtility::parseAs<T>("100"), 100);
}

TEST(StringUtility,parseAs)
{
    testParseAsIntegral<char>();
    testParseAsIntegral<short>();
    testParseAsIntegral<int>();
    testParseAsIntegral<long>();
    testParseAsIntegral<long long>();
    testParseAsFloat<float>();
    testParseAsFloat<double>();
    testParseAsFloat<long double>();
    ASSERT_NOTHROW(StringUtility::parseAs<bool>("true"));
    ASSERT_EQ(StringUtility::parseAs<bool>("true"), true);
    ASSERT_NOTHROW(StringUtility::parseAs<bool>("false"));
    ASSERT_EQ(StringUtility::parseAs<bool>("false"), false);
}