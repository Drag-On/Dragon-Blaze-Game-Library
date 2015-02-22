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
#include <sstream>
#include <streambuf>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
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

bool initialized = false;
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
Vec3f lightAmbientColor { 1, 1, 1 };
float lightAmbientIntensity = 0.1f;
Vec3f matSpecColor { 1, 1, 1 };
float matSpecWidth = 3;

double delta = 1;
float moveSpeed = 10.0f;
QuatF meshRotation;

TextureIO textureIO {};
MeshIO meshIO {};

struct loadTexture
{
	std::string file;
	Vec4i color;
	ITexture** ppTarget = nullptr;
} loadTexture;
std::mutex loadTextureMutex;

struct loadMesh
{
	std::string file;
	unsigned int baseMeshType = 0;
	IMesh** ppTarget = nullptr;
} loadMesh;
std::mutex loadMeshMutex;

std::string screenshotFile;
std::mutex screenShotMutex;

/**
 * @brief Resizes the render context with the window
 * @param args
 */
void resizeHandler(IWindow::FramebufferResizeEventArgs const& args)
{
	pWnd->getRenderContext().viewport(0, 0, args.width, args.height);
	matProj = Mat4f::makeProjection(pi_4(), float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(), 0.01, 100);
}

void inputHandler(IWindow::InputEventArgs const& args)
{
	auto& input = pWnd->getInput();

	// Close on escape
	if(args.key == Input::Key::KEY_ESCAPE && args.action == Input::KeyState::PRESSED)
		pWnd->close();

	// Modify lights
	// Ambient intensity
	if(args.key == Input::Key::KEY_KP_ADD && args.action == Input::KeyState::PRESSED && args.input.isDown(Input::Modifier::KEY_CONTROL))
		lightAmbientIntensity += 0.01f;
	else if(args.key == Input::Key::KEY_KP_SUBTRACT && args.action == Input::KeyState::PRESSED && args.input.isDown(Input::Modifier::KEY_CONTROL))
		lightAmbientIntensity -= 0.01f;
	// Specular exponent
	else if(args.key == Input::Key::KEY_KP_ADD && args.action == Input::KeyState::PRESSED && args.input.isDown(Input::Modifier::KEY_ALT))
		matSpecWidth += 0.5f;
	else if(args.key == Input::Key::KEY_KP_SUBTRACT && args.action == Input::KeyState::PRESSED && args.input.isDown(Input::Modifier::KEY_ALT))
		matSpecWidth -= 0.5f;
	// Light intensity
	else if(args.key == Input::Key::KEY_KP_ADD && args.action == Input::KeyState::PRESSED)
		lightIntensity += 1.0f;
	else if(args.key == Input::Key::KEY_KP_SUBTRACT && args.action == Input::KeyState::PRESSED)
		lightIntensity -= 1.0f;

	if(lightIntensity < 0)
		lightIntensity = 0;
	if (matSpecWidth < 1)
		matSpecWidth = 1;
	if(lightAmbientIntensity < 0)
		lightAmbientIntensity = 0;

	// Draw mode
	if(args.key == Input::Key::KEY_ENTER && args.action == Input::KeyState::PRESSED)
	{
		switch(pWnd->getRenderContext().getDrawMode())
		{
		case IRenderContext::DrawMode::Fill:
			pWnd->getRenderContext().setDrawMode(IRenderContext::DrawMode::Line);
			break;
		case IRenderContext::DrawMode::Line:
			pWnd->getRenderContext().setDrawMode(IRenderContext::DrawMode::Point);
			break;
		case IRenderContext::DrawMode::Point:
			pWnd->getRenderContext().setDrawMode(IRenderContext::DrawMode::Fill);
			break;
		}
	}
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
	auto& input = pWnd->getInput();
	// Move light
	if (input.isDown(Input::Key::KEY_W))
		lightPos = QuatF{Vec3f{static_cast<float>(-moveSpeed * delta), 0, 0}} * lightPos;
	if (input.isDown(Input::Key::KEY_A))
		lightPos = QuatF{Vec3f{0, static_cast<float>(-moveSpeed * delta), 0}} * lightPos;
	if (input.isDown(Input::Key::KEY_S))
		lightPos = QuatF{Vec3f{static_cast<float>(moveSpeed * delta), 0, 0}} * lightPos;
	if (input.isDown(Input::Key::KEY_D))
		lightPos = QuatF{Vec3f{0, static_cast<float>(moveSpeed * delta), 0}} * lightPos;

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
	Platform::get()->curShaderProgram()->setUniformFloat3(handle_lightAmbient, (lightAmbientIntensity * lightAmbientColor).getDataPointer());
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

void checkLoad()
{
	// Check if there is a texture that needs to be loaded
	loadTextureMutex.lock();
	if(loadTexture.ppTarget != nullptr)
	{
		if(loadTexture.file.size() > 0)
		{
			auto tex = textureIO.load(loadTexture.file);
			if(tex != nullptr)
			{
				delete *(loadTexture.ppTarget);
				*(loadTexture.ppTarget) = tex;
				(*(loadTexture.ppTarget))->bind();
				Platform::get()->curTexture()->generateMipMaps();
			}
		}
		else
		{
			unsigned char color[4] = {static_cast<unsigned char>(loadTexture.color[0]), static_cast<unsigned char>(loadTexture.color[1]), static_cast<unsigned char>(loadTexture.color[2]), static_cast<unsigned char>(loadTexture.color[3])};
			delete *(loadTexture.ppTarget);
			*(loadTexture.ppTarget) = TextureUtility::createTexture(TextureUtility::ImageData(&color[0], 1, 1));
			(*(loadTexture.ppTarget))->bind();
			Platform::get()->curTexture()->generateMipMaps();
		}
		loadTexture.ppTarget = nullptr;
	}
	loadTextureMutex.unlock();

	// Check if there is a mesh that needs to be loaded
	loadMeshMutex.lock();
	if(loadMesh.ppTarget != nullptr)
	{
		if(loadMesh.file.size() > 0)
		{
			auto mesh = meshIO.load(loadMesh.file);
			if (mesh != nullptr)
			{
				delete *(loadMesh.ppTarget);
				*(loadMesh.ppTarget) = mesh;
				MeshUtility::generateTangentBase(*(loadMesh.ppTarget));
				(*(loadMesh.ppTarget))->updateBuffers();
			}
		}
		else
		{
			switch (loadMesh.baseMeshType)
			{
			case 0:
				delete *(loadMesh.ppTarget);
				*(loadMesh.ppTarget) = MeshUtility::createIcoSphere(3, false);
				break;
			case 1:
				delete *(loadMesh.ppTarget);
				*(loadMesh.ppTarget) = MeshUtility::createCube(false);
				break;
			case 2:
				delete *(loadMesh.ppTarget);
				*(loadMesh.ppTarget) = MeshUtility::createIcosahedron(false);
				break;
			case 3:
				delete *(loadMesh.ppTarget);
				*(loadMesh.ppTarget) = MeshUtility::createRectangle(false);
				break;
			case 4:
				delete *(loadMesh.ppTarget);
				*(loadMesh.ppTarget) = MeshUtility::createPyramid(false);
				break;
			default:
				loadMeshMutex.unlock();
				return;
			}
			MeshUtility::generateTangentBase(*(loadMesh.ppTarget));
			(*(loadMesh.ppTarget))->updateBuffers();
		}
		loadMesh.ppTarget = nullptr;
	}
	loadMeshMutex.unlock();

	// Check if we need to take a snapshot
	screenShotMutex.lock();
	if(screenshotFile.size() != 0)
	{
		const unsigned int bufSize = pWnd->getFrameWidth() * pWnd->getFrameHeight() * 4;
		char* buffer = new char[bufSize];
		pWnd->getRenderContext().readPixels(0, 0, pWnd->getFrameWidth(), pWnd->getFrameHeight(), ITextureCommands::PixelFormat::RGBA, ITextureCommands::PixelType::UBYTE, bufSize, buffer);
		auto img = TextureUtility::ImageData{reinterpret_cast<unsigned char*>(buffer), static_cast<unsigned int>(pWnd->getFrameWidth()), static_cast<unsigned int>(pWnd->getFrameHeight())};
		auto tex = TextureUtility::createTexture(img);
		textureIO.write(tex, screenshotFile);
		delete tex;
		delete[] buffer;
		screenshotFile.clear();
	}
	screenShotMutex.unlock();
}

void runGraphics()
{
	cout << "> Initing..." << endl;
	Platform::init<OpenGL33>();
	cout << "> Creating a window..." << endl;
	pWnd = Platform::get()->createWindow("Model Viewer", 720, 480, false, 4);
	cout << "> Setting rendering properties..." << endl;
	pWnd->getRenderContext().setDepthTest(IRenderContext::DepthTestValue::Less);
	pWnd->getRenderContext().setFaceCulling(IRenderContext::FaceCullingValue::Back);
	cout << "> Creating timer..." << endl;
	pTimer = Platform::get()->createTimer();
	cout << "> Adding handlers..." << endl;
	pWnd->addFramebufferResizeCallback(resizeHandler);
	pWnd->addInputCallback(inputHandler);
	cout << "> Loading plugins..." << endl;
	textureIO.addFormat("plugins/Texture/BMP/libDBGL_BMP." + Library::getFileExtension());
	textureIO.addFormat("plugins/Texture/TGA/libDBGL_TGA." + Library::getFileExtension());
	textureIO.addFormat("plugins/Texture/DDS/libDBGL_DDS." + Library::getFileExtension());
	meshIO.addFormat("plugins/Mesh/OBJ/libDBGL_OBJ." + Library::getFileExtension());
	cout << "> Loading default mesh..." << endl;
	pMesh = MeshUtility::createIcoSphere(3, false);
	MeshUtility::generateTangentBase(pMesh);
	pMesh->updateBuffers();
	cout << "> Loading default textures..." << endl;
	unsigned char whiteVal[] = { 255, 255, 255, 255 };
	pTexDiff = TextureUtility::createTexture(TextureUtility::ImageData(&whiteVal[0], 1, 1));
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
	cout << "> Loading default shader..." << endl;
	pSP = loadShader("DiffSpecNorm.vert", "DiffSpecNorm.frag");
	cout << "> Showing window..." << endl;
	pWnd->show();
	initialized = true;
	while (pWnd->isOpen())
	{
		delta = pTimer->getDelta();
		pWnd->pollEvents();
		pWnd->getRenderContext().clear(IRenderContext::COLOR | IRenderContext::DEPTH);
		update();
		render();
		checkLoad();
		pWnd->swapBuffer();
	}
	delete pMesh;
	pMesh = nullptr;
	delete pTexDiff;
	pTexDiff = nullptr;
	delete pTexSpec;
	pTexSpec = nullptr;
	delete pTexNorm;
	pTexNorm = nullptr;
	delete pSP;
	pSP = nullptr;
	delete pWnd;
	pWnd = nullptr;
	cout << "Destroying platform..." << endl << "> ";
	std::flush(cout);
	Platform::destroy();
}

/**
 * @brief Splits a string
 * @param s String to split
 * @param delim Delimiter
 * @param container Container to add tokens to
 */
void tokenize(std::string const& s, char delim, std::vector<std::string>& container)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
		container.push_back(item);
}

/**
 * @brief Interprets input from the command line
 * @param command Input line
 * @return True in case the command was valid, otherwise false
 */
bool interpretCommand(std::string const& command)
{
	if(command == "help")
	{
		cout << R"str(::Console commands:)str" << endl;
		cout << R"str(:: "help" for help.)str" << endl;
		cout << R"str(:: "exit" to quit the program.)str" << endl;
		cout << R"str(:: "screenshot <filename>" to save a screenshot.)str" << endl;
		cout << R"str(:: "set tex diffuse <filename>" to load a diffuse texture map.)str" << endl;
		cout << R"str(:: "set tex diffuse color <red>,<green>,<blue>,<alpha>" to use a color as a diffuse texture map.)str" << endl;
		cout << R"str(:: "set tex specular <filename>" to load a specular texture map.)str" << endl;
		cout << R"str(:: "set tex specular color <red>,<green>,<blue>,<alpha>" to use a color as a specular texture map.)str" << endl;
		cout << R"str(:: "set tex normal <filename>" to load a normal texture map.)str" << endl;
		cout << R"str(:: "set tex normal color <red>,<green>,<blue>,<alpha>" to use a color as a normal texture map.)str" << endl;
		cout << R"str(:: "set mesh <filename>" to load a mesh.)str" << endl;
		cout << R"str(:: "set mesh sphere" to use a sphere as a mesh.)str" << endl;
		cout << R"str(:: "set mesh cube" to use a cube as a mesh.)str" << endl;
		cout << R"str(:: "set mesh icosahedron" to use an icosahedron as a mesh.)str" << endl;
		cout << R"str(:: "set mesh plane" to use a plane as a mesh.)str" << endl;
		cout << R"str(:: "set mesh pyramid" to use a pyramid as a mesh.)str" << endl;
		cout << R"str(:: "set light intensity <value>" to modify light intensity.)str" << endl;
		cout << R"str(:: "set light color <red>,<green>,<blue>" to modify light color.)str" << endl;
		cout << R"str(:: "set ambient intensity <value>" to modify ambient light intensity.)str" << endl;
		cout << R"str(:: "set ambient color <red>,<green>,<blue>" to modify ambient light color.)str" << endl;
		cout << R"str(:: "set specular exponent <value>" to modify specular exponent.)str" << endl;
		cout << R"str(:: "set specular color <red>,<green>,<blue>" to modify specular color.)str" << endl;
		cout << R"str(::Viewer commands:)str" << endl;
		cout << R"str(:: [W][A][S][D] to move light.)str" << endl;
		cout << R"str(:: [UP][LEFT][DOWN][RIGHT] to rotate mesh.)str" << endl;
		cout << R"str(:: [+][-] to modify light intensity.)str" << endl;
		cout << R"str(:: [CTRL] + [+][-] to modify ambient light intensity.)str" << endl;
		cout << R"str(:: [ALT] + [+][-] to modify specular exponent.)str" << endl;
		cout << R"str(:: [ENTER] to switch between draw modes.)str" << endl;
		return true;
	}
	else if(command == "exit")
		return true;
	else
	{
		auto readColor = [](std::string const& token, int r = 255, int g = 255, int b = 255, int a = 255)
		{
			std::vector<std::string> colors;
			tokenize(token, ',', colors);
			Vec4i color{r, g, b, a};
			if(colors.size() >= 3)
			{
				color[0] = dbgl::clamp(stoi(colors[0]), 0, 255);
				color[1] = dbgl::clamp(stoi(colors[1]), 0, 255);
				color[2] = dbgl::clamp(stoi(colors[2]), 0, 255);
			}
			if(colors.size() >= 4)
				color[3] = dbgl::clamp(stoi(colors[3]), 0, 255);
			return color;
		};

		std::vector<std::string> tokens;
		tokenize(command, ' ', tokens);
		if(tokens.size() == 2 && tokens[0] == "screenshot")
		{
			screenShotMutex.lock();
			screenshotFile = tokens[1];
			screenShotMutex.unlock();
			return true;
		}
		else if(tokens.size() >= 4)
		{
			if(tokens[0] == "set" && tokens[1] == "light")
			{
				if(tokens[2] == "intensity")
					lightIntensity = stof(tokens[3]);
				if(tokens[2] == "color")
				{
					auto color = readColor(tokens[3]);
					lightColor = Vec3f{color[0]/255.0f, color[1]/255.0f, color[2]/255.0f};
				}
				if(lightIntensity < 0)
					lightIntensity = 0;
				return true;
			}
			else if(tokens[0] == "set" && tokens[1] == "ambient")
			{
				if(tokens[2] == "intensity")
					lightAmbientIntensity = stof(tokens[3]);
				if(tokens[2] == "color")
				{
					auto color = readColor(tokens[3]);
					lightAmbientColor = Vec3f{color[0]/255.0f, color[1]/255.0f, color[2]/255.0f};
				}
				if(lightAmbientIntensity < 0)
					lightAmbientIntensity = 0;
				return true;
			}
			else if(tokens[0] == "set" && tokens[1] == "specular")
			{
				if(tokens[2] == "exponent")
					matSpecWidth = stof(tokens[3]);
				if(tokens[2] == "color")
				{
					auto color = readColor(tokens[3]);
					matSpecColor = Vec3f{color[0]/255.0f, color[1]/255.0f, color[2]/255.0f};
				}
				if(matSpecWidth < 1)
					matSpecWidth = 1;
				return true;
			}
			else if(tokens[0] == "set" && tokens[1] == "tex")
			{
				if(tokens[2] == "diffuse")
				{
					if(tokens.size() == 4)
					{
						loadTextureMutex.lock();
						loadTexture.file = tokens[3];
						loadTexture.ppTarget = &pTexDiff;
						loadTextureMutex.unlock();
						return true;
					}
					else if (tokens.size() == 5 && tokens[3] == "color")
					{
						loadTextureMutex.lock();
						loadTexture.file = "";
						loadTexture.color = readColor(tokens[4]);
						loadTexture.ppTarget = &pTexDiff;
						loadTextureMutex.unlock();
						return true;
					}
				}
				else if(tokens[2] == "specular")
				{
					if(tokens.size() == 4)
					{
						loadTextureMutex.lock();
						loadTexture.file = tokens[3];
						loadTexture.ppTarget = &pTexSpec;
						loadTextureMutex.unlock();
						return true;
					}
					else if (tokens.size() == 5 && tokens[3] == "color")
					{
						loadTextureMutex.lock();
						loadTexture.file = "";
						loadTexture.color = readColor(tokens[4]);
						loadTexture.ppTarget = &pTexSpec;
						loadTextureMutex.unlock();
						return true;
					}
				}
				if(tokens[2] == "normal")
				{
					if(tokens.size() == 4)
					{
						loadTextureMutex.lock();
						loadTexture.file = tokens[3];
						loadTexture.ppTarget = &pTexNorm;
						loadTextureMutex.unlock();
						return true;
					}
					else if (tokens.size() == 5 && tokens[3] == "color")
					{
						loadTextureMutex.lock();
						loadTexture.file = "";
						loadTexture.color = readColor(tokens[4], 255/2, 255/2);
						loadTexture.ppTarget = &pTexNorm;
						loadTextureMutex.unlock();
						return true;
					}
				}
			}
		}
		else if(tokens.size() == 3)
		{
			if(tokens[0] == "set" && tokens[1] == "mesh")
			{
				if(tokens[2] == "sphere")
				{
					loadMeshMutex.lock();
					loadMesh.file = "";
					loadMesh.baseMeshType = 0;
					loadMesh.ppTarget = &pMesh;
					loadMeshMutex.unlock();
					return true;
				}
				else if(tokens[2] == "cube")
				{
					loadMeshMutex.lock();
					loadMesh.file = "";
					loadMesh.baseMeshType = 1;
					loadMesh.ppTarget = &pMesh;
					loadMeshMutex.unlock();
					return true;
				}
				else if(tokens[2] == "icosahedron")
				{
					loadMeshMutex.lock();
					loadMesh.file = "";
					loadMesh.baseMeshType = 2;
					loadMesh.ppTarget = &pMesh;
					loadMeshMutex.unlock();
					return true;
				}
				else if(tokens[2] == "plane")
				{
					loadMeshMutex.lock();
					loadMesh.file = "";
					loadMesh.baseMeshType = 3;
					loadMesh.ppTarget = &pMesh;
					loadMeshMutex.unlock();
					return true;
				}
				else if(tokens[2] == "pyramid")
				{
					loadMeshMutex.lock();
					loadMesh.file = "";
					loadMesh.baseMeshType = 4;
					loadMesh.ppTarget = &pMesh;
					loadMeshMutex.unlock();
					return true;
				}
				else
				{
					loadMeshMutex.lock();
					loadMesh.file = tokens[2];
					loadMesh.ppTarget = &pMesh;
					loadMeshMutex.unlock();
					return true;
				}
			}
		}
	}
	return false;
}

/**
 * @brief Main application entry point
 * @return
 */
int main(/* int argc, const char* argv[] */)
{
	std::thread threadGraphics(runGraphics);
	while(!initialized)
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	std::string input;
	while(input != "exit")
	{
		input.clear();
		cout << "> ";
		getline(cin, input);
		if(!interpretCommand(input))
			cout << ":: Unknown command. Try \"help\"." << endl;
	}
	if (pWnd != nullptr)
		pWnd->close();
	threadGraphics.join();
	cout << "> Finished!" << endl;
	return 0;
}

