//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef SCENENODEOBJECT_H_
#define SCENENODEOBJECT_H_

#include "DBGL/Math/Matrix4x4.h"

namespace dbgl
{
    /**
     * @brief Abstract base class for objects associated with a scene node
     */
    class SceneNodeObject
    {
	public:
	    /**
	     * @brief Destructor
	     */
	    virtual ~SceneNodeObject() = 0;
	    /**
	     * @return The transform applied by this object (relative to parent)
	     */
	    virtual Mat4f const& getTransform() = 0;
	    /**
	     * @brief Updates this object
	     * @param transform Accumulated transforms of all parent objects and
	     * 			this object
	     */
	    virtual void update(Mat4f transform) = 0;
    };
}

#endif /* SCENENODEOBJECT_H_ */
