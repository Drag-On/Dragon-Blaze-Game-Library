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
#include "DBGL/Math/Utility.h"

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
	    CameraComponent(float fieldOfView = pi_4(), float near = 0.1f, float far = 100.0f);
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
	    /**
	     * @brief Updates this component
	     * @param deltaTime Time since last update
	     */
	    virtual void update(Entity* owner, double deltaTime);
	    /**
	     * @brief Called upon render process
	     * @param rc RenderContext to draw to
	     */
	    virtual void render(Entity* owner, RenderContext const* rc);
	    /**
	     * @brief Determines whether this component wants to be updated
	     * @return True if needs to be updated, otherwise false
	     */
	    virtual bool needUpdate() const;
	    /**
	     * @brief Determines whether this component wants to be rendered
	     * @return True if needs to be rendered, otherwise false
	     */
	    virtual bool needRender() const;

	private:
	    float m_fieldOfView, m_near, m_far;
    };
}



#endif /* CAMERACOMPONENT_H_ */
