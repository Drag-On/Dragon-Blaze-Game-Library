//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_SCENE_SCENE_H_
#define INCLUDE_DBGL_RENDERER_SCENE_SCENE_H_

#include "DBGL/Core/Collection/Tree/ObjectHierarchy.h"
#include "DBGL/Renderer/Entity/GameEntity.h"

namespace dbgl
{
	class Scene: public ObjectHierarchy<GameEntity>
	{
	public:
		// TODO: Implement scene graph
	};
}

#endif /* INCLUDE_DBGL_RENDERER_SCENE_SCENE_H_ */
