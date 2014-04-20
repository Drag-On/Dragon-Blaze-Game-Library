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
#include "DBGL/System/Log/Log.h"
#include "DBGL/Window/WindowManager.h"
#include "DBGL/Window/SimpleWindow.h"
#include "DBGL/Rendering/RenderContext.h"
#include "DBGL/Rendering/Mesh/Mesh.h"
#include "DBGL/Rendering/ShaderProgram.h"
#include "DBGL/Rendering/Texture/Texture.h"
#include "DBGL/Rendering/Camera.h"
#include "DBGL/Math/Vector3.h"
#include "DBGL/Math/Utility.h"
#include "DBGL/Math/Quaternion.h"

using namespace dbgl;

Window* pWnd;
Mesh* pMeshPyramid, *pMeshBox, *pMeshIco, *pMeshPlane, *pMeshSphere, *pMeshPillar;
ShaderProgram* pShaderDiffSpec, *pShaderNorm, *pShaderNoLight;
Texture* pTexBricks, *pTexBricksNormal, *pTexBricksSpecular, *pTexWhite, *pTexMarble, *pTexMarbleNormal, *pTexMarbleSpecular;
Camera* pCam;
Mat4f view, projection;
Vec3f light1Pos = Vec3f(0, 3, 3), lightColor = Vec3f(1.0f, 0.5f, 0.0f) * 15; // Orange
Vec3f light2Pos = Vec3f(1, 2, 4.5f), light2Color = Vec3f(0.5f, 0.5f, 1.0f) * 25; // Blue-ish
Vec3f light1Offset, light2Offset; // For movement of light
Vec3f matSpecular = Vec3f(0.1, 0.1, 0.2);
float mouseSpeed = 3.0f, moveSpeed = 2.5;
float icoAngle = 0;

void scrollCallback(Window::ScrollEventArgs const& args)
{
    // Zoom
    pCam->setFieldOfView(pCam->getFieldOfView() + 0.1f * args.yOffset);
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	    float(pWnd->getFrameWidth()) / pWnd->getFrameHeight(),
	    pCam->getNear(), pCam->getFar());
}

void framebufferResizeCallback(Window::FramebufferResizeEventArgs const& args)
{
    // Update projection matrix if the windows was rescaled
    projection = Mat4f::makeProjection(pCam->getFieldOfView(),
	    float(args.width) / args.height, pCam->getNear(), pCam->getFar());
}

void updateCallback(Window::UpdateEventArgs const& args)
{
    auto deltaTime = args.deltaTime;

    // Update mouse
    double x, y;
    pWnd->getCursorPos(x, y);
    double horizontal = deltaTime * mouseSpeed
	    * (pWnd->getFrameWidth() / 2.0 - x);
    double vertical = deltaTime * mouseSpeed
	    * (pWnd->getFrameHeight() / 2.0 - y);
    pCam->rotate(horizontal, -vertical);
    // Camera vectors
    Vec3f direction = pCam->rotation() * Vec3f(0, 0, 1);
    Vec3f right = pCam->rotation() * Vec3f(-1, 0, 0);
    // Reset mouse position to center of the screen
    pWnd->setCursorPos(pWnd->getFrameWidth() / 2, pWnd->getFrameHeight() / 2);

    // Update keyboard
    if (pWnd->getKey(GLFW_KEY_W) == GLFW_PRESS)
	pCam->position() += direction * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_A) == GLFW_PRESS)
	pCam->position() -= right * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_S) == GLFW_PRESS)
	pCam->position() -= direction * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_D) == GLFW_PRESS)
	pCam->position() += right * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_E) == GLFW_PRESS)
	pCam->position() += Vec3f(0, 1, 0) * deltaTime * moveSpeed;
    if (pWnd->getKey(GLFW_KEY_Q) == GLFW_PRESS)
	pCam->position() -= Vec3f(0, 1, 0) * deltaTime * moveSpeed;

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

    // We'll need some matrices later on
    Mat4f model, mv, mvp;

    // Real position of the lights
    Vec3f light1RealPos = light1Pos + light1Offset;
    Vec3f light2RealPos = light2Pos + light2Offset;

    // Update view matrix
    view = Mat4f::makeView(pCam->position(), pCam->rotation() * Vec3f(0, 0, 1),
	    pCam->rotation() * Vec3f(0, 1, 0));

    // Draw lights using simple color shader
    pShaderNoLight->use();
    // Get uniform handles
    GLint mvpId = pShaderNoLight->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    GLint colorId = pShaderNoLight->getDefaultUniformHandle(ShaderProgram::Uniform::COLOR);
    if (mvpId <= 0)
	return;

    // Draw sphere at light 1 position
    pShaderNoLight->setUniformFloat3(colorId, lightColor.getNormalized().getDataPointer());
    mvp = projection * view * Mat4f::makeTranslation(light1RealPos) * Mat4f::makeScale(0.2f);
    pShaderNoLight->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    rc->draw(*pMeshSphere);
    // Draw sphere at light 2 position
    pShaderNoLight->setUniformFloat3(colorId, light2Color.getNormalized().getDataPointer());
    mvp = projection * view * Mat4f::makeTranslation(light2RealPos) * Mat4f::makeScale(0.2f);
    pShaderNoLight->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    rc->draw(*pMeshSphere);

    // Draw ground using diffuse + specular shader
    pShaderDiffSpec->use();

    // Get uniform handles
    GLint mId = pShaderDiffSpec->getDefaultUniformHandle(ShaderProgram::Uniform::MODEL);
    mvpId = pShaderDiffSpec->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    GLint itmId = pShaderDiffSpec->getDefaultUniformHandle(ShaderProgram::Uniform::ITM);
    GLint itvId = pShaderDiffSpec->getDefaultUniformHandle(ShaderProgram::Uniform::ITV);
    GLint numLightsId = pShaderDiffSpec->getUniformHandle("i_numLights");
    GLint light0PosId = pShaderDiffSpec->getUniformHandle("lights[0].v3_position_w");
    GLint light0ColorId = pShaderDiffSpec->getUniformHandle("lights[0].v3_color");
    GLint light1PosId = pShaderDiffSpec->getUniformHandle("lights[1].v3_position_w");
    GLint light1ColorId = pShaderDiffSpec->getUniformHandle("lights[1].v3_color");
    GLint ambientId = pShaderDiffSpec->getUniformHandle("v3_ambientLight");
    GLint matSpecColId = pShaderDiffSpec->getUniformHandle("mat.v3_specColor");
    GLint matSpecWidthId = pShaderDiffSpec->getUniformHandle("mat.f_specWidth");
    GLint diffuseId = pShaderDiffSpec->getDefaultUniformHandle(ShaderProgram::TEX_DIFFUSE);
    GLint specularId = pShaderDiffSpec->getDefaultUniformHandle(ShaderProgram::TEX_SPECULAR);

    // Bind textures
    // Bind diffuse texture to unit 0
    pShaderDiffSpec->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexWhite->getHandle());
    pShaderDiffSpec->setUniformSampler(diffuseId, 0);
    // Bind specular texture to unit 1
    pShaderDiffSpec->bindTexture(GL_TEXTURE1, GL_TEXTURE_2D, pTexWhite->getHandle());
    pShaderDiffSpec->setUniformSampler(specularId, 1);

    // Calc matrices
    model = Mat4f::makeTranslation(Vec3f(0, -1, 0)) * QuatF(Vec3f(0, 0, 1), Vec3f(0, 1, 0)) * Mat4f::makeScale(10);
    mvp = projection * view * model;

    // Set uniforms
    pShaderDiffSpec->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderDiffSpec->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderDiffSpec->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE, model.getInverted().transpose().getDataPointer());
    pShaderDiffSpec->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE, view.getInverted().transpose().getDataPointer());
    pShaderDiffSpec->setUniformInt(numLightsId, 2);
    pShaderDiffSpec->setUniformFloat3(light0PosId, light1RealPos.getDataPointer());
    pShaderDiffSpec->setUniformFloat3(light0ColorId, lightColor.getDataPointer());
    pShaderDiffSpec->setUniformFloat3(light1PosId, light2RealPos.getDataPointer());
    pShaderDiffSpec->setUniformFloat3(light1ColorId, light2Color.getDataPointer());
    pShaderDiffSpec->setUniformFloat3(ambientId, Vec3f(0.2, 0.2, 0.2).getDataPointer());
    pShaderDiffSpec->setUniformFloat3(matSpecColId, matSpecular.getDataPointer());
    pShaderDiffSpec->setUniformFloat(matSpecWidthId, 10);

    // Draw ground plane
    rc->draw(*pMeshPlane);

    // Draw everything else using the normal mapping shader
    pShaderNorm->use();

    // Get uniform handles
    mId = pShaderNorm->getDefaultUniformHandle(ShaderProgram::Uniform::MODEL);
    mvpId = pShaderNorm->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
    itmId = pShaderNorm->getDefaultUniformHandle(ShaderProgram::Uniform::ITM);
    itvId = pShaderNorm->getDefaultUniformHandle(ShaderProgram::Uniform::ITV);
    numLightsId = pShaderNorm->getUniformHandle("i_numLights");
    light0PosId = pShaderNorm->getUniformHandle("lights[0].v3_position_w");
    light0ColorId = pShaderNorm->getUniformHandle("lights[0].v3_color");
    light1PosId = pShaderNorm->getUniformHandle("lights[1].v3_position_w");
    light1ColorId = pShaderNorm->getUniformHandle("lights[1].v3_color");
    ambientId = pShaderNorm->getUniformHandle("v3_ambientLight");
    matSpecColId = pShaderNorm->getUniformHandle("mat.v3_specColor");
    matSpecWidthId = pShaderNorm->getUniformHandle("mat.f_specWidth");
    diffuseId = pShaderNorm->getDefaultUniformHandle(ShaderProgram::TEX_DIFFUSE);
    specularId = pShaderNorm->getDefaultUniformHandle(ShaderProgram::TEX_SPECULAR);
    GLint normalId = pShaderNorm->getDefaultUniformHandle(ShaderProgram::TEX_NORMAL);

    // Bind textures
    // Bind diffuse texture to unit 0
    pShaderDiffSpec->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexBricks->getHandle());
    pShaderDiffSpec->setUniformSampler(diffuseId, 0);
    // Bind specular texture to unit 1
    pShaderDiffSpec->bindTexture(GL_TEXTURE1, GL_TEXTURE_2D, pTexBricksSpecular->getHandle());
    pShaderDiffSpec->setUniformSampler(specularId, 1);
    // Bind normal texture to unit 2
    pShaderDiffSpec->bindTexture(GL_TEXTURE2, GL_TEXTURE_2D, pTexBricksNormal->getHandle());
    pShaderDiffSpec->setUniformSampler(normalId, 2);

    // Set uniforms that are the same for all of the following models
    pShaderNorm->setUniformInt(numLightsId, 2);
    pShaderNorm->setUniformFloat3(light0PosId, light1RealPos.getDataPointer());
    pShaderNorm->setUniformFloat3(light0ColorId, lightColor.getDataPointer());
    pShaderNorm->setUniformFloat3(light1PosId, light2RealPos.getDataPointer());
    pShaderNorm->setUniformFloat3(light1ColorId, light2Color.getDataPointer());
    pShaderNorm->setUniformFloat3(ambientId, Vec3f(0.2, 0.2, 0.2).getDataPointer());
    pShaderNorm->setUniformFloat3(matSpecColId, matSpecular.getDataPointer());
    pShaderNorm->setUniformFloat(matSpecWidthId, 10);

    // Render pyramid
    model = Mat4f();
    mvp = projection * view * model;
    pShaderNorm->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE, model.getInverted().transpose().getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE, view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshPyramid);

    // Render box
    model = Mat4f::makeTranslation(5, 0, 3) * QuatF(Vec3f(0, pi_4(), 0));
    mvp = projection * view * model;
    pShaderNorm->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE, model.getInverted().transpose().getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE, view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshBox);

    // Render Sphere
    model = Mat4f::makeTranslation(2, 0, 8);
    mvp = projection * view * model;
    pShaderNorm->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE, model.getInverted().transpose().getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE, view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshSphere);

    // Render icosahedron
    model = Mat4f::makeTranslation(-3, 0, 5) * QuatF(Vec3f(1, 1, 1), icoAngle);
    mvp = projection * view * model;
    pShaderNorm->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE, model.getInverted().transpose().getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE, view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshIco);

    // Bind textures
    // Bind diffuse texture to unit 0
    pShaderDiffSpec->bindTexture(GL_TEXTURE0, GL_TEXTURE_2D, pTexMarble->getHandle());
    pShaderDiffSpec->setUniformSampler(diffuseId, 0);
    // Bind specular texture to unit 1
    pShaderDiffSpec->bindTexture(GL_TEXTURE1, GL_TEXTURE_2D, pTexMarbleSpecular->getHandle());
    pShaderDiffSpec->setUniformSampler(specularId, 1);
    // Bind normal texture to unit 2
    pShaderDiffSpec->bindTexture(GL_TEXTURE2, GL_TEXTURE_2D, pTexMarbleNormal->getHandle());
    pShaderDiffSpec->setUniformSampler(normalId, 2);

    // Render pillar
    model = Mat4f::makeTranslation(-2.5, 1.2f, 2) * QuatF(Vec3f(0, 1, 0), pi_5());
    mvp = projection * view * model;
    pShaderNorm->setUniformFloatMatrix4Array(mId, 1, GL_FALSE, model.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE, mvp.getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE, model.getInverted().transpose().getDataPointer());
    pShaderNorm->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE, view.getInverted().transpose().getDataPointer());
    rc->draw(*pMeshPillar);
}

int main()
{
    LOG->setLogLevel(DBG);
    // Create window
    pWnd = WindowManager::get()->createWindow<SimpleWindow>();
    // Initialize it
    pWnd->init();
    // Add a camera
    Vec3f direction = Vec3f(6, -2, 0);
    pCam = new Camera(Vec3f(-1, 2, 3), direction, Vec3f(0, 0, 1).cross(direction), pi_4(),
	    0.1, 100);
    // Load meshes, shader and texture
    pMeshPyramid = Mesh::makePyramid(Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
    pMeshBox = Mesh::makeCube(Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
    pMeshPlane = Mesh::makePlane();
    pMeshIco = Mesh::load(Mesh::OBJ,"../common/Icosahedron.obj", Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
    pMeshSphere = Mesh::load(Mesh::OBJ,"../common/Sphere.obj", Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
    pMeshPillar = Mesh::load(Mesh::OBJ, "../common/Pillar.obj", Mesh::SendToGPU | Mesh::Optimize | Mesh::GenerateTangentBase);
    pShaderNoLight = new ShaderProgram("../common/NoLight.vert", "../common/NoLight.frag");
    pShaderDiffSpec = new ShaderProgram("../common/DiffSpec.vert", "../common/DiffSpec.frag");
    pShaderNorm = new ShaderProgram("../common/DiffSpecNorm.vert", "../common/DiffSpecNorm.frag");
    pTexBricks = Texture::load(Texture::DDS, "../common/Bricks01.DDS", Texture::FlipVertically);
    pTexBricksNormal = Texture::load(Texture::TGA, "../common/Bricks01_normal.tga");
    pTexBricksSpecular = Texture::load(Texture::TGA, "../common/Bricks01_specular.tga");
    pTexWhite = Texture::load(Texture::BOGUS, "");
    pTexMarble = Texture::load(Texture::DDS, "../common/Marble_Cream_01_Diffuse.DDS", Texture::FlipVertically);
    pTexMarbleNormal = Texture::load(Texture::TGA, "../common/Marble_Cream_01_Normal.tga");
    pTexMarbleSpecular = Texture::load(Texture::TGA, "../common/Marble_Cream_01_Specular.tga");
    // Add update- and render callback so we can draw the mesh
    pWnd->addUpdateCallback(std::bind(&updateCallback, std::placeholders::_1));
    pWnd->addRenderCallback(std::bind(&renderCallback, std::placeholders::_1));
    pWnd->addScrollCallback(std::bind(&scrollCallback, std::placeholders::_1));
    pWnd->addFramebufferResizeCallback(std::bind(&framebufferResizeCallback, std::placeholders::_1));
    // Show window
    pWnd->show();
    // Run update loop
    while (WindowManager::get()->isRunning())
    {
	WindowManager::get()->update();
    }
    // Clean up
    delete pMeshPyramid;
    delete pMeshBox;
    delete pMeshIco;
    delete pMeshPlane;
    delete pMeshSphere;
    delete pMeshPillar;
    delete pShaderNoLight;
    delete pShaderDiffSpec;
    delete pShaderNorm;
    delete pTexBricks;
    delete pTexBricksNormal;
    delete pTexBricksSpecular;
    delete pTexWhite;
    delete pTexMarble;
    delete pTexMarbleNormal;
    delete pTexMarbleSpecular;
    delete pCam;
    // delete pWnd; // No need for this as windows will delete themselves when closed
    // Free remaining internal resources
    WindowManager::get()->terminate();
    return 0;
}

