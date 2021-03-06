/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#include "Input/Device.h"
#include "Input/KeyboardEvents.h"

NAMESPACE_ENGINE_BEGIN

//-----------------------------------//

/**
 * Keyboard device.
 */

class API_ENGINE Keyboard : public InputDevice
{
public:	

	Keyboard();

	// Checks if the given key is pressed.
	bool isKeyPressed( Keys::Enum keyCode ) const;

	// Resets the keys state.
	void resetKeys();

	// Returns the current state of the keys.
	GETTER(KeyState, const std::vector<bool>&, keyState)

	// Event is sent when a key is pressed.
	Event1<const KeyEvent&> onKeyPress;

	// Event is sent when a key is released.
	Event1<const KeyEvent&> onKeyRelease;

	// Event is sent when text is input.
	Event1<const KeyEvent&> onKeyText;

private:
	
	// Processes an event (only if it's a keyboard event).
	virtual void processEvent( const InputEvent& event );

	// Return this device as a keyboard.
	GETTER(Type, const InputDeviceType::Enum, InputDeviceType::Keyboard)

	// Handles a key press event.
	void keyPressed( const KeyEvent& keyEvent );
	
	// Handles a key release event.
	void keyReleased( const KeyEvent& keyEvent );
	
	// Current key state.
	std::vector<bool> keyState;
	
	// Last key pressed.
	Keys::Enum lastKey;
};

//-----------------------------------//

NAMESPACE_ENGINE_END
