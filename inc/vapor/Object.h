/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "Reflection.h"

namespace vapor {

//-----------------------------------//

/**
 * Objects are the root class for types using the reflection services.
 */

class CORE_API Object
{
public:

	Object();

	// Gets the type of the object.
	virtual const Class& getType() const = 0;

	// Serialization fix-up phase.
	virtual void fixUp();
};

//-----------------------------------//

} // end namespace