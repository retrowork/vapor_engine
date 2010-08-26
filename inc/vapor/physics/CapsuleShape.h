/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "vapor/physics/Shape.h"

class btCapsuleShape;

namespace vapor {

//-----------------------------------//

class VAPOR_API CapsuleShape : public Shape
{
	DECLARE_CLASS_()

public:

	CapsuleShape();
	virtual ~CapsuleShape();

	// Updates the shape.
	void update( double delta );

	// Gets the internal Bullet shape.
	btCollisionShape* const getBulletShape() const;

protected:

	float height;
	float radius;

	// Bullet box shape.
	btCapsuleShape* capsuleShape;
};

TYPEDEF_SHARED_POINTER_FROM_TYPE( CapsuleShape );
TYPEDEF_SHARED_WEAK_POINTER_FROM_TYPE( CapsuleShape );

//-----------------------------------//

} // end namespace
