#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include "Window.h"

namespace vapor {
	namespace render {

class SDLWindow : public Window
{
public:

	SDLWindow(const string& title, shared_ptr<WindowSettings> windowSettings);
	virtual ~SDLWindow();

	void update ();

	bool pump();

	void setTitle(const string& title) const;

	void setCursor(bool state) const;

private:

	WindowSettings   *settings;			// window settings
	SDL_VideoInfo	*vidinfo;			// video information
	SDL_Surface		*display;			// the actual display surface

	// Initializes the Display system
	bool init();

	// Opens a new window
	bool open ();
};

} } // end namespaces