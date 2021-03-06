/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "Math/Vector.h"

NAMESPACE_CORE_BEGIN

//-----------------------------------//

/**
 * Ray class.
 */

class API_CORE Ray
{
public:

	Ray();
	Ray( const Vector3& origin, const Vector3& direction );
	Ray( const Ray& ray );

	// Gets a point on the ray.
	Vector3 getPoint( float distance ) const;

	// Intersects the ray with a triangle.
	bool intersects( const Vector3 (&tri)[3], float& t, float& u, float& v ) const;

public:

	// Point representing the origin of the ray.
	Vector3 origin;

	// Vector representing the direction of the ray.
	Vector3 direction;
};

//-----------------------------------//

NAMESPACE_CORE_END