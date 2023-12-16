#pragma once
#include "checkML.h"
#include "GameState.h"
#include "PlayState.h"

class PauseState : public GameState
{
private:
	PlayState* previous;
public:
	PauseState();
	~PauseState();
};

