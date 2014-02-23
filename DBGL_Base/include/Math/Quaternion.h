//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <cmath>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

namespace dbgl
{
    /**
     * @brief Quaternions can be used wonderfully to represent rotations
     */
    template<typename T> class Quaternion
    {
	public:
	    /**
	     * @brief Constructor
	     * @param x Quaternion x component
	     * @param y Quaternion y component
	     * @param z Quaternion z component
	     * @param w Quaternion w component
	     */
	    Quaternion(T x = 0, T y = 0, T z = 0, T w = 1);
	    /**
	     * @brief Constructor
	     * @param data All components as a vector
	     */
	    Quaternion(Vector4<T> data);
	    /**
	     * @brief Constructor
	     * @param axis Axis to rotate around
	     * @param angle Angle in radians
	     */
	    Quaternion(Vector3<T> axis, T angle);
	    /**
	     * @brief Constructor
	     * @param angles Angles around x, y and z
	     */
	    Quaternion(Vector3<T> angles);
	    /**
	     * @brief Checks if this is a unit quaternion and does no rotation at all
	     * @return True in case it's unit, otherwise false
	     */
	    bool isUnit();
	    /**
	     * @brief Converts this quaternion to a rotation matrix
	     * @return The matrix executing the same rotation as this quaternion
	     */
	    Matrix4x4<T> getMatrix();
	    /**
	     * @brief Converts this quaternion into euler angles
	     * @return Euler angles executing the same rotation as this quaternion
	     */
	    Vector3<T> getAngles();
	private:
	    Vector4<T> _data;
    };

    // Some default types
    using QuatI = Quaternion<int>;
    using QuatF = Quaternion<float>;
    using QuatD = Quaternion<double>;
}

#include "Quaternion.imp"

#endif /* QUATERNION_H_ */
