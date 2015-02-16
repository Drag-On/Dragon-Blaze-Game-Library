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
#include "DBGL/Core/Hashing/OATHasher.h"
#include "DBGL/Core/Test/Test.h"

using namespace dbgl;
using namespace std;

TEST(OATHasher,equal32)
{
    std::string str1 {"Ein String"};
    std::string str2 {"Ein String"};
    ASSERT_EQ(OATHasher::hash32(str1), OATHasher::hash32(str2));
}

TEST(OATHasher,prior)
{
    std::vector<std::string> strings = {
	    "", "abc", "0", "C:/Programs/Whatever/Foo.exe", "./bar", "Hey yo, whassup?", "ResourceA", "ResourceB"
    };
    std::vector<uint32_t> hashes32{};
    for(unsigned int i = 0; i < strings.size(); i++)
    {
	auto hash32 = OATHasher::hash32(strings[i]);
	ASSERT(std::find(hashes32.begin(), hashes32.end(), hash32) == hashes32.end());
	hashes32.push_back(hash32);
    }
}

