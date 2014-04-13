//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/SceneRenderContext.h"

namespace dbgl
{
    SceneRenderContext::SceneRenderContext(unsigned int frameWidth, unsigned int frameHeight) :
	    RenderContext(frameWidth, frameHeight)
    {
    }

    SceneRenderContext::~SceneRenderContext()
    {
    }

    void SceneRenderContext::addViewport(Viewport* viewport)
    {
	m_viewports.push_back(viewport);
    }

    void SceneRenderContext::removeViewport(Viewport* viewport)
    {
	m_viewports.erase(
		std::remove(m_viewports.begin(), m_viewports.end(), viewport),
		m_viewports.end());
    }

    void SceneRenderContext::draw(Renderable const& entity) const
    {
	// Check if valid
	if (entity.pMesh == NULL || entity.pShader == NULL)
	{
	    LOG->warning("Invalid render attempt.");
	    return;
	}

	// Define shortcuts
	Mesh* pMesh = entity.pMesh;
	Vec3f const& position = entity.position;
	Vec3f const& scale = entity.scale;
	QuatF const& rotation = entity.rotation;
	ShaderProgram* pShader = entity.pShader;
	Texture* pTexDiffuse = entity.pTexDiffuse;
	Texture* pTexNormal = entity.pTexNormal;
	Texture* pTexSpecular = entity.pTexSpecular;

	Mat4f modelMat = Mat4f::makeTranslation(position) * rotation.getMatrix() * Mat4f::makeScale(scale);
	Mat4f itmMat = modelMat.getInverted().transpose();

	// Check all viewports
	for (auto &viewport : m_viewports)
	{
	    // Check if viewport has a camera
	    if (viewport->getCamera() == NULL)
	    {
		continue;
	    }
	    // Calculate absolute viewport values
	    // TODO: This is not needed for each mesh!
	    int viewportX = viewport->getXRatio() * m_frameWidth;
	    int viewportY = viewport->getYRatio() * m_frameHeight;
	    int viewportWidth = viewport->getWidthRatio()
	    * (m_frameWidth - viewportX);
	    int viewportHeight = viewport->getHeightRatio()
	    * (m_frameHeight - viewportY);
	    // Set viewport
	    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);

	    // TODO: Frustum culling

	    // Send diffuse texture if the shader wants it
	    GLint diffuseId = pShader->getDefaultUniformHandle(
		    ShaderProgram::TEX_DIFFUSE);
	    if (diffuseId >= 0 && pTexDiffuse != NULL)
	    {
		// Bind to texture unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pTexDiffuse->getHandle());
		pShader->setUniformSampler(diffuseId, 0);
	    }
	    // Send normal texture if the shader wants it
	    GLint normalId = pShader->getDefaultUniformHandle(
		    ShaderProgram::TEX_NORMAL);
	    if (normalId >= 0 && pTexNormal != NULL)
	    {
		// Bind to texture unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pTexNormal->getHandle());
		pShader->setUniformSampler(normalId, 1);
	    }
	    // Send specular texture if the shader wants it
	    GLint specularId = pShader->getDefaultUniformHandle(
		    ShaderProgram::TEX_SPECULAR);
	    if (specularId >= 0 && pTexSpecular != NULL)
	    {
		// Bind to texture unit 2
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, pTexSpecular->getHandle());
		pShader->setUniformSampler(specularId, 2);
	    }
	    // Send model matrix if the shader wants it
	    GLint modelId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::MODEL);
	    if (modelId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(modelId, 1, GL_FALSE,
			modelMat.getDataPointer());
	    }
	    // Send view matrix if the shader wants it
	    GLint viewId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::VIEW);
	    if (viewId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(viewId, 1, GL_FALSE,
			viewport->getViewMat().getDataPointer());
	    }
	    // Send projection matrix if the shader wants it
	    GLint projectionId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::PROJECTION);
	    if (projectionId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(projectionId, 1, GL_FALSE,
			viewport->getProjectionMat().getDataPointer());
	    }
	    // Send mv matrix if the shader wants it
	    GLint mvId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::MV);
	    if (mvId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(mvId, 1, GL_FALSE,
			(viewport->getViewMat() * modelMat).getDataPointer());
	    }
	    // Send mvp matrix if the shader wants it
	    GLint mvpId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::MVP);
	    if (mvpId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(mvpId, 1, GL_FALSE,
			(viewport->getViewProjectionMat() * modelMat).getDataPointer());
	    }
	    // Send itm matrix if the shader wants it
	    GLint itmId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::ITM);
	    if (itmId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(itmId, 1, GL_FALSE,
			itmMat.getDataPointer());
	    }
	    // Send itv matrix if the shader wants it
	    GLint itvId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::ITV);
	    if (itvId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(itvId, 1, GL_FALSE,
			(viewport->getITViewMat()).getDataPointer());
	    }
	    // Send itmv matrix if the shader wants it
	    GLint itmvId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::ITMV);
	    if (itmvId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(itmvId, 1, GL_FALSE,
			(viewport->getITViewMat() * itmMat).getDataPointer());
	    }
	    // Render mesh
	    RenderContext::draw(*pMesh);
	}
    }

    void SceneRenderContext::preRender()
    {
	RenderContext::preRender();

	// Update all viewports
	for (auto &viewport : m_viewports)
	{
	    viewport->update(m_frameWidth, m_frameHeight);
	}
    }

}
