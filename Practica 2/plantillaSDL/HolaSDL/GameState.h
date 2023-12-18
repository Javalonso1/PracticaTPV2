#pragma once
#include "checkML.h"
#include "gameList.h"
#include "GameObject.h"
#include "SDL_image.h"
#include "EventHandler.h"
#include <list>

class Game;

class GameState
{
protected:
	Game* myGame;
	GameList<GameObject, true> objects;
	std::list<GameList<GameObject, true>::anchor> deletions;
	std::list<EventHandler*> listeners;
public:
	GameState(Game*);
	virtual ~GameState();
	virtual void Update() = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents(const SDL_Event&);
	virtual void Save() = 0;
	void addEventListener(EventHandler*);
	void hasDied(GameList<GameObject, true>::anchor Iterador);
	void addObject(GameObject*);
	SDL_Renderer* getRenderer();
};

