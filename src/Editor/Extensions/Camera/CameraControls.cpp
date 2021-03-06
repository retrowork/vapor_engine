/************************************************************************
*
* vapor3D Editor � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#include "Editor/API.h"
#include "CameraControls.h"
#include "Core/Utilities.h"
#include "DocumentWindow.h"
#include "EditorIcons.h"
#include "Editor.h"
#include "Graphics/RenderView.h"

#ifdef ALL_PLUGINS

NAMESPACE_EDITOR_BEGIN

//-----------------------------------//

CameraControls::CameraControls( 
	EditorFrame* editor, wxWindow* parent, wxWindowID id,
	const wxPoint& pos, const wxSize& size, long style ) 
	: wxPanel(parent, id, pos, size, style)
	, editor(editor)
	, viewframe(nullptr)
{
	buildControls();

	viewframe = (Viewframe*) parent;
	assert( viewframe != nullptr );
	
	setCamera( viewframe->getMainCamera().lock() );
}

//-----------------------------------//

TransformPtr CameraControls::getCameraTransform() const
{
	RenderView* view = viewframe->getView();
	assert( view != nullptr );

	CameraPtr camera = view->getCamera();
	assert( camera != nullptr );

	EntityPtr nodeCamera = camera->getEntity()->getShared();
	assert( nodeCamera != nullptr );

	TransformPtr transCamera = nodeCamera->getTransform();
	assert( transCamera != nullptr );

	return transCamera;
}

//-----------------------------------//

void CameraControls::onCameraSpeedSpin( wxSpinDoubleEvent& event )
{
	float value = event.GetValue();

	RenderView* view = viewframe->getView();
	
	CameraPtr camera( view->getCamera() );
	assert( camera != nullptr );

	EntityPtr nodeCamera = camera->getEntity()->getShared();
	assert( nodeCamera != nullptr );

	CameraControllerPtr cameraController =
		nodeCamera->getComponentFromFamily<CameraController>();
	
	cameraController->setMoveSensivity( value );
}

//-----------------------------------//

void CameraControls::updateCameraSpeedSpin()
{
	RenderView* view = viewframe->getView();
	const CameraPtr& camera = view->getCamera();

	EntityPtr entity = camera->getEntity()->getShared();
	CameraControllerPtr controller = entity->getComponentFromFamily<CameraController>();

	if( !controller )
		return;

	float cameraMoveSensivity = controller->getMoveSensivity();
	spinCameraSpeed->SetValue( cameraMoveSensivity );
}

//-----------------------------------//

void CameraControls::getCamerasInScene(const ScenePtr& scene)
{
	const std::vector<EntityPtr>& entities = scene->getEntities();

	for(uint i = 0; i < entities.size(); i++)
	{
		EntityPtr entity = entities[i];
		CameraPtr camera = entity->getComponent<Camera>();
		
		if(!camera) continue;
		
		const String& name = entity->getName();
		cameras[name] = camera;
	}
}

//-----------------------------------//

void CameraControls::updateCameraSelection()
{
	cameras.clear();

	choiceView->Clear();

	Engine* engine = GetEditor().getEngine();
	getCamerasInScene(engine->getSceneManager());
	getCamerasInScene(editor->getEditorScene());

	wxArrayString choices;

	choices.Add("Free");
	choices.Add("Top");
	choices.Add("Down");
	choices.Add("Left");
	choices.Add("Right");

	choiceView->Append(choices);

	CameraMap::const_iterator it;
	for(it = cameras.begin(); it != cameras.end(); ++it)
	{
		int n = choiceView->Append(it->first);
		choiceView->SetClientData(n, (void*) &it->second);
	}

	const CameraPtr& currentCamera = viewframe->getView()->getCamera();
	const String& name = currentCamera->getEntity()->getName();
	choiceView->SetStringSelection(name);
}

//-----------------------------------//

void CameraControls::onCameraChoice( wxCommandEvent& event )
{
	void* object = choiceView->GetClientData( event.GetSelection() );
	
	if( !object )
		return;

	CameraPtr* camera = (CameraPtr*) object;
	setCamera(*camera);
}

//-----------------------------------//

void CameraControls::setCamera(const CameraPtr& camera)
{
	if(currentCamera)
	{
		TransformPtr transform = currentCamera->getEntity()->getTransform();
		transform->onTransform.Disconnect( this, &CameraControls::onCameraTransform );
	}

	RenderView* view = viewframe->getView();
	view->setCamera(camera);

	currentCamera = camera;

	TransformPtr transform = camera->getEntity()->getTransform();
	transform->onTransform.Connect( this, &CameraControls::onCameraTransform );

	onCameraTransform();
	updateCameraSpeedSpin();
	updateCameraSelection();
}

//-----------------------------------//

void CameraControls::onCameraTransform()
{
	// We need to switch to a neutral locale or else the text
	// conversion will lead to different results depending on
	// each machine due to different locale settings.

	LocaleSwitch locale;
	
	TransformPtr transCamera = getCameraTransform();
	Vector3 position = transCamera->getPosition();
	
	String str;
	
	str = String::fromFloat( position.x );
	textX->ChangeValue( str );
	
	str = String::fromFloat( position.y );
	textY->ChangeValue( str );
	
	str = String::fromFloat( position.z );
	textZ->ChangeValue( str );
}

//-----------------------------------//

void CameraControls::updateCameraPosition()
{
	String str( textX->GetValue() );
	float X = String::toNumber<float>( str );
	
	str.assign( textY->GetValue() );
	float Y = String::toNumber<float>( str );
	
	str.assign( textZ->GetValue() );
	float Z = String::toNumber<float>( str );

	TransformPtr transCamera = getCameraTransform();
	transCamera->setPosition( Vector3(X, Y, Z) );
}

//-----------------------------------//

void CameraControls::onTextEnter( wxCommandEvent& event )
{
	updateCameraPosition();
}

//-----------------------------------//

void CameraControls::buildControls()
{
	const short BAR_HEIGHT = 20;

	wxBoxSizer* sizer = new wxBoxSizer( wxHORIZONTAL );

	const wxString includes( "0123456789." );
	
	// X axis.
	wxStaticText* labelX;
	labelX = new wxStaticText( this, wxID_ANY, wxT("X:") );
	sizer->Add( labelX, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	wxTextValidator validatorX(wxFILTER_INCLUDE_CHAR_LIST, &X);
	validatorX.SetCharIncludes( includes );
	
	textX = new wxTextCtrl( this, wxID_ANY, wxT("0.0"),
		wxDefaultPosition, wxSize(50, BAR_HEIGHT),
		wxTE_CENTRE | wxTE_PROCESS_ENTER, validatorX);

	textX->Bind(wxEVT_COMMAND_TEXT_ENTER, &CameraControls::onTextEnter, this);

	sizer->Add( textX, 0, wxALIGN_CENTER_VERTICAL, 5 );

	// Y axis.
	wxStaticText* labelY;
	labelY = new wxStaticText( this, wxID_ANY, wxT("Y:") );
	sizer->Add( labelY, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );

	wxTextValidator validatorY(wxFILTER_INCLUDE_CHAR_LIST, &Y);
	validatorY.SetCharIncludes( includes );

	textY = new wxTextCtrl( this, wxID_ANY, wxT("0.0"),
		wxDefaultPosition, wxSize(50, BAR_HEIGHT),
		wxTE_CENTRE | wxTE_PROCESS_ENTER, validatorY);

	textY->Bind(wxEVT_COMMAND_TEXT_ENTER, &CameraControls::onTextEnter, this);
	sizer->Add( textY, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	// Z axis.
	wxStaticText* labelZ;
	labelZ = new wxStaticText( this, wxID_ANY, wxT("Z:") );
	sizer->Add( labelZ, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	wxTextValidator validatorZ(wxFILTER_INCLUDE_CHAR_LIST, &Z);
	validatorZ.SetCharIncludes( includes );
	
	textZ = new wxTextCtrl( this, wxID_ANY, wxT("0.0"),
		wxDefaultPosition, wxSize(50, BAR_HEIGHT),
		wxTE_CENTRE | wxTE_PROCESS_ENTER, validatorZ);

	textZ->Bind(wxEVT_COMMAND_TEXT_ENTER, &CameraControls::onTextEnter, this);
	sizer->Add( textZ, 0, wxALIGN_CENTER_VERTICAL, 5 );
	
	// Static line.
	wxStaticLine* staticLine;
	staticLine = new wxStaticLine( this, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxLI_VERTICAL );
	sizer->Add( staticLine, 0, wxEXPAND|wxALL, 5 );

	wxStaticText* labelSpeed;
	labelSpeed = new wxStaticText( this, wxID_ANY, wxT("Speed:") );
	sizer->Add( labelSpeed, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );

	// Camera spin button.
	spinCameraSpeed = new wxSpinCtrlDouble( this, wxID_ANY,
		wxEmptyString, wxDefaultPosition, wxSize(60, BAR_HEIGHT) );
	
	spinCameraSpeed->Bind(wxEVT_COMMAND_SPINCTRLDOUBLE_UPDATED,
		&CameraControls::onCameraSpeedSpin, this);

	spinCameraSpeed->SetRange(0.0f, 1000.0f);
	spinCameraSpeed->SetIncrement(10.0f);
	
	sizer->Add( spinCameraSpeed, 0, wxALIGN_CENTER_VERTICAL, 5 );

	// Camera spin button.
	wxBitmap iconWireframe = wxMEMORY_BITMAP(grid_icon_small);
	buttonWireframe = new wxBitmapButton( this, wxID_ANY, iconWireframe,
		wxDefaultPosition, wxSize(-1, BAR_HEIGHT-1), wxBU_AUTODRAW );
	sizer->Add( buttonWireframe, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	
	wxBitmap iconTextures = wxMEMORY_BITMAP(map_small);
	buttonTextures = new wxBitmapButton( this, wxID_ANY, iconTextures,
		wxDefaultPosition, wxSize(-1, BAR_HEIGHT-1), wxBU_AUTODRAW );
	sizer->Add( buttonTextures, 0, wxALIGN_CENTER_VERTICAL, 5 );

	choiceView = new wxChoice( this, wxID_ANY, wxDefaultPosition,
		wxSize(-1, BAR_HEIGHT-1) );
	choiceView->Bind(wxEVT_COMMAND_CHOICE_SELECTED, &CameraControls::onCameraChoice, this);

	sizer->Add( choiceView, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );

	SetSizerAndFit( sizer );
}

//-----------------------------------//

NAMESPACE_EDITOR_END

#endif