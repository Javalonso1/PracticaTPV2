#pragma once
#include <SDL.h>

class EventHandler
{
private:
public:
	virtual void handleEvent(const SDL_Event&) = 0;
};

