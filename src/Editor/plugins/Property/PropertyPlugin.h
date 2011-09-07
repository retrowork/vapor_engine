/************************************************************************
*
* vapor3D Editor � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "EditorPlugin.h"

#ifdef ENABLE_PLUGIN_PROPERTY

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class PropertyPage;

REFLECT_DECLARE_CLASS(PropertyPlugin)

class PropertyPlugin : public EditorPlugin
{
	REFLECT_DECLARE_OBJECT(PropertyPlugin)

public:

	PropertyPlugin();

	// Gets metadata about this plugin.
	PluginMetadata getMetadata() OVERRIDE;

	// Plugin callbacks.
	void onPluginEnable() OVERRIDE;
	void onPluginDisable() OVERRIDE;

	// Entity callbacks.
	void onEntitySelect( const EntityPtr& ) OVERRIDE;
	void onEntityUnselect( const EntityPtr& ) OVERRIDE;
	void onSceneUnload( const ScenePtr& ) OVERRIDE;

	// Component callbacks.
	void onComponentSelect( const ComponentPtr& ) OVERRIDE;
	void onComponentUnselect( const ComponentPtr& ) OVERRIDE;
	void onComponentChanged(const ComponentPtr& );
	
	// Resource callbacks.
	void onResourceSelect( const ResourcePtr& ) OVERRIDE;
	void onResourceUnselect( const ResourcePtr& ) OVERRIDE;

	// Updates the properties.
	void updateProperties(const EntityPtr& entity);

	PropertyPage* propertyPage;
};

//-----------------------------------//

NAMESPACE_EDITOR_END

#endif