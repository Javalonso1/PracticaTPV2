#include "GameStateMachine.h"
#include <stack>
#include "GameState.h"


GameStateMachine::GameStateMachine() {};
GameStateMachine::~GameStateMachine() {};

void GameStateMachine::update() {
	iono.top()->Update();
}

void GameStateMachine::render() {

}

void GameStateMachine::handleEvent() {

}

void GameStateMachine::pushState() {

}
void GameStateMachine::replaceState() {

}
void GameStateMachine::popState() {

}
