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
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"

using namespace dbgl;
using namespace std;

IWindow* pWnd = nullptr;
IMesh* pMesh = nullptr;
IShaderProgram* pSP = nullptr;

void resizeHandler(IWindow::FramebufferResizeEventArgs const& args)
{
    pWnd->getRenderContext().viewport(0, 0, args.width, args.height);
}

IMesh* createTriangle()
{
    auto mesh = Platform::get()->createMesh();
    mesh->setUsage(IMesh::Usage::StaticDraw);
    mesh->vertices() = { {-1, -1, 0}, {1, -1, 0},{0, 1, 0} };
    mesh->normals() = { {0, 0, 1}, {0, 0, 1}, {0, 0, 1} };
    mesh->uvs() = { {0, 0}, {0.5f, 0.5f}, {1, 0} };
    mesh->indices() = { 0, 1, 2 };
    mesh->updateBuffers();
    return mesh;
}

IShaderProgram* createShaderProgram()
{
    auto vertex = Platform::get()->createShader(IShader::Type::VERTEX,
	    "#version 330 core\n"
	    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
	    "void main(){\n"
		"gl_Position.xyz = vertexPosition_modelspace;\n"
		"gl_Position.w = 1.0;\n"
	    "}");
    auto fragment = Platform::get()->createShader(IShader::Type::FRAGMENT,
	    "#version 330 core\n"
	    "out vec3 color;\n"
	    "void main(){\n"
		"color = vec3(1,0,0);\n"
	    "}");
    vertex->compile();
    fragment->compile();
    auto sp = Platform::get()->createShaderProgram();
    sp->attach(vertex);
    sp->attach(fragment);
    sp->link();
    delete vertex;
    delete fragment;
    return sp;
}

int main()
{
    cout << "Initing..." << endl;
    Platform::init<OpenGL33>();
    cout << "Creating a window..." << endl;
    pWnd = Platform::get()->createWindow("GraphicsTest", 720, 480, false, 0);
    cout << "Adding resize handler..." << endl;
    pWnd->addFramebufferResizeCallback(resizeHandler);
    cout << "Creating mesh..." << endl;
    pMesh = createTriangle();
    cout << "Creating shader..." << endl;
    pSP = createShaderProgram();
    cout << "Showing window..." << endl;
    pWnd->show();
    while(pWnd->isOpen())
    {
	pWnd->waitEvents();
	pWnd->getRenderContext().clear(IRenderContext::COLOR);
	pSP->use();
	pWnd->getRenderContext().drawMesh(pMesh);
	pWnd->swapBuffer();
    }
    pWnd->close();
    delete pMesh;
    delete pSP;
    delete pWnd;
    cout << "Destroying platform..." << endl;
    Platform::destroy();
    cout << "Finished!" << endl;
}

