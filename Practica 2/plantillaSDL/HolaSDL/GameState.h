#pragma once
#include "checkML.h"
#include "gameList.h"
#include "GameObject.h"
#include "SDL_image.h"
#include <list>

class Game;

class GameState
{
protected:
	Game* myGame;
	GameList<GameObject, true> pizza;
	std::list<GameList<GameObject, true>::anchor> queso;
	std::list<GameObject*> listeners;
public:
	GameState(Game*);
	virtual ~GameState() = default;
	virtual void Update() = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents() = 0;
	void addEventListener(GameObject*);
	void hasDied(GameList<GameObject, true>::anchor Iterador);
	void addObject();
	SDL_Renderer* getRenderer();
};

