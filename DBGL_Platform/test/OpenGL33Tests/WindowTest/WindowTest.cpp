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
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"

using namespace dbgl;
using namespace std;

int main()
{
    cout << "Initing..." << endl;
    Platform::init<OpenGL33>();
    cout << "Creating a window..." << endl;
    auto window = Platform::get()->createWindow("WindowTest", 720, 480, false, 0);
    cout << "Showing window..." << endl;
    window->show();
    while(window->isOpen())
    {
	window->waitEvents();
    }
    window->close();
    delete window;
    cout << "Destroying platform..." << endl;
    Platform::destroy();
    cout << "Finished!" << endl;
}

