/************************************************************************
*
* vapor3D � (2008-2011)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "ResourceProcessor.h"
#include "Resources/Mesh.h"
#include "Resources/Animation.h"
#include "Resources/Skeleton.h"

namespace vapor {

//-----------------------------------//

/**
 * Resource processors handle the processing of resource data.
 */

class PIPELINE_API MeshProcessor : public ResourceProcessor
{
	DECLARE_CLASS_()

public:

	MeshProcessor();

	// Processes the given resource.
	bool Process(const ResourcePtr& resource);

	// Gets the processed resource type.
	const Class& GetResourceType() { return Mesh::getStaticType(); }

private:
};

//-----------------------------------//

} // end namespace