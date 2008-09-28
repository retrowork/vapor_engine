/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//// 
//// fuckEngine by triton
////
//// License: fuckGNU License
////
//// Changelog:
////	(18/08/08) Initial implementantion
////
//// Thanks to:
////	Zero (love ya bitch)
////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#pragma once

//#include "Engine.h"

namespace vapor {
	namespace math {

/////////////////////////////////////////////////////////////////////////////
// VECTOR CLASS TEMPLATE
/////////////////////////////////////////////////////////////////////////////

template <typename T>
class Vector3 
{

public:

	T x, y, z;

	// Default empty constructor
	Vector3 ()
	{ }
	
	// Copy constructor
	Vector3 (const Vector3<T> &v)
		: x(v.x), y(v.y), z(v.z)
	{ }

	// Constructs a vector from 3 values
	Vector3 (const T a, const T b, const T c)
		: x(a), y(b), z(c)
	{ }
	
	// Assignment
	Vector3 &operator = (const Vector3<T> &v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	}

	// Equality
	bool operator == (const Vector3<T> &v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z); 
	}

	// Inequality
    bool operator != (const Vector3<T> &v) const
	{
		return (x != v.x) || (y != v.y) || (z != v.z);
	}

	// Addition combined
	Vector3 &operator += (const Vector3<T> &v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	// Subtraction combined
	Vector3 &operator -= (const Vector3<T> &v) 
	{
		x -= v.x; y -= v.y;	z -= v.z;
		return *this;
	}

	// Multiplication by a scalar combined
	Vector3 &operator *= (float s) {
		x *= s;	y *= s;	z *= s;
		return *this;
	}

	// Division by a scalar combined
	Vector3 &operator /= (float s) 
	{
		assert(s != 0);
		*this *= 1.0f / s;
		return *this;
	}
	
	// Unary minus
	Vector3 operator - () const	{ return Vector3(-x, -y, -z); }

	// Binary addition
	Vector3	operator + (const Vector3<T> &v) const { return Vector3(x+v.x, y+v.y, z+v.z); }

	// Binary subtraction
	Vector3 operator - (const Vector3<T> &v) const { return Vector3(x-v.x, y-v.y, z-v.z); }
	
	// Multiplication by a scalar
	Vector3 operator * (float s) const { return Vector3(x*s, y*s, z*s); }

	// Division by a scalar	
	Vector3 operator / (float s) const
	{
		assert(s != 0);
		float t = 1.0f / s;
		return Vector3(x*t, y*t, z*t);
	}

	// Zeroes the vector
	void zero() { x = y = z = 0.0f; }

	// Gets the length of the vector
	T length() const { return std::sqrt(x*x + y*y + z*z); }
	
	// Normalize the vector
	void normalize() 
	{
		T len = length();

		if (len > 0.0f) // check for divide-by-zero
		{
			x /= len; y /= len; z /= len; 
		}
	}

};

/////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS
/////////////////////////////////////////////////////////////////////////////

typedef Vector3<float> Vec3f;
typedef Vector3<double> Vec3d;

// Global zero vector constant
//extern const Vec3f vectorZero;

} } // end namespaces