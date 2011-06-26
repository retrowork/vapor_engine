/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "Core/Stream.h"
#include "Resources/Resource.h"

namespace vapor {

//-----------------------------------//

#define RESOURCE_LOADER_PREPARE(T)									\
	virtual Resource* prepare(const Stream&) { return Allocate(T, AllocatorGetHeap()); }

/**
 * Resource loaders decode resource data into a proper resource.
 * This is an interface that should be implemented to provide the
 * resource codec services for the formats handled by the loader.
 * The loader also provides the extensions of those formats.
 */

REFLECT_DECLARE_CLASS(ResourceLoader)

class RESOURCE_API ResourceLoader : public Object
{
	DECLARE_UNCOPYABLE(ResourceLoader)
	REFLECT_DECLARE_OBJECT(ResourceLoader)

public:

	ResourceLoader() {}
	virtual ~ResourceLoader() {}

	// Creates the resource with no data.
	// Note: All I/O should be done in 'decode'.
	virtual Resource* prepare(const Stream&) = 0;

	// Decodes a given file into a resource.
	virtual bool decode(const Stream&, Resource* res) = 0;

	// Gets the name of this resource loader.
	virtual const String getName() const = 0;

	// Gets the resource group of this loader.
	virtual ResourceGroup::Enum getResourceGroup() const = 0;

	// Gets a list of recognized extensions by this loader.
	GETTER(Extensions, const std::vector<String>&, extensions);

	std::vector<String> extensions;
};

//-----------------------------------//

} // end namespace