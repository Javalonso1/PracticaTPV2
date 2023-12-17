#include "GameStateMachine.h"
#include <stack>
#include "GameState.h"


GameStateMachine::GameStateMachine() {

};
GameStateMachine::~GameStateMachine() {};

void GameStateMachine::update() {
	iono.top()->Update();
}

void GameStateMachine::render() const {
	iono.top()->Render();
}

void GameStateMachine::handleEvent(const SDL_Event& ev) {
	iono.top()->HandleEvents(ev);
}

void GameStateMachine::pushState(GameState* newState) {
	iono.push(newState);
}

void GameStateMachine::replaceState(GameState* newState) {
	iono.pop();
	iono.push(newState);
}

void GameStateMachine::popState() {
	iono.pop();
}
