/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "Core/API.h"
#include "Math/EulerAngles.h"

NAMESPACE_CORE_BEGIN

//-----------------------------------//

EulerAngles::EulerAngles()
	: x(0)
	, y(0)
	, z(0)
{ }

//-----------------------------------//

EulerAngles::EulerAngles( float x, float y, float z )
	: x(x)
	, y(y)
	, z(z)
{ }

//-----------------------------------//

EulerAngles::EulerAngles( const EulerAngles& ang )
	: x(ang.x)
	, y(ang.y)
	, z(ang.z)
{ }

//-----------------------------------//

EulerAngles& EulerAngles::operator += (const EulerAngles& ang)
{
	x += ang.x;
	y += ang.y;
	z += ang.z;

	return *this;
}

//-----------------------------------//

EulerAngles& EulerAngles::operator += (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

//-----------------------------------//

void EulerAngles::rotate( float x, float y, float z )
{
	x += x;
	y += y;
	z += z;
}

//-----------------------------------//

void EulerAngles::identity()
{
	x = y = z = 0;
}

//-----------------------------------//

NAMESPACE_CORE_END