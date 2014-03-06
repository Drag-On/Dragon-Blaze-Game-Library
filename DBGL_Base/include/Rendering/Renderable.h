//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace dbgl
{
    /**
     * @brief Accumulates all information necessary to render something
     */
    struct Renderable
    {
	public:
	    Mesh* pMesh = NULL;
	    Vec3f position = Vec3f(0, 0, 0);
	    Vec3f scale = Vec3f(1, 1, 1);
	    QuatF rotation = QuatF(0, 0, 0, 1);
	    ShaderProgram* pShader = NULL;
	    Texture* pTexDiffuse = NULL;
	    Texture* pTexNormal = NULL;
    };
}

#endif /* RENDERABLE_H_ */
