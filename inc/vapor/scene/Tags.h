/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

namespace vapor { namespace scene {

//-----------------------------------//

/**
 * We define some default tags that we need and/or find useful.
 * Note that position 24 to 31 are reserved for internal engine use.
 */

namespace Tags
{
	enum Bitfield
	{
		NonPickable = 24,
		NonCollidable,
		UpdateTransformsOnly
	};
}

//-----------------------------------//

} } // end namespaces