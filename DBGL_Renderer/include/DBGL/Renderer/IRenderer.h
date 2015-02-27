//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_IRENDERER_H_
#define INCLUDE_DBGL_RENDERER_IRENDERER_H_

#include "DBGL/Renderer/Entity/IRenderEntity.h"
#include "DBGL/Renderer/Entity/ICameraEntity.h"
#include "DBGL/Platform/Window/IWindow.h"

namespace dbgl
{
	/**
	 * @brief Interface class for all renderer implementations
	 */
	class IRenderer
	{
	public:
		/**
		 * @brief Destructor
		 */
		virtual ~IRenderer() = default;
		/**
		 * @brief Adds a new render entity to the renderer's management
		 * @param entity Entity to add
		 * @return True if the entity was added, otherwise false
		 */
		virtual bool addEntity(IRenderEntity* entity) = 0;
		/**
		 * @brief Removes an entity from the renderer
		 * @param entity Entity to remove
		 * @return True if the entity was removed, otherwise false
		 */
		virtual bool removeEntity(IRenderEntity* entity) = 0;
		/**
		 * @brief Sets a new camera entity
		 * @param camera Camera to use for rendering. Set nullptr to disable rendering.
		 */
		virtual void setCameraEntity(ICameraEntity* camera) = 0;
		/**
		 * @brief Renders all entities that have been added
		 * @param rc Context to render to
		 * @note This method does not swap the back buffer
		 */
		virtual void render(IRenderContext* rc) = 0;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_IRENDERER_H_ */
