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
#include "DBGL/Platform/Platform.h"
#include "DBGL/Platform/Implementation/OpenGL33.h"
#include "DBGL/Core/Math/Matrix4x4.h"
#include "DBGL/Core/Math/Vector4.h"
#include "DBGL/Core/Math/Quaternion.h"
#include "DBGL/Resources/Mesh/MeshUtility.h"
#include "DBGL/Resources/Texture/TextureUtility.h"
#include "DBGL/Resources/Sprite/BitmapFont.h"
#include "DBGL/Renderer/ForwardRenderer/ForwardRenderer.h"

using namespace std;
using namespace dbgl;

IRenderer* pRenderer = nullptr;
ITimer* pTimer = nullptr;
IWindow* pWnd = nullptr;
IMesh* pSphere = nullptr;
IShaderProgram* pShaderProgram = nullptr;
IShaderProgram* pShaderProgramSprite = nullptr;
ITexture* pTex = nullptr;
BitmapFont* pFont = nullptr;

class Camera : public ICameraEntity
{
public:
	Mat4f m_view;
	Mat4f m_projection;
	Vec3f m_pos;
	QuatF m_orientation;
	Camera(Vec3f pos, QuatF orient) : m_pos(pos), m_orientation(orient)
	{
	}
	virtual Mat4f const& getViewMatrix()
	{
		return m_view;
	}
	virtual Mat4f const& getProjectionMatrix()
	{
		return m_projection;
	}
	void update()
	{
		auto dir = /*m_orientation * */Vec3f{0, 0, -1};
		auto up = Vec3f{0, 1, 0};
		m_view = Mat4f::makeView(m_pos, dir, up);
		m_projection = Mat4f::makeProjection(pi_4(), float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(), 0.01, 100);
	}
};

Camera cam{Vec3f { 0.0, 0.0, 5.0 }, QuatF {Vec3f { 0, 0, 1 }, Vec3f { 0, 0, -1 }}};

class Entity : public IRenderEntity
{
public:
	IMesh* m_pMesh;
	IShaderProgram* m_pShaderProgram;
	ITexture* m_pTexture;
	bool m_translucent = false;
	int m_materialID;
	Vec3f m_pos;
	QuatF m_orientation;
	Mat4f m_modelMat;
	Entity(IMesh* mesh, IShaderProgram* shaderProgram, ITexture* tex, bool translucent, int materialID)
	{
		m_pMesh = mesh;
		m_pShaderProgram = shaderProgram;
		m_pTexture = tex;
		m_translucent = translucent;
		m_materialID = materialID;
	}
	virtual bool isTranslucent()
	{
		return m_translucent;
	}
	virtual void setupUnique()
	{
		// Use shader
		m_pShaderProgram->use();

		// Compute matrices
		auto MVP = cam.m_projection * cam.m_view * m_modelMat;
		auto ITMV = (cam.m_view * m_modelMat).getInverted().transpose();

		// Get uniform handles
		auto handle_MVP = m_pShaderProgram->getUniformHandle("MVP");
		auto handle_ITMV = m_pShaderProgram->getUniformHandle("ITMV");

		// Set uniform values
		Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_MVP, 1, false, MVP.getDataPointer());
		Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_ITMV, 1, false, ITMV.getDataPointer());
	}
	virtual void setupMaterial()
	{
		// Use shader
		m_pShaderProgram->use();

		// Bind textures
		Platform::get()->curTexture()->activateUnit(0);
		m_pTexture->bind();

		// Get uniform handles
		auto handle_texDiff = m_pShaderProgram->getUniformHandle("tex_diffuse");

		// Set uniform values
		Platform::get()->curShaderProgram()->setUniformSampler(handle_texDiff, 0);
	}
	virtual int getMaterialId()
	{
		return m_materialID;
	}
	virtual Mat4f const& getModelMatrix()
	{
		return m_modelMat;
	}
	virtual IMesh* getMesh()
	{
		return m_pMesh;
	}
	void update()
	{
		m_modelMat = Mat4f::makeTranslation(m_pos) * m_orientation;
	}
};

/**
 * @brief Resizes the render context with the window
 * @param args
 */
void resizeHandler(IWindow::FramebufferResizeEventArgs const& args)
{
	pWnd->getRenderContext().viewport(0, 0, args.width, args.height);
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

void update()
{
	cam.update();
}

int main()
{
	cout << "Initing..." << endl;
	Platform::init<OpenGL33>();
	cout << "Creating a window..." << endl;
	pWnd = Platform::get()->createWindow("Renderer", 720, 480, false, 4);
	pWnd->addFramebufferResizeCallback(resizeHandler);
	pTimer = Platform::get()->createTimer();
	cout << "Setting rendering properties..." << endl;
	pWnd->getRenderContext().setDepthTest(IRenderContext::DepthTestValue::Less);
	pWnd->getRenderContext().setFaceCulling(IRenderContext::FaceCullingValue::Back);
	cout << "Initializing default meshes, textures and shader..." << endl;
	pSphere = MeshUtility::createIcoSphere(4, true, IMesh::Usage::StaticDraw);
	pShaderProgram = loadShader("Assets/Shaders/CamLight.vert", "Assets/Shaders/CamLight.frag");
	pShaderProgramSprite = loadShader("Assets/Shaders/Sprite.vert", "Assets/Shaders/Sprite.frag");
	pFont = new BitmapFont{};
	unsigned char whiteVal[] = { 255, 255, 255, 255 };
	pTex = TextureUtility::createTexture(TextureUtility::ImageData(&whiteVal[0], 1, 1));
	pTex->bind();
	Platform::get()->curTexture()->generateMipMaps();
	cout << "Initializing renderer..." << endl;
	pRenderer = new ForwardRenderer{true};
	pRenderer->setCameraEntity(&cam);
	Entity e1{pSphere, pShaderProgram, pTex, false, 0};
	pRenderer->addEntity(&e1);
	Entity e2{pSphere, pShaderProgram, pTex, false, 1};
	e2.m_pos = Vec3f{-1.0f, 0.0f, -2.0f};
	pRenderer->addEntity(&e2);
	cout << "Showing window..." << endl;
	pWnd->show();
	while (pWnd->isOpen())
	{
		pWnd->pollEvents();
		update();
		e1.update();
		e2.update();
		pRenderer->render(&pWnd->getRenderContext());
		pFont->drawText(&pWnd->getRenderContext(), pShaderProgramSprite, std::to_string(pRenderer->getFPS()), 10, pWnd->getFrameHeight() - pFont->getLineHeight() - 10);
		pWnd->swapBuffer();
	}
	delete pSphere;
	delete pShaderProgram;
	delete pShaderProgramSprite;
	delete pTex;
	delete pFont;
	delete pTimer;
	cout << "Destroying platform..." << endl;
	Platform::destroy();
}

