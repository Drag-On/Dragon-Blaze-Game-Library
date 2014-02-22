//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"

namespace dbgl
{
    /**
     * @brief Works as a camera
     */
    class Camera
    {
	public:
	    /**
	     * @brief Constructor
	     * @param position Camera position
	     * @param target Target position to focus
	     * @param up Vector defining where "up" is
	     * @param fieldOfView Opening angle
	     * @param near Near clipping plane
	     * @param far Far clipping plane
	     */
	    Camera(Vec3f position, Vec3f target, Vec3f up, float fieldOfView, float near, float far);
	    ~Camera();
	    /**
	     * @return Position
	     */
	    Vec3f& position();
	    /**
	     * @return Target
	     */
	    Vec3f& target();
	    /**
	     * @return Up vector
	     */
	    Vec3f& up();
	    /**
	     * @return Opening angle
	     */
	    float getFieldOfView() const;
	    /**
	     * @param fieldOfView New opening angle
	     */
	    void setFieldOfView(float fieldOfView);
	    /**
	     * @return Near clipping plane
	     */
	    float getNear() const;
	    /**
	     * @param near New near clipping plane
	     */
	    void setNear(float near);
	    /**
	     * @return Far clipping plane
	     */
	    float getFar() const;
	    /**
	     * @param far New far clipping plane
	     */
	    void setFar(float far);
	private:
	    Vec3f _position, _target, _up;
	    float _fieldOfView, _near, _far;
    };
}

#endif /* CAMERA_H_ */