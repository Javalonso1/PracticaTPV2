#include "GameStateMachine.h"
#include <stack>
#include "GameState.h"


GameStateMachine::GameStateMachine() {

};
GameStateMachine::~GameStateMachine() {
	while (iono.size() != 0) {
		delete iono.top();
		iono.pop();
	}
};

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
	delete iono.top();
	iono.pop();
	iono.push(newState);
}

void GameStateMachine::popState() {
	delete iono.top();
	iono.pop();
}
void GameStateMachine::Save() {
	iono.top()->Save();
}
