/************************************************************************
*
* vapor3D Editor � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "PCH.h"
#include "ScenePlugin.h"
#include "ScenePage.h"
#include "Editor.h"
#include "EditorIcons.h"

namespace vapor { namespace editor {

//-----------------------------------//

ScenePlugin::ScenePlugin( EditorFrame* frame )
	: Plugin(frame)
	, scenePage(nullptr)
{ }

//-----------------------------------//

PluginMetadata ScenePlugin::getMetadata()
{
	PluginMetadata metadata;
	
	metadata.name = "Scene";
	metadata.description = "Provides a page with the scene contents";
	metadata.author = "triton";
	metadata.version = "1.0";

	return metadata;
}

//-----------------------------------//

void ScenePlugin::onPluginEnable()
{
	wxNotebook* notebookCtrl = editor->getNotebook();
	assert( notebookCtrl != nullptr );

	wxImageList* imageList = notebookCtrl->GetImageList();
	assert( imageList != nullptr );

	wxBitmap iconSitemap = wxMEMORY_BITMAP(sitemap_color);
	iconScene = imageList->Add(iconSitemap);

	scenePage = new ScenePage( editor, notebookCtrl );

	bool scenePageAdded = 
		notebookCtrl->AddPage( scenePage, wxEmptyString/*wxT("Scene")*/,
		true, iconScene );

	if( !scenePageAdded )
		warn( "editor", "Could not add page to notebook" );
}

//-----------------------------------//

void ScenePlugin::onPluginDisable()
{
	removePage( scenePage );
}

//-----------------------------------//

} } // end namespaces