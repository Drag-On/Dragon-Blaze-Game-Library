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

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/ShaderProgram.h"
#include "Rendering/Texture/Texture.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace dbgl
{
    /**
     * @brief Accumulates all information necessary to render something
     */
    class Renderable
    {
	public:
	    Renderable();
	    Renderable(Mesh* mesh, ShaderProgram* shader, Texture* diff = NULL,
		    Texture* norm = NULL, Texture* spec = NULL,
		    Vec3f pos = Vec3f(0, 0, 0), Vec3f scle = Vec3f(1, 1, 1),
		    QuatF rot = QuatF());
	    Renderable(Renderable const& other);
	    void set(Mesh* mesh, ShaderProgram* shader, Texture* diff = NULL,
		    Texture* norm = NULL, Texture* spec = NULL,
		    Vec3f pos = Vec3f(0, 0, 0), Vec3f scle = Vec3f(1, 1, 1),
		    QuatF rot = QuatF());

	    Mesh* pMesh = NULL;
	    Vec3f position = Vec3f(0, 0, 0);
	    Vec3f scale = Vec3f(1, 1, 1);
	    QuatF rotation = QuatF(0, 0, 0, 1);
	    ShaderProgram* pShader = NULL;
	    Texture* pTexDiffuse = NULL;
	    Texture* pTexNormal = NULL;
	    Texture* pTexSpecular = NULL;
    };
}

#endif /* RENDERABLE_H_ */
