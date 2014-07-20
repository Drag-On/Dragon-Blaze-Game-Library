//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Material/Material.h"

namespace dbgl
{
    Material::Material(ShaderProgram const& shaderProgram) : m_pShaderProgram(&shaderProgram)
    {
    }

    void Material::prepare() const
    {
	m_pShaderProgram->use();
    }

    ShaderProgram const* Material::getShader() const
    {
	return m_pShaderProgram;
    }
}
