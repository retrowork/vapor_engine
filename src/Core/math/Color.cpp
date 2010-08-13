/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "vapor/PCH.h"
#include "vapor/math/Color.h"

namespace vapor {

//-----------------------------------//

Color::Color(float r, float g, float b, float a)
	: r(r)
	, g(g)
	, b(b)
	, a(a)
{ }

//-----------------------------------//

Color::Color(int r, int g, int b, int a)
	: r(r/255.0f)
	, g(g/255.0f)
	, b(b/255.0f)
	, a(a/255.0f)
{ }

//-----------------------------------//

Color::Color(const Color& c)
	: r(c.r)
	, b(c.b)
	, g(c.g)
	, a(c.a)
{ }

//-----------------------------------//

bool Color::operator == (const Color& c) const
{
	return (r == c.r)
		&& (g == c.g)
		&& (b == c.b)
		&& (a == c.a); 
}

//-----------------------------------//

bool Color::nearEqual(const Color& a, float tolerance )
{
	return (fabs(a.r - r) < tolerance)
		&& (fabs(a.g - g) < tolerance)
		&& (fabs(a.b - b) < tolerance);
}

//-----------------------------------//

Color Color::operator * (float s) const
{
	return Color(r*s, g*s, b*s, a); 
}

//-----------------------------------//

Color::operator Vector3 () const
{
	return Vector3( r, g, b );
}

//-----------------------------------//

const VAPOR_API Color Color::White(1.0f, 1.0f, 1.0f);
const VAPOR_API Color Color::Black(0.0f, 0.0f, 0.0f);
const VAPOR_API Color Color::Red(1.0f, 0.0f, 0.0f);
const VAPOR_API Color Color::Green(0.0f, 1.0f, 0.0f);
const VAPOR_API Color Color::Blue(0.0f, 0.0f, 1.0f);
const VAPOR_API Color Color::NavyBlue(0.0f, 0.0f, 0.5f);
const VAPOR_API Color Color::SkyBlue(0.5f, 0.7f, 1.0f);
const VAPOR_API Color Color::Yellow(1.0f, 1.0f, 0.0f);

//-----------------------------------//

} // end namespace