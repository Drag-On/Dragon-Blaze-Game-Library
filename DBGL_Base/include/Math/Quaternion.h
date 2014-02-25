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
#include "Tools.h"

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
	     * @brief Copy constructor
	     * @param other Quaternion to copy
	     */
	    Quaternion(const Quaternion<T>& other);
	    /**
	     * @brief Checks, if this quaternion is similar to the passed one
	     * @param other Other quaternion
	     * @param precision How close they need to be
	     * @return True in case they are similar, oherwise false
	     */
	    bool isSimilar(Quaternion const& other,
		    double precision = 0.1) const;
	    /**
	     * @brief Checks if this is a unit quaternion and does no rotation at all
	     * @return True in case it's unit, otherwise false
	     */
	    bool isUnit() const;
	    /**
	     * @brief Converts this quaternion to a rotation matrix
	     * @return The matrix executing the same rotation as this quaternion
	     */
	    Matrix4x4<T> getMatrix() const;
	    /**
	     * @brief Converts this quaternion into euler angles
	     * @return Euler angles executing the same rotation as this quaternion
	     */
	    Vector3<T> getAngles() const;
	    /**
	     * @return Squared euklidean length of the underlying vector
	     */
	    T getSquaredLength() const;
	    /**
	     * @return Euklidean length of the underlying vector
	     */
	    T getLength() const;
	    /**
	     * @return A normalized version of this quaternion
	     */
	    Quaternion<T> getNormalized() const;
	    /**
	     * @brief Normalizes this quaternion
	     * @return Reference to this quaternion
	     */
	    Quaternion<T>& normalize();
	    /**
	     * @brief Calculates the dot product
	     * @param rhs Other quaternion to calculate dot product with
	     * @return Dot product
	     */
	    const T dot(Quaternion<T> const& rhs) const;
	    // Operators
	    Quaternion<T>& operator=(Quaternion<T> const& rhs);
	    const Quaternion<T> operator+(Quaternion<T> const& rhs) const;
	    Quaternion<T>& operator+=(Quaternion<T> const& rhs);
	    const Quaternion<T> operator-(Quaternion<T> const& rhs) const;
	    Quaternion<T>& operator-=(Quaternion<T> const& rhs);
	    const Quaternion<T> operator*(Quaternion<T> const& rhs) const;
	    const Quaternion<T> operator*(T const& rhs) const;
	    Quaternion<T>& operator*=(Quaternion<T> const& rhs);
	    Quaternion<T>& operator*=(T const& rhs);
	    const Quaternion<T> operator/(T const& rhs) const;
	    Quaternion<T>& operator/=(T const& rhs);
	    Quaternion<T> operator-() const;
	    bool operator==(Quaternion<T> const& rhs) const;
	    bool operator!=(Quaternion<T> const& rhs) const;
	    T& operator[](std::size_t const& index);
	    const T& operator[](std::size_t const& index) const;
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
