//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/System/Entity/RenderComponent.h"

namespace dbgl
{
    RenderComponent::RenderComponent(Mesh& mesh, Material& mat, Environment& env) :
	    m_pMesh(&mesh), m_pMaterial(&mat), m_pEnvironment(&env)
    {
    }

    void RenderComponent::update(Entity* /* owner */, double /* deltaTime */)
    {
	// No update needed
    }

    void RenderComponent::render(Entity* owner, RenderContext const* rc)
    {
	// Send material properties to shader
	m_pMaterial->prepare();

	// Calculate matrices and send them to shader
	prepareMatrices(owner->getComponent<TransformComponent>().get(), rc);

	// Draw mesh!
	rc->draw(*m_pMesh);
    }

    bool RenderComponent::needUpdate() const
    {
	return false;
    }

    bool RenderComponent::needRender() const
    {
	return true;
    }

    void RenderComponent::prepareMatrices(TransformComponent* transform, RenderContext const* rc)
    {
	// Calculate matrices
	auto position = transform->position();
	auto rotation = transform->rotation();
	auto scale = transform->scale();
	auto pShader = m_pMaterial->getShader();
	auto cam = m_pEnvironment->getCamera();
	auto frameWidth = rc->getWidth();
	auto frameHeight = rc->getHeight();

	Mat4f modelMat = Mat4f::makeTranslation(position) * rotation.getMatrix() * Mat4f::makeScale(scale);
	Mat4f itmMat = modelMat.getInverted().transpose();
	Vec3f direction{}, up{};
	cam->getOrientation(&direction, &up, nullptr);
	Mat4f viewMat = Mat4f::makeView(cam->position(), direction, up);
	Mat4f itvMat = viewMat.getInverted().transpose();
	Mat4f projMat = Mat4f::makeProjection(cam->getFieldOfView(), frameWidth / frameHeight, cam->getNear(),
		cam->getFar());
	// Send model matrix if the shader wants it
	GLint modelId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::MODEL);
	if (modelId >= 0)
	{
	    pShader->setUniformFloatMatrix4Array(modelId, 1, GL_FALSE, modelMat.getDataPointer());
	}
	// Send view matrix if the shader wants it
	GLint viewId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::VIEW);
	if (viewId >= 0)
	{
	    pShader->setUniformFloatMatrix4Array(viewId, 1, GL_FALSE, viewMat.getDataPointer());
	}
	// Send projection matrix if the shader wants it
	GLint projectionId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::PROJECTION);
	if (projectionId >= 0)
	{
	    pShader->setUniformFloatMatrix4Array(projectionId, 1, GL_FALSE, projMat.getDataPointer());
	}
	// Send mv matrix if the shader wants it
	GLint mvId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::MV);
	if (mvId >= 0)
	{
	    pShader->setUniformFloatMatrix4Array(mvId, 1, GL_FALSE,
		    (viewMat * modelMat).getDataPointer());
	}
	// Send mvp matrix if the shader wants it
	GLint mvpId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::MVP);
	if (mvpId >= 0)
	{
	    pShader->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE,
		    (projMat * viewMat * modelMat).getDataPointer());
	}
	// Send itm matrix if the shader wants it
	GLint itmId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::ITM);
	if (itmId >= 0)
	{
	    pShader->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE, itmMat.getDataPointer());
	}
	// Send itv matrix if the shader wants it
	GLint itvId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::ITV);
	if (itvId >= 0)
	{
	    pShader->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE,
		    itvMat.getDataPointer());
	}
	// Send itmv matrix if the shader wants it
	GLint itmvId = pShader->getDefaultUniformHandle(ShaderProgram::Uniform::ITMV);
	if (itmvId >= 0)
	{
	    pShader->setUniformFloatMatrix4Array(itmvId, 1, GL_FALSE,
		    (itvMat * itmMat).getDataPointer());
	}
    }
}

