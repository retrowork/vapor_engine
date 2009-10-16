/************************************************************************
*
* vaporEngine (2008-2009)
*
*	<http://www.portugal-a-programar.org>
*
************************************************************************/

#include "vapor/PCH.h"

#include "vapor/scene/FirstPersonCamera.h"

using namespace vapor::input;
using namespace vapor::math;

namespace vapor {
	namespace scene {

//-----------------------------------//

FirstPersonCamera::FirstPersonCamera( input::InputManager* input,
	render::Device* device, Projection::Enum projection )
	: Camera( device, projection ), inputManager( input ), 
	sensivity( 10.0f ), cameraSensivity( 0.001f )
{
	registerCallbacks();	
}

//-----------------------------------//

void FirstPersonCamera::update( double delta )
{
	Camera::update( delta );
	checkControls();
	centerCursor();
}

//-----------------------------------//

void FirstPersonCamera::checkControls()
{
	Keyboard* kbd = inputManager->getKeyboard();
	const std::vector< bool >& state = kbd->getKeyState();

	if( state[Keys::W] == true )
		translate( math::Vector3( 0.0f, 0.0f, 0.1f * sensivity ) );

	if( state[Keys::S] == true )
		translate( math::Vector3( 0.0f, 0.0f, -0.1f * sensivity ) );
	
	if( state[Keys::A] == true )
		translate( math::Vector3( 0.1f * sensivity, 0.0f, 0.0f ) );

	if( state[Keys::D] == true )
		translate( math::Vector3( -0.1f * sensivity, 0.0f, 0.0f ) );
	
	if( state[Keys::Q] == true )
		translate( math::Vector3( 0.0f, -0.1f * sensivity, 0.0f ) );

	if( state[Keys::Z] == true )
		translate( math::Vector3( 0.0f, 0.1f * sensivity, 0.0f ) );
}

//-----------------------------------//

const std::string FirstPersonCamera::name() const
{
	return "FPCamera";
}

//-----------------------------------//

const std::string FirstPersonCamera::save(int ind)
{
	return "camera";
}

//-----------------------------------//

void FirstPersonCamera::setSensivity( float sensivity )
{
	this->sensivity = sensivity;
}

//-----------------------------------//

void FirstPersonCamera::registerCallbacks()
{
	Keyboard* kbd = inputManager->getKeyboard();
	Mouse* mouse = inputManager->getMouse();

	if( kbd )
	{
		kbd->onKeyPress += fd::bind( &FirstPersonCamera::onKeyPressed, this );
	}
	
	if( mouse )
	{
		mouse->onMouseMove += fd::bind( &FirstPersonCamera::onMouseMove, this );
		mouse->onMouseButtonPress += fd::bind( &FirstPersonCamera::onButtonPressed, this );
		mouse->onMouseButtonRelease += fd::bind( &FirstPersonCamera::onButtonReleased, this );
	}
}

//-----------------------------------//

void FirstPersonCamera::onKeyPressed( const KeyEvent& keyEvent )
{
	switch( keyEvent.keyCode )
	{	
		case Keys::LControl:
		{
			render::Window* window = renderDevice->getWindow();
			window->setCursorState( !window->getCursorState() );
			centerCursor();
			break;
		}
		case Keys::N:
		{
			setSensivity( sensivity - 0.5f );
			break;
		}
		case Keys::M:
		{
			setSensivity( sensivity + 0.5f );
			break;
		}
	}
}

//-----------------------------------//

void FirstPersonCamera::onMouseMove( const MouseMoveEvent& moveEvent )
{
	render::Window* window = renderDevice->getWindow();

	if( !window->getCursorState() )
	{
		Vector3 currentPosition( moveEvent.x, moveEvent.y, 0 );

		Vector3 delta = currentPosition - lastPosition;
		lastPosition = currentPosition;

		rotate( delta.y * cameraSensivity, delta.x * cameraSensivity, 0 );
	}
}

//-----------------------------------//

void FirstPersonCamera::onButtonPressed( const MouseButtonEvent& buttonEvent )
{

}

//-----------------------------------//

void FirstPersonCamera::onButtonReleased( const MouseButtonEvent& buttonEvent )
{

}

//-----------------------------------//

void FirstPersonCamera::centerCursor()
{
	render::Window* window = renderDevice->getWindow();

	if( !window->getCursorState() )
	{
		int nw = window->getSettings().getWidth() / 2;
		int nh = window->getSettings().getHeight() / 2;
		
		window->setCursorPosition( nw, nh );

		lastPosition.x = static_cast<float>( nw );
		lastPosition.y = static_cast<float>( nh );
	}
}

//-----------------------------------//

} } // end namespaces