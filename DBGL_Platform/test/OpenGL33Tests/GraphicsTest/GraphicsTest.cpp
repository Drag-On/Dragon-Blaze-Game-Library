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

IWindow* pWnd = nullptr;

void resizeHandler(IWindow::FramebufferResizeEventArgs const& args)
{
    pWnd->getRenderContext().viewport(0, 0, args.width, args.height);
}

int main()
{
    cout << "Initing..." << endl;
    Platform::init<OpenGL33>();
    cout << "Creating a window..." << endl;
    pWnd = Platform::get()->createWindow("GraphicsTest", 720, 480, false, 0);
    cout << "Adding resize handler..." << endl;
    pWnd->addFramebufferResizeCallback(resizeHandler);
    cout << "Showing window..." << endl;
    pWnd->show();
    while(pWnd->isOpen())
    {
	pWnd->waitEvents();
	pWnd->getRenderContext().clear(IRenderContext::COLOR);
	pWnd->swapBuffer();
    }
    pWnd->close();
    delete pWnd;
    cout << "Destroying platform..." << endl;
    Platform::destroy();
    cout << "Finished!" << endl;
}

