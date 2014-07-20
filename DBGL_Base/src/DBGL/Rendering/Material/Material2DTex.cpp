//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Material/Material2DTex.h"

namespace dbgl
{
    Material2DTex::Material2DTex(ShaderProgram const& shaderProgram, Texture const& diffuse, Texture const* pNormal,
	    Texture const* pSpecular) :
	    Material(shaderProgram), m_pDiffuse(&diffuse), m_pNormal(pNormal), m_pSpecular(pSpecular)
    {
    }

    void Material2DTex::prepare() const
    {
	// Call base class
	Material::prepare();

	// Send diffuse texture if the shader wants it
	GLint diffuseId = m_pShaderProgram->getDefaultUniformHandle(ShaderProgram::TEX_DIFFUSE);
	if (diffuseId >= 0 && m_pDiffuse != nullptr)
	{
	    // Bind to texture unit 0
	    glActiveTexture(GL_TEXTURE0);
	    glBindTexture(GL_TEXTURE_2D, m_pDiffuse->getHandle());
	    m_pShaderProgram->setUniformSampler(diffuseId, 0);
	}
	// Send normal texture if the shader wants it
	GLint normalId = m_pShaderProgram->getDefaultUniformHandle(ShaderProgram::TEX_NORMAL);
	if (normalId >= 0 && m_pNormal != nullptr)
	{
	    // Bind to texture unit 1
	    glActiveTexture(GL_TEXTURE1);
	    glBindTexture(GL_TEXTURE_2D, m_pNormal->getHandle());
	    m_pShaderProgram->setUniformSampler(normalId, 1);
	}
	// Send specular texture if the shader wants it
	GLint specularId = m_pShaderProgram->getDefaultUniformHandle(ShaderProgram::TEX_SPECULAR);
	if (specularId >= 0 && m_pSpecular != nullptr)
	{
	    // Bind to texture unit 2
	    glActiveTexture(GL_TEXTURE2);
	    glBindTexture(GL_TEXTURE_2D, m_pSpecular->getHandle());
	    m_pShaderProgram->setUniformSampler(specularId, 2);
	}
	// Send specular color and width if the shader wants it
	GLint specularColorId = m_pShaderProgram->getDefaultUniformHandle(ShaderProgram::SPEC_COLOR);
	if (specularColorId >= 0)
	{
	    m_pShaderProgram->setUniformFloat3(specularColorId, m_specColor.getDataPointer());
	}
	GLint specularWidthId = m_pShaderProgram->getDefaultUniformHandle(ShaderProgram::SPEC_WIDTH);
	if (specularWidthId >= 0)
	{
	    m_pShaderProgram->setUniformFloat(specularWidthId, m_specWidth);
	}
    }

    Texture const* Material2DTex::getDiffuse() const
    {
	return m_pDiffuse;
    }

    void Material2DTex::setDiffuse(Texture const& diffuse)
    {
	m_pDiffuse = &diffuse;
    }

    Texture const* Material2DTex::getNormal() const
    {
	return m_pNormal;
    }

    void Material2DTex::setNormal(Texture const& normal)
    {
	m_pNormal = &normal;
    }

    Texture const* Material2DTex::getSpecular() const
    {
	return m_pSpecular;
    }

    void Material2DTex::setSpecular(Texture const& specular)
    {
	m_pSpecular = &specular;
    }

    Vec3f const& Material2DTex::getSpecColor() const
    {
	return m_specColor;
    }

    void Material2DTex::setSpecColor(Vec3f const& color)
    {
	m_specColor = color;
    }

    float Material2DTex::getSpecWidth() const
    {
	return m_specWidth;
    }

    void Material2DTex::setSpecWidth(float width)
    {
	m_specWidth = width;
    }

}
