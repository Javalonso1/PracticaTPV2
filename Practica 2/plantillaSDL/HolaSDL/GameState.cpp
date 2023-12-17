#include "GameState.h"
#include "Game.h"
#include "gameList.h"
#include "GameObject.h"
#include "SDL_image.h"
#include "EventHandler.h"
#include <list>


GameState::GameState(Game* a): myGame(a) {}

SDL_Renderer* GameState::getRenderer() {
	return myGame->getRenderer();
}

void GameState::addEventListener(EventHandler* listen) {
	listeners.push_back(listen);
}

void GameState::hasDied(GameList<GameObject, true>::anchor Iterador) {
	queso.push_back(Iterador);
}

void GameState::HandleEvents(const SDL_Event& ev) {
	for (auto i = listeners.begin(); i != listeners.end(); ++i) {
		(*i)->handleEvent(ev);
	}
}
/*
void GameState::addObject(GameObject* g) {
	pizza.push_back(g);
}*/