#pragma once
#include "checkML.h"
#include <stack>
#include "GameState.h"

class GameStateMachine
{
private:
	std::stack<GameState*> iono;
public:
	GameStateMachine();
	~GameStateMachine();
	void pushState();
	void replaceState();
	void popState();
	void update(); 
	void render(); 
	void handleEvent();
};

