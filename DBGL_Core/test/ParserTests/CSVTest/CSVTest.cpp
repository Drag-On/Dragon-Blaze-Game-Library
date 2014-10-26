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
#include "DBGL/Core/Parsers/CSV.h"

using namespace dbgl;
using namespace std;

int main()
{
    cout << "Reading in csv..." << endl;
    try
    {
	CSV csv { "test.csv" };
	cout << "Elements:" << endl;
	for(int y = 0; y < 4; y++)
	    for(int x = 0; x < 4; x++)
		cout << "Element (" << x << "," << y << ") = " << csv.getStringValue(x, y) << endl;
    }
    catch (exception& e)
    {
	cerr << e.what() << endl;
    }
    return 0;
}

