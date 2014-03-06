//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/RenderContext.h"

namespace dbgl
{
    RenderContext::RenderContext(unsigned int frameWidth,
	    unsigned int frameHeight) :
	    _frameWidth(frameWidth), _frameHeight(frameHeight)
    {
    }

    RenderContext::~RenderContext()
    {
    }

    void RenderContext::addViewport(Viewport* viewport)
    {
	_viewports.push_back(viewport);
    }

    void RenderContext::removeViewport(Viewport* viewport)
    {
	_viewports.erase(
		std::remove(_viewports.begin(), _viewports.end(), viewport),
		_viewports.end());
    }

    void RenderContext::draw(Renderable const* const entity) const
    {
	// Check if valid
	if (entity->pMesh == NULL || entity->pShader == NULL)
	{
	    LOG->warning("Invalid render attempt.");
	    return;
	}

	// Define shortcuts
	Mesh* pMesh = entity->pMesh;
	Vec3f const& position = entity->position;
	Vec3f const& scale = entity->scale;
	QuatF const& rotation = entity->rotation;
	ShaderProgram* pShader = entity->pShader;
	Texture* pTexDiffuse = entity->pTexDiffuse;
	Texture* pTexNormal = entity->pTexNormal;

	Mat4f modelMat = Mat4f::makeTranslation(position) * rotation.getMatrix() * Mat4f::makeScale(scale);
	Mat4f itmMat = modelMat.getInverted().transpose();

	// Check all viewports
	for (auto &viewport : _viewports)
	{
	    // Check if viewport has a camera
	    if (viewport->getCamera() == NULL)
	    {
		continue;
	    }
	    // Calculate absolute viewport values
	    // TODO: This is not needed for each mesh!
	    int viewportX = viewport->getXRatio() * _frameWidth;
	    int viewportY = viewport->getYRatio() * _frameHeight;
	    int viewportWidth = viewport->getWidthRatio()
	    * (_frameWidth - viewportX);
	    int viewportHeight = viewport->getHeightRatio()
	    * (_frameHeight - viewportY);
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
		glBindTexture(GL_TEXTURE_2D, pTexDiffuse->getTextureHandle());
		pShader->setUniformSampler(diffuseId, 0);
	    }
	    // Send normal texture if the shader wants it
	    GLint normalId = pShader->getDefaultUniformHandle(
		    ShaderProgram::TEX_NORMAL);
	    if (normalId >= 0 && pTexNormal != NULL)
	    {
		// Bind to texture unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pTexNormal->getTextureHandle());
		pShader->setUniformSampler(normalId, 1);
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
	    // Send itmv matrix if the shader wants it
	    GLint itmvId = pShader->getDefaultUniformHandle(
		    ShaderProgram::Uniform::ITMV);
	    if (itmvId >= 0)
	    {
		pShader->setUniformFloatMatrix4Array(itmvId, 1, GL_FALSE,
			(viewport->getITViewMat() * itmMat).getDataPointer());
	    }
	    // Render mesh
	    renderMesh(pMesh);
	}
    }

    void RenderContext::changeSize(unsigned int width, unsigned int height)
    {
	_frameWidth = width;
	_frameHeight = height;
    }

    void RenderContext::renderMesh(const Mesh* mesh) const
    {
	// Bind vertex buffer : 0
	if (mesh->_vertices.size() > 0)
	{
	    glEnableVertexAttribArray(0);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh->_vertexBuffer);
	    glVertexAttribPointer(0,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Bind UV buffer : 1
	if (mesh->_uv.size() > 0)
	{
	    glEnableVertexAttribArray(1);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh->_uvBuffer);
	    glVertexAttribPointer(1,	// attribute
		    2,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Bind normal buffer : 2
	if (mesh->_normals.size() > 0)
	{
	    glEnableVertexAttribArray(2);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh->_normalBuffer);
	    glVertexAttribPointer(2,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Bind tangent buffer : 2
	if (mesh->_tangents.size() > 0)
	{
	    glEnableVertexAttribArray(3);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh->_tangentBuffer);
	    glVertexAttribPointer(3,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Bind bitangent buffer : 2
	if (mesh->_bitangents.size() > 0)
	{
	    glEnableVertexAttribArray(4);
	    glBindBuffer(GL_ARRAY_BUFFER, mesh->_bitangentBuffer);
	    glVertexAttribPointer(4,	// attribute
		    3,			// size
		    GL_FLOAT,		// type
		    GL_FALSE,		// normalized?
		    0,			// stride
		    (void*) 0);		// offset
	}

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->_indexBuffer);

	// Draw!
	glDrawElements(GL_TRIANGLES,	// mode
		mesh->_indices.size(),	// count
		GL_UNSIGNED_SHORT,	// type
		(void*) 0);		// offset

	// Disable buffers
	if (mesh->_vertices.size() > 0)
	    glDisableVertexAttribArray(0);
	if (mesh->_uv.size() > 0)
	    glDisableVertexAttribArray(1);
	if (mesh->_normals.size() > 0)
	    glDisableVertexAttribArray(2);
	if (mesh->_tangents.size() > 0)
	    glDisableVertexAttribArray(3);
	if (mesh->_bitangents.size() > 0)
	    glDisableVertexAttribArray(4);
    }

    void RenderContext::update()
    {
	// Update all viewports
	for (auto &viewport : _viewports)
	{
	    viewport->update(_frameWidth, _frameHeight);
	}
    }
}

