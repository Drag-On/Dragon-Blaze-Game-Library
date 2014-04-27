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
#include <limits>
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Utility.h"

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
	     * @param data All components as a vector in order x, y, z, w
	     */
	    Quaternion(Vector4<T> const& data);
	    /**
	     * @brief Constructor
	     * @param axis Axis to rotate around
	     * @param angle Angle in radians
	     */
	    Quaternion(Vector3<T> const& axis, T angle);
	    /**
	     * @brief Constructor
	     * @param angles Angles around x, y and z in radians
	     */
	    Quaternion(Vector3<T> const& angles);
	    /**
	     * @brief Constructs a quaternion such that it rotates start onto dest
	     * @param start Start vector
	     * @param end End vector
	     */
	    Quaternion(Vector3<T> const& start, Vector3<T> const& dest);
	    /**
	     * @brief Constructs a quaternion such that it rotates start onto dest,
	     * 	      preserving up
	     * @param start Start vector
	     * @param end End vector
	     * @param up Up vector
	     */
	    Quaternion(Vector3<T> const& start, Vector3<T> const& dest, Vector3<T> const& up);
	    /**
	     * @brief Copy constructor
	     * @param other Quaternion to copy
	     */
	    Quaternion(Quaternion<T> const& other);
	    /**
	     * @return Reference to x value
	     */
	    T& x();
	    /**
	     * @return Reference to x value
	     */
	    const T& x() const;
	    /**
	     * @return Reference to y value
	     */
	    T& y();
	    /**
	     * @return Reference to y value
	     */
	    const T& y() const;
	    /**
	     * @return Reference to z value
	     */
	    T& z();
	    /**
	     * @return Reference to z value
	     */
	    const T& z() const;
	    /**
	     * @return Reference to w value
	     */
	    T& w();
	    /**
	     * @return Reference to w value
	     */
	    const T& w() const;
	    /**
	     * @brief Initializes this quaternion from an axis and an angle
	     * @param axis Axis to rotate around
	     * @param angle Angle in radians
	     * @returns Reference to this quaternion
	     */
	    Quaternion<T>& fromAngleAxis(Vector3<T> axis, T angle);
	    /**
	     * @brief Initializes this quaternion from an angles around x, y and z
	     * @param angles Angles around x, y and z in radians
	     * @returns Reference to this quaternion
	     */
	    Quaternion<T>& fromAngles(Vector3<T> const& angles);
	    /**
	     * @brief Initializes this quaternion such that it rotates start onto dest
	     * @param start Start vector
	     * @param end End vector
	     * @returns Reference to this quaternion
	     */
	    Quaternion<T>& fromVectors(Vector3<T> start, Vector3<T> dest);
	    /**
	     * @brief Initializes this quaternion such that it rotates start onto dest,
	     * 	      preserving up
	     * @param start Start vector
	     * @param end End vector
	     * @param up Up vector
	     * @returns Reference to this quaternion
	     */
	    Quaternion<T>& fromVectors(Vector3<T> start, Vector3<T> dest,
		    Vector3<T> up);
	    /**
	     * @brief Checks, if this quaternion is similar to the passed one
	     * @param other Other quaternion
	     * @param precision How close they need to be
	     * @return True in case they are similar, oherwise false
	     */
	    bool isSimilar(Quaternion<T> const& other,
		    double precision = 0.1) const;
	    /**
	     * @brief Checks, if this quaternion resembles a similar rotation to other
	     * @param other Other quaternion
	     * @param precision How close they need to be
	     * @return True in case they are similar, oherwise false
	     */
	    bool isSimilarRot(Quaternion<T> const& other,
		    double precision = 0.1) const;
	    /**
	     * @brief Checks if this is a unit quaternion
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
	     * @return A conjugated copy
	     */
	    Quaternion<T> getConjugated() const;
	    /**
	     * @brief Conjugates this quaternion
	     * @return Reference to this quaternion
	     */
	    Quaternion<T>& conjugate();
	    /**
	     * @return An inverted copy of this quaternion
	     */
	    Quaternion<T> getInverted() const;
	    /**
	     * @brief Inverts this quaternion
	     * @return Reference to this quaternion
	     */
	    Quaternion<T>& invert();
	    /**
	     * @brief Calculates the dot product
	     * @param rhs Other quaternion to calculate dot product with
	     * @return Result of dot product
	     */
	    const T dot(Quaternion<T> const& rhs) const;
	    /**
	     * @brief Calculates the cross product
	     * @param rhs Other quaternion to calculate cross product with
	     * @return Result of cross product
	     */
	    Quaternion<T> cross(Quaternion<T> const& rhs) const;
	    /**
	     * @brief Linear interpolation of two quaternions
	     * @param other Quaternion to interpolate with
	     * @param factor Factor of interpolation in the [0, 1] range
	     * @return A new quaternion interpolated out of this one and other
	     * @details The interpolation is oriented. If a factor out of range is
	     * 	       passed, a warning is written to LOG and it is cropped to
	     * 	       the closest number (0 or 1).
	     */
	    Quaternion<T> lerp(Quaternion<T> const& other, T factor) const;
	    /**
	     * @brief Sperical linear interpolation of two quaternions
	     * @param other Quaternion to interpolate with
	     * @param factor Factor of interpolation, defined for any real
	     * @return A new quaternion interpolated out of this one and other
	     * @details This method guarantees to always use the shortest path
	     * 	       for the interpolation. Constant speed.
	     */
	    Quaternion<T> slerp(Quaternion<T> const& other, T factor) const;
	    /**
	     * @brief Interpolates this quaternion so that it becomes more similar to other
	     * @param other Rotation to interpolate to
	     * @param maxAngle Maximum angle to rotate by
	     * @returns Reference to this quaternion
	     */
	    Quaternion<T>& rotateTowards(Quaternion<T> other, T maxAngle);
	    /**
	     * @brief Standard assignment operator
	     */
	    Quaternion<T>& operator=(Quaternion<T> const& rhs);
	    /**
	     * @brief Standard quaternion addition
	     */
	    const Quaternion<T> operator+(Quaternion<T> const& rhs) const;
	    /**
	     * @brief Standard quaternion addition
	     */
	    Quaternion<T>& operator+=(Quaternion<T> const& rhs);
	    /**
	     * @brief Standard quaternion subtraction
	     */
	    const Quaternion<T> operator-(Quaternion<T> const& rhs) const;
	    /**
	     * @brief Standard quaternion subtraction
	     */
	    Quaternion<T>& operator-=(Quaternion<T> const& rhs);
	    /**
	     * @brief Standard quaternion multiplication
	     */
	    const Quaternion<T> operator*(Quaternion<T> const& rhs) const;
	    /**
	     * @brief Rotates the vector by this quaternion
	     */
	    const Vector3<T> operator*(Vector3<T> const& rhs) const;
	    /**
	     * @brief Rotates the vector by this quaternion
	     */
	    const Vector4<T> operator*(Vector4<T> const& rhs) const;
	    /**
	     * @brief Standard quaternion multiplication
	     */
	    const Quaternion<T> operator*(T const& rhs) const;
	    /**
	     * @brief Standard quaternion multiplication
	     */
	    Quaternion<T>& operator*=(Quaternion<T> const& rhs);
	    /**
	     * @brief Standard quaternion multiplication
	     */
	    Quaternion<T>& operator*=(T const& rhs);
	    /**
	     * @brief Standard quaternion multiplication
	     */
	    const Quaternion<T> operator/(T const& rhs) const;
	    /**
	     * @brief Standard quaternion multiplication
	     */
	    Quaternion<T>& operator/=(T const& rhs);
	    /**
	     * @brief Inverts the sign of all values
	     * @warning This is not the same as conjugate()!
	     */
	    Quaternion<T> operator-() const;
	    /**
	     * @brief Checks for equal values
	     */
	    bool operator==(Quaternion<T> const& rhs) const;
	    /**
	     * @brief Checks for equal values
	     */
	    bool operator!=(Quaternion<T> const& rhs) const;
	    /**
	     * @brief Converts to rotation matrix
	     */
	    operator Matrix4x4<T>() const;
	private:
	    Vector4<T> m_data;
    };

    // Some default types
    /**
     * @brief Quaternion of integers
     */
    using QuatI = Quaternion<int>;
    /**
     * @brief Quaternion of floats
     */
    using QuatF = Quaternion<float>;
    /**
     * @brief Quaternion of doubles
     */
    using QuatD = Quaternion<double>;
}

#include "Quaternion.imp"

#endif /* QUATERNION_H_ */
