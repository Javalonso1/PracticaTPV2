#pragma once
#include <SDL.h>

class EventHandler
{
public:
private:
	virtual void handleEvent(const SDL_Event&) = 0;
};

