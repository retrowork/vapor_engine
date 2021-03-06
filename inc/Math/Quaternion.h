/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "Math/Helpers.h"
#include "Math/EulerAngles.h"
#include <cmath>

NAMESPACE_CORE_BEGIN

//-----------------------------------//

/**
 * Represents a quaternion, useful for storing orientations.
 */

struct API_CORE QuaternionP
{
	float x, y, z, w;
};

struct API_CORE Quaternion : public QuaternionP
{
	// Constructors.
	Quaternion () { identity(); }
	Quaternion (const Quaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; }
	Quaternion (float u) { x = u; y = u; z = u; w = u; }
	Quaternion (float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }

	Quaternion(const EulerAngles& angles)
	{
		Quaternion qx, qy, qz;
		
		qx.setToRotateAboutX(MathDegreeToRadian(angles.x));
		qy.setToRotateAboutY(MathDegreeToRadian(angles.y));
		qz.setToRotateAboutZ(MathDegreeToRadian(angles.z));
		
		*this = qx*qy*qz;
	}

	// Assignment
	Quaternion& operator = (const Quaternion& q)
	{
		x = q.x; y = q.y; z = q.z; w = q.w;
		return *this;
	}

	// Equality
	bool operator == (Quaternion& q) const
	{
		return (x == q.x) && (y == q.y) && (z == q.z) && (w == q.w); 
	}
	
	// Inequality
    bool operator != (Quaternion& q) const
	{
		return (x != q.x) || (y != q.y) || (z != q.z) || (w != q.w);
	}

	// Set to identity.
	void identity()
	{
		w = 1.0f;
		x = y = z = 0.0f;
	}

	//---------------------------------------------------------------------------
	// conjugate
	//
	// Compute the quaternion conjugate.  This is the quaternian
	// with the opposite rotation as the original quaternian.  

	Quaternion conjugate(const Quaternion& q)
	{
		Quaternion result;

		// Same rotation amount
		result.w = q.w;

		// Opposite axis of rotation
		result.x = -q.x;
		result.y = -q.y;
		result.z = -q.z;

		// Return it
		return result;
	}

	//---------------------------------------------------------------------------
	// Quaternion::operator *
	//
	// Quaternion cross product, which concatonates multiple angular
	// displacements.  The order of multiplication, from left to right,
	// corresponds to the order that the angular displacements are
	// applied.  This is backwards from the *standard* definition of
	// quaternion multiplication.  See section 10.4.8 for the rationale
	// behind this deviation from the standard.

	Quaternion operator *(const Quaternion& a) const
	{
		Quaternion result;

		result.w = w*a.w - x*a.x - y*a.y - z*a.z;
		result.x = w*a.x + x*a.w + z*a.y - y*a.z;
		result.y = w*a.y + y*a.w + x*a.z - z*a.x;
		result.z = w*a.z + z*a.w + y*a.x - x*a.y;

		return result;
	}

	//---------------------------------------------------------------------------
	// Quaternion::operator *=
	//
	// Combined cross product and assignment, as per C++ convention

	Quaternion& operator *=(const Quaternion& a)
	{
		// Multiply and assign
		*this = *this * a;

		// Return reference to l-value
		return *this;
	}

	// Gets the magnitude of the quaternion
	float magnitude() const { return std::sqrt(x*x + y*y + z*z + w*w); }

	//---------------------------------------------------------------------------
	// Quaternion::normalize
	//
	// "Normalize" a quaternion.  Note that normally, quaternions
	// are always normalized (within limits of numerical precision).
	// See section 10.4.6 for more information.
	//
	// This function is provided primarily to combat floating point "error
	// creep," which can occur when many successive quaternion operations
	// are applied.

	void normalize()
	{
		// Compute magnitude of the quaternion
		float mag = magnitude();

		// Check for bogus length, to protect against divide by zero
		if (mag > 0.0f)
		{
			// Normalize it
			float oneOverMag = 1.0f / mag;
			w *= oneOverMag;
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		} 
	}

	//---------------------------------------------------------------------------
	// Quaternion::setToRotateAboutX
	// Quaternion::setToRotateAboutY
	// Quaternion::setToRotateAboutZ
	// Quaternion::setToRotateAboutAxis
	//
	// Setup the quaternion to rotate about the specified axis

	void setToRotateAboutX(float theta)
	{
		// Compute the half angle
		float thetaOver2 = theta * .5f;

		// Set the values
		w = cosf(thetaOver2);
		x = sinf(thetaOver2);
		y = 0.0f;
		z = 0.0f;
	}

	//-----------------------------------//

	void setToRotateAboutY(float theta)
	{
		// Compute the half angle
		float thetaOver2 = theta * .5f;

		// Set the values
		w = cosf(thetaOver2);
		x = 0.0f;
		y = sinf(thetaOver2);
		z = 0.0f;
	}

	//-----------------------------------//

	void setToRotateAboutZ(float theta)
	{
		// Compute the half angle
		float thetaOver2 = theta * .5f;

		// Set the values
		w = cosf(thetaOver2);
		x = 0.0f;
		y = 0.0f;
		z = sinf(thetaOver2);
	}

	//-----------------------------------//

	void setToRotateAboutAxis(Vector3 &axis, float theta)
	{
		// The axis of rotation must be normalized
		if ((axis.length() - 1.0f) > .01f)
			axis.normalize();

		// Compute the half angle and its sin
		float thetaOver2 = theta * .5f;
		float sinThetaOver2 = sinf(thetaOver2);

		// Set the values
		w = cosf(thetaOver2);
		x = axis.x * sinThetaOver2;
		y = axis.y * sinThetaOver2;
		z = axis.z * sinThetaOver2;
	}

	//---------------------------------------------------------------------------
	// safeAcos
	//
	// Same as acos(x), but if x is out of range, it is "clamped" to the nearest
	// valid value.  The value returned is in range 0...pi, the same as the
	// standard C acos() function

	float safeAcos(float x)
	{
		// Check limit conditions
		if (x <= -1.0f) return PI;
		else if (x >= 1.0f) return 0.0f;

		// Value is in the domain - use standard C function
		return acosf(x);
	}

	//---------------------------------------------------------------------------
	// Quaternion::getRotationAngle
	//
	// Return the rotation angle theta

	float getRotationAngle()
	{
		// Compute the half angle.  Remember that w = cos(theta / 2)
		float thetaOver2 = safeAcos(w);

		// Return the rotation angle
		return thetaOver2 * 2.0f;
	}

	//---------------------------------------------------------------------------
	// Quaternion::getRotationAxis
	//
	// Return the rotation axis

	Vector3	getRotationAxis() const
	{
		// Compute sin^2(theta/2).  Remember that w = cos(theta/2),
		// and sin^2(x) + cos^2(x) = 1
		float sinThetaOver2Sq = 1.0f - w*w;

		// Protect against numerical imprecision
		if (sinThetaOver2Sq <= 0.0f)
		{
			// Identity quaternion, or numerical imprecision.  Just
			// return any valid vector, since it doesn't matter

			return Vector3(1.0f, 0.0f, 0.0f);
		}

		// Compute 1 / sin(theta/2)
		float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

		// Return axis of rotation
		return Vector3(
			x * oneOverSinThetaOver2,
			y * oneOverSinThetaOver2,
			z * oneOverSinThetaOver2
		);
	}

	// Dot product.
	float dot(const Quaternion& a)
	{
		return a.w*w + a.x*x + a.y*y + a.z*z;
	}

	// Convert to euler angles.
	EulerAngles getEulerAngles() const;

	// Spherical linear interpolation.
	Quaternion slerp(const Quaternion& q, float t);

	static const Quaternion Identity;
};

//-----------------------------------//

NAMESPACE_CORE_END
