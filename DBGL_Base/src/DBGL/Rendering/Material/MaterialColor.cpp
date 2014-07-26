//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "DBGL/Rendering/Material/MaterialColor.h"

namespace dbgl
{
    MaterialColor::MaterialColor(ShaderProgram const& shaderProgram, Vec3f const& color) : Material(shaderProgram), m_color(color)
    {
    }

    void MaterialColor::prepare() const
    {
	// Call base class
	Material::prepare();

	// Send color to shader
	GLint colorId = m_pShaderProgram->getDefaultUniformHandle(ShaderProgram::COLOR);
	if (colorId >= 0)
	{
	    m_pShaderProgram->setUniformFloat3(colorId, m_color.getDataPointer());
	}
    }

    Vec3f& MaterialColor::color()
    {
	return m_color;
    }

}
