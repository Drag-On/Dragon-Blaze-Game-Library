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
    Material2DTex::Material2DTex(ShaderProgram& shaderProgram, Texture& diffuse, Texture* pNormal,
	    Texture* pSpecular) :
	    Material(shaderProgram), m_pDiffuse(&diffuse), m_pNormal(pNormal), m_pSpecular(pSpecular)
    {
    }

    void Material2DTex::prepare()
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
    }

}
