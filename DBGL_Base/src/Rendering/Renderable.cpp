//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#include "Rendering/Renderable.h"

namespace dbgl
{
    Renderable::Renderable()
    {
    }

    Renderable::Renderable(Mesh* mesh, ShaderProgram* shader, Texture* diff,
	    Texture* norm, Texture* spec, Vec3f pos, Vec3f scle, QuatF rot)
    {
	set(mesh, shader, diff, norm, spec, pos, scle, rot);
    }

    Renderable::Renderable(Renderable const& other)
    {
	pMesh = other.pMesh;
	position = other.position;
	scale = other.scale;
	rotation = other.rotation;
	pShader = other.pShader;
	pTexDiffuse = other.pTexDiffuse;
	pTexNormal = other.pTexNormal;
	pTexSpecular = other.pTexSpecular;
    }

    void Renderable::set(Mesh* mesh, ShaderProgram* shader, Texture* diff,
	    Texture* norm, Texture* spec, Vec3f pos, Vec3f scle, QuatF rot)
    {
	pMesh = mesh;
	position = pos;
	scale = scle;
	rotation = rot;
	pShader = shader;
	pTexDiffuse = diff;
	pTexNormal = norm;
	pTexSpecular = spec;
    }
}
