//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include <functional>
#include <cmath>
#include "DBGL/System/System.h"
#include "DBGL/System/Log/Log.h"
#include "DBGL/System/Bitmask/Bitmask.h"
#include "DBGL/System/ResourceManager/ResourceManager.h"
#include "DBGL/System/ResourceManager/ShaderResource.h"
#include "DBGL/System/ResourceManager/MeshResource.h"
#include "DBGL/System/ResourceManager/TextureResource.h"
#include "DBGL/Window/WindowManager.h"
#include "DBGL/Window/SimpleWindow.h"
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Rendering/ShaderProgram.h"
#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/Rendering/Environment/Camera.h"
#include "DBGL/Math/Vector3.h"
#include "DBGL/Math/Utility.h"
#include "DBGL/Math/Quaternion.h"

using namespace dbgl;

SimpleWindow* pWnd = nullptr;
Camera* pCam = nullptr;
Mat4f view {}, projection {};
Vec3f light1Pos = Vec3f(0, 3, 3), lightColor = Vec3f(1.0f, 0.5f, 0.0f) * 15; // Orange
Vec3f light2Pos = Vec3f(1, 2, 4.5f), light2Color = Vec3f(0.5f, 0.5f, 1.0f) * 25; // Blue-ish
Vec3f light1Offset {}, light2Offset {}; // For movement of light
Vec3f matSpecular = Vec3f(0.1, 0.1, 0.2);
float mouseSpeed = 3.0f, moveSpeed = 2.5f;
float icoAngle = 0;
MeshResource* pMeshIco = nullptr, *pMeshSphere = nullptr, *pMeshPillar = nullptr;
ShaderResource* pShaderDiffSpec = nullptr, *pShaderNorm = nullptr, *pShaderNoLight = nullptr;
TextureResource* pTexBricks = nullptr, *pTexBricksNormal = nullptr, *pTexBricksSpecular = nullptr,
	*pTexMarble = nullptr, *pTexMarbleNormal = nullptr, *pTexMarbleSpecular = nullptr;
Mesh* pMeshPyramid = nullptr, *pMeshBox = nullptr, *pMeshPlane = nullptr;
ShaderProgram* pShaderSprite = nullptr;
Texture* pTexWhite = nullptr;

ResourceManager<ShaderResource> shaderResources {};
ResourceManager<MeshResource> meshResources {};
ResourceManager<TextureResource> textureResources {};

ResourceHandle noLightShaderHandle = InvalidHandle;
ResourceHandle diffSpecNormShaderHandle = InvalidHandle;
ResourceHandle diffSpecShaderHandle = InvalidHandle;
ResourceHandle sphereHandle = InvalidHandle;
ResourceHandle pillarHandle = InvalidHandle;
ResourceHandle icoHandle = InvalidHandle;
ResourceHandle texBricksDiffHandle = InvalidHandle;
ResourceHandle texBricksSpecHandle = InvalidHandle;
ResourceHandle texBricksNormHandle = InvalidHandle;
ResourceHandle texMarbleDiffHandle = InvalidHandle;
ResourceHandle texMarbleSpecHandle = InvalidHandle;
ResourceHandle texMarbleNormHandle = InvalidHandle;

void releaseResources()
{
    // Release any previous resources
    shaderResources.release(noLightShaderHandle);
    shaderResources.release(diffSpecNormShaderHandle);
    shaderResources.release(diffSpecShaderHandle);
    meshResources.release(sphereHandle);
    meshResources.release(pillarHandle);
    meshResources.release(icoHandle);
    textureResources.release(texBricksDiffHandle);
    textureResources.release(texBricksSpecHandle);
    textureResources.release(texBricksNormHandle);
    textureResources.release(texMarbleDiffHandle);
    textureResources.release(texMarbleSpecHandle);
    textureResources.release(texMarbleNormHandle);
}

void requestResources()
{
    // Request resources
    pMeshIco = meshResources.request(icoHandle);
    pMeshSphere = meshResources.request(sphereHandle);
    pMeshPillar = meshResources.request(pillarHandle);
    pShaderDiffSpec = shaderResources.request(diffSpecShaderHandle);
    pShaderNorm = shaderResources.request(diffSpecNormShaderHandle);
    pShaderNoLight = shaderResources.request(noLightShaderHandle);
    pTexBricks = textureResources.request(texBricksDiffHandle);
    pTexBricksNormal = textureResources.request(texBricksNormHandle);
    pTexBricksSpecular = textureResources.request(texBricksSpecHandle);
    pTexMarble = textureResources.request(texMarbleDiffHandle);
    pTexMarbleNormal = textureResources.request(texMarbleNormHandle);
    pTexMarbleSpecular = textureResources.request(texMarbleSpecHandle);
}

void scrollCallback(Window::ScrollEventArgs const& args)
{
    // Zoom
    pCam->setFieldOfView(pCam->getFieldOfView() + 0.1f * args.yOffset);
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	    float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(), pCam->getNear(), pCam->getFar());
}

void framebufferResizeCallback(Window::FramebufferResizeEventArgs const& args)
{
    // Update projection matrix if the windows was rescaled
    projection = Mat4f::makeProjection(pCam->getFieldOfView(), float(args.width) / args.height,
	    pCam->getNear(), pCam->getFar());
}

void updateCallback(Window::UpdateEventArgs const& args)
{
    auto deltaTime = args.deltaTime;

    // Update mouse
    double x = 0, y = 0;
    pWnd->getCursorPos(x, y);
    double horizontal = deltaTime * mouseSpeed * (pWnd->getFrameWidth() / 2.0 - x);
    double vertical = deltaTime * mouseSpeed * (pWnd->getFrameHeight() / 2.0 - y);
    pCam->rotate(horizontal, -vertical);
    // Camera vectors
    Vec3f direction = pCam->rotation() * Vec3f(0, 0, 1);
    Vec3f right = pCam->rotation() * Vec3f(-1, 0, 0);
    // Reset mouse position to center of the screen
    pWnd->setCursorPos(pWnd->getFrameWidth() / 2, pWnd->getFrameHeight() / 2);

    // Update keyboard
    if (pWnd->getKey(Input::Key::KEY_W) == Input::KeyState::DOWN)
	pCam->position() += direction * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_A) == Input::KeyState::DOWN)
	pCam->position() -= right * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_S) == Input::KeyState::DOWN)
	pCam->position() -= direction * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_D) == Input::KeyState::DOWN)
	pCam->position() += right * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_E) == Input::KeyState::DOWN)
	pCam->position() += Vec3f(0, 1, 0) * deltaTime * moveSpeed;
    if (pWnd->getKey(Input::Key::KEY_Q) == Input::KeyState::DOWN)
	pCam->position() -= Vec3f(0, 1, 0) * deltaTime * moveSpeed;

    if(args.input.isReleased(Input::KEY_R))
    {
	releaseResources();
	if (args.input.isDown(Input::KEY_LEFT_CONTROL))
	{
	    LOG.debug("Deleting all resources from memory. Loading fresh from hard disk.");
	    // Make sure the resources are deleted from memory
	    while (shaderResources.needLoad())
		shaderResources.loadNext();
	    while (meshResources.needLoad())
		meshResources.loadNext();
	    while (textureResources.needLoad())
		textureResources.loadNext();
	}
	// Request them again
	requestResources();
    }

    // Drive rotation of icosahedron
    icoAngle += deltaTime;

    // Update moving light
    double currentTime = WindowManager::get()->getTime();
    light1Offset.x() = sin(currentTime) * 3;
    light1Offset.y() = -sin(currentTime) * 1;
    light1Offset.z() = cos(currentTime) * 3;

    light2Offset.y() = sin(currentTime);
}

void renderCallback(Window::RenderEventArgs const& args)
{
    auto rc = args.rc;

    int needLoad = shaderResources.getLoadQueueSize() + meshResources.getLoadQueueSize()
	    + textureResources.getLoadQueueSize();
    if (needLoad > 0)
    {
	std::string msg = "Loading... " + std::to_string(needLoad);
	unsigned int x = pWnd->getFrameWidth()/2 - pWnd->getDefaultFont().getWidth(msg)/2;
	unsigned int y = pWnd->getFrameHeight()/2 - pWnd->getDefaultFont().getLineHeight()/2;
	pWnd->getDefaultFont().drawText(*rc, *pShaderSprite, std::string(msg), x, y);
	if (shaderResources.needLoad())
	{
	    LOG.debug("Loading shader resource (" + std::to_string(needLoad) + ").");
	    shaderResources.loadNext();
	    return;
	}
	if (meshResources.needLoad())
	{
	    LOG.debug("Loading mesh resource (" + std::to_string(needLoad) + ").");
	    meshResources.loadNext();
	    return;
	}
	if (textureResources.needLoad())
	{
	    LOG.debug("Loading texture resource (" + std::to_string(needLoad) + ").");
	    textureResources.loadNext();
	    return;
	}
    }

    // We'll need some matrices later on
    Mat4f model {}, mv {}, mvp {};

    // Real position of the lights
    Vec3f light1RealPos = light1Pos + light1Offset;
    Vec3f light2RealPos = light2Pos + light2Offset;

    // Update view matrix
    view = Mat4f::makeView(pCam->position(), pCam->rotation() * Vec3f(0, 0, 1),
	    pCam->rotation() * Vec3f(0, 1, 0));

    // Draw lights using simple color shader
    pShaderNoLight->getShader()->use();
    // Get uniform handles
    GLint mvpId = pShaderNoLight->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    GLint colorId = pShaderNoLight->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::COLOR);
    if (mvpId <= 0)
	return;

    // Draw sphere at light 1 position
    pShaderNoLight->getShader()->setUniformFloat3(colorId, lightColor.getNormalized().getDataPointer());
    mvp = projection * view * Mat4f::makeTranslation(light1RealPos) * Mat4f::makeScale(0.2f);
    pShaderNoLight->getShader()->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    rc->draw(*pMeshSphere->getMesh());
    // Draw sphere at light 2 position
    pShaderNoLight->getShader()->setUniformFloat3(colorId, light2Color.getNormalized().getDataPointer());
    mvp = projection * view * Mat4f::makeTranslation(light2RealPos) * Mat4f::makeScale(0.2f);
    pShaderNoLight->getShader()->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    rc->draw(*pMeshSphere->getMesh());

    // Draw ground using diffuse + specular shader
    pShaderDiffSpec->getShader()->use();

    // Get uniform handles
    GLint mId = pShaderDiffSpec->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::MODEL);
    mvpId = pShaderDiffSpec->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    GLint itmId = pShaderDiffSpec->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::ITM);
    GLint itvId = pShaderDiffSpec->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::ITV);
    GLint numLightsId = pShaderDiffSpec->getShader()->getUniformHandle("i_numLights");
    GLint light0PosId = pShaderDiffSpec->getShader()->getUniformHandle("lights[0].v3_position_w");
    GLint light0ColorId = pShaderDiffSpec->getShader()->getUniformHandle("lights[0].v3_color");
    GLint light1PosId = pShaderDiffSpec->getShader()->getUniformHandle("lights[1].v3_position_w");
    GLint light1ColorId = pShaderDiffSpec->getShader()->getUniformHandle("lights[1].v3_color");
    GLint ambientId = pShaderDiffSpec->getShader()->getUniformHandle("v3_ambientLight");
    GLint matSpecColId = pShaderDiffSpec->getShader()->getUniformHandle("mat.v3_specColor");
    GLint matSpecWidthId = pShaderDiffSpec->getShader()->getUniformHandle("mat.f_specWidth");
    GLint diffuseId = pShaderDiffSpec->getShader()->getDefaultUniformHandle(ShaderProgram::TEX_DIFFUSE);
    GLint specularId = pShaderDiffSpec->getShader()->getDefaultUniformHandle(ShaderProgram::TEX_SPECULAR);

    // Bind textures
    // Bind diffuse texture to unit 0
    pShaderDiffSpec->getShader()->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexWhite->getHandle());
    pShaderDiffSpec->getShader()->setUniformSampler(diffuseId, 0);
    // Bind specular texture to unit 1
    pShaderDiffSpec->getShader()->bindTexture(GL_TEXTURE1, GL_TEXTURE_2D, pTexWhite->getHandle());
    pShaderDiffSpec->getShader()->setUniformSampler(specularId, 1);

    // Calc matrices
    model = Mat4f::makeTranslation(Vec3f(0, -1, 0)) * QuatF(Vec3f(0, 0, 1), Vec3f(0, 1, 0))
	    * Mat4f::makeScale(10);
    mvp = projection * view * model;

    // Set uniforms
    pShaderDiffSpec->getShader()->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE,
	    model.getInverted().transpose().getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE,
	    view.getInverted().transpose().getDataPointer());
    pShaderDiffSpec->getShader()->setUniformInt(numLightsId, 2);
    pShaderDiffSpec->getShader()->setUniformFloat3(light0PosId, light1RealPos.getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloat3(light0ColorId, lightColor.getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloat3(light1PosId, light2RealPos.getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloat3(light1ColorId, light2Color.getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloat3(ambientId, Vec3f(0.2, 0.2, 0.2).getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloat3(matSpecColId, matSpecular.getDataPointer());
    pShaderDiffSpec->getShader()->setUniformFloat(matSpecWidthId, 10);

    // Draw ground plane
    rc->draw(*pMeshPlane);

    // Draw everything else using the normal mapping shader
    pShaderNorm->getShader()->use();

    // Get uniform handles
    mId = pShaderNorm->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::MODEL);
    mvpId = pShaderNorm->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    itmId = pShaderNorm->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::ITM);
    itvId = pShaderNorm->getShader()->getDefaultUniformHandle(ShaderProgram::Uniform::ITV);
    numLightsId = pShaderNorm->getShader()->getUniformHandle("i_numLights");
    light0PosId = pShaderNorm->getShader()->getUniformHandle("lights[0].v3_position_w");
    light0ColorId = pShaderNorm->getShader()->getUniformHandle("lights[0].v3_color");
    light1PosId = pShaderNorm->getShader()->getUniformHandle("lights[1].v3_position_w");
    light1ColorId = pShaderNorm->getShader()->getUniformHandle("lights[1].v3_color");
    ambientId = pShaderNorm->getShader()->getUniformHandle("v3_ambientLight");
    matSpecColId = pShaderNorm->getShader()->getUniformHandle("mat.v3_specColor");
    matSpecWidthId = pShaderNorm->getShader()->getUniformHandle("mat.f_specWidth");
    diffuseId = pShaderNorm->getShader()->getDefaultUniformHandle(ShaderProgram::TEX_DIFFUSE);
    specularId = pShaderNorm->getShader()->getDefaultUniformHandle(ShaderProgram::TEX_SPECULAR);
    GLint normalId = pShaderNorm->getShader()->getDefaultUniformHandle(ShaderProgram::TEX_NORMAL);

    // Bind textures
    // Bind diffuse texture to unit 0
    pShaderDiffSpec->getShader()->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexBricks->getTexture()->getHandle());
    pShaderDiffSpec->getShader()->setUniformSampler(diffuseId, 0);
    // Bind specular texture to unit 1
    pShaderDiffSpec->getShader()->bindTexture(GL_TEXTURE1, GL_TEXTURE_2D, pTexBricksSpecular->getTexture()->getHandle());
    pShaderDiffSpec->getShader()->setUniformSampler(specularId, 1);
    // Bind normal texture to unit 2
    pShaderDiffSpec->getShader()->bindTexture(GL_TEXTURE2, GL_TEXTURE_2D, pTexBricksNormal->getTexture()->getHandle());
    pShaderDiffSpec->getShader()->setUniformSampler(normalId, 2);

    // Set uniforms that are the same for all of the following models
    pShaderNorm->getShader()->setUniformInt(numLightsId, 2);
    pShaderNorm->getShader()->setUniformFloat3(light0PosId, light1RealPos.getDataPointer());
    pShaderNorm->getShader()->setUniformFloat3(light0ColorId, lightColor.getDataPointer());
    pShaderNorm->getShader()->setUniformFloat3(light1PosId, light2RealPos.getDataPointer());
    pShaderNorm->getShader()->setUniformFloat3(light1ColorId, light2Color.getDataPointer());
    pShaderNorm->getShader()->setUniformFloat3(ambientId, Vec3f(0.2, 0.2, 0.2).getDataPointer());
    pShaderNorm->getShader()->setUniformFloat3(matSpecColId, matSpecular.getDataPointer());
    pShaderNorm->getShader()->setUniformFloat(matSpecWidthId, 10);

    // Render pyramid
    model = Mat4f();
    mvp = projection * view * model;
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE,
	    model.getInverted().transpose().getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE,
	    view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshPyramid);

    // Render box
    model = Mat4f::makeTranslation(5, 0, 3) * QuatF(Vec3f(0, pi_4(), 0));
    mvp = projection * view * model;
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE,
	    model.getInverted().transpose().getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE,
	    view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshBox);

    // Render Sphere
    model = Mat4f::makeTranslation(2, 0, 8);
    mvp = projection * view * model;
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE,
	    model.getInverted().transpose().getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE,
	    view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshSphere->getMesh());

    // Render icosahedron
    model = Mat4f::makeTranslation(-3, 0, 5) * QuatF(Vec3f(1, 1, 1), icoAngle);
    mvp = projection * view * model;
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE,
	    model.getInverted().transpose().getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE,
	    view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshIco->getMesh());

    // Bind textures
    // Bind diffuse texture to unit 0
    pShaderDiffSpec->getShader()->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexMarble->getTexture()->getHandle());
    pShaderDiffSpec->getShader()->setUniformSampler(diffuseId, 0);
    // Bind specular texture to unit 1
    pShaderDiffSpec->getShader()->bindTexture(GL_TEXTURE1, GL_TEXTURE_2D, pTexMarbleSpecular->getTexture()->getHandle());
    pShaderDiffSpec->getShader()->setUniformSampler(specularId, 1);
    // Bind normal texture to unit 2
    pShaderDiffSpec->getShader()->bindTexture(GL_TEXTURE2, GL_TEXTURE_2D, pTexMarbleNormal->getTexture()->getHandle());
    pShaderDiffSpec->getShader()->setUniformSampler(normalId, 2);

    // Render pillar
    model = Mat4f::makeTranslation(-2.5, 1.2f, 2) * QuatF(Vec3f(0, 1, 0), pi_5());
    mvp = projection * view * model;
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE,
	    model.getInverted().transpose().getDataPointer());
    pShaderNorm->getShader()->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE,
	    view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshPillar->getMesh());
}

int main()
{
    LOG.setLogLevel(Log::Level::DBG);
    // Init
    dbgl::initialize();
    // Create window
    pWnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    pWnd->init(Window::AlphaBlend | Window::DepthTest | Window::FaceCulling);
    // Add a camera
    Vec3f direction = Vec3f(6, -2, 0);
    pCam = new Camera
    {   Vec3f(-1, 2, 3), direction, Vec3f(0, 0, 1).cross(direction), pi_4(),
	0.1, 100};
    // Load meshes, shader and texture
    pMeshPyramid = Mesh::makePyramid(Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
    pMeshBox = Mesh::makeCube(Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
    pMeshPlane = Mesh::makePlane(Mesh::SendToGPU | Mesh::Optimize);
    pTexWhite = Texture::load(Texture::BOGUS, "");
    pShaderSprite = ShaderProgram::createSpriteShader();

    noLightShaderHandle = shaderResources.add(ShaderResource::ShaderResourceInfo
	    {   "../common/NoLight.vert", "../common/NoLight.frag"});
    diffSpecNormShaderHandle = shaderResources.add(ShaderResource::ShaderResourceInfo
	    {   "../common/DiffSpecNorm.vert", "../common/DiffSpecNorm.frag"});
    diffSpecShaderHandle = shaderResources.add(ShaderResource::ShaderResourceInfo
	    {   "../common/DiffSpec.vert", "../common/DiffSpec.frag"});
    icoHandle = meshResources.add(MeshResource::MeshResourceInfo<OBJMeshLoader>
	    {   "../common/Icosahedron.obj", Mesh::Optimize | Mesh::GenerateTangentBase});
    sphereHandle = meshResources.add(MeshResource::MeshResourceInfo<OBJMeshLoader>
	    {   "../common/Sphere.obj", Mesh::Optimize | Mesh::GenerateTangentBase});
    pillarHandle = meshResources.add(MeshResource::MeshResourceInfo<OBJMeshLoader>
	    {   "../common/Pillar.obj", Mesh::Optimize | Mesh::GenerateTangentBase});
    texBricksDiffHandle = textureResources.add(TextureResource::TextureResourceInfo<DDSTextureLoader>
	    {   "../common/Bricks01.DDS", Texture::FlipVertically});
    texBricksSpecHandle = textureResources.add(TextureResource::TextureResourceInfo<TGATextureLoader>
	    {   "../common/Bricks01_specular.tga"});
    texBricksNormHandle = textureResources.add(TextureResource::TextureResourceInfo<TGATextureLoader>
	    {   "../common/Bricks01_normal.tga"});
    texMarbleDiffHandle = textureResources.add(TextureResource::TextureResourceInfo<DDSTextureLoader>
	    {   "../common/Marble_Cream_01_Diffuse.DDS", Texture::FlipVertically});
    texMarbleSpecHandle = textureResources.add(TextureResource::TextureResourceInfo<TGATextureLoader>
	    {   "../common/Marble_Cream_01_Specular.tga"});
    texMarbleNormHandle = textureResources.add(TextureResource::TextureResourceInfo<TGATextureLoader>
	    {   "../common/Marble_Cream_01_Normal.tga"});
    // Request resources
    requestResources();
    // Add update- and render callback so we can draw the mesh
    pWnd->addUpdateCallback(std::bind(&updateCallback, std::placeholders::_1));
    pWnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    pWnd->addScrollCallback(std::bind(&scrollCallback, std::placeholders::_1));
    pWnd->addFramebufferResizeCallback(std::bind(&framebufferResizeCallback, std::placeholders::_1));
    // Show window
    pWnd->show();
    // Run update loop
    while (dbgl::isRunning())
    {
	dbgl::update();
    }
    // Clean up
    delete pCam;
    // delete pWnd; // No need for this as windows will delete themselves when closed
    // Free remaining internal resources
    dbgl::terminate();
    return 0;
}

