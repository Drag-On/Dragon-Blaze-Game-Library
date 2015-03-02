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
#include <list>
#include <random>
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

std::default_random_engine random;

class Camera : public ICameraEntity
{
public:
	Mat4f m_view;
	Mat4f m_projection;
	Vec3f m_pos, m_dir, m_up;
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
	virtual Vec3f const& getPosition()
	{
		return m_pos;
	}
	virtual Vec3f const& getDirection()
	{
		return m_dir;
	}
	virtual Vec3f const& getUp()
	{
		return m_up;
	}
	virtual float getNear()
	{
		return 1;
	}
	virtual float getFar()
	{
		return 100;
	}
	virtual float getFieldOfView()
	{
		return pi_4();
	}
	virtual float getRatio()
	{
		return float(pWnd->getFrameWidth()) / pWnd->getFrameHeight();
	}
	void update()
	{
		m_dir = /*m_orientation * */Vec3f{0, 0, -1};
		m_up = Vec3f{0, 1, 0};
		m_view = Mat4f::makeView(m_pos, m_dir, m_up);
		m_projection = Mat4f::makeProjection(getFieldOfView(), getRatio(), getNear(), getFar());
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
	float m_radius;
	Entity(IMesh* mesh, IShaderProgram* shaderProgram, ITexture* tex, bool translucent, int materialID, float radius)
	{
		m_pMesh = mesh;
		m_pShaderProgram = shaderProgram;
		m_pTexture = tex;
		m_translucent = translucent;
		m_materialID = materialID;
		m_radius = radius;
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
	virtual float getBoundingSphere()
	{
		return m_radius;
	}
	void update()
	{
		m_modelMat = Mat4f::makeTranslation(m_pos) * m_orientation;
	}
};

std::list<Entity> entities;

/**
 * @brief Resizes the render context with the window
 * @param args
 */
void resizeHandler(IWindow::FramebufferResizeEventArgs const& args)
{
	pWnd->getRenderContext().viewport(0, 0, args.width, args.height);
}

void inputHandler(IWindow::InputEventArgs const& args)
{
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

void addRandomEntities(unsigned int amount)
{
	std::uniform_real_distribution<float> dist(-10, 10);
	auto randFloat = std::bind(dist, random);
	for(unsigned int i = 0; i < amount; i++)
	{
		entities.emplace_back(pSphere, pShaderProgram, pTex, false, 0, 1);
		auto last = entities.rbegin();
		last->m_pos = Vec3f{randFloat(), randFloat(), randFloat()};
		pRenderer->addEntity(&(*last));
	}
}

void update()
{
	cam.update();
	for(auto& e : entities)
		e.update();

	auto& input = pWnd->getInput();
	// Move first entity
	auto e = entities.begin();
	if (input.isDown(Input::Key::KEY_W))
		e->m_pos.z() -= 1.5f * pRenderer->getDeltaTime();
	if (input.isDown(Input::Key::KEY_A))
		e->m_pos.x() -= 1.5f * pRenderer->getDeltaTime();
	if (input.isDown(Input::Key::KEY_S))
		e->m_pos.z() += 1.5f * pRenderer->getDeltaTime();
	if (input.isDown(Input::Key::KEY_D))
		e->m_pos.x() += 1.5f * pRenderer->getDeltaTime();
}

int main()
{
	cout << "Initing..." << endl;
	Platform::init<OpenGL33>();
	cout << "Creating a window..." << endl;
	pWnd = Platform::get()->createWindow("Renderer", 720, 480, false, 4);
	pWnd->addFramebufferResizeCallback(resizeHandler);
	pWnd->addInputCallback(inputHandler);
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
	pRenderer = new ForwardRenderer{false};
	pRenderer->setCameraEntity(&cam);
	addRandomEntities(50);
	cout << "Showing window..." << endl;
	pWnd->show();
	while (pWnd->isOpen())
	{
		pWnd->pollEvents();
		update();
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

