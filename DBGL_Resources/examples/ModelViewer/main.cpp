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
#include <fstream>
#include <streambuf>
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"
#include "DBGL/Core/Math/Matrix4x4.h"
#include "DBGL/Core/Math/Vector3.h"
#include "DBGL/Core/Math/Quaternion.h"
#include "DBGL/Core/Math/Utility.h"
#include "DBGL/Resources/Mesh/MeshUtility.h"
#include "DBGL/Resources/Mesh/MeshIO.h"
#include "DBGL/Resources/Texture/TextureUtility.h"
#include "DBGL/Resources/Texture/TextureIO.h"
#include "DBGL/Resources/Color/Color.h"

using namespace dbgl;
using namespace std;

IWindow* pWnd = nullptr;
ITimer* pTimer = nullptr;
IMesh* pMesh = nullptr;
ITexture* pTexDiff = nullptr;
ITexture* pTexSpec = nullptr;
ITexture* pTexNorm = nullptr;
IShaderProgram* pSP = nullptr;

Mat4f matModel, matProj;
Mat4f matView = Mat4f::makeView(Vec3f { 0.0, 0.0, 5.0 }, Vec3f { 0, 0, -1 }, Vec3f { 0, 1, 0 });

Vec3f lightPos { 5, 4, 2 };
Vec3f lightColor { 1, 1, 1 };
float lightIntensity = 15.0f;
Vec3f lightAmbient { 0.1f, 0.1f, 0.1f };
Vec3f matSpecColor { 1, 1, 1 };
float matSpecWidth = 3;

double delta = 1;
float moveSpeed = 50.0f;
QuatF meshRotation;

TextureIO textureIO {};
MeshIO meshIO {};

/**
 * @brief Resizes the render context with the window
 * @param args
 */
void resizeHandler(IWindow::FramebufferResizeEventArgs const& args)
{
	pWnd->getRenderContext().viewport(0, 0, args.width, args.height);
	matProj = Mat4f::makeProjection(pi_4(), float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(), 0.01, 100);
}

void inputHandler(IWindow::InputEventArgs const& /* args */)
{
	auto& input = pWnd->getInput();
	// Move light
	if (input.isDown(Input::Key::KEY_W))
		lightPos.z() -= moveSpeed * delta;
	if (input.isDown(Input::Key::KEY_A))
		lightPos.x() -= moveSpeed * delta;
	if (input.isDown(Input::Key::KEY_S))
		lightPos.z() += moveSpeed * delta;
	if (input.isDown(Input::Key::KEY_D))
		lightPos.x() += moveSpeed * delta;
	if (input.isDown(Input::Key::KEY_Q))
		lightPos.y() -= moveSpeed * delta;
	if (input.isDown(Input::Key::KEY_E))
		lightPos.y() += moveSpeed * delta;

	// Rotate mesh
	if (input.isDown(Input::Key::KEY_UP))
		meshRotation = meshRotation * QuatF{meshRotation.getInverted() * Vec3f{1, 0, 0}, static_cast<float>(moveSpeed * delta)};
	if (input.isDown(Input::Key::KEY_LEFT))
		meshRotation = meshRotation * QuatF{meshRotation.getInverted() * Vec3f{0, 1, 0}, static_cast<float>(-moveSpeed * delta)};
	if (input.isDown(Input::Key::KEY_DOWN))
		meshRotation = meshRotation * QuatF{meshRotation.getInverted() * Vec3f{1, 0, 0}, static_cast<float>(-moveSpeed * delta)};
	if (input.isDown(Input::Key::KEY_RIGHT))
		meshRotation = meshRotation * QuatF{meshRotation.getInverted() * Vec3f{0, 1, 0}, static_cast<float>(moveSpeed * delta)};
	matModel = meshRotation.getMatrix();
}

/**
 * @brief Loads a shader program
 * @param vertex Vertex shader filename
 * @param fragment Fragment shader filename
 * @return The readily compiled shader program
 */
IShaderProgram* loadShader(string vertex, string fragment)
{
	std::ifstream vertexStream(vertex);
	std::string vertexCode((std::istreambuf_iterator<char>(vertexStream)), std::istreambuf_iterator<char>());
	std::ifstream fragmentStream(fragment);
	std::string fragmentCode((std::istreambuf_iterator<char>(fragmentStream)), std::istreambuf_iterator<char>());

	auto pVShader = Platform::get()->createShader(IShader::Type::VERTEX, vertexCode);
	auto pFShader = Platform::get()->createShader(IShader::Type::FRAGMENT, fragmentCode);
	pVShader->compile();
	pFShader->compile();

	IShaderProgram* pSProg = Platform::get()->createShaderProgram();
	pSProg->attach(pVShader);
	pSProg->attach(pFShader);
	pSProg->link();

	delete pVShader;
	delete pFShader;
	return pSProg;
}

/**
 * @brief Update controls etc.
 */
void update()
{

}

/**
 * @brief Prepares the shader for rendering
 */
void render()
{
	// Use shader
	pSP->use();

	// Compute matrices
	auto MVP = matProj * matView * matModel;
	auto ITM = matModel.getInverted().transpose();
	auto ITV = matView.getInverted().transpose();

	// Bind textures
	Platform::get()->curTexture()->activateUnit(0);
	pTexDiff->bind();
	Platform::get()->curTexture()->activateUnit(1);
	pTexSpec->bind();
	Platform::get()->curTexture()->activateUnit(2);
	pTexNorm->bind();

	// Get uniform handles
	auto handle_M = pSP->getUniformHandle("M");
	auto handle_MVP = pSP->getUniformHandle("MVP");
	auto handle_ITM = pSP->getUniformHandle("ITM");
	auto handle_ITV = pSP->getUniformHandle("ITV");
	auto handle_numLights = pSP->getUniformHandle("i_numLights");
	auto handle_lightPos = pSP->getUniformHandle("lights[0].v3_position_w");
	auto handle_lightColor = pSP->getUniformHandle("lights[0].v3_color");
//	auto handle_lightCutoff = pSP->getUniformHandle("lights[0].f_spotCutoff");
//	auto handle_lightDirection = pSP->getUniformHandle("lights[0].v3_direction_w");
	auto handle_lightAmbient = pSP->getUniformHandle("v3_ambientLight");
	auto handle_matSpecCol = pSP->getUniformHandle("mat.v3_specColor");
	auto handle_matSpecWidth = pSP->getUniformHandle("mat.f_specWidth");
	auto handle_texDiff = pSP->getUniformHandle("tex_diffuse");
	auto handle_texSpec = pSP->getUniformHandle("tex_specular");
	auto handle_texNorm = pSP->getUniformHandle("tex_normal");

	// Set uniform values
	// Matrices
	Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_M, 1, false, matModel.getDataPointer());
	Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_MVP, 1, false, MVP.getDataPointer());
	Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_ITM, 1, false, ITM.getDataPointer());
	Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_ITV, 1, false, ITV.getDataPointer());
	// Light
	Platform::get()->curShaderProgram()->setUniformInt(handle_numLights, 1);
	Platform::get()->curShaderProgram()->setUniformFloat3(handle_lightPos, lightPos.getDataPointer());
	Platform::get()->curShaderProgram()->setUniformFloat3(handle_lightColor, (lightIntensity * lightColor).getDataPointer());
	Platform::get()->curShaderProgram()->setUniformFloat3(handle_lightAmbient, lightAmbient.getDataPointer());
	// Material
	Platform::get()->curShaderProgram()->setUniformFloat3(handle_matSpecCol, matSpecColor.getDataPointer());
	Platform::get()->curShaderProgram()->setUniformFloat(handle_matSpecWidth, matSpecWidth);
	// Textures
	Platform::get()->curShaderProgram()->setUniformSampler(handle_texDiff, 0);
	Platform::get()->curShaderProgram()->setUniformSampler(handle_texSpec, 1);
	Platform::get()->curShaderProgram()->setUniformSampler(handle_texNorm, 2);

	// Render
	pWnd->getRenderContext().drawMesh(pMesh);
}

/**
 * @brief Main application entry point
 * @return
 */
int main()
{
	cout << "Initing..." << endl;
	Platform::init<OpenGL33>();
	cout << "Creating a window..." << endl;
	pWnd = Platform::get()->createWindow("Model Viewer", 720, 480, false, 4);
	cout << "Setting rendering properties..." << endl;
	pWnd->getRenderContext().setDepthTest(IRenderContext::DepthTestValue::Less);
	pWnd->getRenderContext().setFaceCulling(IRenderContext::FaceCullingValue::Back);
	cout << "Creating timer..." << endl;
	pTimer = Platform::get()->createTimer();
	cout << "Adding handlers..." << endl;
	pWnd->addFramebufferResizeCallback(resizeHandler);
	pWnd->addInputCallback(inputHandler);
	cout << "Loading plugins..." << endl;
	textureIO.addFormat("plugins/Texture/BMP/libDBGL_BMP." + Library::getFileExtension());
	textureIO.addFormat("plugins/Texture/TGA/libDBGL_TGA." + Library::getFileExtension());
	textureIO.addFormat("plugins/Texture/DDS/libDBGL_DDS." + Library::getFileExtension());
	meshIO.addFormat("plugins/Mesh/OBJ/libDBGL_OBJ." + Library::getFileExtension());
	cout << "Loading default mesh..." << endl;
	pMesh = MeshUtility::createIcosahedron(false);
	MeshUtility::generateTangentBase(pMesh);
	pMesh->updateBuffers();
	cout << "Loading default textures..." << endl;
	unsigned char whiteVal[] = { 255, 255, 255, 255 };
	pTexDiff = TextureUtility::createTexture(TextureUtility::ImageData(&whiteVal[0], 1, 1));
//	pTexDiff = textureIO.load("test.bmp");
	pTexDiff->bind();
	Platform::get()->curTexture()->generateMipMaps();
	pTexSpec = TextureUtility::createTexture(TextureUtility::ImageData(&whiteVal[0], 1, 1));
	pTexSpec->bind();
	Platform::get()->curTexture()->generateMipMaps();
	whiteVal[0] = 255 / 2;
	whiteVal[1] = 255 / 2;
	whiteVal[2] = 255;
	pTexNorm = TextureUtility::createTexture(TextureUtility::ImageData(&whiteVal[0], 1, 1));
	pTexNorm->bind();
	Platform::get()->curTexture()->generateMipMaps();
	cout << "Loading default shader..." << endl;
	pSP = loadShader("DiffSpecNorm.vert", "DiffSpecNorm.frag");
	cout << "Showing window..." << endl;
	pWnd->show();
	while (pWnd->isOpen())
	{
		delta = pTimer->getDelta();
		pWnd->pollEvents();
		pWnd->getRenderContext().clear(IRenderContext::COLOR | IRenderContext::DEPTH);
		update();
		render();
		pWnd->swapBuffer();
	}
	pWnd->close();
	delete pMesh;
	delete pSP;
	delete pWnd;
	cout << "Destroying platform..." << endl;
	Platform::destroy();
	cout << "Finished!" << endl;
	return 0;
}

