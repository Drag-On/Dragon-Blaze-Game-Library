//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef RENDERCONTEXT_H_
#define RENDERCONTEXT_H_

#include <vector>
#include "Mesh.h"
#include "Viewport.h"
#include "Math/Vector3.h"

namespace dbgl
{
    class RenderContext
    {
	public:
	    template<typename T> void draw(Mesh mesh, Vector3<T> position);
	private:
	    std::vector<Viewport> _viewports;
    };
}

#endif /* RENDERCONTEXT_H_ */
