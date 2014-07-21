//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef CAMERACOMPONENT_H_
#define CAMERACOMPONENT_H_

#include "Entity.h"

namespace dbgl
{
    /**
     * @brief Camera that can be attached to any entity (should also have a transform component for obvious reasons)
     */
    class CameraComponent : public Entity::Component
    {
	public:
	    /**
	     * @brief Constructor
	     * @param fieldOfView Opening angle
	     * @param near Near clipping plane
	     * @param far Far clipping plane
	     */
	    CameraComponent(float fieldOfView = 2.0943951f, float near = 0.1f, float far = 100.0f);
	    /**
	     * @brief Provides access to the opening angle
	     * @return Reference to the opening angle variable
	     */
	    float& fieldOfView();
	    /**
	     * @brief Provides read access to the opening angle
	     * @return Reference to the opening angle variable
	     */
	    float const& fieldOfView() const;
	    /**
	     * @brief Provides access to the near clipping plane
	     * @return Reference to the near clipping plane variable
	     */
	    float& near();
	    /**
	     * @brief Provides read access to the near clipping plane
	     * @return Reference to the near clipping plane variable
	     */
	    float const& near() const;
	    /**
	     * @brief Provides access to the far clipping plane
	     * @return Reference to the far clipping plane variable
	     */
	    float& far();
	    /**
	     * @brief Provides read access to the far clipping plane
	     * @return Reference to the far clipping plane variable
	     */
	    float const& far() const;

	private:
	    float m_fieldOfView, m_near, m_far;
    };
}



#endif /* CAMERACOMPONENT_H_ */
