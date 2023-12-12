#include "GameState.h"
#include "Game.h"
GameState::GameState(Game* a): myGame(a) {}
SDL_Renderer* GameState::getRenderer() {
	return myGame->getRenderer();
}