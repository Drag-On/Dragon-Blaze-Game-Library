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
#include "DBGL/Renderer/Scene/Scene.h"
#include "DBGL/Renderer/ForwardRenderer/ForwardRenderer.h"
#include "DBGL/Renderer/Material/IMaterial.h"
#include "DBGL/Renderer/Component/CameraComponent.h"
#include "DBGL/Renderer/Component/RenderComponent.h"
#include "DBGL/Renderer/Component/TransformComponent.h"

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
GameEntity camera;

std::default_random_engine randomizer;

class CustomMaterial : public IMaterial
{
public:
    ~CustomMaterial()
    {
    }

    bool isTranslucent()
    {
        return false;
    }

    void setupUnique(GameEntity const& entity)
    {
        // TODO: Doesn't belong into material!

        // Use shader
        pShaderProgram->use();

        auto cam = camera.getComponent<CameraComponent>();

        // Compute matrices
        auto MVP = cam->getProjectionMatrix() * cam->getViewMatrix() * entity.transformComponent()->modelMat();
        auto ITMV = (cam->getViewMatrix() * entity.transformComponent()->modelMat()).getInverted().transpose();

        // Get uniform handles
        auto handle_MVP = pShaderProgram->getUniformHandle("MVP");
        auto handle_ITMV = pShaderProgram->getUniformHandle("ITMV");

        // Set uniform values
        Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_MVP, 1, false, MVP.getDataPointer());
        Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_ITMV, 1, false, ITMV.getDataPointer());
    }

    void setupMaterial()
    {
        // Use shader
        pShaderProgram->use();

        // Bind textures
        Platform::get()->curTexture()->activateUnit(0);
        pTex->bind();

        // Get uniform handles
        auto handle_texDiff = pShaderProgram->getUniformHandle("tex_diffuse");

        // Set uniform values
        Platform::get()->curShaderProgram()->setUniformSampler(handle_texDiff, 0);
    }

    int getMaterialId()
    {
        return 0;
    }

    void load()
    {
    }

    void unload()
    {
    }
};

CustomMaterial material;

//Camera cam{Vec3f { 0.0, 0.0, 5.0 }, QuatF {Vec3f { 0, 0, 1 }, Vec3f { 0, 0, -1 }}};

//class Entity : public IRenderEntity
//{
//public:
//	IMesh* m_pMesh;
//	IShaderProgram* m_pShaderProgram;
//	ITexture* m_pTexture;
//	bool m_translucent = false;
//	int m_materialID;
//	Vec3f m_pos;
//	float m_scale = 1;
//	QuatF m_orientation;
//	Mat4f m_modelMat;
//	Sphere<float> m_bounds;
//	Entity(IMesh* mesh, IShaderProgram* shaderProgram, ITexture* tex, bool translucent, int materialID, float radius)
//	{
//		m_pMesh = mesh;
//		m_pShaderProgram = shaderProgram;
//		m_pTexture = tex;
//		m_translucent = translucent;
//		m_materialID = materialID;
//		m_bounds.center() = m_pos;
//		m_bounds.radius() = radius;
//	}
//	virtual bool isTranslucent()
//	{
//		return m_translucent;
//	}
//	virtual bool isStatic()
//	{
//		return true;
//	}
//	virtual void setupUnique()
//	{
//		// Use shader
//		m_pShaderProgram->use();
//
//		// Compute matrices
//		auto MVP = cam.m_projection * cam.m_view * m_modelMat;
//		auto ITMV = (cam.m_view * m_modelMat).getInverted().transpose();
//
//		// Get uniform handles
//		auto handle_MVP = m_pShaderProgram->getUniformHandle("MVP");
//		auto handle_ITMV = m_pShaderProgram->getUniformHandle("ITMV");
//
//		// Set uniform values
//		Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_MVP, 1, false, MVP.getDataPointer());
//		Platform::get()->curShaderProgram()->setUniformFloatMatrix4Array(handle_ITMV, 1, false, ITMV.getDataPointer());
//	}
//	virtual void setupMaterial()
//	{
//		// Use shader
//		m_pShaderProgram->use();
//
//		// Bind textures
//		Platform::get()->curTexture()->activateUnit(0);
//		m_pTexture->bind();
//
//		// Get uniform handles
//		auto handle_texDiff = m_pShaderProgram->getUniformHandle("tex_diffuse");
//
//		// Set uniform values
//		Platform::get()->curShaderProgram()->setUniformSampler(handle_texDiff, 0);
//	}
//	virtual int getMaterialId()
//	{
//		return m_materialID;
//	}
//	virtual Vec3f const& getPosition()
//	{
//		return m_pos;
//	}
//	virtual Mat4f const& getModelMatrix()
//	{
//		return m_modelMat;
//	}
//	virtual IMesh* getMesh()
//	{
//		return m_pMesh;
//	}
//	virtual Sphere<float> const& getBoundingSphere()
//	{
//		return m_bounds;
//	}
//	void update()
//	{
//		m_modelMat = Mat4f::makeTranslation(m_pos) * m_orientation * Mat4f::makeScale(m_scale);
//		m_bounds.center() = m_pos;
//		m_bounds.radius() = m_scale;
//	}
//};

//std::list<Entity> entities;

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
    auto& input = pWnd->getInput();

    // Close on escape
    if (args.key == Input::Key::KEY_ESCAPE && args.action == Input::KeyState::PRESSED)
        pWnd->close();
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

void addRandomEntities(Scene* scenegraph, unsigned int amount)
{
    std::uniform_real_distribution<float> dist(-100, 100);
    auto randFloat = std::bind(dist, randomizer);
    std::uniform_real_distribution<float> dist2(1, 10);
    auto randFloat2 = std::bind(dist2, randomizer);
    for (unsigned int i = 0; i < amount; i++)
    {
        GameEntity entity;
        auto scale = randFloat2();
        entity.addComponent<TransformComponent>(Vec3f{randFloat(), randFloat(), randFloat()},
                                                Vec3f{scale, scale, scale});
        entity.addComponent<RenderComponent>(&material, pSphere);
        scenegraph->insert(entity);
//        entities.emplace_back(pSphere, pShaderProgram, pTex, false, 0, 1);
//        auto last = entities.rbegin();
//        last->m_pos = Vec3f{randFloat(), randFloat(), randFloat()};
//        last->m_scale = randFloat2();
//        last->update();
//        pRenderer->addEntity(&(*last));
    }
}

void update(Scene* scenegraph)
{
    camera.update();
//    for (auto& e : entities)
//        e.update();
    scenegraph->traverse();

    auto& input = pWnd->getInput();
    auto cam = camera.getComponent<CameraComponent>();

    // Move camera entity
    float speedup = 1.0f;
    float xRot = 0, yRot = 0;
    if (input.isDown(Input::Key::KEY_SPACE))
        speedup = 5.0f;
    if (input.isDown(Input::Key::KEY_W))
        camera.transformComponent()->position() += cam->getDirection() * 2.5f * pRenderer->getDeltaTime() * speedup;
    if (input.isDown(Input::Key::KEY_S))
        camera.transformComponent()->position() -= cam->getDirection() * 2.5f * pRenderer->getDeltaTime() * speedup;
    if (input.isDown(Input::Key::KEY_A))
        yRot += 0.5f * pRenderer->getDeltaTime() * speedup;
    if (input.isDown(Input::Key::KEY_D))
        yRot -= 0.5f * pRenderer->getDeltaTime() * speedup;
    if (input.isDown(Input::Key::KEY_Q))
        xRot += 0.5f * pRenderer->getDeltaTime() * speedup;
    if (input.isDown(Input::Key::KEY_E))
        xRot -= 0.5f * pRenderer->getDeltaTime() * speedup;
    camera.transformComponent()->rotation() =
            QuatF(cam->getUp().cross(cam->getDirection()), xRot) * QuatF(cam->getUp(), yRot) *
            camera.transformComponent()->rotation();
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
    unsigned char whiteVal[] = {255, 255, 255, 255};
    pTex = TextureUtility::createTexture(TextureUtility::ImageData(&whiteVal[0], 1, 1));
    pTex->bind();
    Platform::get()->curTexture()->generateMipMaps();
    cout << "Initializing renderer..." << endl;
    pRenderer = new ForwardRenderer{false};
    Scene scenegraph{pRenderer};
    camera.addComponent<TransformComponent>(Vec3f {0.0, 0.0, 5.0}, Vec3f {1, 1, 1}, QuatF {Vec3f {0, 0, 1}});
    camera.addComponent<CameraComponent>(camera.transformComponent(), dbgl::pi_4(), 1, 500, pWnd);
    pRenderer->setCameraEntity(camera.getComponent<CameraComponent>());
    unsigned int amountEntities = 500;
    cout << "Adding " << amountEntities << " entities with " << amountEntities * pSphere->getVertexCount() <<
    " vertices and " << amountEntities * pSphere->getIndexCount() / 3 << " triangles." << endl;
    addRandomEntities(&scenegraph, amountEntities);
    cout << "Showing window..." << endl;
    pWnd->show();
    while (pWnd->isOpen())
    {
        pWnd->pollEvents();
        update(&scenegraph);
        pRenderer->render(&pWnd->getRenderContext());
        pFont->drawText(&pWnd->getRenderContext(), pShaderProgramSprite, std::to_string(pRenderer->getFPS()), 10,
                        pWnd->getFrameHeight() - pFont->getLineHeight() - 10);
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
