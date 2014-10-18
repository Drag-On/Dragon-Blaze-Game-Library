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
#include <string>
#include <vector>
#include "DBGL/Core/Hashing/OATHasher.h"

using namespace dbgl;
using namespace std;

int main()
{
    std::vector<std::string> strings = {
	    "", "abc", "0", "C:/Programs/Whatever/Foo.exe", "./bar", "Hey yo, whassup?", "ResourceA", "ResourceB"
    };
    for(unsigned int i = 0; i < strings.size(); i++)
    {
	auto hash32 = OATHasher::hash32(strings[i]);
	cout << "32 bit hash for \"" << strings[i] << "\" is " << hash32 << "." << endl;
    }
    return 0;
}

