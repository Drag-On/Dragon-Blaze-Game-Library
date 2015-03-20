//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2015 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_DBGL_RENDERER_ENTITY_IGAMECOMPONENT_H_
#define INCLUDE_DBGL_RENDERER_ENTITY_IGAMECOMPONENT_H_

namespace dbgl
{
	/**
	 * @brief Interface class for all entity components
	 */
	class IGameComponent
	{
	public:
		/**
		 * @brief Destructor
		 */
		virtual ~IGameComponent() = default;
		/**
		 * @brief Update the component
		 */
		virtual void update() = 0;
	};
}

#endif /* INCLUDE_DBGL_RENDERER_ENTITY_IGAMECOMPONENT_H_ */
