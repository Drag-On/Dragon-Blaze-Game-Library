//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef MATERIALCOLOR_H_
#define MATERIALCOLOR_H_

#include "Material.h"
#include "DBGL/Math/Vector3.h"

namespace dbgl
{
    /**
     * @brief A simple material which only includes a color
     */
    class MaterialColor: public Material
    {
	public:
	    /**
	     * @brief Constructor
	     * @param shaderProgram Shader to use
	     * @param color Color to use
	     */
	    MaterialColor(ShaderProgram const& shaderProgram, Vec3f const& color);
	    /**
	     * @brief Prepares this material to be used in the next render process(es).
	     */
	    virtual void prepare() const;
	    /**
	     * @brief Provides access to the color
	     * @return Reference to the current color
	     */
	    Vec3f& color();

	private:
	    Vec3f m_color;
    };
}

#endif /* MATERIALCOLOR_H_ */
