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
#include "Math/Quaternion.h"

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
	     * @param direction Direction to look at
	     * @param up Vector defining where "up" is
	     * @param fieldOfView Opening angle
	     * @param near Near clipping plane
	     * @param far Far clipping plane
	     */
	    Camera(Vec3f position, Vec3f direction, Vec3f up, float fieldOfView, float near, float far);
	    /**
	     * @brief Constructor
	     * @param position Camera position
	     * @param orientation Initial camera rotation
	     * @param fieldOfView Opening angle
	     * @param near Near clipping plane
	     * @param far Far clipping plane
	     */
	    Camera(Vec3f position, QuatF orientation, float fieldOfView, float near, float far);
	    /**
	     * @brief Destructor
	     */
	    ~Camera();
	    /**
	     * @return Position
	     */
	    Vec3f& position();
	    /**
	     * @return Rotation
	     */
	    QuatF& rotation();
	    /**
	     * @brief Provides vectors pointing from the camera towards the target and up.
	     * 	      They are copied into the provided arguments
	     * @details One or more arguments may be passed as NULL
	     * @param direction Pointing from the camera to the target
	     * @param up Defines the up direction of the camera
	     * @param right Pointing to the right of the camera
	     */
	    void getOrientation(Vec3f* direction, Vec3f* up, Vec3f* right) const;
	    /**
	     * @param Modifies this cams orientation by using vectors
	     * @param direction New direction
	     * @param up Up vector
	     */
	    void setOrientation(Vec3f const& direction, Vec3f const& up);
	    /**
	     * @brief Rotates the camera relative to it's current orientation
	     * @param horizontal Amount to rotate on left-right-axis
	     * @param vertical Amount to rotate on up-down-axis
	     */
	    void rotate(float horizontal, float vertical);
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
	    Vec3f _position;
	    QuatF _rotation;
	    float _fieldOfView, _near, _far;
    };
}

#endif /* CAMERA_H_ */
