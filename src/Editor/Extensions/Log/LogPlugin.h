/************************************************************************
*
* vapor3D Editor © (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "EditorPlugin.h"

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

class LogFrame;

REFLECT_DECLARE_CLASS(LogPlugin)

class LogPlugin : public EditorPlugin
{
	REFLECT_DECLARE_OBJECT(LogPlugin)

public:

	LogPlugin();

	// Gets metadata about this plugin.
	PluginMetadata getMetadata() OVERRIDE;

	// Plugin enable callback.
	void onPluginEnable() OVERRIDE;

	// Plugin disable callback.
	void onPluginDisable() OVERRIDE;

	// Handles new button click.
	void onLogButtonClick(wxCommandEvent& event);

protected:

	// Log toolbar button.
	wxAuiToolBarItem* logButton;

	// Log frame.
	LogFrame* log;
};

//-----------------------------------//

NAMESPACE_EDITOR_END