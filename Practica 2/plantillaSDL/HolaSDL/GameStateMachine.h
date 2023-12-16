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
	void update(); 
	void render() const; 
	void handleEvent(const SDL_Event&);
	void pushState(GameState*);
	void replaceState(GameState*);
	void popState();
};

