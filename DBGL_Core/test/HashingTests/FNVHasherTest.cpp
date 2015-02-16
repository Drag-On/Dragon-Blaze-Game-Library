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
#include <string>
#include <vector>
#include <algorithm>
#include "DBGL/Core/Test/Test.h"
#include "DBGL/Core/Hashing/FNVHasher.h"

using namespace dbgl;
using namespace std;

TEST(FNVHasher,equality32)
{
    std::string str{"A String"};
    std::string str2{"A String"};
    ASSERT_EQ(FNVHasher::hash32(str), FNVHasher::hash32(str2));
}

TEST(FNVHasher,equality64)
{
    std::string str{"A String"};
    std::string str2{"A String"};
    ASSERT_EQ(FNVHasher::hash64(str), FNVHasher::hash64(str2));
}

TEST(FNVHasher,prior)
{
    std::vector<std::string> strings = {
	    "", "abc", "0", "C:/Programs/Whatever/Foo.exe", "./bar", "Hey yo, whassup?", "ResourceA", "ResourceB"
    };
    std::vector<uint32_t> hashes32{};
    std::vector<uint64_t> hashes64{};
    for(unsigned int i = 0; i < strings.size(); i++)
    {
	uint32_t hash32 = FNVHasher::hash32(strings[i]);
	ASSERT(std::find(hashes32.begin(), hashes32.end(), hash32) == hashes32.end());
	hashes32.push_back(hash32);
	uint64_t hash64 = FNVHasher::hash64(strings[i]);
	ASSERT(std::find(hashes64.begin(), hashes64.end(), hash64) == hashes64.end());
	hashes64.push_back(hash64);
    }
}
