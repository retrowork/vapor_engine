/************************************************************************
*
* vapor3D Editor � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

class ResourceIndexer;
struct ResourceMetadata;

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class ResourceThumbnailer
{
public:

	ResourceThumbnailer();

	// Sets the resource indexer.
	void setIndexer(ResourceIndexer*);

	// Updates the thumbnailer.
	void update();

	// Generate thumbnail.
	ImagePtr generateMesh(const MeshHandle& mesh);

	Event1<const ResourceMetadata&> onResourceThumbnailed;

protected:

	void onResourceIndexed(const ResourceMetadata&);

	// Sets up the render buffers.
	bool setupRender();

	ResourceIndexer* indexer;

	ScenePtr scene;
	EntityPtr entityCamera;
	CameraPtr camera;
	RenderView* renderView;

	//TexturePtr colorTexture;
	RenderBuffer* renderBuffer;
};

//-----------------------------------//

NAMESPACE_EDITOR_END