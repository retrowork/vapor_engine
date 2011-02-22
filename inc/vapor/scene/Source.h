/************************************************************************
*
* vapor3D Engine � (2008-2010)
*
*	<http://www.vapor3d.org>
*
************************************************************************/

#pragma once

#ifdef VAPOR_AUDIO_OPENAL

#include "scene/Component.h"
#include "audio/Source.h"

FWD_DECL_INTRUSIVE(Sound)

namespace vapor {

//-----------------------------------//

struct SourceState
{
	DECLARE_ENUM()

	enum Enum
	{
		Play,
		Pause,
		Stop
	};
};

//-----------------------------------//

struct SourceMode
{
	DECLARE_ENUM()

	enum Enum
	{
		Static,
		Streaming
	};
};

//-----------------------------------//

class AudioSource;

/**
 * Uses the position and orientation defined in the node 
 * as the sound source location.
 */

class VAPOR_API Source : public Component 
{
	DECLARE_UNCOPYABLE(Source)
	DECLARE_CLASS_()

public:

	Source();
	virtual ~Source();

	// Sets the state of the source.
	void setState( SourceState::Enum state );

	// Sets the mode of the source.
	void setMode( SourceMode::Enum mode );

	// Sets the volume of the source. Volume is in the range [0.0-1.0].
	void setVolume( float volume );

	// Sets the pitch of the source. Pitch is in the range [0.0-1.0].
	void setPitch( float pitch );

	// Sets the minimum rolloff distance of the source.
	void setMinDistance( float distance );

	// Sets the maximum rolloff distance of the source.
	void setMaxDistance( float distance );

	// Sets the rolloff factor of the source. Rolloff is in the range [0.0-1.0].
	void setRolloff( float rolloff );

	// Sets the rolloff mode of the source.
	void setRolloffMode( RolloffMode::Enum mode );

	// Sets the loop of the source.
	void setLoop( bool state );

	// Sets the sound of the source.
	void setSound( const SoundPtr& sound );

	// Updates the component.
	virtual void update( double delta );

protected:

	// State of the source.
	SourceState::Enum state;

	// State of the source.
	SourceMode::Enum mode;

	// Loops the source.
	bool loop;

	// Volume of the source.
	float volume;

	// Pitch of the source.
	float pitch;

	// Minimum rolloff distance.
	float minDistance;

	// Maximum rolloff distance.
	float maxDistance;

	// Rolloff mode of the source.
	RolloffMode::Enum rolloffMode;

	// Rolloff of the source.
	float rolloff;

	// Sound resource.
	SoundPtr sound;

	// Audio source.
	AudioSource* audioSource;
};

TYPEDEF_SHARED_POINTER_FROM_TYPE( Source );

//-----------------------------------//

} // end namespace

#endif