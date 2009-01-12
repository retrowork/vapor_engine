/************************************************************************
*
* vaporEngine by triton � (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
* DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
* Version 2, December 2004
* 
* DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
* TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
* 
* 0. You just DO WHAT THE FUCK YOU WANT TO.
*
************************************************************************/

#pragma once

namespace vapor {
	namespace math {

/////////////////////////////////////////////////////////////////////////////
// VECTOR CLASS TEMPLATE
/////////////////////////////////////////////////////////////////////////////

template <typename T>
class Vector3T
{

public:

	T x, y, z;

	// Default empty constructor
	Vector3T ()
	{ }
	
	// Copy constructor
	Vector3T (const Vector3T<T> &v)
		: x(v.x), y(v.y), z(v.z)
	{ }

	// Constructs a vector from 3 values
	Vector3T (const T a, const T b, const T c)
		: x(a), y(b), z(c)
	{ }
	
	// Assignment
	Vector3T &operator = (const Vector3T<T> &v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	}

	// Equality
	bool operator == (const Vector3T<T> &v) const
	{
		return (x == v.x) && (y == v.y) && (z == v.z); 
	}

	// Inequality
    bool operator != (const Vector3T<T> &v) const
	{
		return (x != v.x) || (y != v.y) || (z != v.z);
	}

	// Addition combined
	Vector3T &operator += (const Vector3T<T> &v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	// Subtraction combined
	Vector3T &operator -= (const Vector3T<T> &v) 
	{
		x -= v.x; y -= v.y;	z -= v.z;
		return *this;
	}

	// Multiplication by a scalar combined
	Vector3T &operator *= (float s) {
		x *= s;	y *= s;	z *= s;
		return *this;
	}

	// Division by a scalar combined
	Vector3T &operator /= (float s) 
	{
		//TODO: gcc fails here
		//assert(s != 0);
		*this *= 1.0f / s;
		return *this;
	}
	
	// Unary minus
	Vector3T operator - () const	{ return Vector3T(-x, -y, -z); }

	// Binary addition
	Vector3T operator + (const Vector3T<T> &v) const { return Vector3T(x+v.x, y+v.y, z+v.z); }

	// Binary subtraction
	Vector3T operator - (const Vector3T<T> &v) const { return Vector3T(x-v.x, y-v.y, z-v.z); }
	
	// Multiplication by a scalar
	Vector3T operator * (float s) const { return Vector3T(x*s, y*s, z*s); }

	// Division by a scalar	
	Vector3T operator / (float s) const
	{
		//assert(s != 0);
		float t = 1.0f / s;
		return Vector3T(x*t, y*t, z*t);
	}

	// Zeroes the vector
	void zero() { x = y = z = 0.0f; }

	// Gets the length of the vector
	// TODO: std::sqrt GCC fail
	T length() const { return sqrt(x*x + y*y + z*z); }
	
	// Normalize the vector
	void normalize() 
	{
		T len = length();

		if (len > 0.0f) // check for divide-by-zero
		{
			x /= len; y /= len; z /= len; 
		}
	}

	// special points
        //static const Vector3 ZERO;
        //static const Vector3 UNIT_X;
        //static const Vector3 UNIT_Y;
        //static const Vector3 UNIT_Z;
        //static const Vector3 NEGATIVE_UNIT_X;
        //static const Vector3 NEGATIVE_UNIT_Y;
        //static const Vector3 NEGATIVE_UNIT_Z;
        //static const Vector3 UNIT_SCALE;

};

/////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS
/////////////////////////////////////////////////////////////////////////////

typedef Vector3T<float> Vector3;
typedef Vector3T<double> Vector3d;

typedef Vector3 Vertex;

} } // end namespaces