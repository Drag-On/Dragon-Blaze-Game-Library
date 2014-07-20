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
#include "DBGL/Math/Vector3.h"

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
	    Material2DTex(ShaderProgram const& shaderProgram, Texture const& diffuse, Texture const* pNormal, Texture const* pSpecular);
	    /**
	     * @brief Prepares this material to be used in the next render process(es).
	     */
	    virtual void prepare() const;
	    /**
	     * @brief Provides read-access to the diffuse texture
	     * @return Pointer to the currently used diffuse texture
	     */
	    Texture const* getDiffuse() const;
	    /**
	     * @brief Changes the diffuse texture to the passed new texture
	     * @param diffuse New diffuse texture
	     */
	    void setDiffuse(Texture const& diffuse);
	    /**
	     * @brief Provides read-access to the normal texture
	     * @return Pointer to the currently used normal texture
	     */
	    Texture const* getNormal() const;
	    /**
	     * @brief Changes the normal texture to the passed new texture
	     * @param normal New normal texture
	     */
	    void setNormal(Texture const& normal);
	    /**
	     * @brief Provides read-access to the specular texture
	     * @return Pointer to the currently used specular texture
	     */
	    Texture const* getSpecular() const;
	    /**
	     * @brief Changes the specular texture to the passed new texture
	     * @param specular New normal texture
	     */
	    void setSpecular(Texture const& specular);
	    /**
	     * @brief Provides read-access to the specular color
	     * @return Pointer to the currently used specular color
	     */
	    Vec3f const& getSpecColor() const;
	    /**
	     * Changes the specular color to the passed new color
	     * @param color New color
	     */
	    void setSpecColor(Vec3f const& color);
	    /**
	     * @brief Provides read-access to the specular width
	     * @return Pointer to the currently used specular width
	     */
	    float getSpecWidth() const;
	    /**
	     * @brief Changes the specular width to the passed new value
	     * @param width New specular width
	     */
	    void setSpecWidth(float width);

	private:
	    Texture const* m_pDiffuse;
	    Texture const* m_pNormal;
	    Texture const* m_pSpecular;
	    Vec3f m_specColor = {1.0f, 1.0f, 1.0f};
	    float m_specWidth = 5.0f;
    };
}



#endif /* MATERIAL2DTEX_H_ */
