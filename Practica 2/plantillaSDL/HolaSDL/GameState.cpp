#include "GameState.h"
#include "Game.h"
#include "gameList.h"
#include "GameObject.h"
#include "SDL_image.h"
#include <list>


GameState::GameState(Game* a): myGame(a) {}

SDL_Renderer* GameState::getRenderer() {
	return myGame->getRenderer();
}

void GameState::addEventListener(GameObject* listen) {
	listeners.push_back(listen);
}

void GameState::hasDied(GameList<GameObject, true>::anchor Iterador) {
	queso.push_back(Iterador);
}