//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATERIAL2DTEX_H_
#define MATERIAL2DTEX_H_

#include "Material.h"
#include "DBGL/Rendering/Texture/Texture.h"

namespace dbgl
{
    /**
     * @brief A two-dimensional texture with additional normal- and/or specular map.
     * @details Every material of this type must have a diffuse texture and might have a normal map and a specular map.
     * @note Note that the passed \p shaderProgram needs to support all the texture types. This class does not attempt to
     * 	     check the shader for compatibility, it's the programmer's responsibility to do so.
     */
    class Material2DTex : public Material
    {
	public:
	    /**
	     * @brief Constructor
	     * @param shaderProgram Shader to use for rendering
	     * @param diffuse Diffuse texture
	     * @param pNormal Normal map or nullptr if none
	     * @param pSpecular Specular map or nullptr if none
	     * @note If the passed shader expects a normal or specular map it's not sufficient to simply pass
	     * 	     nullptr for those arguments to disable them. The shader needs to know how to handle the data
	     * 	     that's passed to it.
	     */
	    Material2DTex(ShaderProgram& shaderProgram, Texture& diffuse, Texture* pNormal, Texture* pSpecular);
	    /**
	     * @brief Prepares this material to be used in the next render process(es).
	     */
	    virtual void prepare();

	private:
	    Texture* m_pDiffuse;
	    Texture* m_pNormal;
	    Texture* m_pSpecular;
	    // TODO: Specular color, specular width
    };
}



#endif /* MATERIAL2DTEX_H_ */
