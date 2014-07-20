//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "DBGL/Rendering/ShaderProgram.h"

namespace dbgl
{
    /**
     * @brief Base class combining surface features of a mesh.
     * @details This can affect surface features like color, texture, shader..., yet, it does not have any
     * 		influence on lighting conditions (e.g. position or intensity of light).
     */
    class Material
    {
	public:
	    /**
	     * @brief Constructor
	     * @param shaderProgram Shader to use
	     */
	    Material(ShaderProgram const& shaderProgram);
	    /**
	     * @brief Destructor
	     */
	    virtual ~Material() = default;
	    /**
	     * @brief Prepares this material to be used in the next render process(es).
	     */
	    virtual void prepare() const;
	    /**
	     * @return Pointer to the shader attached to this material
	     */
	    ShaderProgram const* getShader() const;

	protected:
	    ShaderProgram const* m_pShaderProgram;
    };
}

#endif /* MATERIAL_H_ */
