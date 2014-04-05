//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef TRANSFORMENTITYCOMPONENT_H_
#define TRANSFORMENTITYCOMPONENT_H_

#include "EntityComponent.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"

namespace dbgl
{
    /**
     * @brief Entity component holding all transform information
     */
    class TransformEntityComponent: public EntityComponent
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~TransformEntityComponent();
	    /**
	     * @brief Initializes this component
	     * @param pos Initial position
	     * @param scale Initial scale
	     * @param rot Initial rotation
	     */
	    void init(Vec3f pos, Vec3f scale, QuatF rot);
	    /**
	     * @return Reference to position
	     */
	    Vec3f& position();
	    /**
	     * @return Reference to scale
	     */
	    Vec3f& scale();
	    /**
	     * @return Reference to rotation
	     */
	    QuatF& rotation();
	    /**
	     * @brief Updates all components
	     * @param deltaTime Time since last update
	     */
	    virtual void update(std::map<std::type_index, EntityComponent*> const& components, double deltaTime);
	private:
	    Vec3f m_position = Vec3f(0, 0, 0);
	    Vec3f m_scale = Vec3f(1, 1, 1);
	    QuatF m_rotation = QuatF(0, 0, 0, 1);
    };
}

#endif /* TRANSFORMENTITYCOMPONENT_H_ */
