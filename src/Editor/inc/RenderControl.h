/************************************************************************
*
* vapor3D Editor � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include <wx/glcanvas.h>

namespace vapor { namespace editor {

class RenderWindow;
class EditorInputManager;

//-----------------------------------//

/**
 * Let's link vapor with wxWidgets. There are some different approaches
 * that can be used to do this, some more flexible/difficult than others.
 * We create a custom wxWidgets window impementation for vapor3D. This is
 * probably the most difficult approach but also the most flexible since.
 * wxWidgets creates the OpenGL context (wxGLCanvas control) and we can
 * control various attributes of the context.
 */

class RenderControl : public wxGLCanvas 
{
public:

	RenderControl( 	wxWindow* parent, wxWindowID id = wxID_ANY,
					const int* attribList = nullptr,
					const wxPoint& pos	= wxDefaultPosition,
					const wxSize& size = wxDefaultSize,
					long style = 0 | wxFULL_REPAINT_ON_RESIZE | wxSTATIC_BORDER,
					const wxString&	name = "vaporGLCanvas",
					const wxPalette& palette = wxNullPalette );

	// Flag this control to be redrawn.
	void flagRedraw();

	// Starts firing the update and render frame timers.
	void startFrameLoop();

	// Starts firing the update and render frame timers.
	void stopFrameLoop();

	// Gets the associated window.
	GETTER(RenderWindow, RenderWindow*, window)

	// Gets the associated input manager.
	GETTER(InputManager, EditorInputManager*, inputManager)

	// Add your frame updating code here.
	fd::delegate<void(double)> onUpdate;

	// Add your frame rendering code here.
	fd::delegate<void()> onRender;

protected:

	// Handles the update and redraw logic.
	void doUpdate(wxTimerEvent&);
	void doRender(wxTimerEvent&);

	// Window events.
	void OnIdle(wxIdleEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnFocusSet(wxFocusEvent& event);
	void OnFocusKill(wxFocusEvent& event);

	// Input events.
	void OnKeyDown(wxKeyEvent& event);
	void OnKeyUp(wxKeyEvent& event);
	void OnMouseEvent(wxMouseEvent& event);
	void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);

	// Timer responsible for update ticks.
	wxTimer frameUpdateTimer;

	// Timer responsible for rendering ticks.
	wxTimer frameRenderTimer;

	// Holds an instance to the engine.
	Engine* engine;

	// Window associated with this control.
	RenderWindow* window;

	// Holds an instance of the input manager.
	EditorInputManager* inputManager;

	// Tracks if the control needs to be redrawn.
	bool needsRedraw;

	DECLARE_EVENT_TABLE()
};

//-----------------------------------//

} } // end namespaces